#include <string.h>
#include <stdio.h>

#include "episode_map.h"
#include "color.h"
#include "overhead_map.h"
#include "wall_textures.h"

episode_map::episode_map()
{
  name       = NULL;
  things     = NULL;
  linedefs   = NULL;
  vertexes   = NULL;
  segments   = NULL;
  subsectors = NULL;
  nodes      = NULL;
  sectors    = NULL;
}

episode_map::~episode_map()
{
  if(name)       { delete[] name;       }
  if(things )    { delete[] things;     }
  if(linedefs)   { delete[] linedefs;   }
  if(vertexes)   { delete[] vertexes;   }
  if(segments)   { delete[] segments;   }
  if(subsectors) { delete[] subsectors; }
  if(nodes)      { delete[] nodes;      }
  if(sectors)    { delete[] sectors;    }
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
    if(strcmp(cur_lump->get_name(),"THINGS")==0)
    {
      if(!read_things(cur_lump)) { return false; }
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
      reject_tbl.read_from_lump(lump, num_sectors);
    }
    else if(strcmp(cur_lump->get_name(),"BLOCKMAP")==0)
    {
      _block_map.read_from_lump(lump, num_sectors);
    }
    else
    {
      done = true;
    }
    cur_lump = wad->get_next_lump(cur_lump);
  }

  link_nodes_to_children();
  link_subsectors_to_segments();
  link_segments_to_children();
  link_linedefs_to_children();
  link_sidedefs_to_children();

  return true;
}

bool episode_map::read_things(wad_lump const *lump)
{
  uint8_t const *thing_ptr;
  num_things = lump->get_num_bytes() / THING_NUM_BYTES;
  things = new thing[num_things];

  for(int i=0; i<num_things; i++)
  {
    thing_ptr = lump->get_data() + (i*THING_NUM_BYTES);
    things[i].read_from_lump_data(thing_ptr);
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
    linedef_num = segments[i].get_linedef_num();
    ld = &linedefs[linedef_num];
    segments[i].set_linedef(ld);

    v_num = segments[i].get_start_vertex_num();
    if(v_num >= num_vertexes)
    {
      printf("WARNING: segment %d links to vertex %d > num_vertexes %d\n", i, v_num, num_vertexes);
    }
    v = &vertexes[v_num];
    segments[i].set_start_vertex(v);

    v_num = segments[i].get_end_vertex_num();
    if(v_num >= num_vertexes)
    {
      printf("WARNING: segment %d links to vertex %d > num_vertexes %d\n", i, v_num, num_vertexes);
    }
    v = &vertexes[v_num];
    segments[i].set_end_vertex(v);
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
      printf("WARNING: couldn't find sidedef %d's upper texture \"%s\"\n", i, sidedefs[i].get_upper_texture_name());
    }

    tex = wall_textures_get_by_name(sidedefs[i].get_lower_texture_name());
    if(tex) { sidedefs[i].set_lower_texture(tex); }
    else if(strlen(sidedefs[i].get_lower_texture_name())>1)
    {
      printf("WARNING: couldn't find sidedef %d's lower texture \"%s\"\n", i, sidedefs[i].get_lower_texture_name());
    }

    tex = wall_textures_get_by_name(sidedefs[i].get_mid_texture_name());
    if(tex) { sidedefs[i].set_mid_texture(tex); }
    else if(strlen(sidedefs[i].get_mid_texture_name())>1)
    {
      printf("WARNING: couldn't find sidedef %d's mid texture \"%s\"\n", i, sidedefs[i].get_mid_texture_name());
    }
  }
}

void episode_map::draw_overhead_map(overhead_map *omap) const
{
  color_rgba blu(  0,   0, 255, 255);

/*  for(int i=0; i<num_nodes; i++)
  {
    node const *cur_node = &nodes[i];
 
    omap->draw_partition_line(cur_node->get_partition(),  &red);
    if(cur_node->get_left()->is_subsector())
    {
      omap->draw_node_bbox(&(cur_node->get_left()->_bbox),  &grn);
    }
    if(cur_node->get_right()->is_subsector())
    {
      omap->draw_node_bbox(&(cur_node->get_right()->_bbox), &blu);
    }
  }*/
  for(int i=0; i<num_linedefs; i++)
  {
    linedef const *l = &linedefs[i];
    vertex const *v1 = l->get_start_vertex();
    vertex const *v2 = l->get_end_vertex();
    omap->draw_line(v1, v2, &blu);
  }
}

void episode_map::render_player_view(column_range_list *col_ranges, projector const *_projector, player const *_player, overhead_map *omap) const
{
  nodes[num_nodes-1].render_player_view(col_ranges, _projector, _player, omap);
}
