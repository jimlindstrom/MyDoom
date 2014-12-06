#ifndef __PATCH_NAMES_LUMP_H
#define __PATCH_NAMES_LUMP_H

#include <stdint.h>

class patch_names_lump
{
public:
  patch_names_lump();
  ~patch_names_lump();

  bool read_from_lump_data(uint8_t const *lump_data);

  uint32_t get_num_patch_names() const { return num_patch_names; }

  char const *get_patch_name_by_num(int num) const;
  uint16_t get_patch_num_by_name(char const *name) const;

private:

  uint32_t num_patch_names;
  char **patch_names;
};

#endif
