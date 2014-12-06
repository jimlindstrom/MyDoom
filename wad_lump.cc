#include <string.h>
#include <stdio.h>

#include "wad_lump.h"

wad_lump::wad_lump()
{
  name = NULL;
  data = NULL;
}

wad_lump::~wad_lump()
{
  if(name) { delete name; }
  if(data) { delete data; }
}

void wad_lump::set_name(char const *_name)
{
  if(name) { delete name; }
  name = new char[strlen(_name)+1];
  strcpy(name, _name);
  name[strlen(_name)] = 0;
}

void wad_lump::set_data(void const *src, int32_t _num_bytes)
{
  num_bytes = _num_bytes;
  if(data) { delete data; }
  data = new uint8_t[num_bytes];
  memcpy(data, src, num_bytes);
  //for(int i=0;i<512;i++) { printf("0x%02x ", ((uint8_t*)src)[i]); if(i%16==15) { printf("\n"); } } printf("\n");
}

bool wad_lump::is_named(char const *_name) const
{
  return (strcmp(_name, name)==0);
}
