#include <stdlib.h>
#include <stdio.h>

#include "vis_planes.h"
#include "common.h"

#define SCREEN_HEIGHT 480 // FIXME...

vis_planes::vis_planes()
{
  num_vis_planes = 0;
  for(int16_t x=0; x<MAX_SCREEN_WIDTH; x++)
  {
    ceiling_clip[x] = -1;
    floor_clip[x]   = SCREEN_HEIGHT;
  }
}

vis_planes::~vis_planes()
{
}

void vis_planes::draw_planes(void)
{
  printf("  drawing visplanes\n");
  for(int i=0; i<num_vis_planes; i++)
  {
    _vis_planes[i].draw();
  }
}

vis_plane *vis_planes::find_or_create(int16_t height, flat const *tex, uint16_t light_level)
{
  vis_plane *vp;

  if((vp = find(height, tex, light_level)))
  {
    return vp;
  }
  return create(height, tex, light_level);
}

vis_plane *vis_planes::create(int16_t height, flat const *tex, uint16_t light_level)
{
  vis_plane *vp;
  
  num_vis_planes++;
  if(num_vis_planes >= MAX_VIS_PLANES)
  {
    printf("ERROR: out of visplanes!\n");
    exit(0);
  }
  vp = &_vis_planes[num_vis_planes-1];
  vp->init(height, tex, light_level);
  printf("    created vis_plane 0x%08x\n", (uint32_t)vp);
  return vp;
}

vis_plane *vis_planes::find(int16_t height, flat const *tex, uint16_t light_level)
{
  for(uint16_t i=0; i<num_vis_planes; i++)
  {
    if(_vis_planes[i].matches(height, tex, light_level))
    {
      return &_vis_planes[i];
    }
  }
  return NULL;
}

vis_plane *vis_planes::adjust_or_create(vis_plane *vp, int16_t x_l, int16_t x_r)
{
  if(vp->can_be_extended_to(x_l, x_r))
  {
    vp->extend_to(x_l, x_r);
    return vp;
  }
  else
  {
    printf("    cannot extend 0x%08x to [%d,%d]\n", (uint32_t)vp, x_l, x_r);
    vis_plane *new_vp = create(vp->get_height(), vp->get_tex(), vp->get_light_level());
    new_vp->extend_to(x_l, x_r);
    return new_vp;
  }
}

void vis_planes::update_ceiling_clip(int16_t x, int16_t y)
{
  ceiling_clip[x] = MAX(y, ceiling_clip[x]);
}

void vis_planes::update_floor_clip(int16_t x, int16_t y)
{
  floor_clip[x] = MIN(y, floor_clip[x]);
}

int16_t vis_planes::get_ceiling_clip(int16_t x)
{
  return ceiling_clip[x];
}

int16_t vis_planes::get_floor_clip(int16_t x)
{
  return floor_clip[x];
}

