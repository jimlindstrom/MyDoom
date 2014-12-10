#include <string.h>
#include <stdio.h>
#include <math.h>

#include "segment.h"

segment::segment()
{
}

segment::~segment()
{
}

bool segment::read_from_lump_data(uint8_t const *lump_data)
{
  start_vertex_num = *((uint16_t*)lump_data); lump_data += 2;
  end_vertex_num   = *((uint16_t*)lump_data); lump_data += 2;
  angle            = *(( int16_t*)lump_data); lump_data += 2;
  linedef_num      = *((uint16_t*)lump_data); lump_data += 2;
  direction        = *((uint16_t*)lump_data); lump_data += 2;
  offset           = *((uint16_t*)lump_data); lump_data += 2;

  angle >>= 8; // FIXME: make a float, or treat as a proper fixed_t

  return true;
}

void segment::set_linedef(linedef const *ld)
{
  _linedef = ld;
}

void segment::render_player_view(player const *_player, overhead_map *omap) const
{
  if(is_viewer_behind(_player))
  {
    // This is the state in which we're just rendering the map view
    color_rgba red(255, 0, 0, 255);
    omap->draw_line(start_vertex, end_vertex, &red);
  }
  else
  {
    // This is the state in which we're simulating actually rendering the wall in the player's view
    color_rgba grn(0, 255, 0, 255);
    omap->draw_line(start_vertex, end_vertex, &grn);
  }
}

bool segment::is_viewer_behind(player const *_player) const
{
  float angle1 = _player->get_map_position()->angle_to_point(start_vertex) - _player->get_facing_angle();
  float angle2 = _player->get_map_position()->angle_to_point(  end_vertex) - _player->get_facing_angle();

  if     (angle1 >  180) { angle1 -= 360; }
  else if(angle1 < -180) { angle1 += 360; }
  if     (angle2 >  180) { angle2 -= 360; }
  else if(angle2 < -180) { angle2 += 360; }

  float span = angle1 - angle2;
  return ( 
           (span < 0) ||
           ( 
             (fabs(angle1) > _player->get_horiz_fov_radius()) && 
             (fabs(angle2) > _player->get_horiz_fov_radius())
           ) 
         );
}
