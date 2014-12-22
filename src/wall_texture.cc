#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "patches.h"
#include "palettes.h"
#include "wall_texture.h"
#include "lighting.h"
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

// FIXME: merge ldx into tx_offset. Why pass both of them?
void wall_texture::render_col(float ldx, int dz, 
                              int x, float yt, float yb,  float clipped_yt, float clipped_yb,
                              float dist,
                              int16_t tx_offset, int16_t ty_offset,
                              float pct_darkened) const
{
  color_rgba c;
  int16_t h=games_get_screen_height();
  //#define DEBUG_TEXTURES
  #ifdef DEBUG_TEXTURES
  color_rgba cyan(100, 255, 255, 255);
  color_rgba peru(255, 155,  80, 255);
  color_rgba yell(255, 255, 100, 255);
  color_rgba purp(200,   0, 200, 255);
  #endif

  debug_printf("        texture::render(%dx%d)\n", width, height);

  while(ty_offset < 0) { ty_offset += height; }

  int   tx   = (width + tx_offset + (int)ldx) % width;
  for(int y=MAX(0,clipped_yt); y<=MIN(h-1,clipped_yb); y++)
  {
    int ldy = dz*(y-yt)/(yb-yt);
    int ty = (ty_offset+ldy) % height;

    int pix_offset = (ty * width) + tx;
    c.set_to(&pixels[pix_offset]);
    c.darken_by(pct_darkened);
    frame_buf_draw_pixel(x, y, &c);
    #ifdef DEBUG_TEXTURES
    if(( x==x_l) || (x==x_r) || 
       ( (x-1)==x_l) || ((x+1)==x_r) || 
       (y==MAX(0,clipped_yt)) || (y==MIN(h-1,clipped_yb)) ||
       ((y-1)==MAX(0,clipped_yt)) || ((y+1)==MIN(h-1,clipped_yb)))
    {
      switch(clip_type)
      {
        case WALL_1_SIDED_MID:   frame_buf_draw_pixel(x, y, &cyan); break;
        case WALL_2_SIDED_UPPER: frame_buf_draw_pixel(x, y, &peru); break;
        case WALL_2_SIDED_LOWER: frame_buf_draw_pixel(x, y, &yell); break;
        case WALL_2_SIDED_MID:   frame_buf_draw_pixel(x, y, &purp); break;
      }
    }
    #endif
  }
}
