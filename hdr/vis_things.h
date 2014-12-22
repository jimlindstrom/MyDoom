#ifndef __VIS_THINGS_H
#define __VIS_THINGS_H

#include "thing.h"

#define MAX_VIS_THINGS 128

class vis_things
{
public:
  vis_things(void);
  ~vis_things(void);

  void add_thing(thing const *_thing);
  void draw_things(camera const *_camera, column_range_list *col_ranges);

private:
  uint16_t num_vis_things;
  thing const *things[MAX_VIS_THINGS];
  float dists[MAX_VIS_THINGS];

  void calc_distances(camera const *_camera);
  void sort_things_back_to_front(void);
};

#endif
