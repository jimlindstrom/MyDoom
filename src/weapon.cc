#include "weapon.h"
#include "sprites.h"
#include "games.h"
#include "game.h"
#include "projectile.h"
#include "bullet.h"
#include "map_obj_defn_projectiles.h"

/******************************************************************************
 * WEAPON CLASS
 ******************************************************************************/

void weapon::draw(void) const
{
  if(!cur_state) { return; } 

  sprite const *spr = get_cur_sprite(0);
  if(!spr)
  {
    printf("sprite is NULL in state %d\n", cur_state->state_id);
  }

  int16_t h=games_get_screen_height();
  int16_t w=games_get_screen_width();
  float scale = w / 320.0;

  int16_t x = w/2 - (scale*spr->get_width())/2.0;
  int16_t y = (h-1) - (scale*spr->get_height());

  spr->draw(x, y, scale);
}

/******************************************************************************
 * PUNCH
 ******************************************************************************/

static sprite_state_machine_state barehands_states[] = {
  {true, STATE_BAREHANDS_READY,  "PUNG", NULL, 0, 0, 1, EVENT_SPRITE_ANIM_DONE},

  {true, STATE_BAREHANDS_PUNCH1, "PUNG", NULL, 0, 1, 4, EVENT_SPRITE_ANIM_DONE},
  {true, STATE_BAREHANDS_PUNCH2, "PUNG", NULL, 0, 2, 4, EVENT_SPRITE_ANIM_DONE},
  {true, STATE_BAREHANDS_PUNCH3, "PUNG", NULL, 0, 3, 5, EVENT_SPRITE_ANIM_DONE},
  {true, STATE_BAREHANDS_PUNCH4, "PUNG", NULL, 0, 2, 4, EVENT_SPRITE_ANIM_DONE},
  {true, STATE_BAREHANDS_PUNCH5, "PUNG", NULL, 0, 1, 5, EVENT_SPRITE_ANIM_DONE},

  {true, STATE_BAREHANDS_DOWN,   "PUNG", NULL, 0, 0, 1, EVENT_SPRITE_ANIM_DONE},
  {true, STATE_BAREHANDS_UP,     "PUNG", NULL, 0, 0, 1, EVENT_SPRITE_ANIM_DONE},
  {false, 0, "", NULL, 0, 0, 0}
};

static sprite_state_machine_transition barehands_transitions[] = {
  {true, STATE_BAREHANDS_READY,   EVENT_SPRITE_ANIM_DONE, STATE_BAREHANDS_READY},

  /* fire */
  {true, STATE_BAREHANDS_READY,   EVENT_WEAPON_FIRE,      STATE_BAREHANDS_PUNCH1},

  /* don't fire, when not ready */
  {true, STATE_BAREHANDS_PUNCH1,  EVENT_WEAPON_FIRE,      STATE_BAREHANDS_PUNCH1},
  {true, STATE_BAREHANDS_PUNCH2,  EVENT_WEAPON_FIRE,      STATE_BAREHANDS_PUNCH2},
  {true, STATE_BAREHANDS_PUNCH3,  EVENT_WEAPON_FIRE,      STATE_BAREHANDS_PUNCH3},
  {true, STATE_BAREHANDS_PUNCH4,  EVENT_WEAPON_FIRE,      STATE_BAREHANDS_PUNCH4},
  {true, STATE_BAREHANDS_PUNCH5,  EVENT_WEAPON_FIRE,      STATE_BAREHANDS_PUNCH5},
  {true, STATE_BAREHANDS_DOWN,    EVENT_WEAPON_FIRE,      STATE_BAREHANDS_DOWN},
  {true, STATE_BAREHANDS_UP,      EVENT_WEAPON_FIRE,      STATE_BAREHANDS_UP},

  /* punch animation */
  {true, STATE_BAREHANDS_PUNCH1,  EVENT_SPRITE_ANIM_DONE, STATE_BAREHANDS_PUNCH2},
  {true, STATE_BAREHANDS_PUNCH2,  EVENT_SPRITE_ANIM_DONE, STATE_BAREHANDS_PUNCH3},
  {true, STATE_BAREHANDS_PUNCH3,  EVENT_SPRITE_ANIM_DONE, STATE_BAREHANDS_PUNCH4},
  {true, STATE_BAREHANDS_PUNCH4,  EVENT_SPRITE_ANIM_DONE, STATE_BAREHANDS_PUNCH5},
  {true, STATE_BAREHANDS_PUNCH5,  EVENT_SPRITE_ANIM_DONE, STATE_BAREHANDS_READY},

  {true, STATE_BAREHANDS_DOWN,    EVENT_SPRITE_ANIM_DONE, STATE_BAREHANDS_DOWN},
  {true, STATE_BAREHANDS_UP,      EVENT_SPRITE_ANIM_DONE, STATE_BAREHANDS_UP},
  {false, 0, 0, 0}
};

barehands::barehands(game *g) 
: weapon(g, "barehands", STATE_BAREHANDS_READY, barehands_states, barehands_transitions)
{
}

bool barehands::handle_event(int event_id)
{
  bool successful_transition = weapon::handle_event(event_id);
  if(successful_transition && (event_id == EVENT_WEAPON_FIRE))
  {
    printf("FIXME: punch!\n");
  }
  return successful_transition;
}

/******************************************************************************
 * PISTOL
 ******************************************************************************/

static sprite_state_machine_state pistol_states[] = {
  {true, STATE_PISTOL_READY,   "PISG", NULL, 0, 0, 1, EVENT_SPRITE_ANIM_DONE},
  {true, STATE_PISTOL_DOWN,    "PISG", NULL, 0, 0, 1, EVENT_SPRITE_ANIM_DONE},
  {true, STATE_PISTOL_UP,      "PISG", NULL, 0, 0, 1, EVENT_SPRITE_ANIM_DONE},

  {true, STATE_PISTOL_RELOAD1, "PISG", NULL, 0, 0, 4, EVENT_SPRITE_ANIM_DONE},
  {true, STATE_PISTOL_RELOAD2, "PISG", NULL, 0, 1, 6, EVENT_SPRITE_ANIM_DONE},
  {true, STATE_PISTOL_RELOAD3, "PISG", NULL, 0, 2, 4, EVENT_SPRITE_ANIM_DONE},
  {true, STATE_PISTOL_RELOAD4, "PISG", NULL, 0, 1, 5, EVENT_SPRITE_ANIM_DONE},

  {true, STATE_PISTOL_FLASH1,  "PISF", NULL, 1, 0, 7, EVENT_SPRITE_ANIM_DONE},
  {false, 0, "", NULL, 0, 0, 0}
};

