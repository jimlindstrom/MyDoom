#include "game.h"
#include "frame_buf.h"
#include "key_codes.h"
#include "column_range.h"

game::game()
{
  level = 1;
}

game::~game()
{
  frame_time_idx = 0;
}

void game::set_screen_resolution(int w, int h)
{
  screen_width = w;
  screen_height = h;
  _projector.set_screen_size(w, h);
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

  // ZZZZZZZZ
  vertex test_vertex(813.1,-3325.1);
  _player.set_map_position(&test_vertex);
  _player.set_facing_angle(90);
  // ZZZZZZZZ
}

void game::do_frame(void)
{
  column_range_list col_ranges;
  printf("frame\n");

  _player.move();

  printf("  player at (%.1f,%.1f) facing %d\n", _player.get_map_position()->get_x(), _player.get_map_position()->get_y(), _player.get_facing_angle());

  overhead_map omap;
  bbox map_bbox(10, screen_height-10, 10, screen_width-10);
  omap.set_bbox(&map_bbox);
  omap.set_scale(0.125);
  omap.translate_origin(-190,390);
  omap.draw_bbox();

  frame_buf_clear();
  _map->draw_overhead_map(&omap);
  _player.draw_overhead_map(&omap);
  _map->render_player_view(&col_ranges, &_projector, &_player, &omap);
  frame_buf_flush_to_ui();

  track_frames_per_sec();
}

void game::track_frames_per_sec(void)
{
  double t_cur, t_prev, delta_sec, fps;
  int idx_prev = (frame_time_idx+1)%FRAME_TIMES_COUNT;
  int num_frames = FRAME_TIMES_COUNT - 1;

  gettimeofday(&frame_times[frame_time_idx], NULL);

  t_cur  = frame_times[frame_time_idx].tv_sec + (frame_times[frame_time_idx].tv_usec/1000000.0);
  t_prev = frame_times[idx_prev      ].tv_sec + (frame_times[idx_prev      ].tv_usec/1000000.0);

  delta_sec = t_cur - t_prev;
  if(delta_sec>0.0000001 && delta_sec<1.0)
  {
  fps = (double)num_frames / delta_sec;
  printf("%.2f frames/sec (%d frames in %.6fsec)\n", fps, (FRAME_TIMES_COUNT-1), delta_sec);
  }

  frame_time_idx = ((frame_time_idx+1) % FRAME_TIMES_COUNT);
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

