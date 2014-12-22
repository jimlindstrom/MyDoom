#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

#include "wad_segment.h"
#include "vector.h"
#include "common.h"

//#define DEBUG_PRINTING
#include "debug.h"

static uint16_t next_segment_num = 0; // for debug printing

/******************************************************************************
 * wad_segment: public interface
 ******************************************************************************/

wad_segment::wad_segment()
{
  _linedef = NULL;
  front_sector = back_sector = NULL;
}

wad_segment::~wad_segment()
{
}

bool wad_segment::read_from_lump_data(uint8_t const *lump_data)
{
  segment_num  = next_segment_num++; // for debug printing

  vertex_l_num = *((uint16_t*)lump_data); lump_data += 2;
  vertex_r_num = *((uint16_t*)lump_data); lump_data += 2;
  angle =(float)(*(( int16_t*)lump_data))/256.0; lump_data += 2;
  linedef_num  = *((uint16_t*)lump_data); lump_data += 2;
  direction    = *((uint16_t*)lump_data); lump_data += 2;
  offset       = *((uint16_t*)lump_data); lump_data += 2;

  // convert angle from degrees to radians
  angle = DEG_TO_RAD(angle); // FIXME: I'm not sure I use this anywhere...

  return true;
}

void wad_segment::set_linedef(linedef const *ld)
{
  _linedef = ld;
}

bool wad_segment::is_singled_sided_line(void) const
{
  return (back_sector == NULL);
}

bool wad_segment::is_closed_door(void) const
{
  if(is_singled_sided_line()) { return false; }
  return (back_sector->get_ceiling_height() <= front_sector->get_floor_height()  ) ||
         (back_sector->get_floor_height()   >= front_sector->get_ceiling_height());
}

bool wad_segment::is_window(void) const
{
  if(is_singled_sided_line()) { return false; }
  if(is_closed_door())        { return false; }

  return (back_sector->get_ceiling_height() != front_sector->get_ceiling_height()) ||
         (back_sector->get_floor_height()   != front_sector->get_floor_height()  );
}

bool wad_segment::is_empty_line(void) const
{
  if(is_singled_sided_line()) { return false; }
  if(is_closed_door())        { return false; }
  if(is_window())             { return false; }
 
  return (back_sector->get_ceiling_texture() == front_sector->get_ceiling_texture()) &&
         (back_sector->get_floor_texture()   == front_sector->get_floor_texture()  ) &&
         (back_sector->get_light_level()     == front_sector->get_light_level()    ) &&
         (!_linedef->get_sidedef(direction)->has_mid_texture());
}

bool wad_segment::is_other_single_sided_line(void) const
{
  if(is_singled_sided_line()) { return false; }
  if(is_closed_door())        { return false; }
  if(is_window())             { return false; }
  if(is_empty_line())         { return false; }

  return true;
}

bool wad_segment::is_same_floor_plane_on_both_sides(void) const
{
  if(is_singled_sided_line()) { return false; }
  return (back_sector->get_floor_height()  == front_sector->get_floor_height()) &&
         (back_sector->get_floor_texture() == front_sector->get_floor_texture()) &&
         (back_sector->get_light_level()   == front_sector->get_light_level());
}

bool wad_segment::is_same_ceiling_plane_on_both_sides(void) const
{
  if(is_singled_sided_line()) { return false; }
  return (back_sector->get_ceiling_height()  == front_sector->get_ceiling_height()) &&
         (back_sector->get_ceiling_texture() == front_sector->get_ceiling_texture()) &&
         (back_sector->get_light_level()     == front_sector->get_light_level());
}

void wad_segment::render_player_view(column_range_list *col_ranges, projector const *_projector, player const *_player,
                                     vis_planes *vp, vis_plane *floor, vis_plane *ceiling) const
{
  segment_projection *seg_proj = project(_projector, _player);
  if(!seg_proj) { return; }

  int num_wall_projs;
  wall_projection **wall_projs = col_ranges->clip_segment(seg_proj, &num_wall_projs);
  for(int i=0; i<num_wall_projs; i++)
  {
    if(floor)   { floor   = vp->adjust_or_create(floor,   wall_projs[i]->x_l, wall_projs[i]->x_r); }
    if(ceiling) { ceiling = vp->adjust_or_create(ceiling, wall_projs[i]->x_l, wall_projs[i]->x_r); }

    wall_projs[i]->project_vertically(_projector, _player);

    wall_projs[i]->ldx_l        = seg_proj->get_texture_x_offset(wall_projs[i]->x_l);
    wall_projs[i]->ldx_r        = seg_proj->get_texture_x_offset(wall_projs[i]->x_r);
    wall_projs[i]->clip_floor   = seg_proj->clip_floor;
    wall_projs[i]->clip_ceiling = seg_proj->clip_ceiling;
    wall_projs[i]->light_level  = front_sector->get_light_level();
    wall_projs[i]->vp           = vp;
    wall_projs[i]->floor        = floor;
    wall_projs[i]->ceiling      = ceiling;

    _linedef->render(direction, wall_projs[i]);
  }
  delete[] wall_projs;
  delete seg_proj;
}

