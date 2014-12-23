#ifndef __SECTOR_H
#define __SECTOR_H

#include <stdint.h>

#include "flat.h"

#define SECTOR_NUM_BYTES 26 // size on disk (in the lump)

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
