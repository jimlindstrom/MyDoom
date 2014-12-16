#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "patch_names_lump.h"

patch_names_lump::patch_names_lump()
{
  patch_names = NULL;
}

patch_names_lump::~patch_names_lump()
{
  if(patch_names)
  {
    for(int i=0; i<num_patch_names; i++)
    {
      delete[] patch_names[i];
    }
    delete[] patch_names;
  }
}

bool patch_names_lump::read_from_lump_data(uint8_t const *lump_data)
{
  num_patch_names = *((uint32_t*)lump_data); lump_data += 4;

  if(num_patch_names < 1)
  {
    printf("ERROR: no patch names\n");
    return false;
  }
  
  patch_names = new char*[num_patch_names];
  for(int i=0; i<num_patch_names; i++)
  {
    patch_names[i] = new char[8];
    memcpy(&patch_names[i][0], lump_data, 9);
    patch_names[i][8] = 0;
    lump_data += 8;
  }

  return true;
}

char const *patch_names_lump::get_patch_name_by_num(int num) const
{
  return patch_names[num];
}

uint16_t patch_names_lump::get_patch_num_by_name(char const *name) const
{
  for(int i=0; i<num_patch_names; i++)
  {
    if(strcasecmp(patch_names[i], name) == 0)
    {
      return i;
    }
  }

  printf("ERROR: patch name \"%s\" not found in ", name);
  for(int i=0; i<num_patch_names; i++)
  {
    printf(" '%s'", patch_names[i]);
  }
  printf("\n");

  exit(0);
  return 0xffff;
}