/******************************************************************************
 * wad_segment: private interface
 ******************************************************************************/

segment_projection *wad_segment::project(projector const *_projector, player const *_player) const
{
  segment_projection *seg_proj = new segment_projection();

  // quickly reject empty lines, back faces, lines outside/behind FOV
  seg_proj->ang_l = NORMALIZE_ANGLE(_player->get_map_position()->angle_to_point(vertex_l) - _player->get_facing_angle());
  seg_proj->ang_r = NORMALIZE_ANGLE(_player->get_map_position()->angle_to_point(vertex_r) - _player->get_facing_angle());
  if(is_empty_line() ||
     seg_proj->is_backface() ||
     seg_proj->is_outside_fov(_projector->get_horiz_fov_radius()))
  {
    delete seg_proj;
    return NULL;
  }
  debug_printf("  segment %d: (%.1f,%.1f)->(%.1f,%.1f)\n",
               segment_num,
               vertex_l->get_x(), vertex_l->get_y(),
               vertex_r->get_x(), vertex_r->get_y() ); 
  debug_printf("    angles: [%.1f,%.1f]\n", RAD_TO_DEG(seg_proj->angle_l), RAD_TO_DEG(seg_proj->angle_r));

  // If not a solid line segment, don't consider the columns completely occluded. (continue drawing further-back segments)
  if(is_window() || is_other_single_sided_line()) { seg_proj->store_clipping = false; }
  else                                            { seg_proj->store_clipping = true;  }

  // If the back sector has the same floor or ceiling, dont' clip the cooresponding plane
  seg_proj->clip_floor = seg_proj->clip_ceiling = true;
  if(!is_closed_door() && is_same_floor_plane_on_both_sides()  ) { seg_proj->clip_floor   = false; }
  if(!is_closed_door() && is_same_ceiling_plane_on_both_sides()) { seg_proj->clip_ceiling = false; }

  // step 1: translate segment's verticies into player-centric map coordinates
  segment *transformed_seg = transform_origin(_player->get_map_position(), _player->get_facing_angle());

  // Step 2: clip it 
  transformed_seg->clip_to_vectors(_projector->get_left_clipping_vector(),
                                   _projector->get_right_clipping_vector(),
                                   &seg_proj->v_l_c, &seg_proj->v_r_c, 
                                   &seg_proj->u_l_c, &seg_proj->u_r_c);
  delete transformed_seg; // we don't need the transformed seg now that we've clipped it

  // Step 3: Project it
  vertex origin(0,0);
  seg_proj->ang_l_c  = origin.angle_to_point(&seg_proj->v_l_c); 
  seg_proj->ang_r_c  = origin.angle_to_point(&seg_proj->v_r_c); 
  seg_proj->x_l_c    = _projector->project_horiz_angle_to_x(seg_proj->ang_l_c);
  seg_proj->x_r_c    = _projector->project_horiz_angle_to_x(seg_proj->ang_r_c);
  seg_proj->dist_l_c = origin.distance_to_point(&seg_proj->v_l_c);
  seg_proj->dist_r_c = origin.distance_to_point(&seg_proj->v_r_c);

  // guard against zero-width segments
  if(seg_proj->is_zero_width())
  {
    delete seg_proj;
    return NULL;
  }

  // store info we'll need in order to calculate texture offsets
  seg_proj->unclipped_length = get_length();
  seg_proj->unclipped_offset = _linedef->get_start_vertex()->distance_to_point(vertex_l);
  if(direction == 1)
  {
    seg_proj->unclipped_offset = seg_proj->unclipped_length - seg_proj->unclipped_offset;
  }

  return seg_proj;
}

