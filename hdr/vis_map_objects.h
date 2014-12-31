#ifndef __VIS_MAP_OBJECTS_H
#define __VIS_MAP_OBJECTS_H

#include "map_object.h"

#define MAX_VIS_MAP_OBJECTS 128

class vis_map_objects
{
public:
  vis_map_objects(void);
  ~vis_map_objects(void);

  void add_map_object(map_object const *_map_object);
  void draw_map_objects(camera const *_camera, clipped_segment_projections *clipped_seg_projs);

private:
  uint16_t num_vis_map_objects;
  map_object const *map_objects[MAX_VIS_MAP_OBJECTS];
  float dists[MAX_VIS_MAP_OBJECTS];

  void calc_distances(camera const *_camera);
  void sort_map_objects_back_to_front(void);
};

#endif
