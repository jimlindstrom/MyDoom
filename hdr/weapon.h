#ifndef __WEAPON_H
#define __WEAPON_H

#include "sprites.h"

#define WEAPON_STATE_UP		1
#define WEAPON_STATE_DOWN	2
#define WEAPON_STATE_READY	3
#define WEAPON_STATE_ATTACK	4
#define WEAPON_STATE_FLASH	5

class weapon
{
public:
  weapon(char const *sprite_name_up,
         char const *sprite_name_down,
         char const *sprite_name_ready,
         char const *sprite_name_attack,
         char const *sprite_name_flash);

  void draw(void) const;

  int16_t get_ammo(void) const { return ammo; }
  void set_ammo(int16_t a) { ammo = a; }
  void set_state(int s) { state = s; }

private:
  int state;

  sprite_animation *sprite_up;
  sprite_animation *sprite_down;
  sprite_animation *sprite_ready;
  sprite_animation *sprite_attack;
  sprite_animation *sprite_flash;

  sprite const *get_cur_sprite(void) const;

  int16_t ammo;
};

#define NUM_WEAPONS 9

class barehands        : public weapon { public: barehands()        : weapon("PUNG", "PUNG", "PUNG", "PUNG", "PUNG") { }; };
class pistol           : public weapon { public: pistol()           : weapon("PISG", "PISG", "PISG", "PISG", "PISF") { }; };
class shotgun          : public weapon { public: shotgun()          : weapon("SHTG", "SHTG", "SHTG", "SHTG", "SHTF") { }; };
class chaingun         : public weapon { public: chaingun()         : weapon("CHGG", "CHGG", "CHGG", "CHGG", "CHGF") { }; };
class missile_launcher : public weapon { public: missile_launcher() : weapon("MISG", "MISG", "MISG", "MISG", "MISF") { }; };
class plasma_rifle     : public weapon { public: plasma_rifle()     : weapon("PLSG", "PLSG", "PLSG", "PLSG", "PLSF") { }; };
class bfg_9000         : public weapon { public: bfg_9000()         : weapon("BFGG", "BFGG", "BFGG", "BFGG", "BFGF") { }; };
class chainsaw         : public weapon { public: chainsaw()         : weapon("SAWG", "SAWG", "SAWG", "SAWG", "SAWG") { }; };
class super_shotgun    : public weapon { public: super_shotgun()    : weapon("SHT2", "SHT2", "SHT2", "SHT2", "SHT2") { }; };

//FIXME: more...

#endif