static sprite_state_machine_transition pistol_transitions[] = {
  {true, STATE_PISTOL_READY,   EVENT_SPRITE_ANIM_DONE, STATE_PISTOL_READY},

  {true, STATE_PISTOL_READY,   EVENT_WEAPON_FIRE,      STATE_PISTOL_FLASH1},

  {true, STATE_PISTOL_FLASH1,  EVENT_WEAPON_FIRE,      STATE_PISTOL_FLASH1},
  {true, STATE_PISTOL_RELOAD1, EVENT_WEAPON_FIRE,      STATE_PISTOL_RELOAD1},
  {true, STATE_PISTOL_RELOAD2, EVENT_WEAPON_FIRE,      STATE_PISTOL_RELOAD2},
  {true, STATE_PISTOL_RELOAD3, EVENT_WEAPON_FIRE,      STATE_PISTOL_RELOAD3},
  {true, STATE_PISTOL_RELOAD4, EVENT_WEAPON_FIRE,      STATE_PISTOL_RELOAD4},
  {true, STATE_PISTOL_DOWN,    EVENT_WEAPON_FIRE,      STATE_PISTOL_DOWN},
  {true, STATE_PISTOL_UP,      EVENT_WEAPON_FIRE,      STATE_PISTOL_UP},

  {true, STATE_PISTOL_FLASH1,  EVENT_SPRITE_ANIM_DONE, STATE_PISTOL_RELOAD1},
  {true, STATE_PISTOL_RELOAD1, EVENT_SPRITE_ANIM_DONE, STATE_PISTOL_RELOAD2},
  {true, STATE_PISTOL_RELOAD2, EVENT_SPRITE_ANIM_DONE, STATE_PISTOL_RELOAD3},
  {true, STATE_PISTOL_RELOAD3, EVENT_SPRITE_ANIM_DONE, STATE_PISTOL_RELOAD4},
  {true, STATE_PISTOL_RELOAD4, EVENT_SPRITE_ANIM_DONE, STATE_PISTOL_READY},

  {true, STATE_PISTOL_DOWN,    EVENT_SPRITE_ANIM_DONE, STATE_PISTOL_DOWN},
  {true, STATE_PISTOL_UP,      EVENT_SPRITE_ANIM_DONE, STATE_PISTOL_UP},
  {false, 0, 0, 0}
};

pistol::pistol(game *g) 
: weapon(g, "pistol", STATE_PISTOL_READY, pistol_states, pistol_transitions)
{
}

bool pistol::handle_event(int event_id)
{
  bool successful_transition = weapon::handle_event(event_id);
  if(successful_transition && (event_id == EVENT_WEAPON_FIRE))
  {
    map_object *_bullet = new bullet(_game->get_player()->get_camera()->get_map_position(), 
                                     _game->get_player()->get_camera()->get_facing_angle(),
                                     _game->get_player()->get_camera()->get_view_height(),
                                     &tracer_defn, 
                                     _game->get_player()->get_defn()->radius);
    _game->spawn_map_object(_bullet);
  }

  return successful_transition;
}

/******************************************************************************
 * SHOTGUN
 ******************************************************************************/

static sprite_state_machine_state shotgun_states[] = {
  {true, STATE_SHOTGUN_READY,   "SHTG", NULL, 0, 0, 1, EVENT_SPRITE_ANIM_DONE},
  {true, STATE_SHOTGUN_DOWN,    "SHTG", NULL, 0, 0, 1, EVENT_SPRITE_ANIM_DONE},
  {true, STATE_SHOTGUN_UP,      "SHTG", NULL, 0, 0, 1, EVENT_SPRITE_ANIM_DONE},

  {true, STATE_SHOTGUN_RELOAD1, "SHTG", NULL, 0, 0, 3, EVENT_SPRITE_ANIM_DONE},
  {true, STATE_SHOTGUN_RELOAD2, "SHTG", NULL, 0, 0, 7, EVENT_SPRITE_ANIM_DONE},
  {true, STATE_SHOTGUN_RELOAD3, "SHTG", NULL, 0, 1, 5, EVENT_SPRITE_ANIM_DONE},

  {true, STATE_SHOTGUN_RELOAD4, "SHTG", NULL, 0, 2, 5, EVENT_SPRITE_ANIM_DONE},
  {true, STATE_SHOTGUN_RELOAD5, "SHTG", NULL, 0, 3, 4, EVENT_SPRITE_ANIM_DONE},
  {true, STATE_SHOTGUN_RELOAD6, "SHTG", NULL, 0, 2, 5, EVENT_SPRITE_ANIM_DONE},

  {true, STATE_SHOTGUN_RELOAD7, "SHTG", NULL, 0, 1, 5, EVENT_SPRITE_ANIM_DONE},
  {true, STATE_SHOTGUN_RELOAD8, "SHTG", NULL, 0, 0, 3, EVENT_SPRITE_ANIM_DONE},
  {true, STATE_SHOTGUN_RELOAD9, "SHTG", NULL, 0, 0, 7, EVENT_SPRITE_ANIM_DONE},

  {true, STATE_SHOTGUN_FLASH1,  "SHTF", NULL, 1, 0, 4, EVENT_SPRITE_ANIM_DONE},
  {true, STATE_SHOTGUN_FLASH2,  "SHTF", NULL, 1, 1, 3, EVENT_SPRITE_ANIM_DONE},
  {false, 0, "", NULL, 0, 0, 0}
};

