#include <string.h>
#include <stdio.h>

#include "episode_map.h"
#include "color.h"
#include "overhead_map.h"
#include "wall_textures.h"
#include "flats.h"
#include "actor.h"
#include "strobe_light.h"

//#define DEBUG_PRINTING
#include "debug.h"

episode_map::episode_map()
{
  name            = NULL;
  thing_instances = NULL;
  linedefs        = NULL;
  vertexes        = NULL;
  segments        = NULL;
  subsectors      = NULL;
  nodes           = NULL;
  sectors         = NULL;
  num_actors      = 0;
}

episode_map::~episode_map()
{
  if(name)            { delete[] name;            }
  if(thing_instances) { delete[] thing_instances; }
  if(linedefs)        { delete[] linedefs;        }
  if(vertexes)        { delete[] vertexes;        }
  if(segments)        { delete[] segments;        }
  if(subsectors)      { delete[] subsectors;      }
  if(nodes)           { delete[] nodes;           }
  if(sectors)         { delete[] sectors;         }
}

bool episode_map::read_from_lump(wad_file const *wad, wad_lump const *lump)
{
  wad_lump const *cur_lump;
  bool done = false;

  name = new char[strlen(lump->get_name())+1];
  strcpy(name, lump->get_name());

  cur_lump = wad->get_next_lump(lump);
  while(!done)
  {
    debug_printf("reading %s\n", cur_lump->get_name());
    if(strcmp(cur_lump->get_name(),"THINGS")==0)
    {
      if(!read_thing_instances(cur_lump)) { return false; }
    }
    else if(strcmp(cur_lump->get_name(),"LINEDEFS")==0)
    {
      if(!read_linedefs(cur_lump)) { return false; }
    }
    else if(strcmp(cur_lump->get_name(),"SIDEDEFS")==0)
    {
      if(!read_sidedefs(cur_lump)) { return false; }
    }
    else if(strcmp(cur_lump->get_name(),"VERTEXES")==0)
    {
      if(!read_vertexes(cur_lump)) { return false; }
    }
    else if(strcmp(cur_lump->get_name(),"SEGS")==0)
    {
      if(!read_segments(cur_lump)) { return false; }
    }
    else if(strcmp(cur_lump->get_name(),"SSECTORS")==0)
    {
      if(!read_subsectors(cur_lump)) { return false; }
    }
    else if(strcmp(cur_lump->get_name(),"NODES")==0)
    {
      if(!read_nodes(cur_lump)) { return false; }
    }
    else if(strcmp(cur_lump->get_name(),"SECTORS")==0)
    {
      if(!read_sectors(cur_lump)) { return false; }
    }
    else if(strcmp(cur_lump->get_name(),"REJECT")==0)
    {
      reject_tbl.read_from_lump(cur_lump, num_sectors);
    }
    else if(strcmp(cur_lump->get_name(),"BLOCKMAP")==0)
    {
      _block_map.read_from_lump(cur_lump, num_sectors);
    }
    else
    {
      done = true;
    }
    cur_lump = wad->get_next_lump(cur_lump);
  }

  link_nodes_to_children();
  link_sectors_to_flats();
  link_subsectors_to_segments();
  link_sidedefs_to_children();
  link_linedefs_to_children();
  link_segments_to_children();
  link_blocks_to_children();

  return true;
}

bool episode_map::read_thing_instances(wad_lump const *lump)
{
  uint8_t const *thing_instance_ptr;
  num_thing_instances = lump->get_num_bytes() / THING_INSTANCE_NUM_BYTES;
  thing_instances = new thing_instance[num_thing_instances];

  for(int i=0; i<num_thing_instances; i++)
  {
    thing_instance_ptr = lump->get_data() + (i*THING_INSTANCE_NUM_BYTES);
    thing_instances[i].read_from_lump_data(thing_instance_ptr);
  }

  return true;
}

bool episode_map::read_linedefs(wad_lump const *lump)
{
  uint8_t const *linedef_ptr;
  num_linedefs = lump->get_num_bytes() / LINEDEF_NUM_BYTES;
  linedefs = new linedef[num_linedefs];

  for(int i=0; i<num_linedefs; i++)
  {
    linedef_ptr = lump->get_data() + (i*LINEDEF_NUM_BYTES);
    linedefs[i].read_from_lump_data(linedef_ptr);
  }

  return true;
}

