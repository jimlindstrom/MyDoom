#include "vis_things.h"

vis_things::vis_things(void)
{
  num_vis_things = 0;
}

vis_things::~vis_things(void)
{
}

void vis_things::add_thing(thing const *_thing)
{
  if((num_vis_things+1) >= MAX_VIS_THINGS)
  {
    printf("WARNING: too many visible things!\n");
    return;
  }
  things[num_vis_things++] = _thing;
}

void vis_things::draw_things(camera const *_camera, clipped_segment_projections *clipped_seg_projs)
{
  calc_distances(_camera);
  sort_things_back_to_front();

  for(int i=0; i<num_vis_things; i++)
  {
    things[i]->render_player_view(_camera, clipped_seg_projs);
  }
}

void vis_things::calc_distances(camera const *_camera)
{
  for(int i=0; i<num_vis_things; i++)
  {
    dists[i] = _camera->get_map_position()->distance_to_point(things[i]->get_map_position());
  }
}

void vis_things::sort_things_back_to_front(void)
{
  // FIXME: you can do better than a simple bubble sort
  bool done = false;

  while(!done)
  {
    done = true;
    for(int i=0; i<(num_vis_things-1); i++)
    {
      if(dists[i] < dists[i+1])
      {
        done = false;
        thing const *thing_tmp=things[i]; things[i]=things[i+1]; things[i+1]=thing_tmp;
        float dist_tmp=dists[i]; dists[i]=dists[i+1]; dists[i+1]=dist_tmp;
      }
    }
  }
}

