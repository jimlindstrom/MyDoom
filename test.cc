#include <stdio.h>

#include "wad_file.h"
#include "palettes.h"
#include "colormaps.h"

int main(int argc, char **argv)
{
  wad_file w;

  w.read("data/Doom1.WAD");

  palettes_init(&w);
  colormaps_init(&w);

  printf("\nsuccess!\n");

  return 0;
}
