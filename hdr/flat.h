#ifndef __FLAT_H
#define __FLAT_H

#include <stdint.h>
#include <string.h>

#include "common.h"
#include "palette.h"

#define FLAT_WIDTH	64
#define FLAT_HEIGHT	64
#define FLAT_NUM_BYTES	(FLAT_WIDTH*FLAT_HEIGHT)

class flat
{
public:
  flat();
  ~flat();

  bool set_data(uint8_t const *_data);
  void print_html_file(char const *filename, palette const *pal);

  uint8_t get_pixel(int x, int y) const;

  void set_name(char const *_name) { strcpy(name, _name); name[8] = 0; }
  char const *get_name(void) const { return name; }

private:
  uint8_t *data;
  char name[9];
};

#define MAX_FLATS_PER_ANIM 8

class flat_animation
{
public:
  flat_animation() { num_flats=0; cur_idx=0; }
  ~flat_animation() { }

  void set_name(char const *_name) { strcpy(name, _name); name[8] = 0; }
  char const *get_name(void) const { return name; }
  int get_num_flats(void) const { return num_flats; }

  bool is_fake_sky(void) const { return (strcasecmp(name, "F_SKY1") == 0); } 

  void increment(void) { cur_idx = (cur_idx + 1) % num_flats; }
  void set_flat(int n, flat const *f) { flats[n] = f; num_flats = MAX(num_flats, n+1); }
  flat const *get_cur_flat(void) const { return flats[cur_idx]; }
  flat const *get_nth_flat(int n) const { return flats[n]; }

private:
  char name[9];

  flat const *flats[MAX_FLATS_PER_ANIM];
  int num_flats;
  int cur_idx;
};

#endif