bool episode_map::read_sidedefs(wad_lump const *lump)
{
  uint8_t const *sidedef_ptr;
  num_sidedefs = lump->get_num_bytes() / SIDEDEF_NUM_BYTES;
  sidedefs = new sidedef[num_sidedefs];

  for(int i=0; i<num_sidedefs; i++)
  {
    sidedef_ptr = lump->get_data() + (i*SIDEDEF_NUM_BYTES);
    sidedefs[i].read_from_lump_data(sidedef_ptr);
  }

  return true;
}

bool episode_map::read_vertexes(wad_lump const *lump)
{
  uint8_t const *vertex_ptr;
  num_vertexes = lump->get_num_bytes() / VERTEX_NUM_BYTES;
  vertexes = new vertex[num_vertexes];

  for(int i=0; i<num_vertexes; i++)
  {
    vertex_ptr = lump->get_data() + (i*VERTEX_NUM_BYTES);
    vertexes[i].read_from_lump_data(vertex_ptr);
  }

  return true;
}

bool episode_map::read_segments(wad_lump const *lump)
{
  uint8_t const *segment_ptr;
  num_segments = lump->get_num_bytes() / SEGMENT_NUM_BYTES;
  segments = new wad_segment[num_segments];

  for(int i=0; i<num_segments; i++)
  {
    segment_ptr = lump->get_data() + (i*SEGMENT_NUM_BYTES);
    segments[i].read_from_lump_data(segment_ptr);
  }

  return true;
}

bool episode_map::read_subsectors(wad_lump const *lump)
{
  uint8_t const *subsector_ptr;
  num_subsectors = lump->get_num_bytes() / SUBSECTOR_NUM_BYTES;
  subsectors = new subsector[num_subsectors];

  for(int i=0; i<num_subsectors; i++)
  {
    subsector_ptr = lump->get_data() + (i*SUBSECTOR_NUM_BYTES);
    subsectors[i].read_from_lump_data(subsector_ptr);
  }

  return true;
}

bool episode_map::read_nodes(wad_lump const *lump)
{
  uint8_t const *node_ptr;
  num_nodes = lump->get_num_bytes() / NODE_NUM_BYTES;
  nodes = new node[num_nodes];

  for(int i=0; i<num_nodes; i++)
  {
    node_ptr = lump->get_data() + (i*NODE_NUM_BYTES);
    nodes[i].read_from_lump_data(node_ptr);
    if(nodes[i].get_left()->is_node() && nodes[i].get_left()->child_num>num_nodes)
    {
      printf("ERROR: left child node num (%d) is greater than # of nodes (%d)\n", nodes[i].get_left()->child_num, num_nodes);
      return false;
    }
    if(nodes[i].get_right()->is_node() && nodes[i].get_right()->child_num>num_nodes)
    {
      printf("ERROR: right child node num (%d) is greater than # of nodes (%d)\n", nodes[i].get_right()->child_num, num_nodes);
      return false;
    }
  }

  return true;
}

bool episode_map::read_sectors(wad_lump const *lump)
{
  uint8_t const *sector_ptr;
  num_sectors = lump->get_num_bytes() / SECTOR_NUM_BYTES;
  sectors = new sector[num_sectors];

  for(int i=0; i<num_sectors; i++)
  {
    sector_ptr = lump->get_data() + (i*SECTOR_NUM_BYTES);
    sectors[i].read_from_lump_data(sector_ptr);
    switch(sectors[i].get_type())
    {
      case SECTOR_TYPE_NORMAL: 			break;

      case SECTOR_TYPE_GLOWING_LIGHT: 		debug_printf("not implemented: SECTOR_TYPE_GLOWING_LIGHT\n"); break;
      case SECTOR_TYPE_FLICKERING_LIGHTS: 	add_actor(new flickering_light(&sectors[i])); break;
      case SECTOR_TYPE_FIRE_FLICKER: 		debug_printf("not implemented: SECTOR_TYPE_FIRE_FLICKER\n"); break;

      case SECTOR_TYPE_STROBE_SLOW: 		add_actor(new slow_strobe_light(&sectors[i])); break;
      case SECTOR_TYPE_STROBE_FAST: 		add_actor(new fast_strobe_light(&sectors[i])); break;
      case SECTOR_TYPE_SYNC_STROBE_SLOW: 	debug_printf("not implemented: SECTOR_TYPE_SYNC_STROBE_SLOW\n"); break;
      case SECTOR_TYPE_SYNC_STROBE_FAST: 	debug_printf("not implemented: SECTOR_TYPE_SYNC_STROBE_FAST\n"); break;
      case SECTOR_TYPE_STROBE_FAST_DEATH_SLIME: add_actor(new fast_strobe_light(&sectors[i]));break;

      case SECTOR_TYPE_HELLSLIME_DAMAGE: 	debug_printf("not implemented: SECTOR_TYPE_HELLSLIME_DAMAGE\n"); break;
      case SECTOR_TYPE_NUKAGE_DAMAGE: 		debug_printf("not implemented: SECTOR_TYPE_NUKAGE_DAMAGE\n"); break;
      case SECTOR_TYPE_SUPER_HELLSLIME_DAMAGE:	debug_printf("not implemented: SECTOR_TYPE_SUPER_HELLSLIME_DAMAGE\n"); break;
      case SECTOR_TYPE_EXIT_SUPER_DAMAGE: 	debug_printf("not implemented: SECTOR_TYPE_EXIT_SUPER_DAMAGE\n"); break;

      case SECTOR_TYPE_SECRET_SECTOR: 		debug_printf("not implemented: SECTOR_TYPE_SECRET_SECTOR\n"); break;

      case SECTOR_TYPE_DOOR_CLOSE_IN_30_SEC: 	debug_printf("not implemented: SECTOR_TYPE_DOOR_CLOSE_IN_30_SEC\n"); break;
      case SECTOR_TYPE_DOOR_RAISE_IN_5_MIN: 	debug_printf("not implemented: SECTOR_TYPE_DOOR_RAISE_IN_5_MIN\n"); break;

      default: printf("ERROR: unhandled sector type %d\n", sectors[i].get_type()); exit(0);
    }
  }

  return true;
}

