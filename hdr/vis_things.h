#ifndef __VIS_THINGS_H
#define __VIS_THINGS_H

#include "thing.h"

#define MAX_VIS_THINGS 64

class vis_things
{
public:
  vis_things(void);
  ~vis_things(void);

  void add_thing(thing const *_thing);
  void draw_things(column_range_list *col_ranges, projector const *_projector, player const *_player);

private:
  uint16_t num_vis_things;
  thing const *things[MAX_VIS_THINGS];
  float dists[MAX_VIS_THINGS];

  void calc_distances(player const *_player);
  void sort_things_back_to_front(void);
};

#endif
