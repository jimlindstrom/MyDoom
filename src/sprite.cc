#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "common.h"
#include "sprite.h"
#include "palettes.h"
#include "frame_buf.h"
#include "games.h"

#define RANGE_CHECKING

sprite::sprite()
 : picture_data()
{
  num_orientations = 0;
}

sprite::~sprite()
{
}

void sprite::set_name_prefix(char const *_name_prefix)
{
  strncpy(name_prefix, _name_prefix, 4); 
  name_prefix[4]=0;
}

void sprite::set_frame_idx(uint8_t orientation, uint8_t _frame_idx)
{
  #ifdef RANGE_CHECKING
  if(orientation>1) { printf("ERROR: sprite::set_frame_idx() orientation>1\n"); exit(0); }
  #endif
  frame_idx[orientation] = _frame_idx; 
  num_orientations = MAX(num_orientations, orientation+1);
}

void sprite::set_rotation_idx(uint8_t orientation, uint8_t _rotation_idx)
{
  #ifdef RANGE_CHECKING
  if(orientation>1) { printf("ERROR: sprite::set_frame_idx() orientation>1\n"); exit(0); }
  #endif
  rotation_idx[orientation] = _rotation_idx;
  num_orientations = MAX(num_orientations, orientation+1);
}

void sprite::draw(int16_t screen_x, int16_t screen_y, float scale) const
{
  palette const *pal = palettes_get(0); // FIXME
  color_rgba c;

  for(int x=0; x<(float)(scale*get_width()); x++)
  {
    for(int y=0; y<(float)(scale*get_height()); y++)
    {
      uint16_t sprite_x = x/scale;
      uint16_t sprite_y = y/scale;
      if(sprite_x < get_width() && sprite_y < get_height())
      {
        uint8_t color_idx = get_pixel(sprite_x, sprite_y);
        if(color_idx != TRANSPARENT_COLOR_IDX)
        {
          c.set_to(pal->get_color(color_idx));
          frame_buf_overlay_pixel(screen_x+x, screen_y+y, &c);
        }
      }
    }
  }
}