void episode_map::link_nodes_to_children(void)
{
  int child_num;
  for(int i=0; i<num_nodes; i++)
  {
    child_num = nodes[i].get_left()->child_num;
    if(nodes[i].get_left()->is_subsector())
    {
      if(child_num >= num_subsectors)
      {
        printf("WAARNING: node %d's left child is subsector %d > num_subsectors %d\n", i, child_num, num_subsectors);
      }
      nodes[i].set_left_subsector( &(subsectors[child_num]) );
    }
    else
    {
      if(child_num >= num_nodes)
      {
        printf("WAARNING: node %d's left child is nodes %d > num_nodes %d\n", i, child_num, num_nodes);
      }
      nodes[i].set_left_node( &(nodes[child_num]) );
    }

    child_num = nodes[i].get_right()->child_num;
    if(nodes[i].get_right()->is_subsector())
    {
      if(child_num >= num_subsectors)
      {
        printf("WAARNING: node %d's right child is subsector %d > num_subsectors %d\n", i, child_num, num_subsectors);
      }
      nodes[i].set_right_subsector( &(subsectors[child_num]) );
    }
    else
    {
      if(child_num >= num_nodes)
      {
        printf("WAARNING: node %d's right child is nodes %d > num_nodes %d\n", i, child_num, num_nodes);
      }
      nodes[i].set_right_node( &(nodes[child_num]) );
    }
  }
}

void episode_map::link_sectors_to_flats(void)
{
  for(int i=0; i<num_sectors; i++)
  {
    flat_animation const *f;
    char const *name;

    name = sectors[i].get_ceiling_texture_name();
    f = flats_find_by_name(name);
    if(f)
    {
      sectors[i].set_ceiling_texture(f);
    }
    else { printf("ERROR: could not find sector %d's ceiling texture named \"%s\"\n", i, name); exit(0); }

    name = sectors[i].get_floor_texture_name();
    f = flats_find_by_name(name);
    if(f)
    {
      sectors[i].set_floor_texture(f);
    }
    else { printf("ERROR: could not find sector %d's ceiling texture named \"%s\"\n", i, name); exit(0); }
  }
}

void episode_map::link_subsectors_to_segments(void)
{
  wad_segment *seg;
  int seg_num;

  for(int i=0; i<num_subsectors; i++)
  {
    subsectors[i].allocate_segments();
    for(int j=0; j<subsectors[i].get_num_segments(); j++)
    {
      seg_num = subsectors[i].get_first_segment_num()+j;
      if(seg_num >= num_segments)
      {
        printf("WARNING: subsector %d points to segment %d > num_segments %d\n", i, seg_num, num_segments);
      }
      seg = &segments[seg_num];
      subsectors[i].set_nth_segment(j, seg);
    }
  }
}

