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
#include "frame_buf.h"

static int screen_width  = 640;
static int screen_height = 480;

void game_init(void)
{
  wad_file w;

  printf("Reading WAD file.\n");
  w.read("data/Doom1.WAD");

  printf("Initializing...\n");
  if(!palettes_init(&w) || 
     !colormaps_init(&w) || 
     !flats_init(&w) || 
     !sprites_init(&w) || 
     !patches_init(&w) || 
     !wall_textures_init(&w) || 
     !episode_maps_init(&w) || 
     !frame_buf_init(screen_width, screen_height))
  {
    exit(0);
  }
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
  frame_buf_destroy();
}

void game_run(void)
{
  episode_map const *cur_map;

  printf("Running...\n");

  cur_map = episode_maps_get_by_name("E1M1");
  if(!cur_map)
  {
    printf("ERROR: couldn't find map\n");
    return;
  }

  while(1)
  {
    frame_buf_clear();
    cur_map->draw_overhead_map(screen_width, screen_height);
    frame_buf_flush_to_ui();
    usleep(10);
  }
}

