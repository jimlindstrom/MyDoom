#ifndef __PATCH_H
#define __PATCH_H

#include <string.h>
#include <stdint.h>

#include "picture_data.h"

class patch : public picture_data
{
public:
  patch();
  ~patch();

  char const *get_name(void) const { return name; }

  void set_name(char const *_name) { strncpy(name, _name, 8); name[8]=0; }

private:
  char name[9]; // 8 chars + NULL
};

#endif