void episode_map::link_segments_to_children(void)
{
  int i, linedef_num, v_num;
  linedef *ld;
  vertex *v;

  for(i=0; i<num_segments; i++)
  {
    // wire the segment up to its linedef
    linedef_num = segments[i].get_linedef_num();
    ld = &linedefs[linedef_num];
    segments[i].set_linedef(ld);

    // wire the segment up to its start vertex
    v_num = segments[i].get_start_vertex_num();
    if(v_num >= num_vertexes)
    {
      printf("WARNING: segment %d links to vertex %d > num_vertexes %d\n", i, v_num, num_vertexes);
    }
    v = &vertexes[v_num];
    segments[i].set_start_vertex(v);

    // wire the segment up to its end vertex
    v_num = segments[i].get_end_vertex_num();
    if(v_num >= num_vertexes)
    {
      printf("WARNING: segment %d links to vertex %d > num_vertexes %d\n", i, v_num, num_vertexes);
    }
    v = &vertexes[v_num];
    segments[i].set_end_vertex(v);

    // wire the segment up to its front and back sectors
    int seg_dir = segments[i].get_direction();
    sidedef const *front_sidedef = segments[i].get_linedef()->get_sidedef(seg_dir);
    sector const *front_sector = front_sidedef->get_sector();
    segments[i].set_front_sector(front_sector);

    if(segments[i].get_linedef()->is_two_sided())
    {
      seg_dir = 1-seg_dir; // FIXME: make clearer
      sidedef const *back_sidedef = segments[i].get_linedef()->get_sidedef(seg_dir);
      sector const *back_sector = back_sidedef->get_sector();
      segments[i].set_back_sector(back_sector);
    }
  }
}

void episode_map::link_linedefs_to_children(void)
{
  int sidedef_num, vertex_num, i;

  for(i=0; i<num_linedefs; i++)
  {
    if(linedefs[i].has_left_sidedef())
    {
      sidedef_num = linedefs[i].get_left_sidedef_num();
      if(sidedef_num >= num_sidedefs)
      {
        printf("WARNING: linedef %d's left sidedef is %d > num_sidedefs %d\n", i, sidedef_num, num_sidedefs);
      }
      linedefs[i].set_left_sidedef(&sidedefs[sidedef_num]);
    }

    if(linedefs[i].has_right_sidedef())
    {
      sidedef_num = linedefs[i].get_right_sidedef_num();
      if(sidedef_num >= num_sidedefs)
      {
        printf("WARNING: linedef %d's right sidedef is %d > num_sidedefs %d\n", i, sidedef_num, num_sidedefs);
      }
      linedefs[i].set_right_sidedef(&sidedefs[sidedef_num]);
    }

    vertex_num = linedefs[i].get_start_vertex_num();
    if(vertex_num >= num_vertexes)
    {
      printf("WARNING: linedef %d's start vertex is %d, >= num_vertexes %d\n", i, vertex_num, num_vertexes);
    }
    linedefs[i].set_start_vertex(&vertexes[vertex_num]);

    vertex_num = linedefs[i].get_end_vertex_num();
    if(vertex_num >= num_vertexes)
    {
      printf("WARNING: linedef %d's end vertex is %d, >= num_vertexes %d\n", i, vertex_num, num_vertexes);
    }
    linedefs[i].set_end_vertex(&vertexes[vertex_num]);
  }
}

void episode_map::link_sidedefs_to_children(void)
{
  wall_texture const *tex;

  for(int i=0; i<num_sidedefs; i++)
  {
    int sector_num = sidedefs[i].get_sector_num();
    sector *s = &sectors[sector_num];
    sidedefs[i].set_sector(s);

    tex = wall_textures_get_by_name(sidedefs[i].get_upper_texture_name());
    if(tex) { sidedefs[i].set_upper_texture(tex); }
    else if(strlen(sidedefs[i].get_upper_texture_name())>1)
    {
      printf("ERROR: couldn't find sidedef %d's upper texture \"%s\"\n", i, sidedefs[i].get_upper_texture_name());
      exit(0);
    }

    tex = wall_textures_get_by_name(sidedefs[i].get_lower_texture_name());
    if(tex) { sidedefs[i].set_lower_texture(tex); }
    else if(strlen(sidedefs[i].get_lower_texture_name())>1)
    {
      printf("ERROR: couldn't find sidedef %d's lower texture \"%s\"\n", i, sidedefs[i].get_lower_texture_name());
      exit(0);
    }

    tex = wall_textures_get_by_name(sidedefs[i].get_mid_texture_name());
    if(tex) { sidedefs[i].set_mid_texture(tex); }
    else if(strlen(sidedefs[i].get_mid_texture_name())>1)
    {
      printf("ERROR: couldn't find sidedef %d's mid texture \"%s\"\n", i, sidedefs[i].get_mid_texture_name());
      exit(0);
    }
  }
}