static sprite_state_machine_transition shotgun_transitions[] = {
  {true, STATE_SHOTGUN_READY,   EVENT_SPRITE_ANIM_DONE, STATE_SHOTGUN_READY},

  {true, STATE_SHOTGUN_READY,   EVENT_WEAPON_FIRE,      STATE_SHOTGUN_FLASH1},

  {true, STATE_SHOTGUN_FLASH1,  EVENT_WEAPON_FIRE,      STATE_SHOTGUN_FLASH1},
  {true, STATE_SHOTGUN_FLASH2,  EVENT_WEAPON_FIRE,      STATE_SHOTGUN_FLASH2},
  {true, STATE_SHOTGUN_RELOAD1, EVENT_WEAPON_FIRE,      STATE_SHOTGUN_RELOAD1},
  {true, STATE_SHOTGUN_RELOAD2, EVENT_WEAPON_FIRE,      STATE_SHOTGUN_RELOAD2},
  {true, STATE_SHOTGUN_RELOAD3, EVENT_WEAPON_FIRE,      STATE_SHOTGUN_RELOAD3},
  {true, STATE_SHOTGUN_RELOAD4, EVENT_WEAPON_FIRE,      STATE_SHOTGUN_RELOAD4},
  {true, STATE_SHOTGUN_RELOAD5, EVENT_WEAPON_FIRE,      STATE_SHOTGUN_RELOAD5},
  {true, STATE_SHOTGUN_RELOAD6, EVENT_WEAPON_FIRE,      STATE_SHOTGUN_RELOAD6},
  {true, STATE_SHOTGUN_RELOAD7, EVENT_WEAPON_FIRE,      STATE_SHOTGUN_RELOAD7},
  {true, STATE_SHOTGUN_RELOAD8, EVENT_WEAPON_FIRE,      STATE_SHOTGUN_RELOAD8},
  {true, STATE_SHOTGUN_RELOAD9, EVENT_WEAPON_FIRE,      STATE_SHOTGUN_RELOAD9},
  {true, STATE_SHOTGUN_DOWN,    EVENT_WEAPON_FIRE,      STATE_SHOTGUN_DOWN},
  {true, STATE_SHOTGUN_UP,      EVENT_WEAPON_FIRE,      STATE_SHOTGUN_UP},

  {true, STATE_SHOTGUN_FLASH1,  EVENT_SPRITE_ANIM_DONE, STATE_SHOTGUN_FLASH2},
  {true, STATE_SHOTGUN_FLASH2,  EVENT_SPRITE_ANIM_DONE, STATE_SHOTGUN_RELOAD1},

  {true, STATE_SHOTGUN_RELOAD1, EVENT_SPRITE_ANIM_DONE, STATE_SHOTGUN_RELOAD2},
  {true, STATE_SHOTGUN_RELOAD2, EVENT_SPRITE_ANIM_DONE, STATE_SHOTGUN_RELOAD3},
  {true, STATE_SHOTGUN_RELOAD3, EVENT_SPRITE_ANIM_DONE, STATE_SHOTGUN_RELOAD4},

  {true, STATE_SHOTGUN_RELOAD4, EVENT_SPRITE_ANIM_DONE, STATE_SHOTGUN_RELOAD5},
  {true, STATE_SHOTGUN_RELOAD5, EVENT_SPRITE_ANIM_DONE, STATE_SHOTGUN_RELOAD6},
  {true, STATE_SHOTGUN_RELOAD6, EVENT_SPRITE_ANIM_DONE, STATE_SHOTGUN_RELOAD7},

  {true, STATE_SHOTGUN_RELOAD7, EVENT_SPRITE_ANIM_DONE, STATE_SHOTGUN_RELOAD8},
  {true, STATE_SHOTGUN_RELOAD8, EVENT_SPRITE_ANIM_DONE, STATE_SHOTGUN_RELOAD9},
  {true, STATE_SHOTGUN_RELOAD9, EVENT_SPRITE_ANIM_DONE, STATE_SHOTGUN_READY},

  {true, STATE_SHOTGUN_DOWN,    EVENT_SPRITE_ANIM_DONE, STATE_SHOTGUN_DOWN},
  {true, STATE_SHOTGUN_UP,      EVENT_SPRITE_ANIM_DONE, STATE_SHOTGUN_UP},
  {false, 0, 0, 0}
};

shotgun::shotgun(game *g) 
: weapon(g, "shotgun", STATE_SHOTGUN_READY, shotgun_states, shotgun_transitions)
{
}

bool shotgun::handle_event(int event_id)
{
  bool successful_transition = weapon::handle_event(event_id);
  if(successful_transition && (event_id == EVENT_WEAPON_FIRE))
  {
    for(int i=0; i<7; i++)
    {
      map_object *_bullet = new bullet(_game->get_player()->get_camera()->get_map_position(), 
                                       _game->get_player()->get_camera()->get_facing_angle(),
                                       _game->get_player()->get_camera()->get_view_height(),
                                       &tracer_defn, 
                                       _game->get_player()->get_defn()->radius);
      _game->spawn_map_object(_bullet);
    }
  }
  return successful_transition;
}

/******************************************************************************
 * CHAIN GUN
 ******************************************************************************/

static sprite_state_machine_state chaingun_states[] = {
  {true, STATE_CHAINGUN_READY,   "CHGG", NULL, 0, 0, 1, EVENT_SPRITE_ANIM_DONE},
  {true, STATE_CHAINGUN_DOWN,    "CHGG", NULL, 0, 0, 1, EVENT_SPRITE_ANIM_DONE},
  {true, STATE_CHAINGUN_UP,      "CHGG", NULL, 0, 0, 1, EVENT_SPRITE_ANIM_DONE},

  {true, STATE_CHAINGUN_RELOAD1, "CHGG", NULL, 0, 0, 4, EVENT_SPRITE_ANIM_DONE},
  {true, STATE_CHAINGUN_RELOAD2, "CHGG", NULL, 0, 1, 4, EVENT_SPRITE_ANIM_DONE},
  {true, STATE_CHAINGUN_RELOAD3, "CHGG", NULL, 0, 1, 0, EVENT_SPRITE_ANIM_DONE},

  {true, STATE_CHAINGUN_FLASH1,  "CHGF", NULL, 1, 0, 5, EVENT_SPRITE_ANIM_DONE},
  {true, STATE_CHAINGUN_FLASH2,  "CHGF", NULL, 1, 1, 5, EVENT_SPRITE_ANIM_DONE},
  {false, 0, "", NULL, 0, 0, 0}
};

