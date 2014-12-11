#include <string.h>
#include <stdio.h>
#include <math.h>
#include "column_range.h"

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

void segment::render_player_view(projector const *_projector, player const *_player, overhead_map *omap) const
{
  float angle1, angle2;

  calculate_angles_from_player(_player, &angle1, &angle2);
  if(is_viewer_behind(_projector, angle1, angle2))
  {
    // This is the state in which we're just rendering the map view
    color_rgba red(255, 0, 0, 255);
    omap->draw_line(start_vertex, end_vertex, &red);
  }
  else
  {
    // This is the state in which we're simulating actually rendering the wall in the player's view
    int x1 = _projector->project_horiz_angle_to_x(angle1);
    int x2 = _projector->project_horiz_angle_to_x(angle2);
    printf("segment 0x%08x: angles:[%.1f, %.1f], x:[%d, %d]\n", this, angle1, angle2, x1, x2);

    color_rgba grn(0, 255, 0, 255);
    omap->draw_line(start_vertex, end_vertex, &grn);
  }
}

void segment::calculate_angles_from_player(player const *_player, float *angle1, float *angle2) const
{
  *angle1 = _player->get_map_position()->angle_to_point(start_vertex) - _player->get_facing_angle();
  *angle2 = _player->get_map_position()->angle_to_point(  end_vertex) - _player->get_facing_angle();

  if     (*angle1 >  180) { *angle1 -= 360; }
  else if(*angle1 < -180) { *angle1 += 360; }
  if     (*angle2 >  180) { *angle2 -= 360; }
  else if(*angle2 < -180) { *angle2 += 360; }
}

bool segment::is_viewer_behind(projector const *_projector, float angle1, float angle2) const
{
  return ( 
           (angle1 < angle2) ||
           ( 
             (fabs(angle1) > _projector->get_horiz_fov_radius()) && 
             (fabs(angle2) > _projector->get_horiz_fov_radius())
           ) 
         );
}
