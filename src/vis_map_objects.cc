#include <stdio.h>

#include "vis_map_objects.h"

vis_map_objects::vis_map_objects(void)
{
  num_vis_map_objects = 0;
}

vis_map_objects::~vis_map_objects(void)
{
}

void vis_map_objects::add_map_object(map_object const *_map_object)
{
  if((num_vis_map_objects+1) >= MAX_VIS_MAP_OBJECTS)
  {
    printf("WARNING: too many visible map_objects!\n");
    return;
  }
  map_objects[num_vis_map_objects++] = _map_object;
}

void vis_map_objects::draw_map_objects(camera const *_camera, clipped_segment_projections *clipped_seg_projs)
{
  calc_distances(_camera);
  sort_map_objects_back_to_front();

  for(int i=0; i<num_vis_map_objects; i++)
  {
    map_objects[i]->render_player_view(_camera, clipped_seg_projs);
  }
}

void vis_map_objects::calc_distances(camera const *_camera)
{
  for(int i=0; i<num_vis_map_objects; i++)
  {
    dists[i] = _camera->get_map_position()->distance_to_point(map_objects[i]->get_map_position());
  }
}

void vis_map_objects::sort_map_objects_back_to_front(void)
{
  // FIXME: you can do better than a simple bubble sort
  bool done = false;

  while(!done)
  {
    done = true;
    for(int i=0; i<(num_vis_map_objects-1); i++)
    {
      if(dists[i] < dists[i+1])
      {
        done = false;
        map_object const *map_object_tmp=map_objects[i]; map_objects[i]=map_objects[i+1]; map_objects[i+1]=map_object_tmp;
        float dist_tmp=dists[i]; dists[i]=dists[i+1]; dists[i+1]=dist_tmp;
      }
    }
  }
}

