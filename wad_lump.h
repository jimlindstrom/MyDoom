#ifndef __WAD_LUMP_H
#define __WAD_LUMP_H

#include <stdint.h>

class wad_lump
{
public:
  wad_lump();
  ~wad_lump();

  char const *get_name(void) const { return name; }
  int32_t get_num_bytes(void) const { return num_bytes; }
  uint8_t const *get_data(void) const { return data; }

  void set_name(char const *_name);
  void set_data(void const *src, int32_t _num_bytes);

  bool is_named(char const *_name);
  
private:
  char *name;
  int32_t num_bytes;
  uint8_t *data;
};

#endif
