#ifndef __WEAPON_H
#define __WEAPON_H

#include "sprites.h"
#include "sprite_state_machine.h"

/******************************************************************************
 * STATES
 ******************************************************************************/

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

#define STATE_CHAINGUN_READY	31
#define STATE_CHAINGUN_DOWN	32
#define STATE_CHAINGUN_UP	33
#define STATE_CHAINGUN_RELOAD1	34
#define STATE_CHAINGUN_RELOAD2	35
#define STATE_CHAINGUN_RELOAD3	36
#define STATE_CHAINGUN_FLASH1	37
#define STATE_CHAINGUN_FLASH2	38

#define STATE_MISSILE_LAUNCHER_READY	39
#define STATE_MISSILE_LAUNCHER_FLASH1	40
#define STATE_MISSILE_LAUNCHER_FLASH2	41
#define STATE_MISSILE_LAUNCHER_FLASH3	42
#define STATE_MISSILE_LAUNCHER_FLASH4	43
#define STATE_MISSILE_LAUNCHER_RELOAD1	44
#define STATE_MISSILE_LAUNCHER_RELOAD2	45
#define STATE_MISSILE_LAUNCHER_RELOAD3	46
#define STATE_MISSILE_LAUNCHER_DOWN	47
#define STATE_MISSILE_LAUNCHER_UP	48

#define STATE_PLASMA_RIFLE_READY	49
#define STATE_PLASMA_RIFLE_DOWN		50
#define STATE_PLASMA_RIFLE_UP		51
#define STATE_PLASMA_RIFLE_RELOAD1	52
#define STATE_PLASMA_RIFLE_RELOAD2	53
#define STATE_PLASMA_RIFLE_FLASH1	54
#define STATE_PLASMA_RIFLE_FLASH2	55

#define STATE_BFG_9000_READY		56
#define STATE_BFG_9000_DOWN		57
#define STATE_BFG_9000_UP		58
#define STATE_BFG_9000_RELOAD1		59
#define STATE_BFG_9000_RELOAD2		60
#define STATE_BFG_9000_RELOAD3		61
#define STATE_BFG_9000_RELOAD4		62
#define STATE_BFG_9000_FLASH1		63
#define STATE_BFG_9000_FLASH2		64

#define STATE_CHAINSAW_READY1		65
#define STATE_CHAINSAW_READY2		66
#define STATE_CHAINSAW_DOWN		67
#define STATE_CHAINSAW_UP		68
#define STATE_CHAINSAW_SAW1		69
#define STATE_CHAINSAW_SAW2		70
#define STATE_CHAINSAW_SAW3		71

#define STATE_SUPER_SHOTGUN_READY	72
#define STATE_SUPER_SHOTGUN_DOWN	73
#define STATE_SUPER_SHOTGUN_UP		74
#define STATE_SUPER_SHOTGUN_GUN1	75
#define STATE_SUPER_SHOTGUN_GUN2	76
#define STATE_SUPER_SHOTGUN_GUN3	77
#define STATE_SUPER_SHOTGUN_GUN4	78
#define STATE_SUPER_SHOTGUN_GUN5	79
#define STATE_SUPER_SHOTGUN_GUN6	80
#define STATE_SUPER_SHOTGUN_GUN7	81
#define STATE_SUPER_SHOTGUN_GUN8	82
#define STATE_SUPER_SHOTGUN_GUN9	83
#define STATE_SUPER_SHOTGUN_GUN10	84
#define STATE_SUPER_SHOTGUN_NR1		85
#define STATE_SUPER_SHOTGUN_NR2		86
#define STATE_SUPER_SHOTGUN_FLASH1	87
#define STATE_SUPER_SHOTGUN_FLASH2	88

/******************************************************************************
 * EVENTS
 ******************************************************************************/

#define EVENT_SPRITE_ANIM_DONE	 1
#define EVENT_WEAPON_FIRE	 2

/******************************************************************************
 * WEAPON CLASSES
 ******************************************************************************/

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

class barehands         : public weapon { public: barehands();        };
class pistol            : public weapon { public: pistol();           };
class shotgun           : public weapon { public: shotgun();          };
class chaingun          : public weapon { public: chaingun();         };
class missile_launcher  : public weapon { public: missile_launcher(); };
class plasma_rifle      : public weapon { public: plasma_rifle();     };
class bfg_9000          : public weapon { public: bfg_9000();         };
class chainsaw          : public weapon { public: chainsaw();         };
class super_shotgun     : public weapon { public: super_shotgun();    };

#define NUM_WEAPONS 9 

#endif
