#ifndef __VIS_PLANES_H
#define __VIS_PLANES_H

#include <stdint.h>
#include "vis_plane.h"
#include "games.h"
#include "projector.h"
#include "player.h"

#define MAX_VIS_PLANES (128)

class vis_planes
{
public:
  vis_planes();
  ~vis_planes();

  void draw_planes(projector const *_projector, player const *_player);

  vis_plane *find_or_create(int16_t height, flat const *tex, uint16_t light_level);
  vis_plane *create(int16_t height, flat const *tex, uint16_t light_level);
  vis_plane *find(int16_t height, flat const *tex, uint16_t light_level);

  vis_plane *adjust_or_create(vis_plane *vp, int16_t x_l, int16_t x_r);

  void update_ceiling_clip(int16_t x, int16_t y);
  void update_floor_clip(int16_t x, int16_t y);
  int16_t get_ceiling_clip(int16_t x);
  int16_t get_floor_clip(int16_t x);

private:
  uint16_t num_vis_planes;
  vis_plane _vis_planes[MAX_VIS_PLANES];

  int16_t ceiling_clip[MAX_SCREEN_WIDTH];
  int16_t floor_clip[MAX_SCREEN_WIDTH];
};

#endif
