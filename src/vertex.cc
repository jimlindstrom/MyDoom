#include <string.h>

#include "vertex.h"

vertex::vertex()
{
}

vertex::~vertex()
{
}

bool vertex::read_from_lump_data(uint8_t const *lump_data)
{
  x = *((int16_t*)lump_data); lump_data += 2;
  y = *((int16_t*)lump_data); lump_data += 2;

  return true;
}

