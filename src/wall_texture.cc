#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "patches.h"
#include "palettes.h"
#include "wall_texture.h"
#include "common.h"
#include "frame_buf.h"

//#define DEBUG_PRINTING
#include "debug.h"

wall_texture::wall_texture()
{
  name[0] = NULL;
  patches = NULL;
  pixels = NULL;
}

wall_texture::~wall_texture()
{
  if(patches) { delete[] patches; }
  if(pixels) { delete[] pixels; }
}

bool wall_texture::read_from_maptexture_data(uint8_t const *data, patch_names_lump const *pnames)
{
  char const *patch_name;

  memcpy(name, data, 8);             data += 8;
  name[8] = NULL;

  masked         = *((uint32_t*)data); data += 4;
  width          = *((uint16_t*)data); data += 2;
  height         = *((uint16_t*)data); data += 2;
                                       data += 4; // ignored
  num_patches    = *((uint16_t*)data); data += 2;

  patches = new wall_patch[num_patches];
  for(int i=0; i<num_patches; i++)
  {
    patches[i].originx   = *((uint16_t*)data); data += 2;
    patches[i].originy   = *((uint16_t*)data); data += 2;
    patches[i].patch_num = *((uint16_t*)data); data += 2;
    patches[i].stepdir   = *((uint16_t*)data); data += 2;
    patches[i].colormap  = *((uint16_t*)data); data += 2;

    patch_name = pnames->get_patch_name_by_num(patches[i].patch_num);
    patches[i]._patch = patches_get_by_name(patch_name);
    if(!patches[i]._patch)
    {
      printf("ERROR(2): could not find patch named \"%s\"\n", patch_name);
      exit(0);
    }
  }

  if(!is_valid())
  {
    return false;
  }

  pre_render();

  return true;
}

bool wall_texture::is_valid(void)
{
  if(strlen(name)<1)
  {
    printf("ERROR: wall texture has no name\n");
    return false;
  }

  if(width<0 || width>2000 || height<0 || height>2000) // arbitrary guesses at sane values
  {
    printf("ERROR: wall texture crazy dimensions: %dx%d\n", width, height);
    return false;
  }

  return true;
}

void wall_texture::pre_render(void)
{
  pixels = new color_rgb[width*height];

  // First initialize all pixels to transparent. Some just won't get written, and they should be see-thru
  color_rgb black_see_thru(0,0,0); // FIXME: make this rgab
  for(int x=0; x<width; x++)
  {
    for(int y=0; y<height; y++)
    {
      pixels[(y*width)+x].set_to(&black_see_thru);
    }
  }

  debug_printf("Pre-rendering \"%s\". size: %dx%d\n", name, width, height);
  for(int p=0; p<num_patches; p++)
  {
    wall_patch *cur_patch = &patches[p];
    if(!cur_patch->_patch) // this link can fail, for some reason....
    {
      printf("ERROR: could not find patch!\n");
      exit(0);
    }

    debug_printf("  patch %d. origin:(%d,%d) step:%d, colormap:%d, size: %dx%d\n", 
                 p, cur_patch->originx, cur_patch->originy, cur_patch->stepdir, cur_patch->colormap,
                 cur_patch->_patch->get_width(), cur_patch->_patch->get_height());
    palette const *cur_pal = palettes_get(cur_patch->colormap);
    int16_t y = cur_patch->originy;
    for(int16_t v=0; v<cur_patch->_patch->get_height(); v++, y++)
    {
      int16_t x = cur_patch->originx;
      for(int16_t u=0; u<cur_patch->_patch->get_width(); u++, x++)
      {
        if((x < 0) || (x >= width) || (y < 0) || (y >= height))
        {
          /* real doom just clips these and silently ignores */
        }
        else
        {
          uint8_t color_idx = cur_patch->_patch->get_pixel(u, v);    // {u,v} over patch {width,height}
          pixels[(y*width)+x].set_to(cur_pal->get_color(color_idx)); // {x,y} over wall {width,height}
        }
      }
    }
  }
}

