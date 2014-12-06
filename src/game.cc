#include <stdio.h>
#include <unistd.h>

#include "game.h"

#include "wad_file.h"
#include "palettes.h"
#include "colormaps.h"
#include "flats.h"
#include "sprites.h"
#include "patches.h"
#include "wall_textures.h"
#include "episode_maps.h"

void game_init(void)
{
  wad_file w;

  printf("Reading WAD file.\n");
  w.read("data/Doom1.WAD");

  printf("Initializing...\n");
  palettes_init(&w);
  colormaps_init(&w);
  flats_init(&w);
  sprites_init(&w);
  patches_init(&w);
  wall_textures_init(&w);
  episode_maps_init(&w);
  printf("Successfully initialized.\n\n");
}

void game_destroy(void)
{
  printf("\n");
  printf("Shutting down.\n");
  episode_maps_destroy();
  wall_textures_destroy();
  patches_destroy();
  sprites_destroy();
  flats_destroy();
  colormaps_destroy();
  palettes_destroy();
}

void game_run(void)
{
  printf("Running...\n");

  while(1) { sleep(1); }
}

