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

static int16_t screen_width  = 768;
static int16_t screen_height = 480;
static game *cur_game = NULL;
static episode_map *cur_map = NULL;

char wad_filename[100] = "data/Doom1.WAD";

void game_init(void)
{
  wad_file w;

  printf("Reading WAD file.\n");
  w.read(wad_filename);

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

  while(!cur_game->is_done())
  {
    cur_game->do_frame();
    usleep(10);
  }

  delete cur_game;
  cur_game = NULL;
  cur_map = NULL;
}

void game_post_event_key_up(int key_code)
{
  if(cur_game)
  {
    cur_game->handle_key_up(key_code);
  }
}

void game_post_event_key_down(int key_code)
{
  if(cur_game)
  {
    cur_game->handle_key_down(key_code);
  }
}

int16_t games_get_screen_width(void)
{
  return screen_width;
}

int16_t games_get_screen_height(void)
{
  return screen_height;
}

uint32_t games_get_frame_counter(void)
{
  if(cur_game)
  {
    return cur_game->get_frame_count();
  }
  return 0;
}
