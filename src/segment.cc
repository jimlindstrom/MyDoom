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

void segment::render_player_view(column_range_list *col_ranges, projector const *_projector, player const *_player, overhead_map *omap) const
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
    #if 1
    printf("  segment 0x%08x: (%d,%d)->(%d,%d)\n",
           (unsigned int)this, 
           start_vertex->get_x(), start_vertex->get_y(), 
           end_vertex->get_x(), end_vertex->get_y() );

    // This is the state in which we're simulating actually rendering the wall in the player's view
    int x1 = _projector->project_horiz_angle_to_x(angle1);
    int x2 = _projector->project_horiz_angle_to_x(angle2);
    if(x1 > x2) // FIXME: why?
    {
      int i = x1;
      x1 = x2;
      x2 = i;
      float g = angle1;
      angle1 = angle2;
      angle2 = g;
    }
    printf("    angles:[%.1f, %.1f], x:[%d, %d]\n", angle1, angle2, x1, x2);
    if(x1 < x2)  // need to figure out how to handle the == case
    {
      column_range **clipped_ranges;
      int num_clipped_crs;
      clipped_ranges = col_ranges->insert_with_clipping(x1, x2, &num_clipped_crs);
      printf("    %d clipped ranges\n", num_clipped_crs);
      color_rgba grn(0, 255, 0, 255);
      vertex v1, v2, d;
      d.set_x(end_vertex->get_x() - start_vertex->get_x());
      d.set_y(end_vertex->get_y() - start_vertex->get_y());
      for(int i=0; i<num_clipped_crs; i++)
      {
        float t1 = (clipped_ranges[i]->x_left - x1)/(float)(x2-x1);
        v1.set_x(start_vertex->get_x() + t1*d.get_x());
        v1.set_y(start_vertex->get_y() + t1*d.get_y());
        float t2 = (clipped_ranges[i]->x_right- x1)/(float)(x2-x1);
        v2.set_x(start_vertex->get_x() + t2*d.get_x());
        v2.set_y(start_vertex->get_y() + t2*d.get_y());
        printf("      clipped range %d: [%d,%d], t:[%.2f,%.2f]\n", i, clipped_ranges[i]->x_left, clipped_ranges[i]->x_right, t1, t2);
        printf("        drawing (%d,%d)->(%d,%d)\n", v1.get_x(), v1.get_y(), v2.get_x(), v2.get_y());
        omap->draw_line(&v1, &v2, &grn);
      }
      delete[] clipped_ranges;
    }
    #else
    color_rgba grn(0, 255, 0, 255);
    omap->draw_line(start_vertex, end_vertex, &grn);
    #endif
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
