#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "patches.h"
#include "palettes.h"
#include "wall_texture.h"
#include "common.h"
#include "frame_buf.h"

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

  //printf("%dx%d [before]\n", width, height);

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

    if(patches[i]._patch) // this link can fail, for some reason....
    {
      uint16_t needed_width  = patches[i].originx + patches[i]._patch->get_width();
      uint16_t needed_height = patches[i].originy + patches[i]._patch->get_height();
      if(needed_width  > width ) { width  = needed_width;  } 
      if(needed_height > height) { height = needed_height; } 
      //printf("%dx%d [needed]\n", needed_width, needed_height);
    }
  }

  //printf("%dx%d [after]\n", width, height);

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

  printf("Pre-rendering \"%s\". size: %dx%d\n", name, width, height);
  for(int p=0; p<num_patches; p++)
  {
    wall_patch *cur_patch = &patches[p];
    if(cur_patch->_patch) // this link can fail, for some reason....
    {
      printf("  patch %d. origin:(%d,%d) step:%d, colormap:%d, size: %dx%d\n", 
             p, cur_patch->originx, cur_patch->originy, cur_patch->stepdir, cur_patch->colormap,
             cur_patch->_patch->get_width(), cur_patch->_patch->get_height());
      palette const *cur_pal = palettes_get(cur_patch->colormap);
      int16_t y = cur_patch->originy;
      for(int16_t v=0; v<cur_patch->_patch->get_height(); v++, y++)
      {
        int16_t x = cur_patch->originx;
        for(int16_t u=0; u<cur_patch->_patch->get_width(); u++, x++)
        {
          if((x <= 0) || (x >= width) || (y <= 0) || (y >= height))
          {
            //printf("WARNING: pixel (%d,%d) is out of range [0..%d, 0..%d]\n", x,y, width,height);
          }
          else
          {
            uint8_t color_idx = cur_patch->_patch->get_pixel(u, v);
            pixels[(y*width)+x].set_to(cur_pal->get_color(color_idx));
          }
        }
      }
    }
  }
}

void wall_texture::render(float ldx_l, float ldx_r, int ld_h, int x_l, int x_r, float yt_l, float yb_l, float yt_r, float yb_r) const
{
  color_rgba c;

  printf("        texture::render(%dx%d)\n", width, height);
  for(int x=x_l; x<=x_r; x++)
  {
    int ldx = (ldx_r-ldx_l)*(x-x_l)/(x_r-x_l);
    int tx = ldx % width;

    float yb = yb_l + (yb_r-yb_l)*(x-x_l)/(x_r-x_l);
    float yt = yt_l + (yt_r-yt_l)*(x-x_l)/(x_r-x_l);

    for(int y=yb; y<=yt; y++)
    {
      if( (y>=0) && (y<640) ) // FIXME: magic #
      {
        int ldy = ld_h*(y-yb)/(yt-yb);
        int ty = ldy % height;
  
        int pix_offset = (ty * width) +tx;
        c.set_to(&pixels[pix_offset]);
        frame_buf_draw_point(x, 640-y, &c);
      }
    }
  }
}
