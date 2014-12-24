#include <stdio.h>
#include <math.h>

#include "common.h"
#include "game.h"
#include "frame_buf.h"
#include "key_codes.h"
#include "flats.h"
#include "clipped_segment_projections.h"
#include "vis_things.h"
#include "vis_planes.h"

//#define DEBUG_PRINTING
#include "debug.h"

bool game_custom_start_pos = false;
float game_custom_start_x;
float game_custom_start_y;
float game_custom_start_r;

game::game()
{
  level = 1;
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
    else
    {
      // FIXME: need to make sure this doesn't happen...
    }
  }

  _player.set_weapon(0, new barehands());
  _player.set_weapon(1, new pistol());
  _player.set_weapon(2, new shotgun());
  _player.set_weapon(3, new chaingun());
  _player.set_weapon(4, new missile_launcher());
  _player.set_weapon(5, new plasma_rifle());
  _player.set_weapon(6, new bfg_9000());
  _player.set_weapon(7, new chainsaw());
  _player.set_weapon(8, new super_shotgun());
  _player.select_weapon(2);

  if(game_custom_start_pos)
  {
    vertex v(game_custom_start_x, game_custom_start_y);
    _player.reset_camera(&v, DEG_TO_RAD(game_custom_start_r));
  }
}

void game::do_frame(void)
{
  debug_printf("frame\n");

  flats_animate();
  _player.animate_weapon();
  _map->direct_actors();
  _player.move(_map);

  debug_printf("  player at (%.1f,%.1f,%.1f) facing %.1f\n", 
         _player.get_camera()->get_map_position()->get_x(), 
         _player.get_camera()->get_map_position()->get_y(), 
         _player.get_camera()->get_view_height(),
         RAD_TO_DEG(_player.get_camera()->get_facing_angle()));

  frame_buf_clear();
  render_player_view();
  render_overhead_map();
  frame_buf_flush_to_ui();
  _fps_tracker.tick();
}

void game::render_player_view(void)
{
  clipped_segment_projections clipped_seg_projs;
  vis_planes _vis_planes;
  vis_things _vis_things;

  _map->render_player_view(_player.get_camera(), &clipped_seg_projs, &_vis_planes, &_vis_things);
  _vis_planes.draw_planes( _player.get_camera());
  _vis_things.draw_things( _player.get_camera(), &clipped_seg_projs);
  _player.draw_weapon();
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

void game::handle_key_down(int key_code)
{

  switch(key_code)
  {
    case KEY_RIGHTARROW:_player.set_is_turning_right(true); break;
    case KEY_LEFTARROW:	_player.set_is_turning_left(true); break;
    case KEY_UPARROW:	_player.set_is_moving_forward(true); break;
    case KEY_DOWNARROW:	_player.set_is_moving_backward(true); break;
    case ',':		_player.set_is_strafing_left(true); break;
    case '.':		_player.set_is_strafing_right(true); break;

    case '1': 		_player.select_weapon(0); break;
    case '2': 		_player.select_weapon(1); break;
    case '3': 		_player.select_weapon(2); break;
    case '4': 		_player.select_weapon(3); break;
    case '5': 		_player.select_weapon(4); break;
    case '6': 		_player.select_weapon(5); break;
    case '7': 		_player.select_weapon(6); break;
    case '8': 		_player.select_weapon(7); break;
    case '9': 		_player.select_weapon(8); break;

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
    case KEY_RCTRL: 	_player.fire_weapon(); break;
    case KEY_RALT: break;

    case 'q': handle_quit(); break;

    default: debug_printf("unhandled key: %d ('%c')\n", key_code, key_code); break;
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

