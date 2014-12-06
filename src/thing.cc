#include "thing.h"

thing()
{
}

~thing()
{
}

bool read_from_lump_data(uint8_t *lump_data)
{
  x            = *(( int16_t*)lump_data); lump_data += 2;
  y            = *(( int16_t*)lump_data); lump_data += 2;
  facing_angle = *(( int16_t*)lump_data); lump_data += 2;
  thing_type   = *((uint16_t*)lump_data); lump_data += 2;
  flags        = *((uint16_t*)lump_data); lump_data += 2;
}

