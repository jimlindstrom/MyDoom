#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "wad_endian.h"
#include "wad_header.h"

wad_header::wad_header()
{
}

wad_header::~wad_header()
{
}

bool wad_header::read(FILE *f)
{
  fread(identification,  sizeof(char),  4, f);
  fread(&num_lumps,      sizeof(int32_t), 1, f);
  fread(&infotableofs,   sizeof(int32_t), 1, f);

  identification[4] = 0; // NULL-terminate the ID
  num_lumps    = LITTLE_ENDIAN32_TO_LOCAL_ENDIAN32(num_lumps);
  infotableofs = LITTLE_ENDIAN32_TO_LOCAL_ENDIAN32(infotableofs);

  return is_valid();
}

bool wad_header::is_iwad(void)
{
  return (strcmp(identification, "IWAD")==0);
}

bool wad_header::is_pwad(void)
{
  return (strcmp(identification, "PWAD")==0);
}

void wad_header::print(void)
{
  printf("Header:\n");
  printf("  identification: %s\n", identification);
  printf("  num_lumps: %d\n", num_lumps);
  printf("  infotableofs: %d\n", infotableofs);
}

bool wad_header::is_valid(void)
{
  if(!is_iwad() && !is_pwad())
  {
    printf("WARNING: WAD header has invalid type: \"%s\"\n", identification);
    return false;
  }

  if( (num_lumps <      1) || 
      (num_lumps > 100000) ) // arbitrary guess at sane number
  {
    printf("WARNING: WAD header num lumps (%d) seems invalid\n", num_lumps);
    return false;
  }

  if( (infotableofs <         1) || 
      (infotableofs > 100000000) ) // arbitrary guess at sane number
  {
    printf("WARNING: WAD header infotableofs (%d) seems invalid\n", infotableofs);
    return false;
  }

  return true;
}
