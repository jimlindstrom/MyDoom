#ifndef __GAME_H
#define __GAME_H

#include <stdint.h>

#include "fps_tracker.h"
#include "episode_map.h"
#include "projector.h"
#include "player.h"

class game
{
public:
  game();
  ~game();

  void set_map(episode_map const *__map) { _map = __map; }
  void set_screen_resolution(int w, int h);

  void init_things(void);

  void do_frame(void);

  void handle_key_down(int key_code);
  void handle_key_up(int key_code);
  void handle_quit(void) { done = true; }

  bool is_done(void) const { return done; }

  uint32_t get_frame_count(void) const { return _fps_tracker.get_frame_count(); }

private:
  bool done;
  int screen_width;
  int screen_height;
  int level;
  episode_map const *_map;
  player _player;

  fps_tracker _fps_tracker;

  void render_player_view(void);
  void render_overhead_map(void);
};

#endif