static sprite_state_machine_transition chaingun_transitions[] = {
  {true, STATE_CHAINGUN_READY,   EVENT_SPRITE_ANIM_DONE, STATE_CHAINGUN_READY},

  {true, STATE_CHAINGUN_READY,   EVENT_WEAPON_FIRE,      STATE_CHAINGUN_FLASH1},
  {true, STATE_CHAINGUN_FLASH1,  EVENT_WEAPON_FIRE,      STATE_CHAINGUN_FLASH1},
  {true, STATE_CHAINGUN_FLASH2,  EVENT_WEAPON_FIRE,      STATE_CHAINGUN_FLASH1},
  {true, STATE_CHAINGUN_RELOAD1, EVENT_WEAPON_FIRE,      STATE_CHAINGUN_FLASH1},
  {true, STATE_CHAINGUN_RELOAD2, EVENT_WEAPON_FIRE,      STATE_CHAINGUN_FLASH1},
  {true, STATE_CHAINGUN_RELOAD3, EVENT_WEAPON_FIRE,      STATE_CHAINGUN_FLASH1},

  {true, STATE_CHAINGUN_FLASH1,  EVENT_SPRITE_ANIM_DONE, STATE_CHAINGUN_FLASH2},
  {true, STATE_CHAINGUN_FLASH2,  EVENT_SPRITE_ANIM_DONE, STATE_CHAINGUN_RELOAD1},

  {true, STATE_CHAINGUN_RELOAD1, EVENT_SPRITE_ANIM_DONE, STATE_CHAINGUN_RELOAD2},
  {true, STATE_CHAINGUN_RELOAD2, EVENT_SPRITE_ANIM_DONE, STATE_CHAINGUN_RELOAD3},
  {true, STATE_CHAINGUN_RELOAD3, EVENT_SPRITE_ANIM_DONE, STATE_CHAINGUN_READY},

  {true, STATE_CHAINGUN_DOWN,    EVENT_SPRITE_ANIM_DONE, STATE_CHAINGUN_DOWN},
  {true, STATE_CHAINGUN_UP,      EVENT_SPRITE_ANIM_DONE, STATE_CHAINGUN_UP},
  {false, 0, 0, 0}
};

chaingun::chaingun(game *g) 
: weapon(g, "chaingun", STATE_CHAINGUN_READY, chaingun_states, chaingun_transitions)
{
}

bool chaingun::handle_event(int event_id)
{
  bool successful_transition = weapon::handle_event(event_id);
  if(successful_transition && (event_id == EVENT_WEAPON_FIRE))
  {
    // FIXME: this should fire **continuously**
    map_object *_bullet = new bullet(_game->get_player()->get_camera()->get_map_position(), 
                                     _game->get_player()->get_camera()->get_facing_angle(),
                                     _game->get_player()->get_camera()->get_view_height(),
                                     &tracer_defn, 
                                     _game->get_player()->get_defn()->radius);
    _game->spawn_map_object(_bullet);
  }
  return successful_transition;
}

/******************************************************************************
 * MISSILE LAUNCHER
 ******************************************************************************/

static sprite_state_machine_state missile_launcher_states[] = {
  {true, STATE_MISSILE_LAUNCHER_READY,   "MISG", NULL, 0, 0, 1, EVENT_SPRITE_ANIM_DONE},
  {true, STATE_MISSILE_LAUNCHER_DOWN,    "MISG", NULL, 0, 0, 1, EVENT_SPRITE_ANIM_DONE},
  {true, STATE_MISSILE_LAUNCHER_UP,      "MISG", NULL, 0, 0, 1, EVENT_SPRITE_ANIM_DONE},

  {true, STATE_MISSILE_LAUNCHER_RELOAD1, "MISG", NULL, 0, 1, 8, EVENT_SPRITE_ANIM_DONE},
  {true, STATE_MISSILE_LAUNCHER_RELOAD2, "MISG", NULL, 0, 1,12, EVENT_SPRITE_ANIM_DONE},
  {true, STATE_MISSILE_LAUNCHER_RELOAD3, "MISG", NULL, 0, 1, 1, EVENT_SPRITE_ANIM_DONE},

  {true, STATE_MISSILE_LAUNCHER_FLASH1,  "MISF", NULL, 1, 0, 3, EVENT_SPRITE_ANIM_DONE},
  {true, STATE_MISSILE_LAUNCHER_FLASH2,  "MISF", NULL, 1, 1, 4, EVENT_SPRITE_ANIM_DONE},
  {true, STATE_MISSILE_LAUNCHER_FLASH3,  "MISF", NULL, 1, 2, 4, EVENT_SPRITE_ANIM_DONE},
  {true, STATE_MISSILE_LAUNCHER_FLASH4,  "MISF", NULL, 1, 3, 4, EVENT_SPRITE_ANIM_DONE},
  {false, 0, "", NULL, 0, 0, 0}
};

