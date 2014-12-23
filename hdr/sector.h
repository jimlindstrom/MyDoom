#ifndef __SECTOR_H
#define __SECTOR_H

#include <stdint.h>

#include "flat.h"

#define SECTOR_NUM_BYTES 26 // size on disk (in the lump)

#define SECTOR_TYPE_NORMAL			 0 // no special effects
#define SECTOR_TYPE_FLICKERING_LIGHTS		 1 // FLICKERING LIGHTS
#define SECTOR_TYPE_STROBE_FAST			 2 // STROBE FAST
#define SECTOR_TYPE_STROBE_SLOW			 3 // STROBE SLOW
#define SECTOR_TYPE_STROBE_FAST_DEATH_SLIME	 4 // STROBE FAST/DEATH SLIME
#define SECTOR_TYPE_HELLSLIME_DAMAGE		 5 // HELLSLIME DAMAGE
#define SECTOR_TYPE_NUKAGE_DAMAGE		 7 // NUKAGE DAMAGE
#define SECTOR_TYPE_GLOWING_LIGHT		 8 // GLOWING LIGHT
#define SECTOR_TYPE_SECRET_SECTOR		 9 // SECRET SECTOR
#define SECTOR_TYPE_DOOR_CLOSE_IN_30_SEC	10 // DOOR CLOSE IN 30 SECONDS
#define SECTOR_TYPE_EXIT_SUPER_DAMAGE		11 // EXIT SUPER DAMAGE! (for E1M8 finale)
#define SECTOR_TYPE_SYNC_STROBE_SLOW		12 // SYNC STROBE SLOW
#define SECTOR_TYPE_SYNC_STROBE_FAST		13 // SYNC STROBE FAST
#define SECTOR_TYPE_DOOR_RAISE_IN_5_MIN		14 // DOOR RAISE IN 5 MINUTES
#define SECTOR_TYPE_SUPER_HELLSLIME_DAMAGE	16 // SUPER HELLSLIME DAMAGE
#define SECTOR_TYPE_FIRE_FLICKER		17 // FIRE FLICKER?

class sector
{
public:
  sector();
  ~sector();

  bool read_from_lump_data(uint8_t const *lump_data);

  int16_t get_floor_height(void) const { return floor_height; }
  int16_t get_ceiling_height(void) const { return ceiling_height; }
  int16_t get_clearance(void) const { return ceiling_height-floor_height; }
  char const *get_floor_texture_name(void) const { return floor_texture_name; }
  char const *get_ceiling_texture_name(void) const { return ceiling_texture_name; }
  uint16_t get_light_level(void) const { return light_level; }
  void set_light_level(uint16_t l) { light_level = l; }
  uint16_t get_type(void) const { return type; }
  uint16_t get_tag_num(void) const { return tag_num; }

  void set_floor_texture(flat_animation const *f) { floor_texture = f; }
  void set_ceiling_texture(flat_animation const *f) { ceiling_texture = f; }
  flat_animation const *get_floor_texture(void) const { return floor_texture; }
  flat_animation const *get_ceiling_texture(void) const { return ceiling_texture; }

private:
  int16_t floor_height;
  int16_t ceiling_height;
  char floor_texture_name[9];
  char ceiling_texture_name[9];
  uint16_t light_level;
  uint16_t type;
  uint16_t tag_num;

  flat_animation const *floor_texture;
  flat_animation const *ceiling_texture;
};

#endif
