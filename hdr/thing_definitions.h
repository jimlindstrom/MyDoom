#ifndef __THING_DEFINITIONS_H
#define __THING_DEFINITIONS_H

#define THING_PLAYER_1_START_TYPE	1
#define THING_PLAYER_2_START_TYPE	2
#define THING_PLAYER_3_START_TYPE	3
#define THING_PLAYER_4_START_TYPE	4
#define THING_DEATHMATCH_START_TYPE	11
#define THING_TELEPORT_LANDING_TYPE	14
#define THING_SPAWN_SPOT_TYPE		87
#define THING_SPAWN_SHOOTER_TYPE	89

// FIXME: these string lengths could likely be tuned down a bit.
typedef struct
{
  uint16_t type_num_dec;
  char     type_num_hex[5]; // FXIME: delete this?
  char     version[3];      // FIXME: delete this?
  uint16_t radius;
  char     sprite_prefix[6];
  char     sequence[8];
  char     klass[8];
  char     description[40];
} thing_definition;

thing_definition const *thing_definition_lookup(uint16_t type_num_dec);

#endif
