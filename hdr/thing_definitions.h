#ifndef __THING_DEFINITIONS_H
#define __THING_DEFINITIONS_H

// FIXME: why special-case this one?
#define THING_PLAYER_1_START_TYPE	1

// FIXME: these string lengths could likely be tuned down a bit.
typedef struct
{
  uint16_t type_num_dec;
  char     type_num_hex[5];
  char     version[3];
  uint16_t radius;
  char     sprite_prefix[6];
  char     sequence[8];
  char     klass[8];
  char     description[40];
} thing_definition;

thing_definition const *thing_definition_lookup(uint16_t type_num_dec);

#endif
