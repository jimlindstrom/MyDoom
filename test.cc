#include <stdio.h>

#include "wad_file.h"
#include "palettes.h"
#include "colormaps.h"
#include "flats.h"
#include "sprites.h"

int main(int argc, char **argv)
{
  wad_file w;

  printf("Reading WAD file.\n");
  w.read("data/Doom1.WAD");

  printf("Initializing...\n");
  palettes_init(&w);
  colormaps_init(&w);
  flats_init(&w);
  sprites_init(&w);

  printf("\nSuccess!\n\n");

  printf("Shutting down...\n");
  sprites_destroy();
  flats_destroy();
  colormaps_destroy();
  palettes_destroy();

  return 0;
}
