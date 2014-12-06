#ifndef __SIDEDEF_H
#define __SIDEDEF_H

#include <stdint.h>

#define SIDEDEF_NUM_BYTES 30 // size on disk (in the lump)

class sidedef
{
public:
  sidedef();
  ~sidedef();

  bool read_from_lump_data(uint8_t const *lump_data);

  int16_t get_x_offset(void) const { return x_offset; };
  int16_t get_y_offset(void) const { return y_offset; };
  char const *get_upper_texture_name(void) const { return upper_texture_name; };
  char const *get_lower_texture_name(void) const { return lower_texture_name; };
  char const *get_mid_texture_name(void) const { return mid_texture_name; };
  uint16_t get_sector_num(void) const { return sector_num; }

private:
  int16_t  x_offset;              // FIXME: signed?
  int16_t  y_offset;              // FIXME: signed?
  char     upper_texture_name[9]; // 8 + NULL
  char     lower_texture_name[9]; // 8 + NULL
  char     mid_texture_name[9];   // 8 + NULL
  uint16_t sector_num;            // Sector number this sidedef 'faces'
};

#endif
