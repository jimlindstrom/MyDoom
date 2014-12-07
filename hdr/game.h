#ifndef __GAME_H
#define __GAME_H

#include "episode_map.h"
#include "player.h"

class game
{
public:
  game();
  ~game();

  void set_map(episode_map const *__map) { _map = __map; }
  void set_screen_resolution(int w, int h) { screen_width = w; screen_height = h; }

  void init_things(void);

  void do_frame(void);

private:
  int screen_width;
  int screen_height;
  int level;
  episode_map const *_map;
  player _player;
};

#endif
