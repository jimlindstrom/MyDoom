#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "wad_file.h"
#include "wad_directory.h"

wad_file::wad_file()
{
  lumps = NULL;
}

wad_file::~wad_file()
{
  if(lumps) 
  {
    delete [] lumps;
  }
}

bool wad_file::read(char const *filename)
{
  FILE *f;
  int d;

  f = fopen(filename, "r");
   
  if (!header.read(f))
  {
    printf("ERROR: invalid WAD header\n");
    return false;
  }
  //header.print();

  if(!read_lumps(f))
  {
    return false;
  }

  fclose(f);
   
  return true;
}

bool wad_file::read_lumps(FILE *f)
{
  int lump_idx;
  long int pos;
  uint32_t lump_num_bytes;
  uint8_t *lump_data;

  fseek(f, header.get_infotableofs(), SEEK_SET);
  pos = ftell(f);

  num_lumps = header.get_num_lumps();
  lumps = new wad_lump[num_lumps];
 
  for(int lump_idx=0; lump_idx<num_lumps; lump_idx++)
  {
    wad_directory dir;

    fseek(f, pos, SEEK_SET);
    if (!dir.read(f))
    {
      printf("ERROR: invalid WAD directory %d of %d\n", lump_idx, num_lumps);
      return false;
    }
    //dir.print();
    pos = ftell(f);

    fseek(f, dir.get_filepos(), SEEK_SET);
    lump_num_bytes = dir.get_size();
    lump_data = new uint8_t[lump_num_bytes];
    fread(lump_data, lump_num_bytes, sizeof(uint8_t), f);
    lumps[lump_idx].set_name(dir.get_name());
    lumps[lump_idx].set_data(lump_data, lump_num_bytes);
    delete[] lump_data;
  }

  return has_required_lumps();
  return true;
}

bool wad_file::has_required_lumps(void)
{
  int i;
  for(i=0; i<NUM_REQUIRED_LUMP_NAMES; i++)
  {
    if(!find_lump_by_name(required_lump_names[i]))
    {
      printf("ERROR: WAD does not contain a required lump named \"%s\"\n", required_lump_names[i]);
      return false;
    }
  }

  return true;
}

wad_lump const *wad_file::find_lump_by_name(char const *name) const
{
  int lump_idx;

  for(int lump_idx=0; lump_idx<num_lumps; lump_idx++)
  {
    if(lumps[lump_idx].is_named(name))
    {
      return &lumps[lump_idx];
    }
  }

  return NULL;
}

wad_lump const *wad_file::get_next_lump(wad_lump const *cur_lump) const
{
  int lump_idx;

  for(int lump_idx=0; lump_idx<(num_lumps-1); lump_idx++)
  {
    if(lumps[lump_idx].is_named(cur_lump->get_name()))
    {
      return &lumps[lump_idx+1];
    }
  }

  return NULL;

}
