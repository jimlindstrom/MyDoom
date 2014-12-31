#include "map_object.h"

/******************************************************************************
 * MT_FIRE
 ******************************************************************************/

map_obj_state fire_normal_states[] =
{
{true,  STATE_FIRE1,            "FIRE", 0,      2,      1,      "A_StartFire",          STATE_FIRE2,            0,      0},
{true,  STATE_FIRE2,            "FIRE", 1,      2,      1,      "A_Fire",               STATE_FIRE3,            0,      0},
{true,  STATE_FIRE3,            "FIRE", 0,      2,      1,      "A_Fire",               STATE_FIRE4,            0,      0},
{true,  STATE_FIRE4,            "FIRE", 1,      2,      1,      "A_Fire",               STATE_FIRE5,            0,      0},
{true,  STATE_FIRE5,            "FIRE", 2,      2,      1,      "A_FireCrackle",        STATE_FIRE6,            0,      0},
{true,  STATE_FIRE6,            "FIRE", 1,      2,      1,      "A_Fire",               STATE_FIRE7,            0,      0},
{true,  STATE_FIRE7,            "FIRE", 2,      2,      1,      "A_Fire",               STATE_FIRE8,            0,      0},
{true,  STATE_FIRE8,            "FIRE", 1,      2,      1,      "A_Fire",               STATE_FIRE9,            0,      0},
{true,  STATE_FIRE9,            "FIRE", 2,      2,      1,      "A_Fire",               STATE_FIRE10,           0,      0},
{true,  STATE_FIRE10,           "FIRE", 3,      2,      1,      "A_Fire",               STATE_FIRE11,           0,      0},
{true,  STATE_FIRE11,           "FIRE", 2,      2,      1,      "A_Fire",               STATE_FIRE12,           0,      0},
{true,  STATE_FIRE12,           "FIRE", 3,      2,      1,      "A_Fire",               STATE_FIRE13,           0,      0},
{true,  STATE_FIRE13,           "FIRE", 2,      2,      1,      "A_Fire",               STATE_FIRE14,           0,      0},
{true,  STATE_FIRE14,           "FIRE", 3,      2,      1,      "A_Fire",               STATE_FIRE15,           0,      0},
{true,  STATE_FIRE15,           "FIRE", 4,      2,      1,      "A_Fire",               STATE_FIRE16,           0,      0},
{true,  STATE_FIRE16,           "FIRE", 3,      2,      1,      "A_Fire",               STATE_FIRE17,           0,      0},
{true,  STATE_FIRE17,           "FIRE", 4,      2,      1,      "A_Fire",               STATE_FIRE18,           0,      0},
{true,  STATE_FIRE18,           "FIRE", 3,      2,      1,      "A_Fire",               STATE_FIRE19,           0,      0},
{true,  STATE_FIRE19,           "FIRE", 4,      2,      1,      "A_FireCrackle",        STATE_FIRE20,           0,      0},
{true,  STATE_FIRE20,           "FIRE", 5,      2,      1,      "A_Fire",               STATE_FIRE21,           0,      0},
{true,  STATE_FIRE21,           "FIRE", 4,      2,      1,      "A_Fire",               STATE_FIRE22,           0,      0},
{true,  STATE_FIRE22,           "FIRE", 5,      2,      1,      "A_Fire",               STATE_FIRE23,           0,      0},
{true,  STATE_FIRE23,           "FIRE", 4,      2,      1,      "A_Fire",               STATE_FIRE24,           0,      0},
{true,  STATE_FIRE24,           "FIRE", 5,      2,      1,      "A_Fire",               STATE_FIRE25,           0,      0},
{true,  STATE_FIRE25,           "FIRE", 6,      2,      1,      "A_Fire",               STATE_FIRE26,           0,      0},
{true,  STATE_FIRE26,           "FIRE", 7,      2,      1,      "A_Fire",               STATE_FIRE27,           0,      0},
{true,  STATE_FIRE27,           "FIRE", 6,      2,      1,      "A_Fire",               STATE_FIRE28,           0,      0},
{true,  STATE_FIRE28,           "FIRE", 7,      2,      1,      "A_Fire",               STATE_FIRE29,           0,      0},
{true,  STATE_FIRE29,           "FIRE", 6,      2,      1,      "A_Fire",               STATE_FIRE30,           0,      0},
{true,  STATE_FIRE30,           "FIRE", 7,      2,      1,      "A_Fire",               STATE_NULL,             0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_defn fire_defn =
{                       // MT_FIRE
  -1,                   // doomednum
  fire_normal_states,   // spawnstate
  1000,                 // spawnhealth
  NULL,                 // seestate
  //sfx_None,           // seesound
  8,                    // reactiontime
  //sfx_None,           // attacksound
  NULL,                 // painstate
  0,                    // painchance
  //sfx_None,           // painsound
  NULL,                 // meleestate
  NULL,                 // missilestate
  NULL,                 // deathstate
  NULL,                 // xdeathstate
  //sfx_None,           // deathsound
  0,                    // speed
  20,                   // radius
  16,                   // height
  100,                  // mass
  0,                    // damage
  //sfx_None,           // activesound
  MF_NOBLOCKMAP |
  MF_NOGRAVITY,         // flags
  NULL,                 // raisestate
};

/******************************************************************************
 * MT_SMOKE
 ******************************************************************************/

map_obj_state smoke_normal_states[] =
{
{true,  STATE_SMOKE1,           "PUFF", 1,      4,      0,      "",                     STATE_SMOKE2,           0,      0},
{true,  STATE_SMOKE2,           "PUFF", 2,      4,      0,      "",                     STATE_SMOKE3,           0,      0},
{true,  STATE_SMOKE3,           "PUFF", 1,      4,      0,      "",                     STATE_SMOKE4,           0,      0},
{true,  STATE_SMOKE4,           "PUFF", 2,      4,      0,      "",                     STATE_SMOKE5,           0,      0},
{true,  STATE_SMOKE5,           "PUFF", 3,      4,      0,      "",                     STATE_NULL,             0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_defn smoke_defn =
{                       // MT_SMOKE
  -1,                   // doomednum
  smoke_normal_states,  // spawnstate
  1000,                 // spawnhealth
  NULL,                 // seestate
  //sfx_None,           // seesound
  8,                    // reactiontime
  //sfx_None,           // attacksound
  NULL,                 // painstate
  0,                    // painchance
  //sfx_None,           // painsound
  NULL,                 // meleestate
  NULL,                 // missilestate
  NULL,                 // deathstate
  NULL,                 // xdeathstate
  //sfx_None,           // deathsound
  0,                    // speed
  20,                   // radius
  16,                   // height
  100,                  // mass
  0,                    // damage
  //sfx_None,           // activesound
  MF_NOBLOCKMAP |
  MF_NOGRAVITY,         // flags
  NULL,                 // raisestate
};

/******************************************************************************
 * MT_BOSSTARGET
 ******************************************************************************/

map_obj_state bosstarget_normal_states[] =
{
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_defn bosstarget_defn =
{                       // MT_BOSSTARGET
  87,                   // doomednum
  NULL,                 // spawnstate
  1000,                 // spawnhealth
  NULL,                 // seestate
  //sfx_None,           // seesound
  8,                    // reactiontime
  //sfx_None,           // attacksound
  NULL,                 // painstate
  0,                    // painchance
  //sfx_None,           // painsound
  NULL,                 // meleestate
  NULL,                 // missilestate
  NULL,                 // deathstate
  NULL,                 // xdeathstate
  //sfx_None,           // deathsound
  0,                    // speed
  20,                   // radius
  32,                   // height
  100,                  // mass
  0,                    // damage
  //sfx_None,           // activesound
  MF_NOBLOCKMAP |
  MF_NOSECTOR,          // flags
  NULL,                 // raisestate
};

/******************************************************************************
 * MT_BARREL
 ******************************************************************************/

map_obj_state barrel_normal_states[] =
{
{true,  STATE_BAR1,             "BAR1", 0,      6,      0,      "",                     STATE_BAR2,             0,      0},
{true,  STATE_BAR2,             "BAR1", 1,      6,      0,      "",                     STATE_BAR1,             0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_state barrel_die_states[] =
{
{true,  STATE_BEXP,             "BEXP", 0,      5,      1,      "",                     STATE_BEXP2,            0,      0},
{true,  STATE_BEXP2,            "BEXP", 1,      5,      1,      "A_Scream",             STATE_BEXP3,            0,      0},
{true,  STATE_BEXP3,            "BEXP", 2,      5,      1,      "",                     STATE_BEXP4,            0,      0},
{true,  STATE_BEXP4,            "BEXP", 3,      10,     1,      "A_Explode",            STATE_BEXP5,            0,      0},
{true,  STATE_BEXP5,            "BEXP", 4,      10,     1,      "",                     STATE_NULL,             0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_defn barrel_defn =
{                       // MT_BARREL
  2035,                 // doomednum
  barrel_normal_states, // spawnstate
  20,                   // spawnhealth
  NULL,                 // seestate
  //sfx_None,           // seesound
  8,                    // reactiontime
  //sfx_None,           // attacksound
  NULL,                 // painstate
  0,                    // painchance
  //sfx_None,           // painsound
  NULL,                 // meleestate
  NULL,                 // missilestate
  barrel_die_states,    // deathstate
  NULL,                 // xdeathstate
  //sfx_barexp,         // deathsound
  0,                    // speed
  10,                   // radius
  42,                   // height
  100,                  // mass
  0,                    // damage
  //sfx_None,           // activesound
  MF_SOLID |
  MF_SHOOTABLE |
  MF_NOBLOOD,           // flags
  NULL,                 // raisestate
};

/******************************************************************************
 * MT_BLOOD
 ******************************************************************************/

map_obj_state blood_normal_states[] =
{
{true,  STATE_BLOOD1,           "BLUD", 2,      8,      0,      "",                     STATE_BLOOD2,           0,      0},
{true,  STATE_BLOOD2,           "BLUD", 1,      8,      0,      "",                     STATE_BLOOD3,           0,      0},
{true,  STATE_BLOOD3,           "BLUD", 0,      8,      0,      "",                     STATE_NULL,             0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_defn blood_defn =
{                       // MT_BLOOD
  -1,                   // doomednum
  blood_normal_states,  // spawnstate
  1000,                 // spawnhealth
  NULL,                 // seestate
  //sfx_None,           // seesound
  8,                    // reactiontime
  //sfx_None,           // attacksound
  NULL,                 // painstate
  0,                    // painchance
  //sfx_None,           // painsound
  NULL,                 // meleestate
  NULL,                 // missilestate
  NULL,                 // deathstate
  NULL,                 // xdeathstate
  //sfx_None,           // deathsound
  0,                    // speed
  20,                   // radius
  16,                   // height
  100,                  // mass
  0,                    // damage
  //sfx_None,           // activesound
  MF_NOBLOCKMAP,                // flags
  NULL,                 // raisestate
};

/******************************************************************************
 * MT_TFOG
 ******************************************************************************/

map_obj_state tfog_normal_states[] =
{
{true,  STATE_TFOG,             "TFOG", 0,      6,      1,      "",                     STATE_TFOG01,           0,      0},
{true,  STATE_TFOG01,           "TFOG", 1,      6,      1,      "",                     STATE_TFOG02,           0,      0},
{true,  STATE_TFOG02,           "TFOG", 0,      6,      1,      "",                     STATE_TFOG2,            0,      0},
{true,  STATE_TFOG2,            "TFOG", 1,      6,      1,      "",                     STATE_TFOG3,            0,      0},
{true,  STATE_TFOG3,            "TFOG", 2,      6,      1,      "",                     STATE_TFOG4,            0,      0},
{true,  STATE_TFOG4,            "TFOG", 3,      6,      1,      "",                     STATE_TFOG5,            0,      0},
{true,  STATE_TFOG5,            "TFOG", 4,      6,      1,      "",                     STATE_TFOG6,            0,      0},
{true,  STATE_TFOG6,            "TFOG", 5,      6,      1,      "",                     STATE_TFOG7,            0,      0},
{true,  STATE_TFOG7,            "TFOG", 6,      6,      1,      "",                     STATE_TFOG8,            0,      0},
{true,  STATE_TFOG8,            "TFOG", 7,      6,      1,      "",                     STATE_TFOG9,            0,      0},
{true,  STATE_TFOG9,            "TFOG", 8,      6,      1,      "",                     STATE_TFOG10,           0,      0},
{true,  STATE_TFOG10,           "TFOG", 9,      6,      1,      "",                     STATE_NULL,             0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_defn tfog_defn =
{                       // MT_TFOG
  -1,                   // doomednum
  tfog_normal_states,   // spawnstate
  1000,                 // spawnhealth
  NULL,                 // seestate
  //sfx_None,           // seesound
  8,                    // reactiontime
  //sfx_None,           // attacksound
  NULL,                 // painstate
  0,                    // painchance
  //sfx_None,           // painsound
  NULL,                 // meleestate
  NULL,                 // missilestate
  NULL,                 // deathstate
  NULL,                 // xdeathstate
  //sfx_None,           // deathsound
  0,                    // speed
  20,                   // radius
  16,                   // height
  100,                  // mass
  0,                    // damage
  //sfx_None,           // activesound
  MF_NOBLOCKMAP |
  MF_NOGRAVITY,         // flags
  NULL,                 // raisestate
};

/******************************************************************************
 * MT_IFOG
 ******************************************************************************/

map_obj_state ifog_normal_states[] =
{
{true,  STATE_IFOG,             "IFOG", 0,      6,      1,      "",                     STATE_IFOG01,           0,      0},
{true,  STATE_IFOG01,           "IFOG", 1,      6,      1,      "",                     STATE_IFOG02,           0,      0},
{true,  STATE_IFOG02,           "IFOG", 0,      6,      1,      "",                     STATE_IFOG2,            0,      0},
{true,  STATE_IFOG2,            "IFOG", 1,      6,      1,      "",                     STATE_IFOG3,            0,      0},
{true,  STATE_IFOG3,            "IFOG", 2,      6,      1,      "",                     STATE_IFOG4,            0,      0},
{true,  STATE_IFOG4,            "IFOG", 3,      6,      1,      "",                     STATE_IFOG5,            0,      0},
{true,  STATE_IFOG5,            "IFOG", 4,      6,      1,      "",                     STATE_NULL,             0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_defn ifog_defn =
{                       // MT_IFOG
  -1,                   // doomednum
  ifog_normal_states,   // spawnstate
  1000,                 // spawnhealth
  NULL,                 // seestate
  //sfx_None,           // seesound
  8,                    // reactiontime
  //sfx_None,           // attacksound
  NULL,                 // painstate
  0,                    // painchance
  //sfx_None,           // painsound
  NULL,                 // meleestate
  NULL,                 // missilestate
  NULL,                 // deathstate
  NULL,                 // xdeathstate
  //sfx_None,           // deathsound
  0,                    // speed
  20,                   // radius
  16,                   // height
  100,                  // mass
  0,                    // damage
  //sfx_None,           // activesound
  MF_NOBLOCKMAP |
  MF_NOGRAVITY,         // flags
  NULL,                 // raisestate
};

/******************************************************************************
 * MT_TELEPORTMAN
 ******************************************************************************/

map_obj_defn teleportman_defn =
{                       // MT_TELEPORTMAN
  14,                   // doomednum
  NULL,                 // spawnstate
  1000,                 // spawnhealth
  NULL,                 // seestate
  //sfx_None,           // seesound
  8,                    // reactiontime
  //sfx_None,           // attacksound
  NULL,                 // painstate
  0,                    // painchance
  //sfx_None,           // painsound
  NULL,                 // meleestate
  NULL,                 // missilestate
  NULL,                 // deathstate
  NULL,                 // xdeathstate
  //sfx_None,           // deathsound
  0,                    // speed
  20,                   // radius
  16,                   // height
  100,                  // mass
  0,                    // damage
  //sfx_None,           // activesound
  MF_NOBLOCKMAP |
  MF_NOSECTOR,          // flags
  NULL,                 // raisestate
};

/******************************************************************************
 * MT_EXTRABFG
 ******************************************************************************/

map_obj_state extrabfg_normal_states[] =
{
{true,  STATE_BFGEXP,           "BFE2", 0,      8,      1,      "",                     STATE_BFGEXP2,          0,      0},
{true,  STATE_BFGEXP2,          "BFE2", 1,      8,      1,      "",                     STATE_BFGEXP3,          0,      0},
{true,  STATE_BFGEXP3,          "BFE2", 2,      8,      1,      "",                     STATE_BFGEXP4,          0,      0},
{true,  STATE_BFGEXP4,          "BFE2", 3,      8,      1,      "",                     STATE_NULL,             0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_defn extrabfg_defn =
{                       // MT_EXTRABFG
  -1,                   // doomednum
  extrabfg_normal_states,// spawnstate
  1000,                 // spawnhealth
  NULL,                 // seestate
  //sfx_None,           // seesound
  8,                    // reactiontime
  //sfx_None,           // attacksound
  NULL,                 // painstate
  0,                    // painchance
  //sfx_None,           // painsound
  NULL,                 // meleestate
  NULL,                 // missilestate
  NULL,                 // deathstate
  NULL,                 // xdeathstate
  //sfx_None,           // deathsound
  0,                    // speed
  20,                   // radius
  16,                   // height
  100,                  // mass
  0,                    // damage
  //sfx_None,           // activesound
  MF_NOBLOCKMAP |
  MF_NOGRAVITY,         // flags
  NULL,                 // raisestate
};

/******************************************************************************
 * MT_MISC0
 ******************************************************************************/

map_obj_state misc0_normal_states[] =
{
{true,  STATE_ARM1,             "ARM1", 0,      6,      0,      "",                     STATE_ARM1A,            0,      0},
{true,  STATE_ARM1A,            "ARM1", 1,      7,      1,      "",                     STATE_ARM1,             0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_defn misc0_defn =
{                       // MT_MISC0
  2018,                 // doomednum
  misc0_normal_states,  // spawnstate
  1000,                 // spawnhealth
  NULL,                 // seestate
  //sfx_None,           // seesound
  8,                    // reactiontime
  //sfx_None,           // attacksound
  NULL,                 // painstate
  0,                    // painchance
  //sfx_None,           // painsound
  NULL,                 // meleestate
  NULL,                 // missilestate
  NULL,                 // deathstate
  NULL,                 // xdeathstate
  //sfx_None,           // deathsound
  0,                    // speed
  20,                   // radius
  16,                   // height
  100,                  // mass
  0,                    // damage
  //sfx_None,           // activesound
  MF_SPECIAL,           // flags
  NULL,                 // raisestate
};

/******************************************************************************
 * MT_MISC1
 ******************************************************************************/

map_obj_state misc1_normal_states[] =
{
{true,  STATE_ARM2,             "ARM2", 0,      6,      0,      "",                     STATE_ARM2A,            0,      0},
{true,  STATE_ARM2A,            "ARM2", 1,      6,      1,      "",                     STATE_ARM2,             0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_defn misc1_defn =
{                       // MT_MISC1
  2019,                 // doomednum
  misc1_normal_states,  // spawnstate
  1000,                 // spawnhealth
  NULL,                 // seestate
  //sfx_None,           // seesound
  8,                    // reactiontime
  //sfx_None,           // attacksound
  NULL,                 // painstate
  0,                    // painchance
  //sfx_None,           // painsound
  NULL,                 // meleestate
  NULL,                 // missilestate
  NULL,                 // deathstate
  NULL,                 // xdeathstate
  //sfx_None,           // deathsound
  0,                    // speed
  20,                   // radius
  16,                   // height
  100,                  // mass
  0,                    // damage
  //sfx_None,           // activesound
  MF_SPECIAL,           // flags
  NULL,                 // raisestate
};

/******************************************************************************
 * MT_MISC2
 ******************************************************************************/

map_obj_state misc2_normal_states[] =
{
{true,  STATE_BON1,             "BON1", 0,      6,      0,      "",                     STATE_BON1A,            0,      0},
{true,  STATE_BON1A,            "BON1", 1,      6,      0,      "",                     STATE_BON1B,            0,      0},
{true,  STATE_BON1B,            "BON1", 2,      6,      0,      "",                     STATE_BON1C,            0,      0},
{true,  STATE_BON1C,            "BON1", 3,      6,      0,      "",                     STATE_BON1D,            0,      0},
{true,  STATE_BON1D,            "BON1", 2,      6,      0,      "",                     STATE_BON1E,            0,      0},
{true,  STATE_BON1E,            "BON1", 1,      6,      0,      "",                     STATE_BON1,             0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_defn misc2_defn =
{                       // MT_MISC2
  2014,                 // doomednum
  misc2_normal_states,  // spawnstate
  1000,                 // spawnhealth
  NULL,                 // seestate
  //sfx_None,           // seesound
  8,                    // reactiontime
  //sfx_None,           // attacksound
  NULL,                 // painstate
  0,                    // painchance
  //sfx_None,           // painsound
  NULL,                 // meleestate
  NULL,                 // missilestate
  NULL,                 // deathstate
  NULL,                 // xdeathstate
  //sfx_None,           // deathsound
  0,                    // speed
  20,                   // radius
  16,                   // height
  100,                  // mass
  0,                    // damage
  //sfx_None,           // activesound
  MF_SPECIAL |
  MF_COUNTITEM,         // flags
  NULL,                 // raisestate
};

/******************************************************************************
 * MT_MISC3
 ******************************************************************************/

map_obj_state misc3_normal_states[] =
{
{true,  STATE_BON2,             "BON2", 0,      6,      0,      "",                     STATE_BON2A,            0,      0},
{true,  STATE_BON2A,            "BON2", 1,      6,      0,      "",                     STATE_BON2B,            0,      0},
{true,  STATE_BON2B,            "BON2", 2,      6,      0,      "",                     STATE_BON2C,            0,      0},
{true,  STATE_BON2C,            "BON2", 3,      6,      0,      "",                     STATE_BON2D,            0,      0},
{true,  STATE_BON2D,            "BON2", 2,      6,      0,      "",                     STATE_BON2E,            0,      0},
{true,  STATE_BON2E,            "BON2", 1,      6,      0,      "",                     STATE_BON2,             0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_defn misc3_defn =
{                       // MT_MISC3
  2015,                 // doomednum
  misc3_normal_states,  // spawnstate
  1000,                 // spawnhealth
  NULL,                 // seestate
  //sfx_None,           // seesound
  8,                    // reactiontime
  //sfx_None,           // attacksound
  NULL,                 // painstate
  0,                    // painchance
  //sfx_None,           // painsound
  NULL,                 // meleestate
  NULL,                 // missilestate
  NULL,                 // deathstate
  NULL,                 // xdeathstate
  //sfx_None,           // deathsound
  0,                    // speed
  20,                   // radius
  16,                   // height
  100,                  // mass
  0,                    // damage
  //sfx_None,           // activesound
  MF_SPECIAL |
  MF_COUNTITEM,         // flags
  NULL,                 // raisestate
};

/******************************************************************************
 * MT_MISC4
 ******************************************************************************/

map_obj_state misc4_normal_states[] =
{
{true,  STATE_BKEY,             "BKEY", 0,      10,     0,      "",                     STATE_BKEY2,            0,      0},
{true,  STATE_BKEY2,            "BKEY", 1,      10,     1,      "",                     STATE_BKEY,             0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_defn misc4_defn =
{                       // MT_MISC4
  5,                    // doomednum
  misc4_normal_states,  // spawnstate
  1000,                 // spawnhealth
  NULL,                 // seestate
  //sfx_None,           // seesound
  8,                    // reactiontime
  //sfx_None,           // attacksound
  NULL,                 // painstate
  0,                    // painchance
  //sfx_None,           // painsound
  NULL,                 // meleestate
  NULL,                 // missilestate
  NULL,                 // deathstate
  NULL,                 // xdeathstate
  //sfx_None,           // deathsound
  0,                    // speed
  20,                   // radius
  16,                   // height
  100,                  // mass
  0,                    // damage
  //sfx_None,           // activesound
  MF_SPECIAL |
  MF_NOTDMATCH,         // flags
  NULL,                 // raisestate
};

/******************************************************************************
 * MT_MISC5
 ******************************************************************************/

map_obj_state misc5_normal_states[] =
{
{true,  STATE_RKEY,             "RKEY", 0,      10,     0,      "",                     STATE_RKEY2,            0,      0},
{true,  STATE_RKEY2,            "RKEY", 1,      10,     1,      "",                     STATE_RKEY,             0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_defn misc5_defn =
{                       // MT_MISC5
  13,                   // doomednum
  misc5_normal_states,  // spawnstate
  1000,                 // spawnhealth
  NULL,                 // seestate
  //sfx_None,           // seesound
  8,                    // reactiontime
  //sfx_None,           // attacksound
  NULL,                 // painstate
  0,                    // painchance
  //sfx_None,           // painsound
  NULL,                 // meleestate
  NULL,                 // missilestate
  NULL,                 // deathstate
  NULL,                 // xdeathstate
  //sfx_None,           // deathsound
  0,                    // speed
  20,                   // radius
  16,                   // height
  100,                  // mass
  0,                    // damage
  //sfx_None,           // activesound
  MF_SPECIAL |
  MF_NOTDMATCH,         // flags
  NULL,                 // raisestate
};

/******************************************************************************
 * MT_MISC6
 ******************************************************************************/

map_obj_state misc6_normal_states[] =
{
{true,  STATE_YKEY,             "YKEY", 0,      10,     0,      "",                     STATE_YKEY2,            0,      0},
{true,  STATE_YKEY2,            "YKEY", 1,      10,     1,      "",                     STATE_YKEY,             0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_defn misc6_defn =
{                       // MT_MISC6
  6,                    // doomednum
  misc6_normal_states,  // spawnstate
  1000,                 // spawnhealth
  NULL,                 // seestate
  //sfx_None,           // seesound
  8,                    // reactiontime
  //sfx_None,           // attacksound
  NULL,                 // painstate
  0,                    // painchance
  //sfx_None,           // painsound
  NULL,                 // meleestate
  NULL,                 // missilestate
  NULL,                 // deathstate
  NULL,                 // xdeathstate
  //sfx_None,           // deathsound
  0,                    // speed
  20,                   // radius
  16,                   // height
  100,                  // mass
  0,                    // damage
  //sfx_None,           // activesound
  MF_SPECIAL |
  MF_NOTDMATCH,         // flags
  NULL,                 // raisestate
};

/******************************************************************************
 * MT_MISC7
 ******************************************************************************/

map_obj_state misc7_normal_states[] =
{
{true,  STATE_YSKULL,           "YSKU", 0,      10,     0,      "",                     STATE_YSKULL2,          0,      0},
{true,  STATE_YSKULL2,          "YSKU", 1,      10,     1,      "",                     STATE_YSKULL,           0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_defn misc7_defn =
{                       // MT_MISC7
  39,                   // doomednum
  misc7_normal_states,  // spawnstate
  1000,                 // spawnhealth
  NULL,                 // seestate
  //sfx_None,           // seesound
  8,                    // reactiontime
  //sfx_None,           // attacksound
  NULL,                 // painstate
  0,                    // painchance
  //sfx_None,           // painsound
  NULL,                 // meleestate
  NULL,                 // missilestate
  NULL,                 // deathstate
  NULL,                 // xdeathstate
  //sfx_None,           // deathsound
  0,                    // speed
  20,                   // radius
  16,                   // height
  100,                  // mass
  0,                    // damage
  //sfx_None,           // activesound
  MF_SPECIAL |
  MF_NOTDMATCH,         // flags
  NULL,                 // raisestate
};

/******************************************************************************
 * MT_MISC8
 ******************************************************************************/

map_obj_state misc8_normal_states[] =
{
{true,  STATE_RSKULL,           "RSKU", 0,      10,     0,      "",                     STATE_RSKULL2,          0,      0},
{true,  STATE_RSKULL2,          "RSKU", 1,      10,     1,      "",                     STATE_RSKULL,           0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_defn misc8_defn =
{                       // MT_MISC8
  38,                   // doomednum
  misc8_normal_states,  // spawnstate
  1000,                 // spawnhealth
  NULL,                 // seestate
  //sfx_None,           // seesound
  8,                    // reactiontime
  //sfx_None,           // attacksound
  NULL,                 // painstate
  0,                    // painchance
  //sfx_None,           // painsound
  NULL,                 // meleestate
  NULL,                 // missilestate
  NULL,                 // deathstate
  NULL,                 // xdeathstate
  //sfx_None,           // deathsound
  0,                    // speed
  20,                   // radius
  16,                   // height
  100,                  // mass
  0,                    // damage
  //sfx_None,           // activesound
  MF_SPECIAL |
  MF_NOTDMATCH,         // flags
  NULL,                 // raisestate
};

/******************************************************************************
 * MT_MISC9
 ******************************************************************************/

map_obj_state misc9_normal_states[] =
{
{true,  STATE_BSKULL,           "BSKU", 0,      10,     0,      "",                     STATE_BSKULL2,          0,      0},
{true,  STATE_BSKULL2,          "BSKU", 1,      10,     1,      "",                     STATE_BSKULL,           0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_defn misc9_defn =
{                       // MT_MISC9
  40,                   // doomednum
  misc9_normal_states,  // spawnstate
  1000,                 // spawnhealth
  NULL,                 // seestate
  //sfx_None,           // seesound
  8,                    // reactiontime
  //sfx_None,           // attacksound
  NULL,                 // painstate
  0,                    // painchance
  //sfx_None,           // painsound
  NULL,                 // meleestate
  NULL,                 // missilestate
  NULL,                 // deathstate
  NULL,                 // xdeathstate
  //sfx_None,           // deathsound
  0,                    // speed
  20,                   // radius
  16,                   // height
  100,                  // mass
  0,                    // damage
  //sfx_None,           // activesound
  MF_SPECIAL |
  MF_NOTDMATCH,         // flags
  NULL,                 // raisestate
};

/******************************************************************************
 * MT_MISC10
 ******************************************************************************/

map_obj_state misc10_normal_states[] =
{
{true,  STATE_STIM,             "STIM", 0,      -1,     0,      "",                     STATE_NULL,             0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_defn misc10_defn =
{                       // MT_MISC10
  2011,                 // doomednum
  misc10_normal_states, // spawnstate
  1000,                 // spawnhealth
  NULL,                 // seestate
  //sfx_None,           // seesound
  8,                    // reactiontime
  //sfx_None,           // attacksound
  NULL,                 // painstate
  0,                    // painchance
  //sfx_None,           // painsound
  NULL,                 // meleestate
  NULL,                 // missilestate
  NULL,                 // deathstate
  NULL,                 // xdeathstate
  //sfx_None,           // deathsound
  0,                    // speed
  20,                   // radius
  16,                   // height
  100,                  // mass
  0,                    // damage
  //sfx_None,           // activesound
  MF_SPECIAL,           // flags
  NULL,                 // raisestate
};

/******************************************************************************
 * MT_MISC11
 ******************************************************************************/

map_obj_state misc11_normal_states[] =
{
{true,  STATE_MEDI,             "MEDI", 0,      -1,     0,      "",                     STATE_NULL,             0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_defn misc11_defn =
{                       // MT_MISC11
  2012,                 // doomednum
  misc11_normal_states, // spawnstate
  1000,                 // spawnhealth
  NULL,                 // seestate
  //sfx_None,           // seesound
  8,                    // reactiontime
  //sfx_None,           // attacksound
  NULL,                 // painstate
  0,                    // painchance
  //sfx_None,           // painsound
  NULL,                 // meleestate
  NULL,                 // missilestate
  NULL,                 // deathstate
  NULL,                 // xdeathstate
  //sfx_None,           // deathsound
  0,                    // speed
  20,                   // radius
  16,                   // height
  100,                  // mass
  0,                    // damage
  //sfx_None,           // activesound
  MF_SPECIAL,           // flags
  NULL,                 // raisestate
};

/******************************************************************************
 * MT_MISC12
 ******************************************************************************/

map_obj_state misc12_normal_states[] =
{
{true,  STATE_SOUL,             "SOUL", 0,      6,      1,      "",                     STATE_SOUL2,            0,      0},
{true,  STATE_SOUL2,            "SOUL", 1,      6,      1,      "",                     STATE_SOUL3,            0,      0},
{true,  STATE_SOUL3,            "SOUL", 2,      6,      1,      "",                     STATE_SOUL4,            0,      0},
{true,  STATE_SOUL4,            "SOUL", 3,      6,      1,      "",                     STATE_SOUL5,            0,      0},
{true,  STATE_SOUL5,            "SOUL", 2,      6,      1,      "",                     STATE_SOUL6,            0,      0},
{true,  STATE_SOUL6,            "SOUL", 1,      6,      1,      "",                     STATE_SOUL,             0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_defn misc12_defn =
{                       // MT_MISC12
  2013,                 // doomednum
  misc12_normal_states, // spawnstate
  1000,                 // spawnhealth
  NULL,                 // seestate
  //sfx_None,           // seesound
  8,                    // reactiontime
  //sfx_None,           // attacksound
  NULL,                 // painstate
  0,                    // painchance
  //sfx_None,           // painsound
  NULL,                 // meleestate
  NULL,                 // missilestate
  NULL,                 // deathstate
  NULL,                 // xdeathstate
  //sfx_None,           // deathsound
  0,                    // speed
  20,                   // radius
  16,                   // height
  100,                  // mass
  0,                    // damage
  //sfx_None,           // activesound
  MF_SPECIAL |
  MF_COUNTITEM,         // flags
  NULL,                 // raisestate
};

/******************************************************************************
 * MT_INV
 ******************************************************************************/

map_obj_state inv_normal_states[] =
{
{true,  STATE_PINV,             "PINV", 0,      6,      1,      "",                     STATE_PINV2,            0,      0},
{true,  STATE_PINV2,            "PINV", 1,      6,      1,      "",                     STATE_PINV3,            0,      0},
{true,  STATE_PINV3,            "PINV", 2,      6,      1,      "",                     STATE_PINV4,            0,      0},
{true,  STATE_PINV4,            "PINV", 3,      6,      1,      "",                     STATE_PINV,             0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_defn inv_defn =
{                       // MT_INV
  2022,                 // doomednum
  inv_normal_states,    // spawnstate
  1000,                 // spawnhealth
  NULL,                 // seestate
  //sfx_None,           // seesound
  8,                    // reactiontime
  //sfx_None,           // attacksound
  NULL,                 // painstate
  0,                    // painchance
  //sfx_None,           // painsound
  NULL,                 // meleestate
  NULL,                 // missilestate
  NULL,                 // deathstate
  NULL,                 // xdeathstate
  //sfx_None,           // deathsound
  0,                    // speed
  20,                   // radius
  16,                   // height
  100,                  // mass
  0,                    // damage
  //sfx_None,           // activesound
  MF_SPECIAL |
  MF_COUNTITEM,         // flags
  NULL,                 // raisestate
};

/******************************************************************************
 * MT_MISC13
 ******************************************************************************/

map_obj_state misc13_normal_states[] =
{
{true,  STATE_PSTR,             "PSTR", 0,      -1,     1,      "",                     STATE_NULL,             0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_defn misc13_defn =
{                       // MT_MISC13
  2023,                 // doomednum
  misc13_normal_states, // spawnstate
  1000,                 // spawnhealth
  NULL,                 // seestate
  //sfx_None,           // seesound
  8,                    // reactiontime
  //sfx_None,           // attacksound
  NULL,                 // painstate
  0,                    // painchance
  //sfx_None,           // painsound
  NULL,                 // meleestate
  NULL,                 // missilestate
  NULL,                 // deathstate
  NULL,                 // xdeathstate
  //sfx_None,           // deathsound
  0,                    // speed
  20,                   // radius
  16,                   // height
  100,                  // mass
  0,                    // damage
  //sfx_None,           // activesound
  MF_SPECIAL |
  MF_COUNTITEM,         // flags
  NULL,                 // raisestate
};

/******************************************************************************
 * MT_INS
 ******************************************************************************/

map_obj_state ins_normal_states[] =
{
{true,  STATE_PINS,             "PINS", 0,      6,      1,      "",                     STATE_PINS2,            0,      0},
{true,  STATE_PINS2,            "PINS", 1,      6,      1,      "",                     STATE_PINS3,            0,      0},
{true,  STATE_PINS3,            "PINS", 2,      6,      1,      "",                     STATE_PINS4,            0,      0},
{true,  STATE_PINS4,            "PINS", 3,      6,      1,      "",                     STATE_PINS,             0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_defn ins_defn =
{                       // MT_INS
  2024,                 // doomednum
  ins_normal_states,    // spawnstate
  1000,                 // spawnhealth
  NULL,                 // seestate
  //sfx_None,           // seesound
  8,                    // reactiontime
  //sfx_None,           // attacksound
  NULL,                 // painstate
  0,                    // painchance
  //sfx_None,           // painsound
  NULL,                 // meleestate
  NULL,                 // missilestate
  NULL,                 // deathstate
  NULL,                 // xdeathstate
  //sfx_None,           // deathsound
  0,                    // speed
  20,                   // radius
  16,                   // height
  100,                  // mass
  0,                    // damage
  //sfx_None,           // activesound
  MF_SPECIAL |
  MF_COUNTITEM,         // flags
  NULL,                 // raisestate
};

// THINGS BELOW HERE NEED TO BE ADDED TO LIST AT BOTTOM OF FILE

/******************************************************************************
 * MT_MISC14
 ******************************************************************************/

map_obj_state misc14_normal_states[] =
{
{true,  STATE_SUIT,             "SUIT", 0,      -1,     1,      "",                     STATE_NULL,             0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_defn misc14_defn =
{                       // MT_MISC14
  2025,                 // doomednum
  misc14_normal_states, // spawnstate
  1000,                 // spawnhealth
  NULL,                 // seestate
  //sfx_None,           // seesound
  8,                    // reactiontime
  //sfx_None,           // attacksound
  NULL,                 // painstate
  0,                    // painchance
  //sfx_None,           // painsound
  NULL,                 // meleestate
  NULL,                 // missilestate
  NULL,                 // deathstate
  NULL,                 // xdeathstate
  //sfx_None,           // deathsound
  0,                    // speed
  20,                   // radius
  16,                   // height
  100,                  // mass
  0,                    // damage
  //sfx_None,           // activesound
  MF_SPECIAL,           // flags
  NULL                  // raisestate
};

/******************************************************************************
 * MT_MISC15
 ******************************************************************************/

map_obj_state misc15_normal_states[] =
{
{true,  STATE_PMAP,             "PMAP", 0,      6,      1,      "",                     STATE_PMAP2,            0,      0},
{true,  STATE_PMAP2,            "PMAP", 1,      6,      1,      "",                     STATE_PMAP3,            0,      0},
{true,  STATE_PMAP3,            "PMAP", 2,      6,      1,      "",                     STATE_PMAP4,            0,      0},
{true,  STATE_PMAP4,            "PMAP", 3,      6,      1,      "",                     STATE_PMAP5,            0,      0},
{true,  STATE_PMAP5,            "PMAP", 2,      6,      1,      "",                     STATE_PMAP6,            0,      0},
{true,  STATE_PMAP6,            "PMAP", 1,      6,      1,      "",                     STATE_PMAP,             0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_defn misc15_defn =
{                       // MT_MISC15
  2026,                 // doomednum
  misc15_normal_states, // spawnstate
  1000,                 // spawnhealth
  NULL,                 // seestate
  //sfx_None,           // seesound
  8,                    // reactiontime
  //sfx_None,           // attacksound
  NULL,                 // painstate
  0,                    // painchance
  //sfx_None,           // painsound
  NULL,                 // meleestate
  NULL,                 // missilestate
  NULL,                 // deathstate
  NULL,                 // xdeathstate
  //sfx_None,           // deathsound
  0,                    // speed
  20,                   // radius
  16,                   // height
  100,                  // mass
  0,                    // damage
  //sfx_None,           // activesound
  MF_SPECIAL |
  MF_COUNTITEM,         // flags
  NULL                  // raisestate
};

/******************************************************************************
 * MT_MISC16
 ******************************************************************************/

map_obj_state misc16_normal_states[] =
{
{true,  STATE_PVIS,             "PVIS", 0,      6,      1,      "",                     STATE_PVIS2,            0,      0},
{true,  STATE_PVIS2,            "PVIS", 1,      6,      0,      "",                     STATE_PVIS,             0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_defn misc16_defn =
{                       // MT_MISC16
  2045,                 // doomednum
  misc16_normal_states, // spawnstate
  1000,                 // spawnhealth
  NULL,                 // seestate
  //sfx_None,           // seesound
  8,                    // reactiontime
  //sfx_None,           // attacksound
  NULL,                 // painstate
  0,                    // painchance
  //sfx_None,           // painsound
  NULL,                 // meleestate
  NULL,                 // missilestate
  NULL,                 // deathstate
  NULL,                 // xdeathstate
  //sfx_None,           // deathsound
  0,                    // speed
  20,                   // radius
  16,                   // height
  100,                  // mass
  0,                    // damage
  //sfx_None,           // activesound
  MF_SPECIAL |
  MF_COUNTITEM,         // flags
  NULL                  // raisestate
};

/******************************************************************************
 * MT_MEGA
 ******************************************************************************/

map_obj_state mega_normal_states[] =
{
{true,  STATE_MEGA,             "MEGA", 0,      6,      1,      "",                     STATE_MEGA2,            0,      0},
{true,  STATE_MEGA2,            "MEGA", 1,      6,      1,      "",                     STATE_MEGA3,            0,      0},
{true,  STATE_MEGA3,            "MEGA", 2,      6,      1,      "",                     STATE_MEGA4,            0,      0},
{true,  STATE_MEGA4,            "MEGA", 3,      6,      1,      "",                     STATE_MEGA,             0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_defn mega_defn =
{                       // MT_MEGA
  83,                   // doomednum
  mega_normal_states,   // spawnstate
  1000,                 // spawnhealth
  NULL,                 // seestate
  //sfx_None,           // seesound
  8,                    // reactiontime
  //sfx_None,           // attacksound
  NULL,                 // painstate
  0,                    // painchance
  //sfx_None,           // painsound
  NULL,                 // meleestate
  NULL,                 // missilestate
  NULL,                 // deathstate
  NULL,                 // xdeathstate
  //sfx_None,           // deathsound
  0,                    // speed
  20,                   // radius
  16,                   // height
  100,                  // mass
  0,                    // damage
  //sfx_None,           // activesound
  MF_SPECIAL |
  MF_COUNTITEM,         // flags
  NULL                  // raisestate
};

/******************************************************************************
 * MT_CLIP
 ******************************************************************************/

map_obj_state clip_normal_states[] =
{
{true,  STATE_CLIP,             "CLIP", 0,      -1,     0,      "",                     STATE_NULL,             0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_defn clip_defn =
{                       // MT_CLIP
  2007,                 // doomednum
  clip_normal_states,   // spawnstate
  1000,                 // spawnhealth
  NULL,                 // seestate
  //sfx_None,           // seesound
  8,                    // reactiontime
  //sfx_None,           // attacksound
  NULL,                 // painstate
  0,                    // painchance
  //sfx_None,           // painsound
  NULL,                 // meleestate
  NULL,                 // missilestate
  NULL,                 // deathstate
  NULL,                 // xdeathstate
  //sfx_None,           // deathsound
  0,                    // speed
  20,                   // radius
  16,                   // height
  100,                  // mass
  0,                    // damage
  //sfx_None,           // activesound
  MF_SPECIAL,           // flags
  NULL                  // raisestate
};

/******************************************************************************
 * MT_MISC17
 ******************************************************************************/

map_obj_state misc17_normal_states[] =
{
{true,  STATE_AMMO,             "AMMO", 0,      -1,     0,      "",                     STATE_NULL,             0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_defn misc17_defn =
{                       // MT_MISC17
  2048,                 // doomednum
  misc17_normal_states, // spawnstate
  1000,                 // spawnhealth
  NULL,                 // seestate
  //sfx_None,           // seesound
  8,                    // reactiontime
  //sfx_None,           // attacksound
  NULL,                 // painstate
  0,                    // painchance
  //sfx_None,           // painsound
  NULL,                 // meleestate
  NULL,                 // missilestate
  NULL,                 // deathstate
  NULL,                 // xdeathstate
  //sfx_None,           // deathsound
  0,                    // speed
  20,                   // radius
  16,                   // height
  100,                  // mass
  0,                    // damage
  //sfx_None,           // activesound
  MF_SPECIAL,           // flags
  NULL                  // raisestate
};

/******************************************************************************
 * MT_MISC18
 ******************************************************************************/

map_obj_state misc18_normal_states[] =
{
{true,  STATE_ROCK,             "ROCK", 0,      -1,     0,      "",                     STATE_NULL,             0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_defn misc18_defn =
{                       // MT_MISC18
  2010,                 // doomednum
  misc18_normal_states, // spawnstate
  1000,                 // spawnhealth
  NULL,                 // seestate
  //sfx_None,           // seesound
  8,                    // reactiontime
  //sfx_None,           // attacksound
  NULL,                 // painstate
  0,                    // painchance
  //sfx_None,           // painsound
  NULL,                 // meleestate
  NULL,                 // missilestate
  NULL,                 // deathstate
  NULL,                 // xdeathstate
  //sfx_None,           // deathsound
  0,                    // speed
  20,                   // radius
  16,                   // height
  100,                  // mass
  0,                    // damage
  //sfx_None,           // activesound
  MF_SPECIAL,           // flags
  NULL                  // raisestate
};

/******************************************************************************
 * MT_MISC19
 ******************************************************************************/

map_obj_state misc19_normal_states[] =
{
{true,  STATE_BROK,             "BROK", 0,      -1,     0,      "",                     STATE_NULL,             0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_defn misc19_defn =
{                       // MT_MISC19
  2046,                 // doomednum
  misc19_normal_states, // spawnstate
  1000,                 // spawnhealth
  NULL,                 // seestate
  //sfx_None,           // seesound
  8,                    // reactiontime
  //sfx_None,           // attacksound
  NULL,                 // painstate
  0,                    // painchance
  //sfx_None,           // painsound
  NULL,                 // meleestate
  NULL,                 // missilestate
  NULL,                 // deathstate
  NULL,                 // xdeathstate
  //sfx_None,           // deathsound
  0,                    // speed
  20,                   // radius
  16,                   // height
  100,                  // mass
  0,                    // damage
  //sfx_None,           // activesound
  MF_SPECIAL,           // flags
  NULL                  // raisestate
};

/******************************************************************************
 * MT_MISC20
 ******************************************************************************/

map_obj_state misc20_normal_states[] =
{
{true,  STATE_CELL,             "CELL", 0,      -1,     0,      "",                     STATE_NULL,             0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_defn misc20_defn =
{                       // MT_MISC20
  2047,                 // doomednum
  misc20_normal_states, // spawnstate
  1000,                 // spawnhealth
  NULL,                 // seestate
  //sfx_None,           // seesound
  8,                    // reactiontime
  //sfx_None,           // attacksound
  NULL,                 // painstate
  0,                    // painchance
  //sfx_None,           // painsound
  NULL,                 // meleestate
  NULL,                 // missilestate
  NULL,                 // deathstate
  NULL,                 // xdeathstate
  //sfx_None,           // deathsound
  0,                    // speed
  20,                   // radius
  16,                   // height
  100,                  // mass
  0,                    // damage
  //sfx_None,           // activesound
  MF_SPECIAL,           // flags
  NULL                  // raisestate
};

/******************************************************************************
 * MT_MISC21
 ******************************************************************************/

map_obj_state misc21_normal_states[] =
{
{true,  STATE_CELP,             "CELP", 0,      -1,     0,      "",                     STATE_NULL,             0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_defn misc21_defn =
{                       // MT_MISC21
  17,                   // doomednum
  misc21_normal_states, // spawnstate
  1000,                 // spawnhealth
  NULL,                 // seestate
  //sfx_None,           // seesound
  8,                    // reactiontime
  //sfx_None,           // attacksound
  NULL,                 // painstate
  0,                    // painchance
  //sfx_None,           // painsound
  NULL,                 // meleestate
  NULL,                 // missilestate
  NULL,                 // deathstate
  NULL,                 // xdeathstate
  //sfx_None,           // deathsound
  0,                    // speed
  20,                   // radius
  16,                   // height
  100,                  // mass
  0,                    // damage
  //sfx_None,           // activesound
  MF_SPECIAL,           // flags
  NULL                  // raisestate
};

/******************************************************************************
 * MT_MISC22
 ******************************************************************************/

map_obj_state misc22_normal_states[] =
{
{true,  STATE_SHEL,             "SHEL", 0,      -1,     0,      "",                     STATE_NULL,             0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_defn misc22_defn =
{                       // MT_MISC22
  2008,                 // doomednum
  misc22_normal_states, // spawnstate
  1000,                 // spawnhealth
  NULL,                 // seestate
  //sfx_None,           // seesound
  8,                    // reactiontime
  //sfx_None,           // attacksound
  NULL,                 // painstate
  0,                    // painchance
  //sfx_None,           // painsound
  NULL,                 // meleestate
  NULL,                 // missilestate
  NULL,                 // deathstate
  NULL,                 // xdeathstate
  //sfx_None,           // deathsound
  0,                    // speed
  20,                   // radius
  16,                   // height
  100,                  // mass
  0,                    // damage
  //sfx_None,           // activesound
  MF_SPECIAL,           // flags
  NULL                  // raisestate
};

/******************************************************************************
 * MT_MISC23
 ******************************************************************************/

map_obj_state misc23_normal_states[] =
{
{true,  STATE_SBOX,             "SBOX", 0,      -1,     0,      "",                     STATE_NULL,             0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_defn misc23_defn =
{                       // MT_MISC23
  2049,                 // doomednum
  misc23_normal_states, // spawnstate
  1000,                 // spawnhealth
  NULL,                 // seestate
  //sfx_None,           // seesound
  8,                    // reactiontime
  //sfx_None,           // attacksound
  NULL,                 // painstate
  0,                    // painchance
  //sfx_None,           // painsound
  NULL,                 // meleestate
  NULL,                 // missilestate
  NULL,                 // deathstate
  NULL,                 // xdeathstate
  //sfx_None,           // deathsound
  0,                    // speed
  20,                   // radius
  16,                   // height
  100,                  // mass
  0,                    // damage
  //sfx_None,           // activesound
  MF_SPECIAL,           // flags
  NULL                  // raisestate
};

/******************************************************************************
 * MT_MISC24
 ******************************************************************************/

map_obj_state misc24_normal_states[] =
{
{true,  STATE_BPAK,             "BPAK", 0,      -1,     0,      "",                     STATE_NULL,             0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_defn misc24_defn =
{                       // MT_MISC24
  8,                    // doomednum
  misc24_normal_states, // spawnstate
  1000,                 // spawnhealth
  NULL,                 // seestate
  //sfx_None,           // seesound
  8,                    // reactiontime
  //sfx_None,           // attacksound
  NULL,                 // painstate
  0,                    // painchance
  //sfx_None,           // painsound
  NULL,                 // meleestate
  NULL,                 // missilestate
  NULL,                 // deathstate
  NULL,                 // xdeathstate
  //sfx_None,           // deathsound
  0,                    // speed
  20,                   // radius
  16,                   // height
  100,                  // mass
  0,                    // damage
  //sfx_None,           // activesound
  MF_SPECIAL,           // flags
  NULL                  // raisestate
};

/******************************************************************************
 * MT_MISC25
 ******************************************************************************/

map_obj_state misc25_normal_states[] =
{
{true,  STATE_BFUG,             "BFUG", 0,      -1,     0,      "",                     STATE_NULL,             0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_defn misc25_defn =
{                       // MT_MISC25
  2006,                 // doomednum
  misc25_normal_states, // spawnstate
  1000,                 // spawnhealth
  NULL,                 // seestate
  //sfx_None,           // seesound
  8,                    // reactiontime
  //sfx_None,           // attacksound
  NULL,                 // painstate
  0,                    // painchance
  //sfx_None,           // painsound
  NULL,                 // meleestate
  NULL,                 // missilestate
  NULL,                 // deathstate
  NULL,                 // xdeathstate
  //sfx_None,           // deathsound
  0,                    // speed
  20,                   // radius
  16,                   // height
  100,                  // mass
  0,                    // damage
  //sfx_None,           // activesound
  MF_SPECIAL,           // flags
  NULL                  // raisestate
};

/******************************************************************************
 * MT_CHAINGUN
 ******************************************************************************/

map_obj_state chaingun_normal_states[] =
{
{true,  STATE_MGUN,             "MGUN", 0,      -1,     0,      "",                     STATE_NULL,             0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_defn chaingun_defn =
{                       // MT_CHAINGUN
  2002,                 // doomednum
  chaingun_normal_states,// spawnstate
  1000,                 // spawnhealth
  NULL,                 // seestate
  //sfx_None,           // seesound
  8,                    // reactiontime
  //sfx_None,           // attacksound
  NULL,                 // painstate
  0,                    // painchance
  //sfx_None,           // painsound
  NULL,                 // meleestate
  NULL,                 // missilestate
  NULL,                 // deathstate
  NULL,                 // xdeathstate
  //sfx_None,           // deathsound
  0,                    // speed
  20,                   // radius
  16,                   // height
  100,                  // mass
  0,                    // damage
  //sfx_None,           // activesound
  MF_SPECIAL,           // flags
  NULL                  // raisestate
};

/******************************************************************************
 * MT_MISC26
 ******************************************************************************/

map_obj_state misc26_normal_states[] =
{
{true,  STATE_CSAW,             "CSAW", 0,      -1,     0,      "",                     STATE_NULL,             0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_defn misc26_defn =
{                       // MT_MISC26
  2005,                 // doomednum
  misc26_normal_states, // spawnstate
  1000,                 // spawnhealth
  NULL,                 // seestate
  //sfx_None,           // seesound
  8,                    // reactiontime
  //sfx_None,           // attacksound
  NULL,                 // painstate
  0,                    // painchance
  //sfx_None,           // painsound
  NULL,                 // meleestate
  NULL,                 // missilestate
  NULL,                 // deathstate
  NULL,                 // xdeathstate
  //sfx_None,           // deathsound
  0,                    // speed
  20,                   // radius
  16,                   // height
  100,                  // mass
  0,                    // damage
  //sfx_None,           // activesound
  MF_SPECIAL,           // flags
  NULL                  // raisestate
};

/******************************************************************************
 * MT_MISC27
 ******************************************************************************/

map_obj_state misc27_normal_states[] =
{
{true,  STATE_LAUN,             "LAUN", 0,      -1,     0,      "",                     STATE_NULL,             0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_defn misc27_defn =
{                       // MT_MISC27
  2003,                 // doomednum
  misc27_normal_states, // spawnstate
  1000,                 // spawnhealth
  NULL,                 // seestate
  //sfx_None,           // seesound
  8,                    // reactiontime
  //sfx_None,           // attacksound
  NULL,                 // painstate
  0,                    // painchance
  //sfx_None,           // painsound
  NULL,                 // meleestate
  NULL,                 // missilestate
  NULL,                 // deathstate
  NULL,                 // xdeathstate
  //sfx_None,           // deathsound
  0,                    // speed
  20,                   // radius
  16,                   // height
  100,                  // mass
  0,                    // damage
  //sfx_None,           // activesound
  MF_SPECIAL,           // flags
  NULL                  // raisestate
};

/******************************************************************************
 * MT_MISC28
 ******************************************************************************/

map_obj_state misc28_normal_states[] =
{
{true,  STATE_PLAS,             "PLAS", 0,      -1,     0,      "",                     STATE_NULL,             0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_defn misc28_defn =
{                       // MT_MISC28
  2004,                 // doomednum
  misc28_normal_states, // spawnstate
  1000,                 // spawnhealth
  NULL,                 // seestate
  //sfx_None,           // seesound
  8,                    // reactiontime
  //sfx_None,           // attacksound
  NULL,                 // painstate
  0,                    // painchance
  //sfx_None,           // painsound
  NULL,                 // meleestate
  NULL,                 // missilestate
  NULL,                 // deathstate
  NULL,                 // xdeathstate
  //sfx_None,           // deathsound
  0,                    // speed
  20,                   // radius
  16,                   // height
  100,                  // mass
  0,                    // damage
  //sfx_None,           // activesound
  MF_SPECIAL,           // flags
  NULL                  // raisestate
};

/******************************************************************************
 * MT_SHOTGUN
 ******************************************************************************/

map_obj_state shotgun_normal_states[] =
{
{true,  STATE_SHOT,             "SHOT", 0,      -1,     0,      "",                     STATE_NULL,             0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_defn shotgun_defn =
{                       // MT_SHOTGUN
  2001,                 // doomednum
  shotgun_normal_states,// spawnstate
  1000,                 // spawnhealth
  NULL,                 // seestate
  //sfx_None,           // seesound
  8,                    // reactiontime
  //sfx_None,           // attacksound
  NULL,                 // painstate
  0,                    // painchance
  //sfx_None,           // painsound
  NULL,                 // meleestate
  NULL,                 // missilestate
  NULL,                 // deathstate
  NULL,                 // xdeathstate
  //sfx_None,           // deathsound
  0,                    // speed
  20,                   // radius
  16,                   // height
  100,                  // mass
  0,                    // damage
  //sfx_None,           // activesound
  MF_SPECIAL,           // flags
  NULL                  // raisestate
};

/******************************************************************************
 * MT_SUPERSHOTGUN
 ******************************************************************************/

map_obj_state supershotgun_normal_states[] =
{
{true,  STATE_SHOT2,            "SGN2", 0,      -1,     0,      "",                     STATE_NULL,             0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_defn supershotgun_defn =
{                       // MT_SUPERSHOTGUN
  82,                   // doomednum
  supershotgun_normal_states,// spawnstate
  1000,                 // spawnhealth
  NULL,                 // seestate
  //sfx_None,           // seesound
  8,                    // reactiontime
  //sfx_None,           // attacksound
  NULL,                 // painstate
  0,                    // painchance
  //sfx_None,           // painsound
  NULL,                 // meleestate
  NULL,                 // missilestate
  NULL,                 // deathstate
  NULL,                 // xdeathstate
  //sfx_None,           // deathsound
  0,                    // speed
  20,                   // radius
  16,                   // height
  100,                  // mass
  0,                    // damage
  //sfx_None,           // activesound
  MF_SPECIAL,           // flags
  NULL                  // raisestate
};

/******************************************************************************
 * MT_MISC29
 ******************************************************************************/

map_obj_state misc29_normal_states[] =
{
{true,  STATE_TECHLAMP,         "TLMP", 0,      4,      1,      "",                     STATE_TECHLAMP2,        0,      0},
{true,  STATE_TECHLAMP2,        "TLMP", 1,      4,      1,      "",                     STATE_TECHLAMP3,        0,      0},
{true,  STATE_TECHLAMP3,        "TLMP", 2,      4,      1,      "",                     STATE_TECHLAMP4,        0,      0},
{true,  STATE_TECHLAMP4,        "TLMP", 3,      4,      1,      "",                     STATE_TECHLAMP,         0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_defn misc29_defn =
{                       // MT_MISC29
  85,                   // doomednum
  misc29_normal_states, // spawnstate
  1000,                 // spawnhealth
  NULL,                 // seestate
  //sfx_None,           // seesound
  8,                    // reactiontime
  //sfx_None,           // attacksound
  NULL,                 // painstate
  0,                    // painchance
  //sfx_None,           // painsound
  NULL,                 // meleestate
  NULL,                 // missilestate
  NULL,                 // deathstate
  NULL,                 // xdeathstate
  //sfx_None,           // deathsound
  0,                    // speed
  16,                   // radius
  16,                   // height
  100,                  // mass
  0,                    // damage
  //sfx_None,           // activesound
  MF_SOLID,             // flags
  NULL                  // raisestate
};

/******************************************************************************
 * MT_MISC30
 ******************************************************************************/

map_obj_state misc30_normal_states[] =
{
{true,  STATE_TECH2LAMP,        "TLP2", 0,      4,      1,      "",                     STATE_TECH2LAMP2,       0,      0},
{true,  STATE_TECH2LAMP2,       "TLP2", 1,      4,      1,      "",                     STATE_TECH2LAMP3,       0,      0},
{true,  STATE_TECH2LAMP3,       "TLP2", 2,      4,      1,      "",                     STATE_TECH2LAMP4,       0,      0},
{true,  STATE_TECH2LAMP4,       "TLP2", 3,      4,      1,      "",                     STATE_TECH2LAMP,        0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_defn misc30_defn =
{                       // MT_MISC30
  86,                   // doomednum
  misc30_normal_states, // spawnstate
  1000,                 // spawnhealth
  NULL,                 // seestate
  //sfx_None,           // seesound
  8,                    // reactiontime
  //sfx_None,           // attacksound
  NULL,                 // painstate
  0,                    // painchance
  //sfx_None,           // painsound
  NULL,                 // meleestate
  NULL,                 // missilestate
  NULL,                 // deathstate
  NULL,                 // xdeathstate
  //sfx_None,           // deathsound
  0,                    // speed
  16,                   // radius
  16,                   // height
  100,                  // mass
  0,                    // damage
  //sfx_None,           // activesound
  MF_SOLID,             // flags
  NULL                  // raisestate
};

/******************************************************************************
 * MT_MISC31
 ******************************************************************************/

map_obj_state misc31_normal_states[] =
{
{true,  STATE_COLU,             "COLU", 0,      -1,     1,      "",                     STATE_NULL,             0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_defn misc31_defn =
{                       // MT_MISC31
  2028,                 // doomednum
  misc31_normal_states, // spawnstate
  1000,                 // spawnhealth
  NULL,                 // seestate
  //sfx_None,           // seesound
  8,                    // reactiontime
  //sfx_None,           // attacksound
  NULL,                 // painstate
  0,                    // painchance
  //sfx_None,           // painsound
  NULL,                 // meleestate
  NULL,                 // missilestate
  NULL,                 // deathstate
  NULL,                 // xdeathstate
  //sfx_None,           // deathsound
  0,                    // speed
  16,                   // radius
  16,                   // height
  100,                  // mass
  0,                    // damage
  //sfx_None,           // activesound
  MF_SOLID,             // flags
  NULL                  // raisestate
};

/******************************************************************************
 * MT_MISC32
 ******************************************************************************/

map_obj_state misc32_normal_states[] =
{
{true,  STATE_TALLGRNCOL,       "COL1", 0,      -1,     0,      "",                     STATE_NULL,             0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_defn misc32_defn =
{                       // MT_MISC32
  30,                   // doomednum
  misc32_normal_states, // spawnstate
  1000,                 // spawnhealth
  NULL,                 // seestate
  //sfx_None,           // seesound
  8,                    // reactiontime
  //sfx_None,           // attacksound
  NULL,                 // painstate
  0,                    // painchance
  //sfx_None,           // painsound
  NULL,                 // meleestate
  NULL,                 // missilestate
  NULL,                 // deathstate
  NULL,                 // xdeathstate
  //sfx_None,           // deathsound
  0,                    // speed
  16,                   // radius
  16,                   // height
  100,                  // mass
  0,                    // damage
  //sfx_None,           // activesound
  MF_SOLID,             // flags
  NULL                  // raisestate
};

/******************************************************************************
 * MT_MISC33
 ******************************************************************************/

map_obj_state misc33_normal_states[] =
{
{true,  STATE_SHRTGRNCOL,       "COL2", 0,      -1,     0,      "",                     STATE_NULL,             0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_defn misc33_defn =
{                       // MT_MISC33
  31,                   // doomednum
  misc33_normal_states, // spawnstate
  1000,                 // spawnhealth
  NULL,                 // seestate
  //sfx_None,           // seesound
  8,                    // reactiontime
  //sfx_None,           // attacksound
  NULL,                 // painstate
  0,                    // painchance
  //sfx_None,           // painsound
  NULL,                 // meleestate
  NULL,                 // missilestate
  NULL,                 // deathstate
  NULL,                 // xdeathstate
  //sfx_None,           // deathsound
  0,                    // speed
  16,                   // radius
  16,                   // height
  100,                  // mass
  0,                    // damage
  //sfx_None,           // activesound
  MF_SOLID,             // flags
  NULL                  // raisestate
};

/******************************************************************************
 * MT_MISC34
 ******************************************************************************/

map_obj_state misc34_normal_states[] =
{
{true,  STATE_TALLREDCOL,       "COL3", 0,      -1,     0,      "",                     STATE_NULL,             0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_defn misc34_defn =
{                       // MT_MISC34
  32,                   // doomednum
  misc34_normal_states, // spawnstate
  1000,                 // spawnhealth
  NULL,                 // seestate
  //sfx_None,           // seesound
  8,                    // reactiontime
  //sfx_None,           // attacksound
  NULL,                 // painstate
  0,                    // painchance
  //sfx_None,           // painsound
  NULL,                 // meleestate
  NULL,                 // missilestate
  NULL,                 // deathstate
  NULL,                 // xdeathstate
  //sfx_None,           // deathsound
  0,                    // speed
  16,                   // radius
  16,                   // height
  100,                  // mass
  0,                    // damage
  //sfx_None,           // activesound
  MF_SOLID,             // flags
  NULL                  // raisestate
};

/******************************************************************************
 * MT_MISC35
 ******************************************************************************/

map_obj_state misc35_normal_states[] =
{
{true,  STATE_SHRTREDCOL,       "COL4", 0,      -1,     0,      "",                     STATE_NULL,             0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_defn misc35_defn =
{                       // MT_MISC35
  33,                   // doomednum
  misc35_normal_states, // spawnstate
  1000,                 // spawnhealth
  NULL,                 // seestate
  //sfx_None,           // seesound
  8,                    // reactiontime
  //sfx_None,           // attacksound
  NULL,                 // painstate
  0,                    // painchance
  //sfx_None,           // painsound
  NULL,                 // meleestate
  NULL,                 // missilestate
  NULL,                 // deathstate
  NULL,                 // xdeathstate
  //sfx_None,           // deathsound
  0,                    // speed
  16,                   // radius
  16,                   // height
  100,                  // mass
  0,                    // damage
  //sfx_None,           // activesound
  MF_SOLID,             // flags
  NULL                  // raisestate
};

/******************************************************************************
 * MT_MISC36
 ******************************************************************************/

map_obj_state misc36_normal_states[] =
{
{true,  STATE_SKULLCOL,         "COL6", 0,      -1,     0,      "",                     STATE_NULL,             0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_defn misc36_defn =
{                       // MT_MISC36
  37,                   // doomednum
  misc36_normal_states,           // spawnstate
  1000,                 // spawnhealth
  NULL,                 // seestate
  //sfx_None,           // seesound
  8,                    // reactiontime
  //sfx_None,           // attacksound
  NULL,                 // painstate
  0,                    // painchance
  //sfx_None,           // painsound
  NULL,                 // meleestate
  NULL,                 // missilestate
  NULL,                 // deathstate
  NULL,                 // xdeathstate
  //sfx_None,           // deathsound
  0,                    // speed
  16,                   // radius
  16,                   // height
  100,                  // mass
  0,                    // damage
  //sfx_None,           // activesound
  MF_SOLID,             // flags
  NULL                  // raisestate
};

/******************************************************************************
 * MT_MISC37
 ******************************************************************************/

map_obj_state misc37_normal_states[] =
{
{true,  STATE_HEARTCOL,         "COL5", 0,      14,     0,      "",                     STATE_HEARTCOL2,        0,      0},
{true,  STATE_HEARTCOL2,        "COL5", 1,      14,     0,      "",                     STATE_HEARTCOL,         0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_defn misc37_defn =
{                       // MT_MISC37
  36,                   // doomednum
  misc37_normal_states, // spawnstate
  1000,                 // spawnhealth
  NULL,                 // seestate
  //sfx_None,           // seesound
  8,                    // reactiontime
  //sfx_None,           // attacksound
  NULL,                 // painstate
  0,                    // painchance
  //sfx_None,           // painsound
  NULL,                 // meleestate
  NULL,                 // missilestate
  NULL,                 // deathstate
  NULL,                 // xdeathstate
  //sfx_None,           // deathsound
  0,                    // speed
  16,                   // radius
  16,                   // height
  100,                  // mass
  0,                    // damage
  //sfx_None,           // activesound
  MF_SOLID,             // flags
  NULL                  // raisestate
};

/******************************************************************************
 * MT_MISC38
 ******************************************************************************/

map_obj_state misc38_normal_states[] =
{
{true,  STATE_EVILEYE,          "CEYE", 0,      6,      1,      "",                     STATE_EVILEYE2,         0,      0},
{true,  STATE_EVILEYE2,         "CEYE", 1,      6,      1,      "",                     STATE_EVILEYE3,         0,      0},
{true,  STATE_EVILEYE3,         "CEYE", 2,      6,      1,      "",                     STATE_EVILEYE4,         0,      0},
{true,  STATE_EVILEYE4,         "CEYE", 1,      6,      1,      "",                     STATE_EVILEYE,          0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_defn misc38_defn =
{                       // MT_MISC38
  41,                   // doomednum
  misc38_normal_states, // spawnstate
  1000,                 // spawnhealth
  NULL,                 // seestate
  //sfx_None,           // seesound
  8,                    // reactiontime
  //sfx_None,           // attacksound
  NULL,                 // painstate
  0,                    // painchance
  //sfx_None,           // painsound
  NULL,                 // meleestate
  NULL,                 // missilestate
  NULL,                 // deathstate
  NULL,                 // xdeathstate
  //sfx_None,           // deathsound
  0,                    // speed
  16,                   // radius
  16,                   // height
  100,                  // mass
  0,                    // damage
  //sfx_None,           // activesound
  MF_SOLID,             // flags
  NULL                  // raisestate
};

/******************************************************************************
 * MT_MISC39
 ******************************************************************************/

map_obj_state misc39_normal_states[] =
{
{true,  STATE_FLOATSKULL,       "FSKU", 0,      6,      1,      "",                     STATE_FLOATSKULL2,      0,      0},
{true,  STATE_FLOATSKULL2,      "FSKU", 1,      6,      1,      "",                     STATE_FLOATSKULL3,      0,      0},
{true,  STATE_FLOATSKULL3,      "FSKU", 2,      6,      1,      "",                     STATE_FLOATSKULL,       0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_defn misc39_defn =
{                       // MT_MISC39
  42,                   // doomednum
  misc39_normal_states, // spawnstate
  1000,                 // spawnhealth
  NULL,                 // seestate
  //sfx_None,           // seesound
  8,                    // reactiontime
  //sfx_None,           // attacksound
  NULL,                 // painstate
  0,                    // painchance
  //sfx_None,           // painsound
  NULL,                 // meleestate
  NULL,                 // missilestate
  NULL,                 // deathstate
  NULL,                 // xdeathstate
  //sfx_None,           // deathsound
  0,                    // speed
  16,                   // radius
  16,                   // height
  100,                  // mass
  0,                    // damage
  //sfx_None,           // activesound
  MF_SOLID,             // flags
  NULL                  // raisestate
};

/******************************************************************************
 * MT_MISC40
 ******************************************************************************/

map_obj_state misc40_normal_states[] =
{
{true,  STATE_TORCHTREE,        "TRE1", 0,      -1,     0,      "",                     STATE_NULL,             0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_defn misc40_defn =
{                       // MT_MISC40
  43,                   // doomednum
  misc40_normal_states, // spawnstate
  1000,                 // spawnhealth
  NULL,                 // seestate
  //sfx_None,           // seesound
  8,                    // reactiontime
  //sfx_None,           // attacksound
  NULL,                 // painstate
  0,                    // painchance
  //sfx_None,           // painsound
  NULL,                 // meleestate
  NULL,                 // missilestate
  NULL,                 // deathstate
  NULL,                 // xdeathstate
  //sfx_None,           // deathsound
  0,                    // speed
  16,                   // radius
  16,                   // height
  100,                  // mass
  0,                    // damage
  //sfx_None,           // activesound
  MF_SOLID,             // flags
  NULL                  // raisestate
};

/******************************************************************************
 * MT_MISC41
 ******************************************************************************/

map_obj_state misc41_normal_states[] =
{
{true,  STATE_BLUETORCH,        "TBLU", 0,      4,      1,      "",                     STATE_BLUETORCH2,       0,      0},
{true,  STATE_BLUETORCH2,       "TBLU", 1,      4,      1,      "",                     STATE_BLUETORCH3,       0,      0},
{true,  STATE_BLUETORCH3,       "TBLU", 2,      4,      1,      "",                     STATE_BLUETORCH4,       0,      0},
{true,  STATE_BLUETORCH4,       "TBLU", 3,      4,      1,      "",                     STATE_BLUETORCH,        0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_defn misc41_defn =
{                       // MT_MISC41
  44,                   // doomednum
  misc41_normal_states, // spawnstate
  1000,                 // spawnhealth
  NULL,                 // seestate
  //sfx_None,           // seesound
  8,                    // reactiontime
  //sfx_None,           // attacksound
  NULL,                 // painstate
  0,                    // painchance
  //sfx_None,           // painsound
  NULL,                 // meleestate
  NULL,                 // missilestate
  NULL,                 // deathstate
  NULL,                 // xdeathstate
  //sfx_None,           // deathsound
  0,                    // speed
  16,                   // radius
  16,                   // height
  100,                  // mass
  0,                    // damage
  //sfx_None,           // activesound
  MF_SOLID,             // flags
  NULL                  // raisestate
};

/******************************************************************************
 * MT_MISC42
 ******************************************************************************/

map_obj_state misc42_normal_states[] =
{
{true,  STATE_GREENTORCH,       "TGRN", 0,      4,      1,      "",                     STATE_GREENTORCH2,      0,      0},
{true,  STATE_GREENTORCH2,      "TGRN", 1,      4,      1,      "",                     STATE_GREENTORCH3,      0,      0},
{true,  STATE_GREENTORCH3,      "TGRN", 2,      4,      1,      "",                     STATE_GREENTORCH4,      0,      0},
{true,  STATE_GREENTORCH4,      "TGRN", 3,      4,      1,      "",                     STATE_GREENTORCH,       0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_defn misc42_defn =
{                       // MT_MISC42
  45,                   // doomednum
  misc42_normal_states, // spawnstate
  1000,                 // spawnhealth
  NULL,                 // seestate
  //sfx_None,           // seesound
  8,                    // reactiontime
  //sfx_None,           // attacksound
  NULL,                 // painstate
  0,                    // painchance
  //sfx_None,           // painsound
  NULL,                 // meleestate
  NULL,                 // missilestate
  NULL,                 // deathstate
  NULL,                 // xdeathstate
  //sfx_None,           // deathsound
  0,                    // speed
  16,                   // radius
  16,                   // height
  100,                  // mass
  0,                    // damage
  //sfx_None,           // activesound
  MF_SOLID,             // flags
  NULL                  // raisestate
};

/******************************************************************************
 * MT_MISC43
 ******************************************************************************/

map_obj_state misc43_normal_states[] =
{
{true,  STATE_REDTORCH,         "TRED", 0,      4,      1,      "",                     STATE_REDTORCH2,        0,      0},
{true,  STATE_REDTORCH2,        "TRED", 1,      4,      1,      "",                     STATE_REDTORCH3,        0,      0},
{true,  STATE_REDTORCH3,        "TRED", 2,      4,      1,      "",                     STATE_REDTORCH4,        0,      0},
{true,  STATE_REDTORCH4,        "TRED", 3,      4,      1,      "",                     STATE_REDTORCH,         0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_defn misc43_defn =
{                       // MT_MISC43
  46,                   // doomednum
  misc43_normal_states, // spawnstate
  1000,                 // spawnhealth
  NULL,                 // seestate
  //sfx_None,           // seesound
  8,                    // reactiontime
  //sfx_None,           // attacksound
  NULL,                 // painstate
  0,                    // painchance
  //sfx_None,           // painsound
  NULL,                 // meleestate
  NULL,                 // missilestate
  NULL,                 // deathstate
  NULL,                 // xdeathstate
  //sfx_None,           // deathsound
  0,                    // speed
  16,                   // radius
  16,                   // height
  100,                  // mass
  0,                    // damage
  //sfx_None,           // activesound
  MF_SOLID,             // flags
  NULL                  // raisestate
};

/******************************************************************************
 * MT_MISC44
 ******************************************************************************/

map_obj_state misc44_normal_states[] =
{
{true,  STATE_BTORCHSHRT,       "SMBT", 0,      4,      1,      "",                     STATE_BTORCHSHRT2,      0,      0},
{true,  STATE_BTORCHSHRT2,      "SMBT", 1,      4,      1,      "",                     STATE_BTORCHSHRT3,      0,      0},
{true,  STATE_BTORCHSHRT3,      "SMBT", 2,      4,      1,      "",                     STATE_BTORCHSHRT4,      0,      0},
{true,  STATE_BTORCHSHRT4,      "SMBT", 3,      4,      1,      "",                     STATE_BTORCHSHRT,       0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_defn misc44_defn =
{                       // MT_MISC44
  55,                   // doomednum
  misc44_normal_states, // spawnstate
  1000,                 // spawnhealth
  NULL,                 // seestate
  //sfx_None,           // seesound
  8,                    // reactiontime
  //sfx_None,           // attacksound
  NULL,                 // painstate
  0,                    // painchance
  //sfx_None,           // painsound
  NULL,                 // meleestate
  NULL,                 // missilestate
  NULL,                 // deathstate
  NULL,                 // xdeathstate
  //sfx_None,           // deathsound
  0,                    // speed
  16,                   // radius
  16,                   // height
  100,                  // mass
  0,                    // damage
  //sfx_None,           // activesound
  MF_SOLID,             // flags
  NULL                  // raisestate
};

/******************************************************************************
 * MT_MISC45
 ******************************************************************************/

map_obj_state misc45_normal_states[] =
{
{true,  STATE_GTORCHSHRT,       "SMGT", 0,      4,      1,      "",                     STATE_GTORCHSHRT2,      0,      0},
{true,  STATE_GTORCHSHRT2,      "SMGT", 1,      4,      1,      "",                     STATE_GTORCHSHRT3,      0,      0},
{true,  STATE_GTORCHSHRT3,      "SMGT", 2,      4,      1,      "",                     STATE_GTORCHSHRT4,      0,      0},
{true,  STATE_GTORCHSHRT4,      "SMGT", 3,      4,      1,      "",                     STATE_GTORCHSHRT,       0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_defn misc45_defn =
{                       // MT_MISC45
  56,                   // doomednum
  misc45_normal_states, // spawnstate
  1000,                 // spawnhealth
  NULL,                 // seestate
  //sfx_None,           // seesound
  8,                    // reactiontime
  //sfx_None,           // attacksound
  NULL,                 // painstate
  0,                    // painchance
  //sfx_None,           // painsound
  NULL,                 // meleestate
  NULL,                 // missilestate
  NULL,                 // deathstate
  NULL,                 // xdeathstate
  //sfx_None,           // deathsound
  0,                    // speed
  16,                   // radius
  16,                   // height
  100,                  // mass
  0,                    // damage
  //sfx_None,           // activesound
  MF_SOLID,             // flags
  NULL                  // raisestate
};

/******************************************************************************
 * MT_MISC46
 ******************************************************************************/

map_obj_state misc46_normal_states[] =
{
{true,  STATE_RTORCHSHRT,       "SMRT", 0,      4,      1,      "",                     STATE_RTORCHSHRT2,      0,      0},
{true,  STATE_RTORCHSHRT2,      "SMRT", 1,      4,      1,      "",                     STATE_RTORCHSHRT3,      0,      0},
{true,  STATE_RTORCHSHRT3,      "SMRT", 2,      4,      1,      "",                     STATE_RTORCHSHRT4,      0,      0},
{true,  STATE_RTORCHSHRT4,      "SMRT", 3,      4,      1,      "",                     STATE_RTORCHSHRT,       0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_defn misc46_defn =
{                       // MT_MISC46
  57,                   // doomednum
  misc46_normal_states, // spawnstate
  1000,                 // spawnhealth
  NULL,                 // seestate
  //sfx_None,           // seesound
  8,                    // reactiontime
  //sfx_None,           // attacksound
  NULL,                 // painstate
  0,                    // painchance
  //sfx_None,           // painsound
  NULL,                 // meleestate
  NULL,                 // missilestate
  NULL,                 // deathstate
  NULL,                 // xdeathstate
  //sfx_None,           // deathsound
  0,                    // speed
  16,                   // radius
  16,                   // height
  100,                  // mass
  0,                    // damage
  //sfx_None,           // activesound
  MF_SOLID,             // flags
  NULL                  // raisestate
};

/******************************************************************************
 * MT_MISC47
 ******************************************************************************/

map_obj_state misc47_normal_states[] =
{
{true,  STATE_STALAGTITE,       "SMIT", 0,      -1,     0,      "",                     STATE_NULL,             0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_defn misc47_defn =
{                       // MT_MISC47
  47,                   // doomednum
  misc47_normal_states, // spawnstate
  1000,                 // spawnhealth
  NULL,                 // seestate
  //sfx_None,           // seesound
  8,                    // reactiontime
  //sfx_None,           // attacksound
  NULL,                 // painstate
  0,                    // painchance
  //sfx_None,           // painsound
  NULL,                 // meleestate
  NULL,                 // missilestate
  NULL,                 // deathstate
  NULL,                 // xdeathstate
  //sfx_None,           // deathsound
  0,                    // speed
  16,                   // radius
  16,                   // height
  100,                  // mass
  0,                    // damage
  //sfx_None,           // activesound
  MF_SOLID,             // flags
  NULL                  // raisestate
};

/******************************************************************************
 * MT_MISC48
 ******************************************************************************/

map_obj_state misc48_normal_states[] =
{
{true,  STATE_TECHPILLAR,       "ELEC", 0,      -1,     0,      "",                     STATE_NULL,             0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_defn misc48_defn =
{                       // MT_MISC48
  48,                   // doomednum
  misc48_normal_states, // spawnstate
  1000,                 // spawnhealth
  NULL,                 // seestate
  //sfx_None,           // seesound
  8,                    // reactiontime
  //sfx_None,           // attacksound
  NULL,                 // painstate
  0,                    // painchance
  //sfx_None,           // painsound
  NULL,                 // meleestate
  NULL,                 // missilestate
  NULL,                 // deathstate
  NULL,                 // xdeathstate
  //sfx_None,           // deathsound
  0,                    // speed
  16,                   // radius
  16,                   // height
  100,                  // mass
  0,                    // damage
  //sfx_None,           // activesound
  MF_SOLID,             // flags
  NULL                  // raisestate
};

/******************************************************************************
 * MT_MISC49
 ******************************************************************************/

map_obj_state misc49_normal_states[] =
{
{true,  STATE_CANDLESTIK,       "CAND", 0,      -1,     1,      "",                     STATE_NULL,             0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_defn misc49_defn =
{                       // MT_MISC49
  34,                   // doomednum
  misc49_normal_states, // spawnstate
  1000,                 // spawnhealth
  NULL,                 // seestate
  //sfx_None,           // seesound
  8,                    // reactiontime
  //sfx_None,           // attacksound
  NULL,                 // painstate
  0,                    // painchance
  //sfx_None,           // painsound
  NULL,                 // meleestate
  NULL,                 // missilestate
  NULL,                 // deathstate
  NULL,                 // xdeathstate
  //sfx_None,           // deathsound
  0,                    // speed
  20,                   // radius
  16,                   // height
  100,                  // mass
  0,                    // damage
  //sfx_None,           // activesound
  0,                    // flags
  NULL                  // raisestate
};

/******************************************************************************
 * MT_MISC50
 ******************************************************************************/

map_obj_state misc50_normal_states[] =
{
{true,  STATE_CANDELABRA,       "CBRA", 0,      -1,     1,      "",                     STATE_NULL,             0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_defn misc50_defn =
{                       // MT_MISC50
  35,                   // doomednum
  misc50_normal_states, // spawnstate
  1000,                 // spawnhealth
  NULL,                 // seestate
  //sfx_None,           // seesound
  8,                    // reactiontime
  //sfx_None,           // attacksound
  NULL,                 // painstate
  0,                    // painchance
  //sfx_None,           // painsound
  NULL,                 // meleestate
  NULL,                 // missilestate
  NULL,                 // deathstate
  NULL,                 // xdeathstate
  //sfx_None,           // deathsound
  0,                    // speed
  16,                   // radius
  16,                   // height
  100,                  // mass
  0,                    // damage
  //sfx_None,           // activesound
  MF_SOLID,             // flags
  NULL                  // raisestate

};

/******************************************************************************
 * MT_MISC51
 ******************************************************************************/

map_obj_state misc51_normal_states[] =
{
{true,  STATE_BLOODYTWITCH,     "GOR1", 0,      10,     0,      "",                     STATE_BLOODYTWITCH2,    0,      0},
{true,  STATE_BLOODYTWITCH2,    "GOR1", 1,      15,     0,      "",                     STATE_BLOODYTWITCH3,    0,      0},
{true,  STATE_BLOODYTWITCH3,    "GOR1", 2,      8,      0,      "",                     STATE_BLOODYTWITCH4,    0,      0},
{true,  STATE_BLOODYTWITCH4,    "GOR1", 1,      6,      0,      "",                     STATE_BLOODYTWITCH,     0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_defn misc51_defn =
{                       // MT_MISC51
  49,                   // doomednum
  misc51_normal_states, // spawnstate
  1000,                 // spawnhealth
  NULL,                 // seestate
  //sfx_None,           // seesound
  8,                    // reactiontime
  //sfx_None,           // attacksound
  NULL,                 // painstate
  0,                    // painchance
  //sfx_None,           // painsound
  NULL,                 // meleestate
  NULL,                 // missilestate
  NULL,                 // deathstate
  NULL,                 // xdeathstate
  //sfx_None,           // deathsound
  0,                    // speed
  16,                   // radius
  68,                   // height
  100,                  // mass
  0,                    // damage
  //sfx_None,           // activesound
  MF_SOLID |
  MF_SPAWNCEILING |
  MF_NOGRAVITY,         // flags
  NULL                  // raisestate
};

/******************************************************************************
 * MT_MISC52
 ******************************************************************************/

map_obj_state misc52_normal_states[] =
{
{true,  STATE_MEAT2,            "GOR2", 0,      -1,     0,      "",                     STATE_NULL,             0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_defn misc52_defn =
{                       // MT_MISC52
  50,                   // doomednum
  misc52_normal_states, // spawnstate
  1000,                 // spawnhealth
  NULL,                 // seestate
  //sfx_None,           // seesound
  8,                    // reactiontime
  //sfx_None,           // attacksound
  NULL,                 // painstate
  0,                    // painchance
  //sfx_None,           // painsound
  NULL,                 // meleestate
  NULL,                 // missilestate
  NULL,                 // deathstate
  NULL,                 // xdeathstate
  //sfx_None,           // deathsound
  0,                    // speed
  16,                   // radius
  84,                   // height
  100,                  // mass
  0,                    // damage
  //sfx_None,           // activesound
  MF_SOLID |
  MF_SPAWNCEILING |
  MF_NOGRAVITY,         // flags
  NULL                  // raisestate
};

/******************************************************************************
 * MT_MISC53
 ******************************************************************************/

map_obj_state misc53_normal_states[] =
{
{true,  STATE_MEAT3,            "GOR3", 0,      -1,     0,      "",                     STATE_NULL,             0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_defn misc53_defn =
{                       // MT_MISC53
  51,                   // doomednum
  misc53_normal_states, // spawnstate
  1000,                 // spawnhealth
  NULL,                 // seestate
  //sfx_None,           // seesound
  8,                    // reactiontime
  //sfx_None,           // attacksound
  NULL,                 // painstate
  0,                    // painchance
  //sfx_None,           // painsound
  NULL,                 // meleestate
  NULL,                 // missilestate
  NULL,                 // deathstate
  NULL,                 // xdeathstate
  //sfx_None,           // deathsound
  0,                    // speed
  16,                   // radius
  84,                   // height
  100,                  // mass
  0,                    // damage
  //sfx_None,           // activesound
  MF_SOLID |
  MF_SPAWNCEILING |
  MF_NOGRAVITY,         // flags
  NULL                  // raisestate
};

/******************************************************************************
 * MT_MISC54
 ******************************************************************************/

map_obj_state misc54_normal_states[] =
{
{true,  STATE_MEAT4,            "GOR4", 0,      -1,     0,      "",                     STATE_NULL,             0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_defn misc54_defn =
{                       // MT_MISC54
  52,                   // doomednum
  misc54_normal_states, // spawnstate
  1000,                 // spawnhealth
  NULL,                 // seestate
  //sfx_None,           // seesound
  8,                    // reactiontime
  //sfx_None,           // attacksound
  NULL,                 // painstate
  0,                    // painchance
  //sfx_None,           // painsound
  NULL,                 // meleestate
  NULL,                 // missilestate
  NULL,                 // deathstate
  NULL,                 // xdeathstate
  //sfx_None,           // deathsound
  0,                    // speed
  16,                   // radius
  68,                   // height
  100,                  // mass
  0,                    // damage
  //sfx_None,           // activesound
  MF_SOLID |
  MF_SPAWNCEILING |
  MF_NOGRAVITY,         // flags
  NULL                  // raisestate
};

/******************************************************************************
 * MT_MISC55
 ******************************************************************************/

map_obj_state misc55_normal_states[] =
{
{true,  STATE_MEAT5,            "GOR5", 0,      -1,     0,      "",                     STATE_NULL,             0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_defn misc55_defn =
{                       // MT_MISC55
  53,                   // doomednum
  misc55_normal_states, // spawnstate
  1000,                 // spawnhealth
  NULL,                 // seestate
  //sfx_None,           // seesound
  8,                    // reactiontime
  //sfx_None,           // attacksound
  NULL,                 // painstate
  0,                    // painchance
  //sfx_None,           // painsound
  NULL,                 // meleestate
  NULL,                 // missilestate
  NULL,                 // deathstate
  NULL,                 // xdeathstate
  //sfx_None,           // deathsound
  0,                    // speed
  16,                   // radius
  52,                   // height
  100,                  // mass
  0,                    // damage
  //sfx_None,           // activesound
  MF_SOLID |
  MF_SPAWNCEILING |
  MF_NOGRAVITY,         // flags
  NULL                  // raisestate
};

/******************************************************************************
 * MT_MISC56
 ******************************************************************************/

map_obj_defn misc56_defn =
{                       // MT_MISC56
  59,                   // doomednum
  misc52_normal_states, // spawnstate
  1000,                 // spawnhealth
  NULL,                 // seestate
  //sfx_None,           // seesound
  8,                    // reactiontime
  //sfx_None,           // attacksound
  NULL,                 // painstate
  0,                    // painchance
  //sfx_None,           // painsound
  NULL,                 // meleestate
  NULL,                 // missilestate
  NULL,                 // deathstate
  NULL,                 // xdeathstate
  //sfx_None,           // deathsound
  0,                    // speed
  20,                   // radius
  84,                   // height
  100,                  // mass
  0,                    // damage
  //sfx_None,           // activesound
  MF_SPAWNCEILING |
  MF_NOGRAVITY,         // flags
  NULL                  // raisestate
};

/******************************************************************************
 * MT_MISC57
 ******************************************************************************/

map_obj_defn misc57_defn =
{                       // MT_MISC57
  60,                   // doomednum
  misc54_normal_states, // spawnstate
  1000,                 // spawnhealth
  NULL,                 // seestate
  //sfx_None,           // seesound
  8,                    // reactiontime
  //sfx_None,           // attacksound
  NULL,                 // painstate
  0,                    // painchance
  //sfx_None,           // painsound
  NULL,                 // meleestate
  NULL,                 // missilestate
  NULL,                 // deathstate
  NULL,                 // xdeathstate
  //sfx_None,           // deathsound
  0,                    // speed
  20,                   // radius
  68,                   // height
  100,                  // mass
  0,                    // damage
  //sfx_None,           // activesound
  MF_SPAWNCEILING |
  MF_NOGRAVITY,         // flags
  NULL                  // raisestate
};

/******************************************************************************
 * MT_MISC58
 ******************************************************************************/

map_obj_defn misc58_defn =
{                       // MT_MISC58
  61,                   // doomednum
  misc53_normal_states, // spawnstate
  1000,                 // spawnhealth
  NULL,                 // seestate
  //sfx_None,           // seesound
  8,                    // reactiontime
  //sfx_None,           // attacksound
  NULL,                 // painstate
  0,                    // painchance
  //sfx_None,           // painsound
  NULL,                 // meleestate
  NULL,                 // missilestate
  NULL,                 // deathstate
  NULL,                 // xdeathstate
  //sfx_None,           // deathsound
  0,                    // speed
  20,                   // radius
  52,                   // height
  100,                  // mass
  0,                    // damage
  //sfx_None,           // activesound
  MF_SPAWNCEILING |
  MF_NOGRAVITY,         // flags
  NULL                  // raisestate
};

/******************************************************************************
 * MT_MISC59
 ******************************************************************************/

map_obj_defn misc59_defn =
{                       // MT_MISC59
  62,                   // doomednum
  misc55_normal_states, // spawnstate
  1000,                 // spawnhealth
  NULL,                 // seestate
  //sfx_None,           // seesound
  8,                    // reactiontime
  //sfx_None,           // attacksound
  NULL,                 // painstate
  0,                    // painchance
  //sfx_None,           // painsound
  NULL,                 // meleestate
  NULL,                 // missilestate
  NULL,                 // deathstate
  NULL,                 // xdeathstate
  //sfx_None,           // deathsound
  0,                    // speed
  20,                   // radius
  52,                   // height
  100,                  // mass
  0,                    // damage
  //sfx_None,           // activesound
  MF_SPAWNCEILING |
  MF_NOGRAVITY,         // flags
  NULL                  // raisestate
};

/******************************************************************************
 * MT_MISC60
 ******************************************************************************/

map_obj_defn misc60_defn =
{                       // MT_MISC60
  63,                   // doomednum
  misc51_normal_states, // spawnstate
  1000,                 // spawnhealth
  NULL,                 // seestate
  //sfx_None,           // seesound
  8,                    // reactiontime
  //sfx_None,           // attacksound
  NULL,                 // painstate
  0,                    // painchance
  //sfx_None,           // painsound
  NULL,                 // meleestate
  NULL,                 // missilestate
  NULL,                 // deathstate
  NULL,                 // xdeathstate
  //sfx_None,           // deathsound
  0,                    // speed
  20,                   // radius
  68,                   // height
  100,                  // mass
  0,                    // damage
  //sfx_None,           // activesound
  MF_SPAWNCEILING |
  MF_NOGRAVITY,         // flags
  NULL                  // raisestate
};

/******************************************************************************
 * MT_MISC61
 ******************************************************************************/

#if 0 // FIXME: move this to beings.
map_obj_state misc61_normal_states[] =
{
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_defn misc61_defn =
{                       // MT_MISC61
  22,                   // doomednum
  S_HEAD_DIE6,          // spawnstate
  1000,                 // spawnhealth
  NULL,                 // seestate
  //sfx_None,           // seesound
  8,                    // reactiontime
  //sfx_None,           // attacksound
  NULL,                 // painstate
  0,                    // painchance
  //sfx_None,           // painsound
  NULL,                 // meleestate
  NULL,                 // missilestate
  NULL,                 // deathstate
  NULL,                 // xdeathstate
  //sfx_None,           // deathsound
  0,                    // speed
  20,                   // radius
  16,                   // height
  100,                  // mass
  0,                    // damage
  //sfx_None,           // activesound
  0,                    // flags
  NULL                  // raisestate
};

/******************************************************************************
 * MT_MISC62
 ******************************************************************************/

map_obj_state misc62_normal_states[] =
{
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_defn misc62_defn =
{                       // MT_MISC62
  15,                   // doomednum
  S_PLAY_DIE7,          // spawnstate
  1000,                 // spawnhealth
  NULL,                 // seestate
  //sfx_None,           // seesound
  8,                    // reactiontime
  //sfx_None,           // attacksound
  NULL,                 // painstate
  0,                    // painchance
  //sfx_None,           // painsound
  NULL,                 // meleestate
  NULL,                 // missilestate
  NULL,                 // deathstate
  NULL,                 // xdeathstate
  //sfx_None,           // deathsound
  0,                    // speed
  20,                   // radius
  16,                   // height
  100,                  // mass
  0,                    // damage
  //sfx_None,           // activesound
  0,                    // flags
  NULL                  // raisestate
};

/******************************************************************************
 * MT_MISC63
 ******************************************************************************/

map_obj_state misc63_normal_states[] =
{
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_defn misc63_defn =
{                       // MT_MISC63
  18,                   // doomednum
  S_POSS_DIE5,          // spawnstate
  1000,                 // spawnhealth
  NULL,                 // seestate
  //sfx_None,           // seesound
  8,                    // reactiontime
  //sfx_None,           // attacksound
  NULL,                 // painstate
  0,                    // painchance
  //sfx_None,           // painsound
  NULL,                 // meleestate
  NULL,                 // missilestate
  NULL,                 // deathstate
  NULL,                 // xdeathstate
  //sfx_None,           // deathsound
  0,                    // speed
  20,                   // radius
  16,                   // height
  100,                  // mass
  0,                    // damage
  //sfx_None,           // activesound
  0,                    // flags
  NULL                  // raisestate
};

/******************************************************************************
 * MT_MISC64
 ******************************************************************************/

map_obj_state misc64_normal_states[] =
{
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_defn misc64_defn =
{                       // MT_MISC64
  21,                   // doomednum
  S_SARG_DIE6,          // spawnstate
  1000,                 // spawnhealth
  NULL,                 // seestate
  //sfx_None,           // seesound
  8,                    // reactiontime
  //sfx_None,           // attacksound
  NULL,                 // painstate
  0,                    // painchance
  //sfx_None,           // painsound
  NULL,                 // meleestate
  NULL,                 // missilestate
  NULL,                 // deathstate
  NULL,                 // xdeathstate
  //sfx_None,           // deathsound
  0,                    // speed
  20,                   // radius
  16,                   // height
  100,                  // mass
  0,                    // damage
  //sfx_None,           // activesound
  0,                    // flags
  NULL                  // raisestate
};

/******************************************************************************
 * MT_MISC65
 ******************************************************************************/

map_obj_state misc65_normal_states[] =
{
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_defn misc65_defn =
{                       // MT_MISC65
  23,                   // doomednum
  S_SKULL_DIE6,         // spawnstate
  1000,                 // spawnhealth
  NULL,                 // seestate
  //sfx_None,           // seesound
  8,                    // reactiontime
  //sfx_None,           // attacksound
  NULL,                 // painstate
  0,                    // painchance
  //sfx_None,           // painsound
  NULL,                 // meleestate
  NULL,                 // missilestate
  NULL,                 // deathstate
  NULL,                 // xdeathstate
  //sfx_None,           // deathsound
  0,                    // speed
  20,                   // radius
  16,                   // height
  100,                  // mass
  0,                    // damage
  //sfx_None,           // activesound
  0,                    // flags
  NULL                  // raisestate
};

/******************************************************************************
 * MT_MISC66
 ******************************************************************************/

map_obj_state misc66_normal_states[] =
{
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_defn misc66_defn =
{                       // MT_MISC66
  20,                   // doomednum
  S_TROO_DIE5,          // spawnstate
  1000,                 // spawnhealth
  NULL,                 // seestate
  //sfx_None,           // seesound
  8,                    // reactiontime
  //sfx_None,           // attacksound
  NULL,                 // painstate
  0,                    // painchance
  //sfx_None,           // painsound
  NULL,                 // meleestate
  NULL,                 // missilestate
  NULL,                 // deathstate
  NULL,                 // xdeathstate
  //sfx_None,           // deathsound
  0,                    // speed
  20,                   // radius
  16,                   // height
  100,                  // mass
  0,                    // damage
  //sfx_None,           // activesound
  0,                    // flags
  NULL                  // raisestate
};

/******************************************************************************
 * MT_MISC67
 ******************************************************************************/

map_obj_state misc67_normal_states[] =
{
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_defn misc67_defn =
{                       // MT_MISC67
  19,                   // doomednum
  S_SPOS_DIE5,          // spawnstate
  1000,                 // spawnhealth
  NULL,                 // seestate
  //sfx_None,           // seesound
  8,                    // reactiontime
  //sfx_None,           // attacksound
  NULL,                 // painstate
  0,                    // painchance
  //sfx_None,           // painsound
  NULL,                 // meleestate
  NULL,                 // missilestate
  NULL,                 // deathstate
  NULL,                 // xdeathstate
  //sfx_None,           // deathsound
  0,                    // speed
  20,                   // radius
  16,                   // height
  100,                  // mass
  0,                    // damage
  //sfx_None,           // activesound
  0,                    // flags
  NULL                  // raisestate
};

/******************************************************************************
 * MT_MISC68
 ******************************************************************************/

map_obj_state misc68_normal_states[] =
{
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_defn misc68_defn =
{                       // MT_MISC68
  10,                   // doomednum
  S_PLAY_XDIE9,         // spawnstate
  1000,                 // spawnhealth
  NULL,                 // seestate
  //sfx_None,           // seesound
  8,                    // reactiontime
  //sfx_None,           // attacksound
  NULL,                 // painstate
  0,                    // painchance
  //sfx_None,           // painsound
  NULL,                 // meleestate
  NULL,                 // missilestate
  NULL,                 // deathstate
  NULL,                 // xdeathstate
  //sfx_None,           // deathsound
  0,                    // speed
  20,                   // radius
  16,                   // height
  100,                  // mass
  0,                    // damage
  //sfx_None,           // activesound
  0,                    // flags
  NULL                  // raisestate
};

/******************************************************************************
 * MT_MISC69
 ******************************************************************************/

map_obj_state misc69_normal_states[] =
{
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_defn misc69_defn =
{                       // MT_MISC69
  12,                   // doomednum
  S_PLAY_XDIE9,         // spawnstate
  1000,                 // spawnhealth
  NULL,                 // seestate
  //sfx_None,           // seesound
  8,                    // reactiontime
  //sfx_None,           // attacksound
  NULL,                 // painstate
  0,                    // painchance
  //sfx_None,           // painsound
  NULL,                 // meleestate
  NULL,                 // missilestate
  NULL,                 // deathstate
  NULL,                 // xdeathstate
  //sfx_None,           // deathsound
  0,                    // speed
  20,                   // radius
  16,                   // height
  100,                  // mass
  0,                    // damage
  //sfx_None,           // activesound
  0,                    // flags
  NULL                  // raisestate
};
#endif

/******************************************************************************
 * MT_MISC70
 ******************************************************************************/

map_obj_state misc70_normal_states[] =
{
{true,  STATE_HEADSONSTICK,     "POL2", 0,      -1,     0,      "",                     STATE_NULL,             0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_defn misc70_defn =
{                       // MT_MISC70
  28,                   // doomednum
  misc70_normal_states, // spawnstate
  1000,                 // spawnhealth
  NULL,                 // seestate
  //sfx_None,           // seesound
  8,                    // reactiontime
  //sfx_None,           // attacksound
  NULL,                 // painstate
  0,                    // painchance
  //sfx_None,           // painsound
  NULL,                 // meleestate
  NULL,                 // missilestate
  NULL,                 // deathstate
  NULL,                 // xdeathstate
  //sfx_None,           // deathsound
  0,                    // speed
  16,                   // radius
  16,                   // height
  100,                  // mass
  0,                    // damage
  //sfx_None,           // activesound
  MF_SOLID,             // flags
  NULL                  // raisestate
};

/******************************************************************************
 * MT_MISC71
 ******************************************************************************/

map_obj_state misc71_normal_states[] =
{
{true,  STATE_GIBS,             "POL5", 0,      -1,     0,      "",                     STATE_NULL,             0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_defn misc71_defn =
{                       // MT_MISC71
  24,                   // doomednum
  misc71_normal_states, // spawnstate
  1000,                 // spawnhealth
  NULL,                 // seestate
  //sfx_None,           // seesound
  8,                    // reactiontime
  //sfx_None,           // attacksound
  NULL,                 // painstate
  0,                    // painchance
  //sfx_None,           // painsound
  NULL,                 // meleestate
  NULL,                 // missilestate
  NULL,                 // deathstate
  NULL,                 // xdeathstate
  //sfx_None,           // deathsound
  0,                    // speed
  20,                   // radius
  16,                   // height
  100,                  // mass
  0,                    // damage
  //sfx_None,           // activesound
  0,                    // flags
  NULL                  // raisestate
};

/******************************************************************************
 * MT_MISC72
 ******************************************************************************/

map_obj_state misc72_normal_states[] =
{
{true,  STATE_HEADONASTICK,     "POL4", 0,      -1,     0,      "",                     STATE_NULL,             0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_defn misc72_defn =
{                       // MT_MISC72
  27,                   // doomednum
  misc72_normal_states, // spawnstate
  1000,                 // spawnhealth
  NULL,                 // seestate
  //sfx_None,           // seesound
  8,                    // reactiontime
  //sfx_None,           // attacksound
  NULL,                 // painstate
  0,                    // painchance
  //sfx_None,           // painsound
  NULL,                 // meleestate
  NULL,                 // missilestate
  NULL,                 // deathstate
  NULL,                 // xdeathstate
  //sfx_None,           // deathsound
  0,                    // speed
  16,                   // radius
  16,                   // height
  100,                  // mass
  0,                    // damage
  //sfx_None,           // activesound
  MF_SOLID,             // flags
  NULL                  // raisestate
};

/******************************************************************************
 * MT_MISC73
 ******************************************************************************/

map_obj_state misc73_normal_states[] =
{
{true,  STATE_HEADCANDLES,      "POL3", 0,      6,      1,      "",                     STATE_HEADCANDLES2,     0,      0},
{true,  STATE_HEADCANDLES2,     "POL3", 1,      6,      1,      "",                     STATE_HEADCANDLES,      0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_defn misc73_defn =
{                       // MT_MISC73
  29,                   // doomednum
  misc73_normal_states, // spawnstate
  1000,                 // spawnhealth
  NULL,                 // seestate
  //sfx_None,           // seesound
  8,                    // reactiontime
  //sfx_None,           // attacksound
  NULL,                 // painstate
  0,                    // painchance
  //sfx_None,           // painsound
  NULL,                 // meleestate
  NULL,                 // missilestate
  NULL,                 // deathstate
  NULL,                 // xdeathstate
  //sfx_None,           // deathsound
  0,                    // speed
  16,                   // radius
  16,                   // height
  100,                  // mass
  0,                    // damage
  //sfx_None,           // activesound
  MF_SOLID,             // flags
  NULL                  // raisestate
};

/******************************************************************************
 * MT_MISC74
 ******************************************************************************/

map_obj_state misc74_normal_states[] =
{
{true,  STATE_DEADSTICK,        "POL1", 0,      -1,     0,      "",                     STATE_NULL,             0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_defn misc74_defn =
{                       // MT_MISC74
  25,                   // doomednum
  misc74_normal_states, // spawnstate
  1000,                 // spawnhealth
  NULL,                 // seestate
  //sfx_None,           // seesound
  8,                    // reactiontime
  //sfx_None,           // attacksound
  NULL,                 // painstate
  0,                    // painchance
  //sfx_None,           // painsound
  NULL,                 // meleestate
  NULL,                 // missilestate
  NULL,                 // deathstate
  NULL,                 // xdeathstate
  //sfx_None,           // deathsound
  0,                    // speed
  16,                   // radius
  16,                   // height
  100,                  // mass
  0,                    // damage
  //sfx_None,           // activesound
  MF_SOLID,             // flags
  NULL                  // raisestate
};

/******************************************************************************
 * MT_MISC75
 ******************************************************************************/

map_obj_state misc75_normal_states[] =
{
{true,  STATE_LIVESTICK,        "POL6", 0,      6,      0,      "",                     STATE_LIVESTICK2,       0,      0},
{true,  STATE_LIVESTICK2,       "POL6", 1,      8,      0,      "",                     STATE_LIVESTICK,        0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_defn misc75_defn =
{                       // MT_MISC75
  26,                   // doomednum
  misc75_normal_states, // spawnstate
  1000,                 // spawnhealth
  NULL,                 // seestate
  //sfx_None,           // seesound
  8,                    // reactiontime
  //sfx_None,           // attacksound
  NULL,                 // painstate
  0,                    // painchance
  //sfx_None,           // painsound
  NULL,                 // meleestate
  NULL,                 // missilestate
  NULL,                 // deathstate
  NULL,                 // xdeathstate
  //sfx_None,           // deathsound
  0,                    // speed
  16,                   // radius
  16,                   // height
  100,                  // mass
  0,                    // damage
  //sfx_None,           // activesound
  MF_SOLID,             // flags
  NULL                  // raisestate
};

/******************************************************************************
 * MT_MISC76
 ******************************************************************************/

map_obj_state misc76_normal_states[] =
{
{true,  STATE_BIGTREE,          "TRE2", 0,      -1,     0,      "",                     STATE_NULL,             0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_defn misc76_defn =
{                       // MT_MISC76
  54,                   // doomednum
  misc76_normal_states, // spawnstate
  1000,                 // spawnhealth
  NULL,                 // seestate
  //sfx_None,           // seesound
  8,                    // reactiontime
  //sfx_None,           // attacksound
  NULL,                 // painstate
  0,                    // painchance
  //sfx_None,           // painsound
  NULL,                 // meleestate
  NULL,                 // missilestate
  NULL,                 // deathstate
  NULL,                 // xdeathstate
  //sfx_None,           // deathsound
  0,                    // speed
  32,                   // radius
  16,                   // height
  100,                  // mass
  0,                    // damage
  //sfx_None,           // activesound
  MF_SOLID,             // flags
  NULL                  // raisestate
};

/******************************************************************************
 * MT_MISC77
 ******************************************************************************/

map_obj_state misc77_normal_states[] =
{
{true,  STATE_BBAR1,            "FCAN", 0,      4,      1,      "",                     STATE_BBAR2,            0,      0},
{true,  STATE_BBAR2,            "FCAN", 1,      4,      1,      "",                     STATE_BBAR3,            0,      0},
{true,  STATE_BBAR3,            "FCAN", 2,      4,      1,      "",                     STATE_BBAR1,            0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_defn misc77_defn =
{                       // MT_MISC77
  70,                   // doomednum
  misc77_normal_states, // spawnstate
  1000,                 // spawnhealth
  NULL,                 // seestate
  //sfx_None,           // seesound
  8,                    // reactiontime
  //sfx_None,           // attacksound
  NULL,                 // painstate
  0,                    // painchance
  //sfx_None,           // painsound
  NULL,                 // meleestate
  NULL,                 // missilestate
  NULL,                 // deathstate
  NULL,                 // xdeathstate
  //sfx_None,           // deathsound
  0,                    // speed
  16,                   // radius
  16,                   // height
  100,                  // mass
  0,                    // damage
  //sfx_None,           // activesound
  MF_SOLID,             // flags
  NULL                  // raisestate
};

/******************************************************************************
 * MT_MISC78
 ******************************************************************************/

map_obj_state misc78_normal_states[] =
{
{true,  STATE_HANGNOGUTS,       "HDB1", 0,      -1,     0,      "",                     STATE_NULL,             0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_defn misc78_defn =
{                       // MT_MISC78
  73,                   // doomednum
  misc78_normal_states, // spawnstate
  1000,                 // spawnhealth
  NULL,                 // seestate
  //sfx_None,           // seesound
  8,                    // reactiontime
  //sfx_None,           // attacksound
  NULL,                 // painstate
  0,                    // painchance
  //sfx_None,           // painsound
  NULL,                 // meleestate
  NULL,                 // missilestate
  NULL,                 // deathstate
  NULL,                 // xdeathstate
  //sfx_None,           // deathsound
  0,                    // speed
  16,                   // radius
  88,                   // height
  100,                  // mass
  0,                    // damage
  //sfx_None,           // activesound
  MF_SOLID |
  MF_SPAWNCEILING |
  MF_NOGRAVITY,         // flags
  NULL                  // raisestate
};

/******************************************************************************
 * MT_MISC79
 ******************************************************************************/

map_obj_state misc79_normal_states[] =
{
{true,  STATE_HANGBNOBRAIN,     "HDB2", 0,      -1,     0,      "",                     STATE_NULL,             0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_defn misc79_defn =
{                       // MT_MISC79
  74,                   // doomednum
  misc79_normal_states, // spawnstate
  1000,                 // spawnhealth
  NULL,                 // seestate
  //sfx_None,           // seesound
  8,                    // reactiontime
  //sfx_None,           // attacksound
  NULL,                 // painstate
  0,                    // painchance
  //sfx_None,           // painsound
  NULL,                 // meleestate
  NULL,                 // missilestate
  NULL,                 // deathstate
  NULL,                 // xdeathstate
  //sfx_None,           // deathsound
  0,                    // speed
  16,                   // radius
  88,                   // height
  100,                  // mass
  0,                    // damage
  //sfx_None,           // activesound
  MF_SOLID |
  MF_SPAWNCEILING |
  MF_NOGRAVITY,         // flags
  NULL                  // raisestate
};

/******************************************************************************
 * MT_MISC80
 ******************************************************************************/

map_obj_state misc80_normal_states[] =
{
{true,  STATE_HANGTLOOKDN,      "HDB3", 0,      -1,     0,      "",                     STATE_NULL,             0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_defn misc80_defn =
{                       // MT_MISC80
  75,                   // doomednum
  misc80_normal_states, // spawnstate
  1000,                 // spawnhealth
  NULL,                 // seestate
  //sfx_None,           // seesound
  8,                    // reactiontime
  //sfx_None,           // attacksound
  NULL,                 // painstate
  0,                    // painchance
  //sfx_None,           // painsound
  NULL,                 // meleestate
  NULL,                 // missilestate
  NULL,                 // deathstate
  NULL,                 // xdeathstate
  //sfx_None,           // deathsound
  0,                    // speed
  16,                   // radius
  64,                   // height
  100,                  // mass
  0,                    // damage
  //sfx_None,           // activesound
  MF_SOLID |
  MF_SPAWNCEILING |
  MF_NOGRAVITY,         // flags
  NULL                  // raisestate
};

/******************************************************************************
 * MT_MISC81
 ******************************************************************************/

map_obj_state misc81_normal_states[] =
{
{true,  STATE_HANGTSKULL,       "HDB4", 0,      -1,     0,      "",                     STATE_NULL,             0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_defn misc81_defn =
{                       // MT_MISC81
  76,                   // doomednum
  misc81_normal_states, // spawnstate
  1000,                 // spawnhealth
  NULL,                 // seestate
  //sfx_None,           // seesound
  8,                    // reactiontime
  //sfx_None,           // attacksound
  NULL,                 // painstate
  0,                    // painchance
  //sfx_None,           // painsound
  NULL,                 // meleestate
  NULL,                 // missilestate
  NULL,                 // deathstate
  NULL,                 // xdeathstate
  //sfx_None,           // deathsound
  0,                    // speed
  16,                   // radius
  64,                   // height
  100,                  // mass
  0,                    // damage
  //sfx_None,           // activesound
  MF_SOLID |
  MF_SPAWNCEILING |
  MF_NOGRAVITY,         // flags
  NULL                  // raisestate
};

/******************************************************************************
 * MT_MISC82
 ******************************************************************************/

map_obj_state misc82_normal_states[] =
{
{true,  STATE_HANGTLOOKUP,      "HDB5", 0,      -1,     0,      "",                     STATE_NULL,             0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_defn misc82_defn =
{                       // MT_MISC82
  77,                   // doomednum
  misc82_normal_states, // spawnstate
  1000,                 // spawnhealth
  NULL,                 // seestate
  //sfx_None,           // seesound
  8,                    // reactiontime
  //sfx_None,           // attacksound
  NULL,                 // painstate
  0,                    // painchance
  //sfx_None,           // painsound
  NULL,                 // meleestate
  NULL,                 // missilestate
  NULL,                 // deathstate
  NULL,                 // xdeathstate
  //sfx_None,           // deathsound
  0,                    // speed
  16,                   // radius
  64,                   // height
  100,                  // mass
  0,                    // damage
  //sfx_None,           // activesound
  MF_SOLID |
  MF_SPAWNCEILING |
  MF_NOGRAVITY,         // flags
  NULL                  // raisestate
};

/******************************************************************************
 * MT_MISC83
 ******************************************************************************/

map_obj_state misc83_normal_states[] =
{
{true,  STATE_HANGTNOBRAIN,     "HDB6", 0,      -1,     0,      "",                     STATE_NULL,             0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_defn misc83_defn =
{                       // MT_MISC83
  78,                   // doomednum
  misc83_normal_states, // spawnstate
  1000,                 // spawnhealth
  NULL,                 // seestate
  //sfx_None,           // seesound
  8,                    // reactiontime
  //sfx_None,           // attacksound
  NULL,                 // painstate
  0,                    // painchance
  //sfx_None,           // painsound
  NULL,                 // meleestate
  NULL,                 // missilestate
  NULL,                 // deathstate
  NULL,                 // xdeathstate
  //sfx_None,           // deathsound
  0,                    // speed
  16,                   // radius
  64,                   // height
  100,                  // mass
  0,                    // damage
  //sfx_None,           // activesound
  MF_SOLID |
  MF_SPAWNCEILING |
  MF_NOGRAVITY,         // flags
  NULL                  // raisestate
};

/******************************************************************************
 * MT_MISC84
 ******************************************************************************/

map_obj_state misc84_normal_states[] =
{
{true,  STATE_COLONGIBS,        "POB1", 0,      -1,     0,      "",                     STATE_NULL,             0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_defn misc84_defn =
{                       // MT_MISC84
  79,                   // doomednum
  misc84_normal_states, // spawnstate
  1000,                 // spawnhealth
  NULL,                 // seestate
  //sfx_None,           // seesound
  8,                    // reactiontime
  //sfx_None,           // attacksound
  NULL,                 // painstate
  0,                    // painchance
  //sfx_None,           // painsound
  NULL,                 // meleestate
  NULL,                 // missilestate
  NULL,                 // deathstate
  NULL,                 // xdeathstate
  //sfx_None,           // deathsound
  0,                    // speed
  20,                   // radius
  16,                   // height
  100,                  // mass
  0,                    // damage
  //sfx_None,           // activesound
  MF_NOBLOCKMAP,        // flags
  NULL                  // raisestate
};

/******************************************************************************
 * MT_MISC85
 ******************************************************************************/

map_obj_state misc85_normal_states[] =
{
{true,  STATE_SMALLPOOL,        "POB2", 0,      -1,     0,      "",                     STATE_NULL,             0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_defn misc85_defn =
{                       // MT_MISC85
  80,                   // doomednum
  misc85_normal_states, // spawnstate
  1000,                 // spawnhealth
  NULL,                 // seestate
  //sfx_None,           // seesound
  8,                    // reactiontime
  //sfx_None,           // attacksound
  NULL,                 // painstate
  0,                    // painchance
  //sfx_None,           // painsound
  NULL,                 // meleestate
  NULL,                 // missilestate
  NULL,                 // deathstate
  NULL,                 // xdeathstate
  //sfx_None,           // deathsound
  0,                    // speed
  20,                   // radius
  16,                   // height
  100,                  // mass
  0,                    // damage
  //sfx_None,           // activesound
  MF_NOBLOCKMAP,        // flags
  NULL                  // raisestate
};

/******************************************************************************
 * MT_MISC86
 ******************************************************************************/

map_obj_state misc86_normal_states[] =
{
{true,  STATE_BRAINSTEM,        "BRS1", 0,      -1,     0,      "",                     STATE_NULL,             0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_defn misc86_defn =
{                       // MT_MISC86
  81,                   // doomednum
  misc86_normal_states, // spawnstate
  1000,                 // spawnhealth
  NULL,                 // seestate
  //sfx_None,           // seesound
  8,                    // reactiontime
  //sfx_None,           // attacksound
  NULL,                 // painstate
  0,                    // painchance
  //sfx_None,           // painsound
  NULL,                 // meleestate
  NULL,                 // missilestate
  NULL,                 // deathstate
  NULL,                 // xdeathstate
  //sfx_None,           // deathsound
  0,                    // speed
  20,                   // radius
  16,                   // height
  100,                  // mass
  0,                    // damage
  //sfx_None,           // activesound
  MF_NOBLOCKMAP,        // flags
  NULL                  // raisestate
};

/******************************************************************************
 * LIST OF ALL INERT MAP OBJECTS
 ******************************************************************************/

map_obj_defn const *map_obj_inert_defns[] = 
{
  &fire_defn,
  &smoke_defn,
  &bosstarget_defn,
  &barrel_defn,
  &blood_defn,
  &tfog_defn,
  &ifog_defn,
  &teleportman_defn,
  &extrabfg_defn,
  &misc0_defn,
  &misc1_defn,
  &misc2_defn,
  &misc3_defn,
  &misc4_defn,
  &misc5_defn,
  &misc6_defn,
  &misc7_defn,
  &misc8_defn,
  &misc9_defn,
  &misc10_defn,
  &misc11_defn,
  &misc12_defn,
  &inv_defn,
  &misc13_defn,
  &ins_defn,
  &fire_defn,
  NULL
};
