#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "wad_endian.h"
#include "wad_directory.h"

wad_directory::wad_directory()
{
}

wad_directory::~wad_directory()
{
}

bool wad_directory::read(FILE *f)
{
  fread(&filepos, sizeof(int32_t), 1, f);
  fread(&size,    sizeof(int32_t), 1, f);
  fread(name,     sizeof(char),    8, f);

  filepos = LITTLE_ENDIAN32_TO_LOCAL_ENDIAN32(filepos);
  size    = LITTLE_ENDIAN32_TO_LOCAL_ENDIAN32(size);
  name[8] = 0; // NULL-terminate the name

  return is_valid();
}

bool wad_directory::is_named(char const *_name)
{
  return (strcmp(name, _name)==0);
}

void wad_directory::print(void)
{
  printf("Directory:");
  printf("\tname: %-10s", name);
  printf("\tfilepos: % 9d", filepos);
  printf("\tsize: % 8d", size);
  printf("\n");
}

bool wad_directory::is_valid(void)
{
  if(filepos > 10000000)
  {
    printf("WARNING: WAD directory has invalid filepos: %d\n", size);
    return false;
  }

  if(size > 10000000)
  {
    printf("WARNING: WAD directory has invalid size: %d\n", size);
    return false;
  }
  
  if( (strlen(name) < 1) &&
      (strlen(name) > 8) )
  {
    printf("WARNING: WAD directory has invalid name: %s\n", name);
    return false;
  }

  return true;
}
