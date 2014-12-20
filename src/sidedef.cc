#include <string.h>
#include <stdio.h>
#include <ctype.h>

#include "sidedef.h"

//#define DEBUG_PRINTING
#include "debug.h"

sidedef::sidedef()
{
  _sector = NULL;
  upper_texture = NULL;
  lower_texture = NULL;
  mid_texture = NULL;
}

sidedef::~sidedef()
{
}

bool sidedef::read_from_lump_data(uint8_t const *lump_data)
{
  tx_offset = *((int16_t*)lump_data); lump_data += 2;
  ty_offset = *((int16_t*)lump_data); lump_data += 2;

  memcpy(upper_texture_name, lump_data, 8);
  upper_texture_name[8] = 0;
  lump_data += 8;
  for(char *ch=upper_texture_name; *ch!=0; ch++) { *ch = toupper(*ch); }

  memcpy(lower_texture_name, lump_data, 8);
  lower_texture_name[8] = 0;
  lump_data += 8;
  for(char *ch=lower_texture_name; *ch!=0; ch++) { *ch = toupper(*ch); }

  memcpy(mid_texture_name, lump_data, 8);
  mid_texture_name[8] = 0;
  lump_data += 8;
  for(char *ch=mid_texture_name; *ch!=0; ch++) { *ch = toupper(*ch); }

  sector_num = *((uint16_t*)lump_data); lump_data += 2;

  return true;
}
