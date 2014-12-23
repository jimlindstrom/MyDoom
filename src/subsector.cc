#include <stdio.h>
#include <string.h>

#include "subsector.h"

//#define DEBUG_PRINTING
#include "debug.h"

static uint16_t next_subsector_num = 0; // for debug printing purposes

subsector::subsector()
{
  segments = NULL;
}

subsector::~subsector()
{
  if(segments) { delete[] segments; }
}

bool subsector::read_from_lump_data(uint8_t const *lump_data)
{
  subsector_num     = next_subsector_num++; // for debug printing purposes
  num_segments      = *((uint16_t*)lump_data); lump_data += 2;
  first_segment_num = *((uint16_t*)lump_data); lump_data += 2;

  return true;
}

void subsector::allocate_segments(void)
{
  segments = new wad_segment const *[num_segments];
}

void subsector::set_nth_segment(int n, wad_segment const *_segment)
{
  segments[n] = _segment;
}

void subsector::render_player_view(camera const *_camera,
                                   clipped_segment_projections *clipped_seg_projs, 
                                   vis_planes *vp, 
                                   thing *things, int16_t num_things, vis_things *vt) const
{
  debug_printf(" subsector %d\n", subsector_num);

  vis_plane *floor = NULL, *ceiling = NULL;
  sector const *sec = get_sector();
  if(sec->get_floor_height() < _camera->get_view_height())
  {
    floor   = vp->find_or_create(sec->get_floor_height(),   sec->get_floor_texture(),   sec->get_light_level());
  }
  if( (sec->get_ceiling_height() > _camera->get_view_height()) ||
      sec->get_ceiling_texture()->is_fake_sky() )
  {
    ceiling = vp->find_or_create(sec->get_ceiling_height(), sec->get_ceiling_texture(), sec->get_light_level());
  }

  for(int i=0; i<num_segments; i++)
  {
    segments[i]->render_player_view(_camera, clipped_seg_projs, vp, floor, ceiling);
  }

  for(int i=0; i<num_things; i++)
  {
    if(things[i].get_subsector() == this)
    {
      vt->add_thing(&things[i]);
    }
  }
}
