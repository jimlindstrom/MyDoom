#ifndef __GAME_H
#define __GAME_H

#include <sys/time.h>
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

  uint32_t get_frame_count(void) const { return frame_count; }

private:
  bool done;
  int screen_width;
  int screen_height;
  int level;
  episode_map const *_map;
  player _player;
  projector _projector;
  #define FRAME_TIMES_COUNT 50
  struct timeval frame_times[FRAME_TIMES_COUNT];
  int frame_time_idx;
  uint32_t frame_count;

  void track_frames_per_sec(void);
};

#endif
