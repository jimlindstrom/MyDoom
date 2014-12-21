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
  things[num_vis_things++] = _thing;
}

void vis_things::draw_things(column_range_list *col_ranges, projector const *_projector, player const *_player) 
{
  calc_distances(_player);
  sort_things_back_to_front();

  for(int i=0; i<num_vis_things; i++)
  {
    things[i]->render_player_view(col_ranges, _projector, _player);
  }
}

void vis_things::calc_distances(player const *_player)
{
  for(int i=0; i<num_vis_things; i++)
  {
    dists[i] = _player->get_map_position()->distance_to_point(things[i]->get_map_position());
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