void wall_texture::render(float ldx_l, float ldx_r, int ld_h, 
                          int x_l, int x_r, 
                          float yt_l, float yb_l, 
                          float yt_r, float yb_r,
                          float dist_l, float dist_r,
                          int16_t x_offset, int16_t y_offset,
                          uint16_t light_level,
                          vis_planes *vp, 
                          vis_plane *floor, vis_plane *ceiling, 
                          bool clip_ceil, bool clip_floor) const
{
  color_rgba c;
  int16_t h=games_get_screen_height();

  debug_printf("        texture::render(%dx%d)\n", width, height);

  while(x_offset<0) { x_offset += width;  }
  while(y_offset<0) { y_offset += height; }

  if(x_l == x_r)
  {
    debug_printf("          aborting because x_l == x_r\n");
    return;
  }
  for(int x=x_l; x<=x_r; x++)
  {
    int ldx = ldx_l + (ldx_r-ldx_l)*(x-x_l)/(x_r-x_l);
    int tx = (x_offset+ldx) % width;

    float yt = yt_l + (yt_r-yt_l)*(x-x_l)/(x_r-x_l);
    float yb = yb_l + (yb_r-yb_l)*(x-x_l)/(x_r-x_l);
    float dist = dist_l + (dist_r-dist_l)*(x-x_l)/(x_r-x_l);
    float pct_darkened = MIN(dist,1200.0)/1800.0 * // Darken for distance (FIXME: How does Doom do this?)
                         (light_level/255.0);      // Darken for sector light level
    int clip_t = MAX(0,   vp->get_ceiling_clip(x));
    int clip_b = MIN(h-1, vp->get_floor_clip(  x));
    int clipped_yt = MAX(clip_t, MIN(clip_b, yt));
    int clipped_yb = MAX(clip_t, MIN(clip_b, yb));
    debug_printf("          x:%d, y:[%.1f,%.1f] cy:[%d,%d]\n", x, yt,yb, clipped_yt,clipped_yb);

    if(ceiling)
    {
      // top of ceiling = one pixel lower than the [bottom of the lowest ceiling]
      // bot of ceiling = one pixel above the wall (or [ceil], if lower) (or [floor], if higher)
      int16_t ceil_yt = vp->get_ceiling_clip(x)+1;
      int16_t ceil_yb = MIN(vp->get_floor_clip(x)-1, yt-1);
      if(ceil_yt  <= ceil_yb ) { ceiling->update_clip(x, ceil_yb,  ceil_yt ); ceiling->set_dist(x, dist); }
    }
    if(floor)
    {
      // top of floor be: one pixel below the wall (or [floor], if higher) (or [ceil], if lower)
      // bot of floor be: one pixel higher than the [top of the tallest floor]
      int16_t floor_yt = MAX(vp->get_ceiling_clip(x)+1, yb-1);
      int16_t floor_yb = vp->get_floor_clip(x)-1;
      debug_printf("            floor clipping: %d <= %d\n", floor_yt, floor_yb);
      if(floor_yt <= floor_yb) { floor  ->update_clip(x, floor_yb, floor_yt); floor  ->set_dist(x, dist); }
    }
    if(clip_ceil) { vp->update_ceiling_clip(x, yt); }
    else          { vp->update_floor_clip(  x, yt); }
    if(clip_floor){ vp->update_floor_clip(  x, yb); }
    else          { vp->update_ceiling_clip(x, yb); }

    for(int y=MAX(0,clipped_yt); y<=MIN(h-1,clipped_yb); y++)
    {
      int ldy = ld_h*(y-yt)/(yb-yt);
      int ty = (y_offset+ldy) % height;
  
      int pix_offset = (ty * width) + tx;
      c.set_to(&pixels[pix_offset]);
      c.darken_by(pct_darkened);
      frame_buf_draw_pixel(x, y, &c);
    }
  }
}