void episode_map::link_blocks_to_children(void)
{
  for(int col=0; col<_block_map.get_num_cols(); col++)
  {
    for(int row=0; row<_block_map.get_num_rows(); row++)
    {
      block_map_cell *cell = _block_map.get_cell_rw(col, row);
      for(int linedef_num=0; linedef_num<cell->get_num_linedefs(); linedef_num++)
      {
        uint16_t linedef_idx = cell->get_linedef_num(linedef_num);
        if(linedef_idx >= num_linedefs)
        {
          printf("ERROR: block list references linedef %d >= %d\n", linedef_idx, num_linedefs);
          exit(0);
        }
        linedef *cur_linedef = &linedefs[linedef_idx];
        cell->set_linedef(linedef_num, cur_linedef);
      }
    }
  }
}

void episode_map::draw_overhead_map(overhead_map *omap) const
{
  color_rgba blu(  0,   0, 255, 255);

  for(int i=0; i<num_linedefs; i++)
  {
    linedef const *l = &linedefs[i];
    if(l->never_on_automap())
    {
      // don't draw these
    }
    else
    {
      vertex const *v1 = l->get_start_vertex();
      vertex const *v2 = l->get_end_vertex();
      omap->draw_line(v1, v2, &blu);
    }
  }
}

void episode_map::render_player_view(camera const *_camera,
                                     clipped_segment_projections *clipped_seg_projs, 
                                     vis_planes *vp, 
                                     thing * const things[], int num_things, vis_things *vt) const
{
  root_node()->render_player_view(_camera, clipped_seg_projs, vp, things, num_things, vt);
}

bool episode_map::can_move(vertex const *old_position, vertex const *new_position, float obj_radius, float *floor_height) const
{
  // FIXME: take into account closed doors
  // FIXME: take into account high steps / pedestals (too high to step into)
  // FIXME: take into account cabinets (mid-texture gaps with too little dy for the player's height
  // FIXME: take into account being on the border between two cells?

  // loop through everything for center and then the radius at 0,90,180,270
  for(int i=0; i<5; i++)
  {
    vertex v1(old_position), v2(new_position);
    switch(i)
    {
      case 0: break; 
      case 1: v1.set_x(v1.get_x()+obj_radius); v2.set_x(v2.get_x()+obj_radius); break;
      case 2: v1.set_x(v1.get_x()-obj_radius); v2.set_x(v2.get_x()-obj_radius); break;
      case 3: v1.set_y(v1.get_y()+obj_radius); v2.set_y(v2.get_y()+obj_radius); break;
      case 4: v1.set_y(v1.get_y()-obj_radius); v2.set_y(v2.get_y()-obj_radius); break;
    }
    segment move_path(&v1, &v2);

    block_map_cell *cell;
    cell = _block_map.get_cell_by_map_pos(&v1);
    if(cell)
    {
      for(int i=0; i<cell->get_num_linedefs(); i++)
      {
        linedef const *cur_linedef = cell->get_linedef(i);
    
        // does movement intersect line?
        segment line_seg(cur_linedef->get_start_vertex(), cur_linedef->get_end_vertex());
        vertex intersect_point;
        float intersect_pct1, intersect_pct2; // parameter (0..1) across the segment and the vector
        if(line_seg.get_intersection_with_segment(&move_path, &intersect_point, &intersect_pct1, &intersect_pct2) &&
           (0.0 <= intersect_pct1) && (intersect_pct1 <= 1.0) &&
           (0.0 <= intersect_pct2) && (intersect_pct2 <= 1.0) )
        {
          if(cur_linedef->is_one_sided())   { return false; }
          if(cur_linedef->blocks_players()) { return false; }
        }
      }
    }
  }

  subsector const *new_ss;
  new_ss = root_node()->get_subsector_containing(new_position);
  *floor_height = new_ss->get_sector()->get_floor_height(); // FIXME: this is wrong...

  return true;
}

void episode_map::add_actor(actor *a)
{
  if((num_actors+1) >= MAX_NUM_ACTORS)
  {
    printf("ERROR: actor overflow\n");
    exit(0);
  }
  actors[num_actors++] = a;
}

void episode_map::direct_actors(void)
{
  for(int i=0; i<num_actors; i++)
  {
     actors[i]->act();
  }
}
