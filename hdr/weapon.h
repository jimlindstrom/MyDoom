#ifndef __WEAPON_H
#define __WEAPON_H

#include "sprites.h"
#include "sprite_state_machine.h"

#define STATE_SHOTGUN_READY	 1
#define STATE_SHOTGUN_DOWN	 2
#define STATE_SHOTGUN_UP	 3
#define STATE_SHOTGUN_FLASH1	 4
#define STATE_SHOTGUN_FLASH2	 5
#define STATE_SHOTGUN_RELOAD1	 6
#define STATE_SHOTGUN_RELOAD2	 7
#define STATE_SHOTGUN_RELOAD3	 8
#define STATE_SHOTGUN_RELOAD4	 9
#define STATE_SHOTGUN_RELOAD5	10
#define STATE_SHOTGUN_RELOAD6	11
#define STATE_SHOTGUN_RELOAD7	12
#define STATE_SHOTGUN_RELOAD8	13
#define STATE_SHOTGUN_RELOAD9	14

#define STATE_BAREHANDS_READY	15
#define STATE_BAREHANDS_PUNCH1	16
#define STATE_BAREHANDS_PUNCH2	17
#define STATE_BAREHANDS_PUNCH3	18
#define STATE_BAREHANDS_PUNCH4	19
#define STATE_BAREHANDS_PUNCH5	20
#define STATE_BAREHANDS_DOWN	21
#define STATE_BAREHANDS_UP	22

#define STATE_PISTOL_READY	23
#define STATE_PISTOL_UP		24
#define STATE_PISTOL_DOWN	25
#define STATE_PISTOL_FLASH1	26
#define STATE_PISTOL_RELOAD1	27
#define STATE_PISTOL_RELOAD2	28
#define STATE_PISTOL_RELOAD3	29
#define STATE_PISTOL_RELOAD4	30

#define EVENT_SPRITE_ANIM_DONE	 1
#define EVENT_WEAPON_FIRE	 2

class weapon : public sprite_state_machine
{
public:
  weapon(char const *name,
         int initial_state_id,
         sprite_state_machine_state *_states,
         sprite_state_machine_transition *_transitions) 
    : sprite_state_machine(name, initial_state_id, _states,  _transitions) { }
  void draw(void) const;

  int16_t get_ammo(void) const { return ammo; }
  void set_ammo(int16_t a) { ammo = a; }

private:

  int16_t ammo;
};

class barehands : public weapon { public: barehands(); };
class pistol    : public weapon { public: pistol();    };
class shotgun   : public weapon { public: shotgun();   };

#define NUM_WEAPONS 9 // FXIME: why?

#endif
