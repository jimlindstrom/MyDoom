#include "game.h"
#include "frame_buf.h"
#include "key_codes.h"

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
          _player.set_map_position(cur_thing->get_map_position());
          _player.set_facing_angle(cur_thing->get_facing_angle());
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
  _player.move();

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

void game::handle_key_down(int key_code)
{

  switch(key_code)
  {
    case KEY_RIGHTARROW: _player.set_is_turning_right(true); break;
    case KEY_LEFTARROW:  _player.set_is_turning_left(true); break;
    case KEY_UPARROW:    _player.set_is_moving_forward(true); break;
    case KEY_DOWNARROW:  _player.set_is_moving_backward(true); break;

    case KEY_ESCAPE: break;
    case KEY_ENTER: break;
    case KEY_TAB: break;
    case KEY_F1: break;
    case KEY_F2: break;
    case KEY_F3: break;
    case KEY_F4: break;
    case KEY_F5: break;
    case KEY_F6: break;
    case KEY_F7: break;
    case KEY_F8: break;
    case KEY_F9: break;
    case KEY_F10: break;
    case KEY_F11: break;
    case KEY_F12: break;
    case KEY_BACKSPACE: break;
    case KEY_PAUSE: break;
    case KEY_EQUALS: break;
    case KEY_MINUS: break;
    case KEY_RSHIFT: break;
    case KEY_RCTRL: break;
    case KEY_RALT: break;

    case 'q': handle_quit(); break;

    default: printf("unhandled key: %d ('%c')\n", key_code, key_code); break;
  }
}

void game::handle_key_up(int key_code)
{
  switch(key_code)
  {
    case KEY_RIGHTARROW: _player.set_is_turning_right(false); break;
    case KEY_LEFTARROW:  _player.set_is_turning_left(false); break;
    case KEY_UPARROW:    _player.set_is_moving_forward(false); break;
    case KEY_DOWNARROW:  _player.set_is_moving_backward(false); break;

    case KEY_ESCAPE: break;
    case KEY_ENTER: break;
    case KEY_TAB: break;
    case KEY_F1: break;
    case KEY_F2: break;
    case KEY_F3: break;
    case KEY_F4: break;
    case KEY_F5: break;
    case KEY_F6: break;
    case KEY_F7: break;
    case KEY_F8: break;
    case KEY_F9: break;
    case KEY_F10: break;
    case KEY_F11: break;
    case KEY_F12: break;
    case KEY_BACKSPACE: break;
    case KEY_PAUSE: break;
    case KEY_EQUALS: break;
    case KEY_MINUS: break;
    case KEY_RSHIFT: break;
    case KEY_RCTRL: break;
    case KEY_RALT: break;

    default: break;
  }
}