static sprite_state_machine_transition missile_launcher_transitions[] = {
  {true, STATE_MISSILE_LAUNCHER_READY,   EVENT_SPRITE_ANIM_DONE, STATE_MISSILE_LAUNCHER_READY},

  {true, STATE_MISSILE_LAUNCHER_READY,   EVENT_WEAPON_FIRE,      STATE_MISSILE_LAUNCHER_FLASH1},

  {true, STATE_MISSILE_LAUNCHER_FLASH1,  EVENT_WEAPON_FIRE,      STATE_MISSILE_LAUNCHER_FLASH1},
  {true, STATE_MISSILE_LAUNCHER_FLASH2,  EVENT_WEAPON_FIRE,      STATE_MISSILE_LAUNCHER_FLASH2},
  {true, STATE_MISSILE_LAUNCHER_FLASH3,  EVENT_WEAPON_FIRE,      STATE_MISSILE_LAUNCHER_FLASH3},
  {true, STATE_MISSILE_LAUNCHER_FLASH4,  EVENT_WEAPON_FIRE,      STATE_MISSILE_LAUNCHER_FLASH4},
  {true, STATE_MISSILE_LAUNCHER_RELOAD1, EVENT_WEAPON_FIRE,      STATE_MISSILE_LAUNCHER_RELOAD1},
  {true, STATE_MISSILE_LAUNCHER_RELOAD2, EVENT_WEAPON_FIRE,      STATE_MISSILE_LAUNCHER_RELOAD2},
  {true, STATE_MISSILE_LAUNCHER_RELOAD3, EVENT_WEAPON_FIRE,      STATE_MISSILE_LAUNCHER_RELOAD3},
  {true, STATE_MISSILE_LAUNCHER_DOWN,    EVENT_WEAPON_FIRE,      STATE_MISSILE_LAUNCHER_DOWN},
  {true, STATE_MISSILE_LAUNCHER_UP,      EVENT_WEAPON_FIRE,      STATE_MISSILE_LAUNCHER_UP},

  {true, STATE_MISSILE_LAUNCHER_FLASH1,  EVENT_SPRITE_ANIM_DONE, STATE_MISSILE_LAUNCHER_FLASH2},
  {true, STATE_MISSILE_LAUNCHER_FLASH2,  EVENT_SPRITE_ANIM_DONE, STATE_MISSILE_LAUNCHER_FLASH3},
  {true, STATE_MISSILE_LAUNCHER_FLASH3,  EVENT_SPRITE_ANIM_DONE, STATE_MISSILE_LAUNCHER_FLASH4},
  {true, STATE_MISSILE_LAUNCHER_FLASH4,  EVENT_SPRITE_ANIM_DONE, STATE_MISSILE_LAUNCHER_RELOAD1},

  {true, STATE_MISSILE_LAUNCHER_RELOAD1, EVENT_SPRITE_ANIM_DONE, STATE_MISSILE_LAUNCHER_RELOAD2},
  {true, STATE_MISSILE_LAUNCHER_RELOAD2, EVENT_SPRITE_ANIM_DONE, STATE_MISSILE_LAUNCHER_RELOAD3},
  {true, STATE_MISSILE_LAUNCHER_RELOAD3, EVENT_SPRITE_ANIM_DONE, STATE_MISSILE_LAUNCHER_READY},

  {true, STATE_MISSILE_LAUNCHER_DOWN,    EVENT_SPRITE_ANIM_DONE, STATE_MISSILE_LAUNCHER_DOWN},
  {true, STATE_MISSILE_LAUNCHER_UP,      EVENT_SPRITE_ANIM_DONE, STATE_MISSILE_LAUNCHER_UP},
  {false, 0, 0, 0}
};

missile_launcher::missile_launcher(game *g) 
: weapon(g, "missile_launcher", STATE_MISSILE_LAUNCHER_READY, missile_launcher_states, missile_launcher_transitions)
{
}

bool missile_launcher::handle_event(int event_id)
{
  bool successful_transition = weapon::handle_event(event_id);
  if(successful_transition && (event_id == EVENT_WEAPON_FIRE))
  {
    map_object *missile = new projectile(_game->get_player()->get_camera()->get_map_position(), 
                                         _game->get_player()->get_camera()->get_facing_angle(),
                                         _game->get_player()->get_camera()->get_view_height()-20,
                                         &rocket_defn, 
                                        _game->get_player()->get_defn()->radius);
    _game->spawn_map_object(missile);
  }
  return successful_transition;
}

/******************************************************************************
 * PLASMA RIFLE
 ******************************************************************************/

static sprite_state_machine_state plasma_rifle_states[] = {
  {true, STATE_PLASMA_RIFLE_READY,   "PLSG", NULL, 0, 0, 1, EVENT_SPRITE_ANIM_DONE},
  {true, STATE_PLASMA_RIFLE_DOWN,    "PLSG", NULL, 0, 0, 1, EVENT_SPRITE_ANIM_DONE},
  {true, STATE_PLASMA_RIFLE_UP,      "PLSG", NULL, 0, 0, 1, EVENT_SPRITE_ANIM_DONE},

  {true, STATE_PLASMA_RIFLE_RELOAD1, "PLSG", NULL, 0, 0, 3, EVENT_SPRITE_ANIM_DONE},
  {true, STATE_PLASMA_RIFLE_RELOAD2, "PLSG", NULL, 0, 1,20, EVENT_SPRITE_ANIM_DONE},

  {true, STATE_PLASMA_RIFLE_FLASH1,  "PLSF", NULL, 1, 0, 4, EVENT_SPRITE_ANIM_DONE},
  {true, STATE_PLASMA_RIFLE_FLASH2,  "PLSF", NULL, 1, 1, 4, EVENT_SPRITE_ANIM_DONE},
  {false, 0, "", NULL, 0, 0, 0}
};

