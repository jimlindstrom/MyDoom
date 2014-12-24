#include "weapon.h"
#include "sprites.h"
#include "games.h"

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

  {true, STATE_BAREHANDS_READY,   EVENT_WEAPON_FIRE,      STATE_BAREHANDS_PUNCH1},

  {true, STATE_BAREHANDS_PUNCH1,  EVENT_SPRITE_ANIM_DONE, STATE_BAREHANDS_PUNCH2},
  {true, STATE_BAREHANDS_PUNCH2,  EVENT_SPRITE_ANIM_DONE, STATE_BAREHANDS_PUNCH3},
  {true, STATE_BAREHANDS_PUNCH3,  EVENT_SPRITE_ANIM_DONE, STATE_BAREHANDS_PUNCH4},
  {true, STATE_BAREHANDS_PUNCH4,  EVENT_SPRITE_ANIM_DONE, STATE_BAREHANDS_PUNCH5},
  {true, STATE_BAREHANDS_PUNCH5,  EVENT_SPRITE_ANIM_DONE, STATE_BAREHANDS_READY},

  {true, STATE_BAREHANDS_DOWN,    EVENT_SPRITE_ANIM_DONE, STATE_BAREHANDS_DOWN},
  {true, STATE_BAREHANDS_UP,      EVENT_SPRITE_ANIM_DONE, STATE_BAREHANDS_UP},

  {false, 0, 0, 0}
};

barehands::barehands() 
: weapon("barehands", STATE_BAREHANDS_READY, barehands_states, barehands_transitions)
{
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

  {true, STATE_PISTOL_FLASH1,  EVENT_SPRITE_ANIM_DONE, STATE_PISTOL_RELOAD1},

  {true, STATE_PISTOL_RELOAD1, EVENT_SPRITE_ANIM_DONE, STATE_PISTOL_RELOAD2},
  {true, STATE_PISTOL_RELOAD2, EVENT_SPRITE_ANIM_DONE, STATE_PISTOL_RELOAD3},
  {true, STATE_PISTOL_RELOAD3, EVENT_SPRITE_ANIM_DONE, STATE_PISTOL_RELOAD4},
  {true, STATE_PISTOL_RELOAD4, EVENT_SPRITE_ANIM_DONE, STATE_PISTOL_READY},

  {true, STATE_PISTOL_DOWN,    EVENT_SPRITE_ANIM_DONE, STATE_PISTOL_DOWN},
  {true, STATE_PISTOL_UP,      EVENT_SPRITE_ANIM_DONE, STATE_PISTOL_UP},

  {false, 0, 0, 0}
};

pistol::pistol() 
: weapon("pistol", STATE_PISTOL_READY, pistol_states, pistol_transitions)
{
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

shotgun::shotgun() 
: weapon("shotgun", STATE_SHOTGUN_READY, shotgun_states, shotgun_transitions)
{
}

