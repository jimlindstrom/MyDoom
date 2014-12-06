#ifndef __WAD_DIRECTORY_H
#define __WAD_DIRECTORY_H

#include <stdint.h>

class wad_directory
{
public:
  wad_directory();
  ~wad_directory();

  bool read(FILE *f);
  bool is_valid(void);

  bool is_named(char const *_name);

  int32_t get_filepos(void) { return filepos; }
  int32_t get_size(void) { return size; }
  char const *get_name(void) { return name; }

  void print(void);

private:
  int32_t filepos; // An integer holding a pointer to the start of the lump's data in the file.
  int32_t size;    // An integer representing the size of the lump in bytes.
  char    name[9]; // An ASCII string defining the lump's name. Only the characters A-Z (uppercase), 
                   // 0-9, and [ ] - _ should be used in lump names (an exception has to be made for 
                   // some of the Arch-Vile sprites, which use "\"). When a string is less than 8 
                   // bytes long, it should be null-padded to the tight byte.
};

#endif // #ifndef __WAD_DIRECTORY_H