static sprite_state_machine_transition plasma_rifle_transitions[] = {
  {true, STATE_PLASMA_RIFLE_READY,   EVENT_SPRITE_ANIM_DONE, STATE_PLASMA_RIFLE_READY},

  {true, STATE_PLASMA_RIFLE_READY,   EVENT_WEAPON_FIRE,      STATE_PLASMA_RIFLE_FLASH1},

  {true, STATE_PLASMA_RIFLE_FLASH1,  EVENT_WEAPON_FIRE,      STATE_PLASMA_RIFLE_FLASH1},
  {true, STATE_PLASMA_RIFLE_FLASH2,  EVENT_WEAPON_FIRE,      STATE_PLASMA_RIFLE_FLASH2},
  {true, STATE_PLASMA_RIFLE_RELOAD1, EVENT_WEAPON_FIRE,      STATE_PLASMA_RIFLE_RELOAD1},
  {true, STATE_PLASMA_RIFLE_RELOAD2, EVENT_WEAPON_FIRE,      STATE_PLASMA_RIFLE_RELOAD2},
  {true, STATE_PLASMA_RIFLE_DOWN,    EVENT_WEAPON_FIRE,      STATE_PLASMA_RIFLE_DOWN},
  {true, STATE_PLASMA_RIFLE_UP,      EVENT_WEAPON_FIRE,      STATE_PLASMA_RIFLE_UP},

  {true, STATE_PLASMA_RIFLE_FLASH1,  EVENT_SPRITE_ANIM_DONE, STATE_PLASMA_RIFLE_FLASH2},
  {true, STATE_PLASMA_RIFLE_FLASH2,  EVENT_SPRITE_ANIM_DONE, STATE_PLASMA_RIFLE_RELOAD1},

  {true, STATE_PLASMA_RIFLE_RELOAD1, EVENT_SPRITE_ANIM_DONE, STATE_PLASMA_RIFLE_RELOAD2},
  {true, STATE_PLASMA_RIFLE_RELOAD2, EVENT_SPRITE_ANIM_DONE, STATE_PLASMA_RIFLE_READY},

  {true, STATE_PLASMA_RIFLE_DOWN,    EVENT_SPRITE_ANIM_DONE, STATE_PLASMA_RIFLE_DOWN},
  {true, STATE_PLASMA_RIFLE_UP,      EVENT_SPRITE_ANIM_DONE, STATE_PLASMA_RIFLE_UP},
  {false, 0, 0, 0}
};

plasma_rifle::plasma_rifle(game *g) 
: weapon(g, "plasma_rifle", STATE_PLASMA_RIFLE_READY, plasma_rifle_states, plasma_rifle_transitions)
{
}

bool plasma_rifle::handle_event(int event_id)
{
  bool successful_transition = weapon::handle_event(event_id);
  if(successful_transition && (event_id == EVENT_WEAPON_FIRE))
  {
    map_object *plasma = new projectile(_game->get_player()->get_camera()->get_map_position(), 
                                        _game->get_player()->get_camera()->get_facing_angle(),
                                        _game->get_player()->get_camera()->get_view_height()-20,
                                        &plasma_defn, 
                                        _game->get_player()->get_defn()->radius);
    _game->spawn_map_object(plasma);
  }
  return successful_transition;
}

/******************************************************************************
 * BFG 9000
 ******************************************************************************/

static sprite_state_machine_state bfg_9000_states[] = {
  {true, STATE_BFG_9000_READY,   "BFGG", NULL, 0, 0, 1, EVENT_SPRITE_ANIM_DONE},
  {true, STATE_BFG_9000_DOWN,    "BFGG", NULL, 0, 0, 1, EVENT_SPRITE_ANIM_DONE},
  {true, STATE_BFG_9000_UP,      "BFGG", NULL, 0, 0, 1, EVENT_SPRITE_ANIM_DONE},

  {true, STATE_BFG_9000_RELOAD1, "BFGG", NULL, 0, 0,20, EVENT_SPRITE_ANIM_DONE},
  {true, STATE_BFG_9000_RELOAD2, "BFGG", NULL, 0, 1,10, EVENT_SPRITE_ANIM_DONE},
  {true, STATE_BFG_9000_RELOAD3, "BFGG", NULL, 0, 1,10, EVENT_SPRITE_ANIM_DONE},
  {true, STATE_BFG_9000_RELOAD4, "BFGG", NULL, 0, 1,20, EVENT_SPRITE_ANIM_DONE},

  {true, STATE_BFG_9000_FLASH1,  "BFGF", NULL, 1, 0,11, EVENT_SPRITE_ANIM_DONE},
  {true, STATE_BFG_9000_FLASH2,  "BFGF", NULL, 1, 1, 6, EVENT_SPRITE_ANIM_DONE},
  {false, 0, "", NULL, 0, 0, 0}
};

static sprite_state_machine_transition bfg_9000_transitions[] = {
  {true, STATE_BFG_9000_READY,   EVENT_SPRITE_ANIM_DONE, STATE_BFG_9000_READY},

  {true, STATE_BFG_9000_READY,   EVENT_WEAPON_FIRE,      STATE_BFG_9000_FLASH1},

  {true, STATE_BFG_9000_FLASH1,  EVENT_WEAPON_FIRE,      STATE_BFG_9000_FLASH1},
  {true, STATE_BFG_9000_FLASH2,  EVENT_WEAPON_FIRE,      STATE_BFG_9000_FLASH2},
  {true, STATE_BFG_9000_RELOAD1, EVENT_WEAPON_FIRE,      STATE_BFG_9000_RELOAD1},
  {true, STATE_BFG_9000_RELOAD2, EVENT_WEAPON_FIRE,      STATE_BFG_9000_RELOAD2},
  {true, STATE_BFG_9000_RELOAD3, EVENT_WEAPON_FIRE,      STATE_BFG_9000_RELOAD3},
  {true, STATE_BFG_9000_RELOAD4, EVENT_WEAPON_FIRE,      STATE_BFG_9000_RELOAD4},
  {true, STATE_BFG_9000_DOWN,    EVENT_WEAPON_FIRE,      STATE_BFG_9000_DOWN},
  {true, STATE_BFG_9000_UP,      EVENT_WEAPON_FIRE,      STATE_BFG_9000_UP},

  {true, STATE_BFG_9000_FLASH1,  EVENT_SPRITE_ANIM_DONE, STATE_BFG_9000_FLASH2},
  {true, STATE_BFG_9000_FLASH2,  EVENT_SPRITE_ANIM_DONE, STATE_BFG_9000_RELOAD1},

  {true, STATE_BFG_9000_RELOAD1, EVENT_SPRITE_ANIM_DONE, STATE_BFG_9000_RELOAD2},
  {true, STATE_BFG_9000_RELOAD2, EVENT_SPRITE_ANIM_DONE, STATE_BFG_9000_RELOAD3},
  {true, STATE_BFG_9000_RELOAD3, EVENT_SPRITE_ANIM_DONE, STATE_BFG_9000_RELOAD4},
  {true, STATE_BFG_9000_RELOAD4, EVENT_SPRITE_ANIM_DONE, STATE_BFG_9000_READY},

  {true, STATE_BFG_9000_DOWN,    EVENT_SPRITE_ANIM_DONE, STATE_BFG_9000_DOWN},
  {true, STATE_BFG_9000_UP,      EVENT_SPRITE_ANIM_DONE, STATE_BFG_9000_UP},
  {false, 0, 0, 0}
};

