#ifndef __GAME_H
#define __GAME_H

#include <stdint.h>

#include "fps_tracker.h"
#include "episode_map.h"
#include "projector.h"
#include "player.h"
#include "map_object.h"

extern bool game_custom_start_pos;
extern float game_custom_start_x;
extern float game_custom_start_y;
extern float game_custom_start_r;

#define MAX_NUM_MAP_OBJECTS 200

class game
{
public:
  game();
  ~game();

  void set_map(episode_map *__map) { _map = __map; }
  void set_screen_resolution(int w, int h);

  player const *get_player(void) const { return _player; }

  void init_map_objects(void);

  void do_frame(void);

  void handle_key_down(int key_code);
  void handle_key_up(int key_code);
  void handle_quit(void) { done = true; }

  bool is_done(void) const { return done; }

  uint32_t get_frame_count(void) const { return _fps_tracker.get_frame_count(); }

  void spawn_map_object(map_object *_map_object);
  void kill_map_object(map_object *_map_object);
  int get_num_map_objects(void) const { return num_map_objects; }
  map_object *get_nth_map_object(int n) { return map_objects[n]; }

private:
  void render_player_view(void);
  void render_overhead_map(void);
  void tick_map_objects(void);

  bool         done;
  int          screen_width;
  int          screen_height;
  int          level;
  episode_map *_map;
  player      *_player;
  map_object  *map_objects[MAX_NUM_MAP_OBJECTS];
  int          num_map_objects;
  fps_tracker  _fps_tracker;
};

#endif
