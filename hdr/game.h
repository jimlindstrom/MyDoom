#ifndef __GAME_H
#define __GAME_H

#include <stdint.h>

#include "fps_tracker.h"
#include "episode_map.h"
#include "projector.h"
#include "player.h"

extern bool game_custom_start_pos;
extern float game_custom_start_x;
extern float game_custom_start_y;
extern float game_custom_start_r;

class game
{
public:
  game();
  ~game();

  void set_map(episode_map *__map) { _map = __map; }
  void set_screen_resolution(int w, int h);

  void init_things(void);

  void do_frame(void);

  void handle_key_down(int key_code);
  void handle_key_up(int key_code);
  void handle_quit(void) { done = true; }

  bool is_done(void) const { return done; }

  uint32_t get_frame_count(void) const { return _fps_tracker.get_frame_count(); }

  void spawn_thing(thing *_thing);
  void kill_thing(thing *_thing);

private:
  bool done;
  int screen_width;
  int screen_height;
  int level;
  episode_map *_map;
  player _player;

  #define MAX_NUM_THINGS 200
  thing *things[MAX_NUM_THINGS];
  int num_things;

  fps_tracker _fps_tracker;

  void render_player_view(void);
  void render_overhead_map(void);
};

#endif