bfg_9000::bfg_9000(game *g) 
: weapon(g, "bfg_9000", STATE_BFG_9000_READY, bfg_9000_states, bfg_9000_transitions)
{
}

bool bfg_9000::handle_event(int event_id)
{
  bool successful_transition = weapon::handle_event(event_id);
  if(successful_transition && (event_id == EVENT_WEAPON_FIRE))
  {
    map_object *blast = new projectile(_game->get_player()->get_camera()->get_map_position(), 
                                       _game->get_player()->get_camera()->get_facing_angle(),
                                       _game->get_player()->get_camera()->get_view_height()-30,
                                       &bfg_defn, 
                                       _game->get_player()->get_defn()->radius);
    _game->spawn_map_object(blast);
  }
  return successful_transition;
}

/******************************************************************************
 * CHAINSAW
 ******************************************************************************/

static sprite_state_machine_state chainsaw_states[] = {
  {true, STATE_CHAINSAW_READY1,  "SAWG", NULL, 0, 2, 4, EVENT_SPRITE_ANIM_DONE},
  {true, STATE_CHAINSAW_READY2,  "SAWG", NULL, 0, 3, 4, EVENT_SPRITE_ANIM_DONE},

  {true, STATE_CHAINSAW_DOWN,    "SAWG", NULL, 0, 2, 1, EVENT_SPRITE_ANIM_DONE},
  {true, STATE_CHAINSAW_UP,      "SAWG", NULL, 0, 2, 1, EVENT_SPRITE_ANIM_DONE},

  {true, STATE_CHAINSAW_SAW1,    "SAWG", NULL, 0, 0, 4, EVENT_SPRITE_ANIM_DONE},
  {true, STATE_CHAINSAW_SAW2,    "SAWG", NULL, 0, 1, 4, EVENT_SPRITE_ANIM_DONE},
  {true, STATE_CHAINSAW_SAW3,    "SAWG", NULL, 0, 1, 1, EVENT_SPRITE_ANIM_DONE},
  {false, 0, "", NULL, 0, 0, 0}
};

static sprite_state_machine_transition chainsaw_transitions[] = {
  {true, STATE_CHAINSAW_READY1,  EVENT_SPRITE_ANIM_DONE, STATE_CHAINSAW_READY2},
  {true, STATE_CHAINSAW_READY2,  EVENT_SPRITE_ANIM_DONE, STATE_CHAINSAW_READY1},

  {true, STATE_CHAINSAW_READY1,  EVENT_WEAPON_FIRE,      STATE_CHAINSAW_SAW1},
  {true, STATE_CHAINSAW_READY2,  EVENT_WEAPON_FIRE,      STATE_CHAINSAW_SAW1},

  {true, STATE_CHAINSAW_SAW1,    EVENT_WEAPON_FIRE,      STATE_CHAINSAW_SAW1},
  {true, STATE_CHAINSAW_SAW2,    EVENT_WEAPON_FIRE,      STATE_CHAINSAW_SAW2},
  {true, STATE_CHAINSAW_SAW3,    EVENT_WEAPON_FIRE,      STATE_CHAINSAW_SAW3},
  {true, STATE_CHAINSAW_DOWN,    EVENT_WEAPON_FIRE,      STATE_CHAINSAW_DOWN},
  {true, STATE_CHAINSAW_UP,      EVENT_WEAPON_FIRE,      STATE_CHAINSAW_UP},

  {true, STATE_CHAINSAW_SAW1,    EVENT_SPRITE_ANIM_DONE, STATE_CHAINSAW_SAW2},
  {true, STATE_CHAINSAW_SAW2,    EVENT_SPRITE_ANIM_DONE, STATE_CHAINSAW_SAW3},
  {true, STATE_CHAINSAW_SAW3,    EVENT_SPRITE_ANIM_DONE, STATE_CHAINSAW_READY1},

  {true, STATE_CHAINSAW_DOWN,    EVENT_SPRITE_ANIM_DONE, STATE_CHAINSAW_DOWN},
  {true, STATE_CHAINSAW_UP,      EVENT_SPRITE_ANIM_DONE, STATE_CHAINSAW_UP},
  {false, 0, 0, 0}
};

chainsaw::chainsaw(game *g) 
: weapon(g, "chainsaw", STATE_CHAINSAW_READY1, chainsaw_states, chainsaw_transitions)
{
}

bool chainsaw::handle_event(int event_id)
{
  bool successful_transition = weapon::handle_event(event_id);
  if(successful_transition && (event_id == EVENT_WEAPON_FIRE))
  {
    printf("FIXME: saw!\n");
  }
  return successful_transition;
}

/******************************************************************************
 * SUPER SHOTGUN
 ******************************************************************************/

