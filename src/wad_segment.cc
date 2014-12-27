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

bool wad_segment::is_outdoor_area(void) const
{
  return back_sector &&
         back_sector ->get_ceiling_texture() &&
         front_sector->get_ceiling_texture() &&
         back_sector ->get_ceiling_texture()->is_fake_sky() &&
         front_sector->get_ceiling_texture()->is_fake_sky();
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

void wad_segment::render_player_view(camera const *_camera, clipped_segment_projections *clipped_seg_projs,
                                     vis_planes *vp, vis_plane *floor, vis_plane *ceiling) const
{
  segment_projection *seg_proj = project(_camera);
  if(!seg_proj) { return; }

  int num_csps;
  clipped_segment_projection **clipped_seg_proj = clipped_seg_projs->clip_segment(seg_proj, &num_csps);
  debug_printf("    %d clipped wall projections\n", num_csps);
  for(int i=0; i<num_csps; i++)
  {
    // update visplanes
    if(floor)   { floor   = vp->adjust_or_create(floor,   clipped_seg_proj[i]->x_l, clipped_seg_proj[i]->x_r); }
    if(ceiling) { ceiling = vp->adjust_or_create(ceiling, clipped_seg_proj[i]->x_l, clipped_seg_proj[i]->x_r); }

    // set clipping info
    clipped_seg_proj[i]->clip_floor   = seg_proj->clip_floor;
    clipped_seg_proj[i]->clip_ceiling = seg_proj->clip_ceiling;
    debug_printf("    %sfloor && %sclip_floor; %sceil && %sclip_ceil\n",
                 (floor   ? "" : "!"), (seg_proj->clip_floor   ? "" : "!"),
                 (ceiling ? "" : "!"), (seg_proj->clip_ceiling ? "" : "!"));

    // project vertically
    _linedef->set_z_values(direction, is_outdoor_area(), clipped_seg_proj[i]);
    clipped_seg_proj[i]->project_vertically(_camera);

    // set lighting & textures
    clipped_seg_proj[i]->view_ang     = seg_proj->view_ang;
    clipped_seg_proj[i]->light_level  = front_sector->get_light_level();
    clipped_seg_proj[i]->ldx_l        = seg_proj->get_texture_x_offset(clipped_seg_proj[i]->x_l);
    clipped_seg_proj[i]->ldx_r        = seg_proj->get_texture_x_offset(clipped_seg_proj[i]->x_r);
    _linedef->set_textures(direction, clipped_seg_proj[i]);

    // render
    clipped_seg_proj[i]->render(vp, floor, ceiling);
  }
  delete[] clipped_seg_proj;
  delete seg_proj;
}

/******************************************************************************
 * wad_segment: private interface
 ******************************************************************************/

segment_projection *wad_segment::project(camera const *_camera) const
{
  segment_projection *seg_proj = new segment_projection();

  // quickly reject empty lines, back faces, lines outside/behind FOV
  seg_proj->ang_l = NORMALIZE_ANGLE(_camera->get_map_position()->angle_to_point(vertex_l) - _camera->get_facing_angle());
  seg_proj->ang_r = NORMALIZE_ANGLE(_camera->get_map_position()->angle_to_point(vertex_r) - _camera->get_facing_angle());
  if(is_empty_line() ||
     seg_proj->is_backface() ||
     seg_proj->is_outside_fov(_projector->get_horiz_fov_radius()))
  {
    delete seg_proj;
    return NULL;
  }
  debug_printf("  segment %d", segment_num);
  debug_printf(" [%d:%s,%s,%s]", 
               (back_sector ? 2 : 1),
               _linedef->get_sidedef(direction)->get_upper_texture_name(),
               _linedef->get_sidedef(direction)->get_mid_texture_name(),
               _linedef->get_sidedef(direction)->get_lower_texture_name());
  debug_printf(" angles: [%.1f,%.1f]", RAD_TO_DEG(seg_proj->ang_l), RAD_TO_DEG(seg_proj->ang_r));

  // If not a solid line segment, don't consider the columns completely occluded. (continue drawing further-back segments)
  seg_proj->is_opaque = !( is_window() || is_other_single_sided_line() );

  // If the back sector has the same floor or ceiling, dont' clip the cooresponding plane
  seg_proj->clip_floor   = is_closed_door() || !is_same_floor_plane_on_both_sides();
  seg_proj->clip_ceiling = is_closed_door() || !is_same_ceiling_plane_on_both_sides();

  // step 1: translate segment's verticies into player-centric map coordinates
  segment *transformed_seg = transform_origin(_camera->get_map_position(), _camera->get_facing_angle());

  // step 2: clip it 
  transformed_seg->clip_to_vectors(_projector->get_left_clipping_vector(),
                                   _projector->get_right_clipping_vector(),
                                   &seg_proj->v_l_c, &seg_proj->v_r_c, 
                                   &seg_proj->u_l_c, &seg_proj->u_r_c);
  delete transformed_seg; // we don't need the transformed seg now that we've clipped it

  // step 3: Project it
  vertex origin(0,0);
  seg_proj->view_ang = seg_proj->v_l_c.angle_to_point(&seg_proj->v_r_c);
  seg_proj->ang_l_c  = origin.angle_to_point(&seg_proj->v_l_c); 
  seg_proj->ang_r_c  = origin.angle_to_point(&seg_proj->v_r_c); 
  seg_proj->x_l_c    = _projector->project_horiz_angle_to_x(seg_proj->ang_l_c);
  seg_proj->x_r_c    = _projector->project_horiz_angle_to_x(seg_proj->ang_r_c);
  seg_proj->dist_l_c = origin.distance_to_point(&seg_proj->v_l_c);
  seg_proj->dist_r_c = origin.distance_to_point(&seg_proj->v_r_c);
  debug_printf(" dist_c: [%.1f,%.1f]\n", seg_proj->dist_l_c, seg_proj->dist_r_c);

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

