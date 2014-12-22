#include <stdio.h>
#include <math.h>

#include "common.h"
#include "game.h"
#include "frame_buf.h"
#include "key_codes.h"
#include "column_range_list.h"
#include "vis_things.h"
#include "vis_planes.h"

game::game()
{
  level = 1;
  frame_time_idx = 0;
  frame_count = 0;
}

game::~game()
{
}

void game::set_screen_resolution(int w, int h)
{
  screen_width = w;
  screen_height = h;
  _projector->set_screen_size(w, h);
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
          _player.reset_camera(cur_thing->get_map_position(), cur_thing->get_facing_angle());
          break;
  
        default:
          // ignore
          break;
      }
    }
  }

  #if 0
  vertex v(2873.1,-3068.2);
  _player.reset_camera(&v, DEG_TO_RAD(150.4));
  #endif
}

void game::do_frame(void)
{
  printf("frame\n");

  _player.move(_map);

  printf("  player at (%.1f,%.1f,%.1f) facing %.1f\n", 
         _player.get_camera()->get_map_position()->get_x(), 
         _player.get_camera()->get_map_position()->get_y(), 
         _player.get_camera()->get_view_height(),
         RAD_TO_DEG(_player.get_camera()->get_facing_angle()));

  frame_buf_clear();
  render_player_view();
  render_overhead_map();
  frame_buf_flush_to_ui();
  track_frames_per_sec();
}

void game::render_player_view(void)
{
  column_range_list col_ranges;
  vis_planes _vis_planes;
  vis_things _vis_things;

  _map->render_player_view(_player.get_camera(), &col_ranges, &_vis_planes, &_vis_things);
  _vis_planes.draw_planes( _player.get_camera());
  _vis_things.draw_things( _player.get_camera(), &col_ranges);
}

void game::render_overhead_map(void)
{
  overhead_map omap;

  bbox map_bbox(screen_height-10, screen_height-140, screen_width-200, screen_width-10);
  omap.set_bbox(&map_bbox);
  omap.set_scale(0.040);
  omap.translate_origin(-60,-145);
  omap.darken_background();
  omap.draw_bbox();

  _map->draw_overhead_map(&omap); 
  _player.draw_overhead_map_marker(&omap);
}

void game::track_frames_per_sec(void) // FIXME: move into its own class
{
  double delta_sec, fps;
  int idx_prev = (frame_time_idx+1)%FRAME_TIMES_COUNT;
  int num_frames = FRAME_TIMES_COUNT - 1;

  gettimeofday(&frame_times[frame_time_idx], NULL);

  delta_sec =  (frame_times[frame_time_idx].tv_sec - frame_times[idx_prev].tv_sec) +
              ((frame_times[frame_time_idx].tv_usec- frame_times[idx_prev].tv_usec)/1000000.0);
  if(delta_sec>0.00001 && delta_sec<10.0)
  {
    fps = (double)num_frames / delta_sec;
    printf("%.2f frames/sec (%d frames in %.6fsec)\n", fps, (FRAME_TIMES_COUNT-1), delta_sec);
  }

  frame_time_idx = ((frame_time_idx+1) % FRAME_TIMES_COUNT);
  frame_count++;
}

void game::handle_key_down(int key_code)
{

  switch(key_code)
  {
    case KEY_RIGHTARROW: _player.set_is_turning_right(true); break;
    case KEY_LEFTARROW:  _player.set_is_turning_left(true); break;
    case KEY_UPARROW:    _player.set_is_moving_forward(true); break;
    case KEY_DOWNARROW:  _player.set_is_moving_backward(true); break;
    case ',':            _player.set_is_strafing_left(true); break;
    case '.':            _player.set_is_strafing_right(true); break;

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
    case ',':            _player.set_is_strafing_left(false); break;
    case '.':            _player.set_is_strafing_right(false); break;

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