static sprite_state_machine_state super_shotgun_states[] = {
  {true, STATE_SUPER_SHOTGUN_READY,   "SHT2", NULL, 0, 0, 1, EVENT_SPRITE_ANIM_DONE},
  {true, STATE_SUPER_SHOTGUN_DOWN,    "SHT2", NULL, 0, 0, 1, EVENT_SPRITE_ANIM_DONE},
  {true, STATE_SUPER_SHOTGUN_UP,      "SHT2", NULL, 0, 0, 1, EVENT_SPRITE_ANIM_DONE},

  {true, STATE_SUPER_SHOTGUN_GUN1,    "SHT2", NULL, 0, 0, 3, EVENT_SPRITE_ANIM_DONE},
  {true, STATE_SUPER_SHOTGUN_GUN2,    "SHT2", NULL, 0, 0, 7, EVENT_SPRITE_ANIM_DONE},
  {true, STATE_SUPER_SHOTGUN_GUN3,    "SHT2", NULL, 0, 1, 7, EVENT_SPRITE_ANIM_DONE},

  {true, STATE_SUPER_SHOTGUN_GUN4,    "SHT2", NULL, 0, 2, 7, EVENT_SPRITE_ANIM_DONE},
  {true, STATE_SUPER_SHOTGUN_GUN5,    "SHT2", NULL, 0, 3, 7, EVENT_SPRITE_ANIM_DONE},
  {true, STATE_SUPER_SHOTGUN_GUN6,    "SHT2", NULL, 0, 4, 7, EVENT_SPRITE_ANIM_DONE},

  {true, STATE_SUPER_SHOTGUN_GUN7,    "SHT2", NULL, 0, 5, 7, EVENT_SPRITE_ANIM_DONE},
  {true, STATE_SUPER_SHOTGUN_GUN8,    "SHT2", NULL, 0, 6, 6, EVENT_SPRITE_ANIM_DONE},
  {true, STATE_SUPER_SHOTGUN_GUN9,    "SHT2", NULL, 0, 7, 6, EVENT_SPRITE_ANIM_DONE},
  {true, STATE_SUPER_SHOTGUN_GUN10,   "SHT2", NULL, 0, 0, 5, EVENT_SPRITE_ANIM_DONE},

  {true, STATE_SUPER_SHOTGUN_NR1,     "SHT2", NULL, 0, 1, 7, EVENT_SPRITE_ANIM_DONE}, // how do we get here?
  {true, STATE_SUPER_SHOTGUN_NR2,     "SHT2", NULL, 0, 0, 3, EVENT_SPRITE_ANIM_DONE},

  {true, STATE_SUPER_SHOTGUN_FLASH1,  "SHT2", NULL, 1, 8, 5, EVENT_SPRITE_ANIM_DONE},
  {true, STATE_SUPER_SHOTGUN_FLASH2,  "SAWG", NULL, 1, 9, 4, EVENT_SPRITE_ANIM_DONE},
  {false, 0, "", NULL, 0, 0, 0}
};

static sprite_state_machine_transition super_shotgun_transitions[] = {
  {true, STATE_SUPER_SHOTGUN_READY,   EVENT_SPRITE_ANIM_DONE, STATE_SUPER_SHOTGUN_FLASH1},

  {true, STATE_SUPER_SHOTGUN_READY,   EVENT_WEAPON_FIRE,      STATE_SUPER_SHOTGUN_FLASH1},

  {true, STATE_SUPER_SHOTGUN_FLASH1,  EVENT_SPRITE_ANIM_DONE, STATE_SUPER_SHOTGUN_FLASH2},
  {true, STATE_SUPER_SHOTGUN_FLASH2,  EVENT_SPRITE_ANIM_DONE, STATE_SUPER_SHOTGUN_GUN1},

  {true, STATE_SUPER_SHOTGUN_GUN1,    EVENT_SPRITE_ANIM_DONE, STATE_SUPER_SHOTGUN_GUN2},
  {true, STATE_SUPER_SHOTGUN_GUN2,    EVENT_SPRITE_ANIM_DONE, STATE_SUPER_SHOTGUN_GUN3},
  {true, STATE_SUPER_SHOTGUN_GUN3,    EVENT_SPRITE_ANIM_DONE, STATE_SUPER_SHOTGUN_GUN4},

  {true, STATE_SUPER_SHOTGUN_GUN4,    EVENT_SPRITE_ANIM_DONE, STATE_SUPER_SHOTGUN_GUN5},
  {true, STATE_SUPER_SHOTGUN_GUN5,    EVENT_SPRITE_ANIM_DONE, STATE_SUPER_SHOTGUN_GUN6},
  {true, STATE_SUPER_SHOTGUN_GUN6,    EVENT_SPRITE_ANIM_DONE, STATE_SUPER_SHOTGUN_GUN7},

  {true, STATE_SUPER_SHOTGUN_GUN7,    EVENT_SPRITE_ANIM_DONE, STATE_SUPER_SHOTGUN_GUN8},
  {true, STATE_SUPER_SHOTGUN_GUN8,    EVENT_SPRITE_ANIM_DONE, STATE_SUPER_SHOTGUN_GUN9},
  {true, STATE_SUPER_SHOTGUN_GUN9,    EVENT_SPRITE_ANIM_DONE, STATE_SUPER_SHOTGUN_GUN10},
  {true, STATE_SUPER_SHOTGUN_GUN10,   EVENT_SPRITE_ANIM_DONE, STATE_SUPER_SHOTGUN_READY},

  {true, STATE_SUPER_SHOTGUN_NR1,     EVENT_SPRITE_ANIM_DONE, STATE_SUPER_SHOTGUN_NR2},
  {true, STATE_SUPER_SHOTGUN_NR2,     EVENT_SPRITE_ANIM_DONE, STATE_SUPER_SHOTGUN_DOWN},

  {true, STATE_SUPER_SHOTGUN_DOWN,    EVENT_SPRITE_ANIM_DONE, STATE_SUPER_SHOTGUN_DOWN},
  {true, STATE_SUPER_SHOTGUN_UP,      EVENT_SPRITE_ANIM_DONE, STATE_SUPER_SHOTGUN_UP},
  {false, 0, 0, 0}
};

super_shotgun::super_shotgun(game *g) 
: weapon(g, "super_shotgun", STATE_SUPER_SHOTGUN_READY, super_shotgun_states, super_shotgun_transitions)
{
}

bool super_shotgun::handle_event(int event_id)
{
  bool successful_transition = weapon::handle_event(event_id);
  if(successful_transition && (event_id == EVENT_WEAPON_FIRE))
  {
    printf("FIXME: fire!\n");
  }
  return successful_transition;
}

