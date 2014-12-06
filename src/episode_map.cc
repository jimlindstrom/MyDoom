#include <string.h>
#include <stdio.h>

#include "episode_map.h"

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

  //printf("\treading %s\n", name);

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
  segments = new segment[num_segments];

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
  num_subsectors = lump->get_num_bytes() / NODE_NUM_BYTES;
  nodes = new node[num_nodes];

  for(int i=0; i<num_nodes; i++)
  {
    node_ptr = lump->get_data() + (i*NODE_NUM_BYTES);
    nodes[i].read_from_lump_data(node_ptr);
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

