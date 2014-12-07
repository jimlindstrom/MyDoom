#include <stdio.h>
#include <unistd.h>

#include "games.h"

#include "wad_file.h"
#include "palettes.h"
#include "colormaps.h"
#include "flats.h"
#include "sprites.h"
#include "patches.h"
#include "wall_textures.h"
#include "episode_maps.h"
#include "frame_buf.h"

#include "game.h"

static int screen_width  = 640;
static int screen_height = 480;
static game *cur_game = NULL;
static episode_map const *cur_map = NULL;

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
  printf("Running...\n");

  cur_map = episode_maps_get_by_name("E1M1");
  if(!cur_map)
  {
    printf("ERROR: couldn't find map\n");
    return;
  }
  cur_game = new game();
  cur_game->set_map(cur_map);
  cur_game->set_screen_resolution(screen_width, screen_height);

  cur_game->init_things();

  while(1)
  {
    cur_game->do_frame();
    usleep(10);
  }

  delete cur_game;
  cur_game = NULL;
  cur_map = NULL;
}
