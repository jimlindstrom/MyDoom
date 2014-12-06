#ifndef __WAD_HEADER_H
#define __WAD_HEADER_H

#include <stdint.h>

class wad_header
{
public:
  wad_header();
  ~wad_header();

  bool read(FILE *f);
  bool is_valid(void);

  char const *get_identification(void) { return identification; }
  int32_t get_num_lumps(void) { return num_lumps; }
  int32_t get_infotableofs(void) { return infotableofs; }

  bool is_iwad(void);
  bool is_pwad(void);

  void print(void);

private:
  char identification[5]; // The ASCII characters "IWAD" or "PWAD". Defines whether the WAD is an IWAD or a PWAD.
  int32_t num_lumps;      // An integer specifying the number of lumps in the WAD.
  int32_t infotableofs;   // An integer holding a pointer to the location of the directory.
};

#endif // #ifndef __WAD_HEADER_H
