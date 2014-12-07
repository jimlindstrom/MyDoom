#include "game.h"
#include "frame_buf.h"

game::game()
{
  level = 1;
}

game::~game()
{
}

void game::init_things(void)
{
  int i;
  thing const *cur_thing;

  for(i=0; i<_map->get_num_things(); i++)
  {
    cur_thing = _map->get_nth_thing(i);
    if(cur_thing->is_on_in_level_n(level))
    {
      switch(cur_thing->get_thing_type())
      {
        case THING_PLAYER_1_START_TYPE:
          printf("setting player!\n");
          _player.set_x(cur_thing->get_x());
          _player.set_y(cur_thing->get_y());
          _player.set_facing_angle(cur_thing->get_facing_angle());
          printf("player angle: %d\n", cur_thing->get_facing_angle());
          break;
  
        default:
          // ignore
          break;
      }
    }
  }
}

void game::do_frame(void)
{
  overhead_map omap;
  bbox map_bbox(10, screen_height-10, 10, screen_width-10);
  omap.set_bbox(&map_bbox);
  omap.set_scale(0.125);
  omap.translate_origin(-190,390);
  omap.draw_bbox();

  frame_buf_clear();
  _map->draw_overhead_map(&omap);
  _player.draw_overhead_map(&omap);
  frame_buf_flush_to_ui();
}

