#include "map_object.h"

/******************************************************************************
 * PLAYER
 ******************************************************************************/

map_obj_state player_normal_states[] =
{
{true,  STATE_PLAY,             "PLAY", 0,      -1,     0,      "",                     STATE_NULL,             0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_state player_run_states[] =
{
{true,  STATE_PLAY_RUN1,        "PLAY", 0,      4,      0,      "",                     STATE_PLAY_RUN2,        0,      0},
{true,  STATE_PLAY_RUN2,        "PLAY", 1,      4,      0,      "",                     STATE_PLAY_RUN3,        0,      0},
{true,  STATE_PLAY_RUN3,        "PLAY", 2,      4,      0,      "",                     STATE_PLAY_RUN4,        0,      0},
{true,  STATE_PLAY_RUN4,        "PLAY", 3,      4,      0,      "",                     STATE_PLAY_RUN1,        0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_state player_attack_states[] =
{
{true,  STATE_PLAY_ATK1,        "PLAY", 4,      12,     0,      "",                     STATE_PLAY,             0,      0},
{true,  STATE_PLAY_ATK2,        "PLAY", 5,      6,      1,      "",                     STATE_PLAY_ATK1,        0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_state player_pain_states[] =
{
{true,  STATE_PLAY_PAIN,        "PLAY", 6,      4,      0,      "",                     STATE_PLAY_PAIN2,       0,      0},
{true,  STATE_PLAY_PAIN2,       "PLAY", 6,      4,      0,      "A_Pain",               STATE_PLAY,             0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_state player_die_states[] =
{
{true,  STATE_PLAY_DIE1,        "PLAY", 7,      10,     0,      "",                     STATE_PLAY_DIE2,        0,      0},
{true,  STATE_PLAY_DIE2,        "PLAY", 8,      10,     0,      "A_PlayerScream",       STATE_PLAY_DIE3,        0,      0},
{true,  STATE_PLAY_DIE3,        "PLAY", 9,      10,     0,      "A_Fall",               STATE_PLAY_DIE4,        0,      0},
{true,  STATE_PLAY_DIE4,        "PLAY", 10,     10,     0,      "",                     STATE_PLAY_DIE5,        0,      0},
{true,  STATE_PLAY_DIE5,        "PLAY", 11,     10,     0,      "",                     STATE_PLAY_DIE6,        0,      0},
{true,  STATE_PLAY_DIE6,        "PLAY", 12,     10,     0,      "",                     STATE_PLAY_DIE7,        0,      0},
{true,  STATE_PLAY_DIE7,        "PLAY", 13,     -1,     0,      "",                     STATE_NULL,             0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_state player_xdie_states[] =
{
{true,  STATE_PLAY_XDIE1,       "PLAY", 14,     5,      0,      "",                     STATE_PLAY_XDIE2,       0,      0},
{true,  STATE_PLAY_XDIE2,       "PLAY", 15,     5,      0,      "A_XScream",            STATE_PLAY_XDIE3,       0,      0},
{true,  STATE_PLAY_XDIE3,       "PLAY", 16,     5,      0,      "A_Fall",               STATE_PLAY_XDIE4,       0,      0},
{true,  STATE_PLAY_XDIE4,       "PLAY", 17,     5,      0,      "",                     STATE_PLAY_XDIE5,       0,      0},
{true,  STATE_PLAY_XDIE5,       "PLAY", 18,     5,      0,      "",                     STATE_PLAY_XDIE6,       0,      0},
{true,  STATE_PLAY_XDIE6,       "PLAY", 19,     5,      0,      "",                     STATE_PLAY_XDIE7,       0,      0},
{true,  STATE_PLAY_XDIE7,       "PLAY", 20,     5,      0,      "",                     STATE_PLAY_XDIE8,       0,      0},
{true,  STATE_PLAY_XDIE8,       "PLAY", 21,     5,      0,      "",                     STATE_PLAY_XDIE9,       0,      0},
{true,  STATE_PLAY_XDIE9,       "PLAY", 22,     -1,     0,      "",                     STATE_NULL,             0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_defn player_defn =
{                       // MT_PLAYER
  -1,                   // doomednum
  player_normal_states, // spawnstate
  100,                  // spawnhealth
  player_run_states,    // seestate
  //sfx_None,           // seesound
  0,                    // reactiontime
  //sfx_None,           // attacksound
  player_pain_states,   // painstate
  255,                  // painchance
  //sfx_plpain,         // painsound
  NULL,                 // meleestate
  player_attack_states, // missilestate
  player_die_states,    // deathstate
  player_xdie_states,   // xdeathstate
  //sfx_pldeth,         // deathsound
  8,                    // speed (FIXME: This was 0. Why?)
  16,                   // radius
  56,                   // height
  100,                  // mass
  0,                    // damage
  //sfx_None,           // activesound
  MF_SOLID |
  MF_SHOOTABLE |
  MF_DROPOFF |
  MF_PICKUP |
  MF_NOTDMATCH,         // flags
  NULL                  // raisestate
};


/******************************************************************************
 * MT_POSSESSED
 ******************************************************************************/

map_obj_state possessed_normal_states[] =
{
{true,  STATE_POSS_STND,        "POSS", 0,      10,     0,      "A_Look",               STATE_POSS_STND2,       0,      0},
{true,  STATE_POSS_STND2,       "POSS", 1,      10,     0,      "A_Look",               STATE_POSS_STND,        0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_state possessed_run_states[] =
{
{true,  STATE_POSS_RUN1,        "POSS", 0,      4,      0,      "A_Chase",              STATE_POSS_RUN2,        0,      0},
{true,  STATE_POSS_RUN2,        "POSS", 0,      4,      0,      "A_Chase",              STATE_POSS_RUN3,        0,      0},
{true,  STATE_POSS_RUN3,        "POSS", 1,      4,      0,      "A_Chase",              STATE_POSS_RUN4,        0,      0},
{true,  STATE_POSS_RUN4,        "POSS", 1,      4,      0,      "A_Chase",              STATE_POSS_RUN5,        0,      0},
{true,  STATE_POSS_RUN5,        "POSS", 2,      4,      0,      "A_Chase",              STATE_POSS_RUN6,        0,      0},
{true,  STATE_POSS_RUN6,        "POSS", 2,      4,      0,      "A_Chase",              STATE_POSS_RUN7,        0,      0},
{true,  STATE_POSS_RUN7,        "POSS", 3,      4,      0,      "A_Chase",              STATE_POSS_RUN8,        0,      0},
{true,  STATE_POSS_RUN8,        "POSS", 3,      4,      0,      "A_Chase",              STATE_POSS_RUN1,        0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_state possessed_pain_states[] =
{
{true,  STATE_POSS_PAIN,        "POSS", 6,      3,      0,      "",                     STATE_POSS_PAIN2,       0,      0},
{true,  STATE_POSS_PAIN2,       "POSS", 6,      3,      0,      "A_Pain",               STATE_POSS_RUN1,        0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_state possessed_attack_states[] =
{
{true,  STATE_POSS_ATK1,        "POSS", 4,      10,     0,      "A_FaceTarget",         STATE_POSS_ATK2,        0,      0},
{true,  STATE_POSS_ATK2,        "POSS", 5,      8,      0,      "A_PosAttack",          STATE_POSS_ATK3,        0,      0},
{true,  STATE_POSS_ATK3,        "POSS", 4,      8,      0,      "",                     STATE_POSS_RUN1,        0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_state possessed_die_states[] =
{
{true,  STATE_POSS_DIE1,        "POSS", 7,      5,      0,      "",                     STATE_POSS_DIE2,        0,      0},
{true,  STATE_POSS_DIE2,        "POSS", 8,      5,      0,      "A_Scream",             STATE_POSS_DIE3,        0,      0},
{true,  STATE_POSS_DIE3,        "POSS", 9,      5,      0,      "A_Fall",               STATE_POSS_DIE4,        0,      0},
{true,  STATE_POSS_DIE4,        "POSS", 10,     5,      0,      "",                     STATE_POSS_DIE5,        0,      0},
{true,  STATE_POSS_DIE5,        "POSS", 11,     -1,     0,      "",                     STATE_NULL,             0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_state possessed_xdie_states[] =
{
{true,  STATE_POSS_XDIE1,       "POSS", 12,     5,      0,      "",                     STATE_POSS_XDIE2,       0,      0},
{true,  STATE_POSS_XDIE2,       "POSS", 13,     5,      0,      "A_XScream",            STATE_POSS_XDIE3,       0,      0},
{true,  STATE_POSS_XDIE3,       "POSS", 14,     5,      0,      "A_Fall",               STATE_POSS_XDIE4,       0,      0},
{true,  STATE_POSS_XDIE4,       "POSS", 15,     5,      0,      "",                     STATE_POSS_XDIE5,       0,      0},
{true,  STATE_POSS_XDIE5,       "POSS", 16,     5,      0,      "",                     STATE_POSS_XDIE6,       0,      0},
{true,  STATE_POSS_XDIE6,       "POSS", 17,     5,      0,      "",                     STATE_POSS_XDIE7,       0,      0},
{true,  STATE_POSS_XDIE7,       "POSS", 18,     5,      0,      "",                     STATE_POSS_XDIE8,       0,      0},
{true,  STATE_POSS_XDIE8,       "POSS", 19,     5,      0,      "",                     STATE_POSS_XDIE9,       0,      0},
{true,  STATE_POSS_XDIE9,       "POSS", 20,     -1,     0,      "",                     STATE_NULL,             0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_state possessed_raise_states[] =
{
{true,  STATE_POSS_RAISE1,      "POSS", 10,     5,      0,      "",                     STATE_POSS_RAISE2,      0,      0},
{true,  STATE_POSS_RAISE2,      "POSS", 9,      5,      0,      "",                     STATE_POSS_RAISE3,      0,      0},
{true,  STATE_POSS_RAISE3,      "POSS", 8,      5,      0,      "",                     STATE_POSS_RAISE4,      0,      0},
{true,  STATE_POSS_RAISE4,      "POSS", 7,      5,      0,      "",                     STATE_POSS_RUN1,        0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_defn possessed_defn =
{                       // MT_POSSESSED
  3004,                 // doomednum
  possessed_normal_states, // spawnstate
  20,                   // spawnhealth
  possessed_run_states, // seestate
  //sfx_posit1,         // seesound
  8,                    // reactiontime
  //sfx_pistol,         // attacksound
  possessed_pain_states,// painstate
  200,                  // painchance
  //sfx_popain,         // painsound
  0,                    // meleestate
  possessed_attack_states,// missilestate
  possessed_die_states, // deathstate
  possessed_xdie_states,// xdeathstate
  //sfx_podth1,          // deathsound
  8,                    // speed
  20,                   // radius
  56,                   // height
  100,                  // mass
  0,                    // damage
  //sfx_posact,         // activesound
  MF_SOLID |
  MF_SHOOTABLE |
  MF_COUNTKILL,         // flags
  possessed_raise_states// raisestate
};

/******************************************************************************
 * MT_SHOTGUY
 ******************************************************************************/

map_obj_state shotguy_normal_states[] =
{
{true,  STATE_SPOS_STND,        "SPOS", 0,      10,     0,      "A_Look",               STATE_SPOS_STND2,       0,      0},
{true,  STATE_SPOS_STND2,       "SPOS", 1,      10,     0,      "A_Look",               STATE_SPOS_STND,        0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_state shotguy_run_states[] =
{
{true,  STATE_SPOS_RUN1,        "SPOS", 0,      3,      0,      "A_Chase",              STATE_SPOS_RUN2,        0,      0},
{true,  STATE_SPOS_RUN2,        "SPOS", 0,      3,      0,      "A_Chase",              STATE_SPOS_RUN3,        0,      0},
{true,  STATE_SPOS_RUN3,        "SPOS", 1,      3,      0,      "A_Chase",              STATE_SPOS_RUN4,        0,      0},
{true,  STATE_SPOS_RUN4,        "SPOS", 1,      3,      0,      "A_Chase",              STATE_SPOS_RUN5,        0,      0},
{true,  STATE_SPOS_RUN5,        "SPOS", 2,      3,      0,      "A_Chase",              STATE_SPOS_RUN6,        0,      0},
{true,  STATE_SPOS_RUN6,        "SPOS", 2,      3,      0,      "A_Chase",              STATE_SPOS_RUN7,        0,      0},
{true,  STATE_SPOS_RUN7,        "SPOS", 3,      3,      0,      "A_Chase",              STATE_SPOS_RUN8,        0,      0},
{true,  STATE_SPOS_RUN8,        "SPOS", 3,      3,      0,      "A_Chase",              STATE_SPOS_RUN1,        0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_state shotguy_pain_states[] =
{
{true,  STATE_SPOS_PAIN,        "SPOS", 6,      3,      0,      "",                     STATE_SPOS_PAIN2,       0,      0},
{true,  STATE_SPOS_PAIN2,       "SPOS", 6,      3,      0,      "A_Pain",               STATE_SPOS_RUN1,        0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_state shotguy_attack_states[] =
{
{true,  STATE_SPOS_ATK1,        "SPOS", 4,      10,     0,      "A_FaceTarget",         STATE_SPOS_ATK2,        0,      0},
{true,  STATE_SPOS_ATK2,        "SPOS", 5,      10,     1,      "A_SPosAttack",         STATE_SPOS_ATK3,        0,      0},
{true,  STATE_SPOS_ATK3,        "SPOS", 4,      10,     0,      "",                     STATE_SPOS_RUN1,        0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_state shotguy_die_states[] =
{
{true,  STATE_SPOS_DIE1,        "SPOS", 7,      5,      0,      "",                     STATE_SPOS_DIE2,        0,      0},
{true,  STATE_SPOS_DIE2,        "SPOS", 8,      5,      0,      "A_Scream",             STATE_SPOS_DIE3,        0,      0},
{true,  STATE_SPOS_DIE3,        "SPOS", 9,      5,      0,      "A_Fall",               STATE_SPOS_DIE4,        0,      0},
{true,  STATE_SPOS_DIE4,        "SPOS", 10,     5,      0,      "",                     STATE_SPOS_DIE5,        0,      0},
{true,  STATE_SPOS_DIE5,        "SPOS", 11,     -1,     0,      "",                     STATE_NULL,             0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_state shotguy_xdie_states[] =
{
{true,  STATE_SPOS_XDIE1,       "SPOS", 12,     5,      0,      "",                     STATE_SPOS_XDIE2,       0,      0},
{true,  STATE_SPOS_XDIE2,       "SPOS", 13,     5,      0,      "A_XScream",            STATE_SPOS_XDIE3,       0,      0},
{true,  STATE_SPOS_XDIE3,       "SPOS", 14,     5,      0,      "A_Fall",               STATE_SPOS_XDIE4,       0,      0},
{true,  STATE_SPOS_XDIE4,       "SPOS", 15,     5,      0,      "",                     STATE_SPOS_XDIE5,       0,      0},
{true,  STATE_SPOS_XDIE5,       "SPOS", 16,     5,      0,      "",                     STATE_SPOS_XDIE6,       0,      0},
{true,  STATE_SPOS_XDIE6,       "SPOS", 17,     5,      0,      "",                     STATE_SPOS_XDIE7,       0,      0},
{true,  STATE_SPOS_XDIE7,       "SPOS", 18,     5,      0,      "",                     STATE_SPOS_XDIE8,       0,      0},
{true,  STATE_SPOS_XDIE8,       "SPOS", 19,     5,      0,      "",                     STATE_SPOS_XDIE9,       0,      0},
{true,  STATE_SPOS_XDIE9,       "SPOS", 20,     -1,     0,      "",                     STATE_NULL,             0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_state shotguy_raise_states[] =
{
{true,  STATE_SPOS_RAISE1,      "SPOS", 11,     5,      0,      "",                     STATE_SPOS_RAISE2,      0,      0},
{true,  STATE_SPOS_RAISE2,      "SPOS", 10,     5,      0,      "",                     STATE_SPOS_RAISE3,      0,      0},
{true,  STATE_SPOS_RAISE3,      "SPOS", 9,      5,      0,      "",                     STATE_SPOS_RAISE4,      0,      0},
{true,  STATE_SPOS_RAISE4,      "SPOS", 8,      5,      0,      "",                     STATE_SPOS_RAISE5,      0,      0},
{true,  STATE_SPOS_RAISE5,      "SPOS", 7,      5,      0,      "",                     STATE_SPOS_RUN1,        0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_defn shotguy_defn =
{                       // MT_SHOTGUY
  9,                    // doomednum
  shotguy_normal_states,// spawnstate
  30,                   // spawnhealth
  shotguy_run_states,   // seestate
  //sfx_posit2,         // seesound
  8,                    // reactiontime
  //0,                  // attacksound
  shotguy_pain_states,  // painstate
  170,                  // painchance
  //sfx_popain,         // painsound
  0,                    // meleestate
  shotguy_attack_states,// missilestate
  shotguy_die_states,   // deathstate
  shotguy_xdie_states,         // xdeathstate
  //sfx_podth2,         // deathsound
  8,                    // speed
  20,                   // radius
  56,                   // height
  100,                  // mass
  0,                    // damage
  //sfx_posact,         // activesound
  MF_SOLID |
  MF_SHOOTABLE |
  MF_COUNTKILL,         // flags
  shotguy_raise_states  // raisestate
};

/******************************************************************************
 * MT_VILE
 ******************************************************************************/

map_obj_state vile_normal_states[] =
{
{true,  STATE_VILE_STND,        "VILE", 0,      10,     0,      "A_Look",               STATE_VILE_STND2,       0,      0},
{true,  STATE_VILE_STND2,       "VILE", 1,      10,     0,      "A_Look",               STATE_VILE_STND,        0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_state vile_run_states[] =
{
{true,  STATE_VILE_RUN1,        "VILE", 0,      2,      0,      "A_VileChase",          STATE_VILE_RUN2,        0,      0},
{true,  STATE_VILE_RUN2,        "VILE", 0,      2,      0,      "A_VileChase",          STATE_VILE_RUN3,        0,      0},
{true,  STATE_VILE_RUN3,        "VILE", 1,      2,      0,      "A_VileChase",          STATE_VILE_RUN4,        0,      0},
{true,  STATE_VILE_RUN4,        "VILE", 1,      2,      0,      "A_VileChase",          STATE_VILE_RUN5,        0,      0},
{true,  STATE_VILE_RUN5,        "VILE", 2,      2,      0,      "A_VileChase",          STATE_VILE_RUN6,        0,      0},
{true,  STATE_VILE_RUN6,        "VILE", 2,      2,      0,      "A_VileChase",          STATE_VILE_RUN7,        0,      0},
{true,  STATE_VILE_RUN7,        "VILE", 3,      2,      0,      "A_VileChase",          STATE_VILE_RUN8,        0,      0},
{true,  STATE_VILE_RUN8,        "VILE", 3,      2,      0,      "A_VileChase",          STATE_VILE_RUN9,        0,      0},
{true,  STATE_VILE_RUN9,        "VILE", 4,      2,      0,      "A_VileChase",          STATE_VILE_RUN10,       0,      0},
{true,  STATE_VILE_RUN10,       "VILE", 4,      2,      0,      "A_VileChase",          STATE_VILE_RUN11,       0,      0},
{true,  STATE_VILE_RUN11,       "VILE", 5,      2,      0,      "A_VileChase",          STATE_VILE_RUN12,       0,      0},
{true,  STATE_VILE_RUN12,       "VILE", 5,      2,      0,      "A_VileChase",          STATE_VILE_RUN1,        0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_state vile_pain_states[] =
{
{true,  STATE_VILE_PAIN,        "VILE", 16,     5,      0,      "",                     STATE_VILE_PAIN2,       0,      0},
{true,  STATE_VILE_PAIN2,       "VILE", 16,     5,      0,      "A_Pain",               STATE_VILE_RUN1,        0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_state vile_attack_states[] =
{
{true,  STATE_VILE_ATK1,        "VILE", 6,      0,      1,      "A_VileStart",          STATE_VILE_ATK2,        0,      0},
{true,  STATE_VILE_ATK2,        "VILE", 6,      10,     1,      "A_FaceTarget",         STATE_VILE_ATK3,        0,      0},
{true,  STATE_VILE_ATK3,        "VILE", 7,      8,      1,      "A_VileTarget",         STATE_VILE_ATK4,        0,      0},
{true,  STATE_VILE_ATK4,        "VILE", 8,      8,      1,      "A_FaceTarget",         STATE_VILE_ATK5,        0,      0},
{true,  STATE_VILE_ATK5,        "VILE", 9,      8,      1,      "A_FaceTarget",         STATE_VILE_ATK6,        0,      0},
{true,  STATE_VILE_ATK6,        "VILE", 10,     8,      1,      "A_FaceTarget",         STATE_VILE_ATK7,        0,      0},
{true,  STATE_VILE_ATK7,        "VILE", 11,     8,      1,      "A_FaceTarget",         STATE_VILE_ATK8,        0,      0},
{true,  STATE_VILE_ATK8,        "VILE", 12,     8,      1,      "A_FaceTarget",         STATE_VILE_ATK9,        0,      0},
{true,  STATE_VILE_ATK9,        "VILE", 13,     8,      1,      "A_FaceTarget",         STATE_VILE_ATK10,       0,      0},
{true,  STATE_VILE_ATK10,       "VILE", 14,     8,      1,      "A_VileAttack",         STATE_VILE_ATK11,       0,      0},
{true,  STATE_VILE_ATK11,       "VILE", 15,     20,     1,      "",                     STATE_VILE_RUN1,        0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_state vile_die_states[] =
{
{true,  STATE_VILE_DIE1,        "VILE", 16,     7,      0,      "",                     STATE_VILE_DIE2,        0,      0},
{true,  STATE_VILE_DIE2,        "VILE", 17,     7,      0,      "A_Scream",             STATE_VILE_DIE3,        0,      0},
{true,  STATE_VILE_DIE3,        "VILE", 18,     7,      0,      "A_Fall",               STATE_VILE_DIE4,        0,      0},
{true,  STATE_VILE_DIE4,        "VILE", 19,     7,      0,      "",                     STATE_VILE_DIE5,        0,      0},
{true,  STATE_VILE_DIE5,        "VILE", 20,     7,      0,      "",                     STATE_VILE_DIE6,        0,      0},
{true,  STATE_VILE_DIE6,        "VILE", 21,     7,      0,      "",                     STATE_VILE_DIE7,        0,      0},
{true,  STATE_VILE_DIE7,        "VILE", 22,     7,      0,      "",                     STATE_VILE_DIE8,        0,      0},
{true,  STATE_VILE_DIE8,        "VILE", 23,     5,      0,      "",                     STATE_VILE_DIE9,        0,      0},
{true,  STATE_VILE_DIE9,        "VILE", 24,     5,      0,      "",                     STATE_VILE_DIE10,       0,      0},
{true,  STATE_VILE_DIE10,       "VILE", 25,     -1,     0,      "",                     STATE_NULL,             0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_state vile_raise_states[] =
{
{true,  STATE_VILE_HEAL1,       "VILE", 26,     10,     1,      "",                     STATE_VILE_HEAL2,       0,      0},
{true,  STATE_VILE_HEAL2,       "VILE", 27,     10,     1,      "",                     STATE_VILE_HEAL3,       0,      0},
{true,  STATE_VILE_HEAL3,       "VILE", 28,     10,     1,      "",                     STATE_VILE_RUN1,        0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_defn vile_defn =
{                       // MT_VILE
  64,                   // doomednum
  vile_normal_states,   // spawnstate
  700,                  // spawnhealth
  vile_run_states,      // seestate
  //sfx_vilsit,         // seesound
  8,                    // reactiontime
  //0,                  // attacksound
  vile_pain_states,     // painstate
  10,                   // painchance
  //sfx_vipain,         // painsound
  0,                    // meleestate
  vile_attack_states,   // missilestate
  vile_die_states,      // deathstate
  NULL,                 // xdeathstate
  //sfx_vildth,         // deathsound
  15,                   // speed
  20,                   // radius
  56,                   // height
  500,                  // mass
  0,                    // damage
  //sfx_vilact,         // activesound
  MF_SOLID |
  MF_SHOOTABLE |
  MF_COUNTKILL,         // flags
  NULL,                 // raisestate
};

/******************************************************************************
 * MT_UNDEAD
 ******************************************************************************/

map_obj_state undead_normal_states[] =
{
{true,  STATE_SKEL_STND,        "SKEL", 0,      10,     0,      "A_Look",               STATE_SKEL_STND2,       0,      0},
{true,  STATE_SKEL_STND2,       "SKEL", 1,      10,     0,      "A_Look",               STATE_SKEL_STND,        0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_state undead_run_states[] =
{
{true,  STATE_SKEL_RUN1,        "SKEL", 0,      2,      0,      "A_Chase",              STATE_SKEL_RUN2,        0,      0},
{true,  STATE_SKEL_RUN2,        "SKEL", 0,      2,      0,      "A_Chase",              STATE_SKEL_RUN3,        0,      0},
{true,  STATE_SKEL_RUN3,        "SKEL", 1,      2,      0,      "A_Chase",              STATE_SKEL_RUN4,        0,      0},
{true,  STATE_SKEL_RUN4,        "SKEL", 1,      2,      0,      "A_Chase",              STATE_SKEL_RUN5,        0,      0},
{true,  STATE_SKEL_RUN5,        "SKEL", 2,      2,      0,      "A_Chase",              STATE_SKEL_RUN6,        0,      0},
{true,  STATE_SKEL_RUN6,        "SKEL", 2,      2,      0,      "A_Chase",              STATE_SKEL_RUN7,        0,      0},
{true,  STATE_SKEL_RUN7,        "SKEL", 3,      2,      0,      "A_Chase",              STATE_SKEL_RUN8,        0,      0},
{true,  STATE_SKEL_RUN8,        "SKEL", 3,      2,      0,      "A_Chase",              STATE_SKEL_RUN9,        0,      0},
{true,  STATE_SKEL_RUN9,        "SKEL", 4,      2,      0,      "A_Chase",              STATE_SKEL_RUN10,       0,      0},
{true,  STATE_SKEL_RUN10,       "SKEL", 4,      2,      0,      "A_Chase",              STATE_SKEL_RUN11,       0,      0},
{true,  STATE_SKEL_RUN11,       "SKEL", 5,      2,      0,      "A_Chase",              STATE_SKEL_RUN12,       0,      0},
{true,  STATE_SKEL_RUN12,       "SKEL", 5,      2,      0,      "A_Chase",              STATE_SKEL_RUN1,        0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_state undead_pain_states[] =
{
{true,  STATE_SKEL_PAIN,        "SKEL", 11,     5,      0,      "",                     STATE_SKEL_PAIN2,       0,      0},
{true,  STATE_SKEL_PAIN2,       "SKEL", 11,     5,      0,      "A_Pain",               STATE_SKEL_RUN1,        0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_state undead_melee_states[] =
{
{true,  STATE_SKEL_FIST1,       "SKEL", 6,      0,      0,      "A_FaceTarget",         STATE_SKEL_FIST2,       0,      0},
{true,  STATE_SKEL_FIST2,       "SKEL", 6,      6,      0,      "A_SkelWhoosh",         STATE_SKEL_FIST3,       0,      0},
{true,  STATE_SKEL_FIST3,       "SKEL", 7,      6,      0,      "A_FaceTarget",         STATE_SKEL_FIST4,       0,      0},
{true,  STATE_SKEL_FIST4,       "SKEL", 8,      6,      0,      "A_SkelFist",           STATE_SKEL_RUN1,        0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_state undead_missile_states[] =
{
{true,  STATE_SKEL_MISS1,       "SKEL", 9,      0,      1,      "A_FaceTarget",         STATE_SKEL_MISS2,       0,      0},
{true,  STATE_SKEL_MISS2,       "SKEL", 9,      10,     1,      "A_FaceTarget",         STATE_SKEL_MISS3,       0,      0},
{true,  STATE_SKEL_MISS3,       "SKEL", 10,     10,     0,      "A_SkelMissile",        STATE_SKEL_MISS4,       0,      0},
{true,  STATE_SKEL_MISS4,       "SKEL", 10,     10,     0,      "A_FaceTarget",         STATE_SKEL_RUN1,        0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_state undead_die_states[] =
{
{true,  STATE_SKEL_DIE1,        "SKEL", 11,     7,      0,      "",                     STATE_SKEL_DIE2,        0,      0},
{true,  STATE_SKEL_DIE2,        "SKEL", 12,     7,      0,      "",                     STATE_SKEL_DIE3,        0,      0},
{true,  STATE_SKEL_DIE3,        "SKEL", 13,     7,      0,      "A_Scream",             STATE_SKEL_DIE4,        0,      0},
{true,  STATE_SKEL_DIE4,        "SKEL", 14,     7,      0,      "A_Fall",               STATE_SKEL_DIE5,        0,      0},
{true,  STATE_SKEL_DIE5,        "SKEL", 15,     7,      0,      "",                     STATE_SKEL_DIE6,        0,      0},
{true,  STATE_SKEL_DIE6,        "SKEL", 16,     -1,     0,      "",                     STATE_NULL,             0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_state undead_raise_states[] =
{
{true,  STATE_SKEL_RAISE1,      "SKEL", 16,     5,      0,      "",                     STATE_SKEL_RAISE2,      0,      0},
{true,  STATE_SKEL_RAISE2,      "SKEL", 15,     5,      0,      "",                     STATE_SKEL_RAISE3,      0,      0},
{true,  STATE_SKEL_RAISE3,      "SKEL", 14,     5,      0,      "",                     STATE_SKEL_RAISE4,      0,      0},
{true,  STATE_SKEL_RAISE4,      "SKEL", 13,     5,      0,      "",                     STATE_SKEL_RAISE5,      0,      0},
{true,  STATE_SKEL_RAISE5,      "SKEL", 12,     5,      0,      "",                     STATE_SKEL_RAISE6,      0,      0},
{true,  STATE_SKEL_RAISE6,      "SKEL", 11,     5,      0,      "",                     STATE_SKEL_RUN1,        0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_defn undead_defn =
{                       // MT_UNDEAD
  66,                   // doomednum
  undead_normal_states, // spawnstate
  300,                  // spawnhealth
  undead_run_states,    // seestate
  //sfx_skesit,         // seesound
  8,                    // reactiontime
  //0,                  // attacksound
  undead_pain_states,   // painstate
  100,                  // painchance
  //sfx_popain,         // painsound
  undead_melee_states,  // meleestate
  undead_missile_states,// missilestate
  undead_die_states,   // deathstate
  NULL,                 // xdeathstate
  //sfx_skedth,         // deathsound
  10,                   // speed
  20,                   // radius
  56,                   // height
  500,                  // mass
  0,                    // damage
  //sfx_skeact,         // activesound
  MF_SOLID |
  MF_SHOOTABLE |
  MF_COUNTKILL,         // flags
  undead_raise_states   // raisestate
};

/******************************************************************************
 * MT_FATSO
 ******************************************************************************/

map_obj_state fatso_normal_states[] =
{
{true,  STATE_FATT_STND,        "FATT", 0,      15,     0,      "A_Look",               STATE_FATT_STND2,       0,      0},
{true,  STATE_FATT_STND2,       "FATT", 1,      15,     0,      "A_Look",               STATE_FATT_STND,        0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_state fatso_run_states[] =
{
{true,  STATE_FATT_RUN1,        "FATT", 0,      4,      0,      "A_Chase",              STATE_FATT_RUN2,        0,      0},
{true,  STATE_FATT_RUN2,        "FATT", 0,      4,      0,      "A_Chase",              STATE_FATT_RUN3,        0,      0},
{true,  STATE_FATT_RUN3,        "FATT", 1,      4,      0,      "A_Chase",              STATE_FATT_RUN4,        0,      0},
{true,  STATE_FATT_RUN4,        "FATT", 1,      4,      0,      "A_Chase",              STATE_FATT_RUN5,        0,      0},
{true,  STATE_FATT_RUN5,        "FATT", 2,      4,      0,      "A_Chase",              STATE_FATT_RUN6,        0,      0},
{true,  STATE_FATT_RUN6,        "FATT", 2,      4,      0,      "A_Chase",              STATE_FATT_RUN7,        0,      0},
{true,  STATE_FATT_RUN7,        "FATT", 3,      4,      0,      "A_Chase",              STATE_FATT_RUN8,        0,      0},
{true,  STATE_FATT_RUN8,        "FATT", 3,      4,      0,      "A_Chase",              STATE_FATT_RUN9,        0,      0},
{true,  STATE_FATT_RUN9,        "FATT", 4,      4,      0,      "A_Chase",              STATE_FATT_RUN10,       0,      0},
{true,  STATE_FATT_RUN10,       "FATT", 4,      4,      0,      "A_Chase",              STATE_FATT_RUN11,       0,      0},
{true,  STATE_FATT_RUN11,       "FATT", 5,      4,      0,      "A_Chase",              STATE_FATT_RUN12,       0,      0},
{true,  STATE_FATT_RUN12,       "FATT", 5,      4,      0,      "A_Chase",              STATE_FATT_RUN1,        0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_state fatso_pain_states[] =
{
{true,  STATE_FATT_PAIN,        "FATT", 9,      3,      0,      "",                     STATE_FATT_PAIN2,       0,      0},
{true,  STATE_FATT_PAIN2,       "FATT", 9,      3,      0,      "A_Pain",               STATE_FATT_RUN1,        0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_state fatso_attack_states[] =
{
{true,  STATE_FATT_ATK1,        "FATT", 6,      20,     0,      "A_FatRaise",           STATE_FATT_ATK2,        0,      0},
{true,  STATE_FATT_ATK2,        "FATT", 7,      10,     1,      "A_FatAttack1",         STATE_FATT_ATK3,        0,      0},
{true,  STATE_FATT_ATK3,        "FATT", 8,      5,      0,      "A_FaceTarget",         STATE_FATT_ATK4,        0,      0},
{true,  STATE_FATT_ATK4,        "FATT", 6,      5,      0,      "A_FaceTarget",         STATE_FATT_ATK5,        0,      0},
{true,  STATE_FATT_ATK5,        "FATT", 7,      10,     1,      "A_FatAttack2",         STATE_FATT_ATK6,        0,      0},
{true,  STATE_FATT_ATK6,        "FATT", 8,      5,      0,      "A_FaceTarget",         STATE_FATT_ATK7,        0,      0},
{true,  STATE_FATT_ATK7,        "FATT", 6,      5,      0,      "A_FaceTarget",         STATE_FATT_ATK8,        0,      0},
{true,  STATE_FATT_ATK8,        "FATT", 7,      10,     1,      "A_FatAttack3",         STATE_FATT_ATK9,        0,      0},
{true,  STATE_FATT_ATK9,        "FATT", 8,      5,      0,      "A_FaceTarget",         STATE_FATT_ATK10,       0,      0},
{true,  STATE_FATT_ATK10,       "FATT", 6,      5,      0,      "A_FaceTarget",         STATE_FATT_RUN1,        0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_state fatso_die_states[] =
{
{true,  STATE_FATT_DIE1,        "FATT", 10,     6,      0,      "",                     STATE_FATT_DIE2,        0,      0},
{true,  STATE_FATT_DIE2,        "FATT", 11,     6,      0,      "A_Scream",             STATE_FATT_DIE3,        0,      0},
{true,  STATE_FATT_DIE3,        "FATT", 12,     6,      0,      "A_Fall",               STATE_FATT_DIE4,        0,      0},
{true,  STATE_FATT_DIE4,        "FATT", 13,     6,      0,      "",                     STATE_FATT_DIE5,        0,      0},
{true,  STATE_FATT_DIE5,        "FATT", 14,     6,      0,      "",                     STATE_FATT_DIE6,        0,      0},
{true,  STATE_FATT_DIE6,        "FATT", 15,     6,      0,      "",                     STATE_FATT_DIE7,        0,      0},
{true,  STATE_FATT_DIE7,        "FATT", 16,     6,      0,      "",                     STATE_FATT_DIE8,        0,      0},
{true,  STATE_FATT_DIE8,        "FATT", 17,     6,      0,      "",                     STATE_FATT_DIE9,        0,      0},
{true,  STATE_FATT_DIE9,        "FATT", 18,     6,      0,      "",                     STATE_FATT_DIE10,       0,      0},
{true,  STATE_FATT_DIE10,       "FATT", 19,     -1,     0,      "A_BossDeath",          STATE_NULL,             0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_state fatso_xdie_states[] =
{
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_state fatso_raise_states[] =
{
{true,  STATE_FATT_RAISE1,      "FATT", 17,     5,      0,      "",                     STATE_FATT_RAISE2,      0,      0},
{true,  STATE_FATT_RAISE2,      "FATT", 16,     5,      0,      "",                     STATE_FATT_RAISE3,      0,      0},
{true,  STATE_FATT_RAISE3,      "FATT", 15,     5,      0,      "",                     STATE_FATT_RAISE4,      0,      0},
{true,  STATE_FATT_RAISE4,      "FATT", 14,     5,      0,      "",                     STATE_FATT_RAISE5,      0,      0},
{true,  STATE_FATT_RAISE5,      "FATT", 13,     5,      0,      "",                     STATE_FATT_RAISE6,      0,      0},
{true,  STATE_FATT_RAISE6,      "FATT", 12,     5,      0,      "",                     STATE_FATT_RAISE7,      0,      0},
{true,  STATE_FATT_RAISE7,      "FATT", 11,     5,      0,      "",                     STATE_FATT_RAISE8,      0,      0},
{true,  STATE_FATT_RAISE8,      "FATT", 10,     5,      0,      "",                     STATE_FATT_RUN1,        0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_defn fatso_defn =
{                       // MT_FATSO
  67,                   // doomednum
  fatso_normal_states,  // spawnstate
  600,                  // spawnhealth
  fatso_run_states,     // seestate
  //sfx_mansit,         // seesound
  8,                    // reactiontime
  //0,                  // attacksound
  fatso_pain_states,    // painstate
  80,                   // painchance
  //sfx_mnpain,         // painsound
  0,                    // meleestate
  fatso_attack_states,  // missilestate
  fatso_die_states,     // deathstate
  NULL,                 // xdeathstate
  //sfx_mandth,         // deathsound
  8,                    // speed
  48,                   // radius
  64,                   // height
  1000,                 // mass
  0,                    // damage
  //sfx_posact,         // activesound
  MF_SOLID |
  MF_SHOOTABLE |
  MF_COUNTKILL,         // flags
  fatso_raise_states    // raisestate
};

/******************************************************************************
 * MT_CHAINGUY
 ******************************************************************************/

map_obj_state chainguy_normal_states[] =
{
{true,  STATE_CPOS_STND,        "CPOS", 0,      10,     0,      "A_Look",               STATE_CPOS_STND2,       0,      0},
{true,  STATE_CPOS_STND2,       "CPOS", 1,      10,     0,      "A_Look",               STATE_CPOS_STND,        0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_state chainguy_run_states[] =
{
{true,  STATE_CPOS_RUN1,        "CPOS", 0,      3,      0,      "A_Chase",              STATE_CPOS_RUN2,        0,      0},
{true,  STATE_CPOS_RUN2,        "CPOS", 0,      3,      0,      "A_Chase",              STATE_CPOS_RUN3,        0,      0},
{true,  STATE_CPOS_RUN3,        "CPOS", 1,      3,      0,      "A_Chase",              STATE_CPOS_RUN4,        0,      0},
{true,  STATE_CPOS_RUN4,        "CPOS", 1,      3,      0,      "A_Chase",              STATE_CPOS_RUN5,        0,      0},
{true,  STATE_CPOS_RUN5,        "CPOS", 2,      3,      0,      "A_Chase",              STATE_CPOS_RUN6,        0,      0},
{true,  STATE_CPOS_RUN6,        "CPOS", 2,      3,      0,      "A_Chase",              STATE_CPOS_RUN7,        0,      0},
{true,  STATE_CPOS_RUN7,        "CPOS", 3,      3,      0,      "A_Chase",              STATE_CPOS_RUN8,        0,      0},
{true,  STATE_CPOS_RUN8,        "CPOS", 3,      3,      0,      "A_Chase",              STATE_CPOS_RUN1,        0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_state chainguy_pain_states[] =
{
{true,  STATE_CPOS_PAIN,        "CPOS", 6,      3,      0,      "",                     STATE_CPOS_PAIN2,       0,      0},
{true,  STATE_CPOS_PAIN2,       "CPOS", 6,      3,      0,      "A_Pain",               STATE_CPOS_RUN1,        0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_state chainguy_attack_states[] =
{
{true,  STATE_CPOS_ATK1,        "CPOS", 4,      10,     0,      "A_FaceTarget",         STATE_CPOS_ATK2,        0,      0},
{true,  STATE_CPOS_ATK2,        "CPOS", 5,      4,      1,      "A_CPosAttack",         STATE_CPOS_ATK3,        0,      0},
{true,  STATE_CPOS_ATK3,        "CPOS", 4,      4,      1,      "A_CPosAttack",         STATE_CPOS_ATK4,        0,      0},
{true,  STATE_CPOS_ATK4,        "CPOS", 5,      1,      0,      "A_CPosRefire",         STATE_CPOS_ATK2,        0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_state chainguy_die_states[] =
{
{true,  STATE_CPOS_DIE1,        "CPOS", 7,      5,      0,      "",                     STATE_CPOS_DIE2,        0,      0},
{true,  STATE_CPOS_DIE2,        "CPOS", 8,      5,      0,      "A_Scream",             STATE_CPOS_DIE3,        0,      0},
{true,  STATE_CPOS_DIE3,        "CPOS", 9,      5,      0,      "A_Fall",               STATE_CPOS_DIE4,        0,      0},
{true,  STATE_CPOS_DIE4,        "CPOS", 10,     5,      0,      "",                     STATE_CPOS_DIE5,        0,      0},
{true,  STATE_CPOS_DIE5,        "CPOS", 11,     5,      0,      "",                     STATE_CPOS_DIE6,        0,      0},
{true,  STATE_CPOS_DIE6,        "CPOS", 12,     5,      0,      "",                     STATE_CPOS_DIE7,        0,      0},
{true,  STATE_CPOS_DIE7,        "CPOS", 13,     -1,     0,      "",                     STATE_NULL,             0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_state chainguy_xdie_states[] =
{
{true,  STATE_CPOS_XDIE1,       "CPOS", 14,     5,      0,      "",                     STATE_CPOS_XDIE2,       0,      0},
{true,  STATE_CPOS_XDIE2,       "CPOS", 15,     5,      0,      "A_XScream",            STATE_CPOS_XDIE3,       0,      0},
{true,  STATE_CPOS_XDIE3,       "CPOS", 16,     5,      0,      "A_Fall",               STATE_CPOS_XDIE4,       0,      0},
{true,  STATE_CPOS_XDIE4,       "CPOS", 17,     5,      0,      "",                     STATE_CPOS_XDIE5,       0,      0},
{true,  STATE_CPOS_XDIE5,       "CPOS", 18,     5,      0,      "",                     STATE_CPOS_XDIE6,       0,      0},
{true,  STATE_CPOS_XDIE6,       "CPOS", 19,     -1,     0,      "",                     STATE_NULL,             0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_state chainguy_raise_states[] =
{
{true,  STATE_CPOS_RAISE1,      "CPOS", 13,     5,      0,      "",                     STATE_CPOS_RAISE2,      0,      0},
{true,  STATE_CPOS_RAISE2,      "CPOS", 12,     5,      0,      "",                     STATE_CPOS_RAISE3,      0,      0},
{true,  STATE_CPOS_RAISE3,      "CPOS", 11,     5,      0,      "",                     STATE_CPOS_RAISE4,      0,      0},
{true,  STATE_CPOS_RAISE4,      "CPOS", 10,     5,      0,      "",                     STATE_CPOS_RAISE5,      0,      0},
{true,  STATE_CPOS_RAISE5,      "CPOS", 9,      5,      0,      "",                     STATE_CPOS_RAISE6,      0,      0},
{true,  STATE_CPOS_RAISE6,      "CPOS", 8,      5,      0,      "",                     STATE_CPOS_RAISE7,      0,      0},
{true,  STATE_CPOS_RAISE7,      "CPOS", 7,      5,      0,      "",                     STATE_CPOS_RUN1,        0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_defn chainguy_defn =
{                       // MT_CHAINGUY
  65,                   // doomednum
  chainguy_normal_states,// spawnstate
  70,                   // spawnhealth
  chainguy_run_states,  // seestate
  //sfx_posit2,         // seesound
  8,                    // reactiontime
  //0,                  // attacksound
  chainguy_pain_states, // painstate
  170,                  // painchance
  //sfx_popain,         // painsound
  0,                    // meleestate
  chainguy_attack_states,// missilestate
  chainguy_die_states,  // deathstate
  chainguy_xdie_states, // xdeathstate
  //sfx_podth2,         // deathsound
  8,                    // speed
  20,                   // radius
  56,                   // height
  100,                  // mass
  0,                    // damage
  //sfx_posact,         // activesound
  MF_SOLID |
  MF_SHOOTABLE |
  MF_COUNTKILL,         // flags
  chainguy_raise_states // raisestate
};

/******************************************************************************
 * MT_TROOP
 ******************************************************************************/

map_obj_state troop_normal_states[] =
{
{true,  STATE_TROO_STND,        "TROO", 0,      10,     0,      "A_Look",               STATE_TROO_STND2,       0,      0},
{true,  STATE_TROO_STND2,       "TROO", 1,      10,     0,      "A_Look",               STATE_TROO_STND,        0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_state troop_run_states[] =
{
{true,  STATE_TROO_RUN1,        "TROO", 0,      3,      0,      "A_Chase",              STATE_TROO_RUN2,        0,      0},
{true,  STATE_TROO_RUN2,        "TROO", 0,      3,      0,      "A_Chase",              STATE_TROO_RUN3,        0,      0},
{true,  STATE_TROO_RUN3,        "TROO", 1,      3,      0,      "A_Chase",              STATE_TROO_RUN4,        0,      0},
{true,  STATE_TROO_RUN4,        "TROO", 1,      3,      0,      "A_Chase",              STATE_TROO_RUN5,        0,      0},
{true,  STATE_TROO_RUN5,        "TROO", 2,      3,      0,      "A_Chase",              STATE_TROO_RUN6,        0,      0},
{true,  STATE_TROO_RUN6,        "TROO", 2,      3,      0,      "A_Chase",              STATE_TROO_RUN7,        0,      0},
{true,  STATE_TROO_RUN7,        "TROO", 3,      3,      0,      "A_Chase",              STATE_TROO_RUN8,        0,      0},
{true,  STATE_TROO_RUN8,        "TROO", 3,      3,      0,      "A_Chase",              STATE_TROO_RUN1,        0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_state troop_pain_states[] =
{
{true,  STATE_TROO_PAIN,        "TROO", 7,      2,      0,      "",                     STATE_TROO_PAIN2,       0,      0},
{true,  STATE_TROO_PAIN2,       "TROO", 7,      2,      0,      "A_Pain",               STATE_TROO_RUN1,        0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_state troop_attack_states[] =
{
{true,  STATE_TROO_ATK1,        "TROO", 4,      8,      0,      "A_FaceTarget",         STATE_TROO_ATK2,        0,      0},
{true,  STATE_TROO_ATK2,        "TROO", 5,      8,      0,      "A_FaceTarget",         STATE_TROO_ATK3,        0,      0},
{true,  STATE_TROO_ATK3,        "TROO", 6,      6,      0,      "A_TroopAttack",        STATE_TROO_RUN1,        0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_state troop_die_states[] =
{
{true,  STATE_TROO_DIE1,        "TROO", 8,      8,      0,      "",                     STATE_TROO_DIE2,        0,      0},
{true,  STATE_TROO_DIE2,        "TROO", 9,      8,      0,      "A_Scream",             STATE_TROO_DIE3,        0,      0},
{true,  STATE_TROO_DIE3,        "TROO", 10,     6,      0,      "",                     STATE_TROO_DIE4,        0,      0},
{true,  STATE_TROO_DIE4,        "TROO", 11,     6,      0,      "A_Fall",               STATE_TROO_DIE5,        0,      0},
{true,  STATE_TROO_DIE5,        "TROO", 12,     -1,     0,      "",                     STATE_NULL,             0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_state troop_xdie_states[] =
{
{true,  STATE_TROO_XDIE1,       "TROO", 13,     5,      0,      "",                     STATE_TROO_XDIE2,       0,      0},
{true,  STATE_TROO_XDIE2,       "TROO", 14,     5,      0,      "A_XScream",            STATE_TROO_XDIE3,       0,      0},
{true,  STATE_TROO_XDIE3,       "TROO", 15,     5,      0,      "",                     STATE_TROO_XDIE4,       0,      0},
{true,  STATE_TROO_XDIE4,       "TROO", 16,     5,      0,      "A_Fall",               STATE_TROO_XDIE5,       0,      0},
{true,  STATE_TROO_XDIE5,       "TROO", 17,     5,      0,      "",                     STATE_TROO_XDIE6,       0,      0},
{true,  STATE_TROO_XDIE6,       "TROO", 18,     5,      0,      "",                     STATE_TROO_XDIE7,       0,      0},
{true,  STATE_TROO_XDIE7,       "TROO", 19,     5,      0,      "",                     STATE_TROO_XDIE8,       0,      0},
{true,  STATE_TROO_XDIE8,       "TROO", 20,     -1,     0,      "",                     STATE_NULL,             0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_state troop_raise_states[] =
{
{true,  STATE_TROO_RAISE1,      "TROO", 12,     8,      0,      "",                     STATE_TROO_RAISE2,      0,      0},
{true,  STATE_TROO_RAISE2,      "TROO", 11,     8,      0,      "",                     STATE_TROO_RAISE3,      0,      0},
{true,  STATE_TROO_RAISE3,      "TROO", 10,     6,      0,      "",                     STATE_TROO_RAISE4,      0,      0},
{true,  STATE_TROO_RAISE4,      "TROO", 9,      6,      0,      "",                     STATE_TROO_RAISE5,      0,      0},
{true,  STATE_TROO_RAISE5,      "TROO", 8,      6,      0,      "",                     STATE_TROO_RUN1,        0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_defn troop_defn =
{                       // MT_TROOP
  3001,                 // doomednum
  troop_normal_states,  // spawnstate
  60,                   // spawnhealth
  troop_run_states,     // seestate
  //sfx_bgsit1,         // seesound
  8,                    // reactiontime
  //0,                  // attacksound
  troop_pain_states,    // painstate
  200,                  // painchance
  //sfx_popain,         // painsound
  troop_attack_states,  // meleestate
  troop_attack_states,  // missilestate
  troop_die_states,     // deathstate
  troop_xdie_states,    // xdeathstate
  //sfx_bgdth1,         // deathsound
  8,                    // speed
  20,                   // radius
  56,                   // height
  100,                  // mass
  0,                    // damage
  //sfx_bgact,          // activesound
  MF_SOLID |
  MF_SHOOTABLE |
  MF_COUNTKILL,         // flags
  troop_raise_states    // raisestate
};

/******************************************************************************
 * MT_SERGEANT
 ******************************************************************************/

map_obj_state sergeant_normal_states[] =
{
{true,  STATE_SARG_STND,        "SARG", 0,      10,     0,      "A_Look",               STATE_SARG_STND2,       0,      0},
{true,  STATE_SARG_STND2,       "SARG", 1,      10,     0,      "A_Look",               STATE_SARG_STND,        0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_state sergeant_run_states[] =
{
{true,  STATE_SARG_RUN1,        "SARG", 0,      2,      0,      "A_Chase",              STATE_SARG_RUN2,        0,      0},
{true,  STATE_SARG_RUN2,        "SARG", 0,      2,      0,      "A_Chase",              STATE_SARG_RUN3,        0,      0},
{true,  STATE_SARG_RUN3,        "SARG", 1,      2,      0,      "A_Chase",              STATE_SARG_RUN4,        0,      0},
{true,  STATE_SARG_RUN4,        "SARG", 1,      2,      0,      "A_Chase",              STATE_SARG_RUN5,        0,      0},
{true,  STATE_SARG_RUN5,        "SARG", 2,      2,      0,      "A_Chase",              STATE_SARG_RUN6,        0,      0},
{true,  STATE_SARG_RUN6,        "SARG", 2,      2,      0,      "A_Chase",              STATE_SARG_RUN7,        0,      0},
{true,  STATE_SARG_RUN7,        "SARG", 3,      2,      0,      "A_Chase",              STATE_SARG_RUN8,        0,      0},
{true,  STATE_SARG_RUN8,        "SARG", 3,      2,      0,      "A_Chase",              STATE_SARG_RUN1,        0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_state sergeant_pain_states[] =
{
{true,  STATE_SARG_PAIN,        "SARG", 7,      2,      0,      "",                     STATE_SARG_PAIN2,       0,      0},
{true,  STATE_SARG_PAIN2,       "SARG", 7,      2,      0,      "A_Pain",               STATE_SARG_RUN1,        0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_state sergeant_attack_states[] =
{
{true,  STATE_SARG_ATK1,        "SARG", 4,      8,      0,      "A_FaceTarget",         STATE_SARG_ATK2,        0,      0},
{true,  STATE_SARG_ATK2,        "SARG", 5,      8,      0,      "A_FaceTarget",         STATE_SARG_ATK3,        0,      0},
{true,  STATE_SARG_ATK3,        "SARG", 6,      8,      0,      "A_SargAttack",         STATE_SARG_RUN1,        0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_state sergeant_die_states[] =
{
{true,  STATE_SARG_DIE1,        "SARG", 8,      8,      0,      "",                     STATE_SARG_DIE2,        0,      0},
{true,  STATE_SARG_DIE2,        "SARG", 9,      8,      0,      "A_Scream",             STATE_SARG_DIE3,        0,      0},
{true,  STATE_SARG_DIE3,        "SARG", 10,     4,      0,      "",                     STATE_SARG_DIE4,        0,      0},
{true,  STATE_SARG_DIE4,        "SARG", 11,     4,      0,      "A_Fall",               STATE_SARG_DIE5,        0,      0},
{true,  STATE_SARG_DIE5,        "SARG", 12,     4,      0,      "",                     STATE_SARG_DIE6,        0,      0},
{true,  STATE_SARG_DIE6,        "SARG", 13,     -1,     0,      "",                     STATE_NULL,             0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_state sergeant_raise_states[] =
{
{true,  STATE_SARG_RAISE1,      "SARG", 13,     5,      0,      "",                     STATE_SARG_RAISE2,      0,      0},
{true,  STATE_SARG_RAISE2,      "SARG", 12,     5,      0,      "",                     STATE_SARG_RAISE3,      0,      0},
{true,  STATE_SARG_RAISE3,      "SARG", 11,     5,      0,      "",                     STATE_SARG_RAISE4,      0,      0},
{true,  STATE_SARG_RAISE4,      "SARG", 10,     5,      0,      "",                     STATE_SARG_RAISE5,      0,      0},
{true,  STATE_SARG_RAISE5,      "SARG", 9,      5,      0,      "",                     STATE_SARG_RAISE6,      0,      0},
{true,  STATE_SARG_RAISE6,      "SARG", 8,      5,      0,      "",                     STATE_SARG_RUN1,        0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_defn sergeant_defn =
{                       // MT_SERGEANT
  3002,                 // doomednum
  sergeant_normal_states,// spawnstate
  150,                  // spawnhealth
  sergeant_run_states,  // seestate
  //sfx_sgtsit,         // seesound
  8,                    // reactiontime
  //sfx_sgtatk,         // attacksound
  sergeant_pain_states, // painstate
  180,                  // painchance
  //sfx_dmpain,         // painsound
  sergeant_attack_states,// meleestate
  0,                    // missilestate
  sergeant_die_states,  // deathstate
  NULL,                 // xdeathstate
  //sfx_sgtdth,         // deathsound
  10,                   // speed
  30,                   // radius
  56,                   // height
  400,                  // mass
  0,                    // damage
  //sfx_dmact,          // activesound
  MF_SOLID |
  MF_SHOOTABLE |
  MF_COUNTKILL,         // flags
  sergeant_raise_states // raisestate
};

/******************************************************************************
 * MT_SHADOWS
 ******************************************************************************/

map_obj_defn shadows_defn =
{                       // MT_SHADOWS
  58,                   // doomednum
  sergeant_normal_states,// spawnstate
  150,                  // spawnhealth
  sergeant_run_states,  // seestate
  //sfx_sgtsit,         // seesound
  8,                    // reactiontime
  //sfx_sgtatk,         // attacksound
  sergeant_pain_states, // painstate
  180,                  // painchance
  //sfx_dmpain,         // painsound
  sergeant_attack_states,// meleestate
  0,                    // missilestate
  sergeant_die_states,  // deathstate
  NULL,                 // xdeathstate
  //sfx_sgtdth,         // deathsound
  10,                   // speed
  30,                   // radius
  56,                   // height
  400,                  // mass
  0,                    // damage
  //sfx_dmact,          // activesound
  MF_SOLID |
  MF_SHOOTABLE |
  MF_SHADOW |
  MF_COUNTKILL,         // flags
  sergeant_raise_states // raisestate
};

/******************************************************************************
 * MT_HEAD
 ******************************************************************************/

map_obj_state head_normal_states[] =
{
{true,  STATE_HEAD_STND,        "HEAD", 0,      10,     0,      "A_Look",               STATE_HEAD_STND,        0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_state head_run_states[] =
{
{true,  STATE_HEAD_RUN1,        "HEAD", 0,      3,      0,      "A_Chase",              STATE_HEAD_RUN1,        0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_state head_pain_states[] =
{
{true,  STATE_HEAD_PAIN,        "HEAD", 4,      3,      0,      "",                     STATE_HEAD_PAIN2,       0,      0},
{true,  STATE_HEAD_PAIN2,       "HEAD", 4,      3,      0,      "A_Pain",               STATE_HEAD_PAIN3,       0,      0},
{true,  STATE_HEAD_PAIN3,       "HEAD", 5,      6,      0,      "",                     STATE_HEAD_RUN1,        0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_state head_attack_states[] =
{
{true,  STATE_HEAD_ATK1,        "HEAD", 1,      5,      0,      "A_FaceTarget",         STATE_HEAD_ATK2,        0,      0},
{true,  STATE_HEAD_ATK2,        "HEAD", 2,      5,      0,      "A_FaceTarget",         STATE_HEAD_ATK3,        0,      0},
{true,  STATE_HEAD_ATK3,        "HEAD", 3,      5,      1,      "A_HeadAttack",         STATE_HEAD_RUN1,        0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_state head_die_states[] =
{
{true,  STATE_HEAD_DIE1,        "HEAD", 6,      8,      0,      "",                     STATE_HEAD_DIE2,        0,      0},
{true,  STATE_HEAD_DIE2,        "HEAD", 7,      8,      0,      "A_Scream",             STATE_HEAD_DIE3,        0,      0},
{true,  STATE_HEAD_DIE3,        "HEAD", 8,      8,      0,      "",                     STATE_HEAD_DIE4,        0,      0},
{true,  STATE_HEAD_DIE4,        "HEAD", 9,      8,      0,      "",                     STATE_HEAD_DIE5,        0,      0},
{true,  STATE_HEAD_DIE5,        "HEAD", 10,     8,      0,      "A_Fall",               STATE_HEAD_DIE6,        0,      0},
{true,  STATE_HEAD_DIE6,        "HEAD", 11,     -1,     0,      "",                     STATE_NULL,             0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_state head_raise_states[] =
{
{true,  STATE_HEAD_RAISE1,      "HEAD", 11,     8,      0,      "",                     STATE_HEAD_RAISE2,      0,      0},
{true,  STATE_HEAD_RAISE2,      "HEAD", 10,     8,      0,      "",                     STATE_HEAD_RAISE3,      0,      0},
{true,  STATE_HEAD_RAISE3,      "HEAD", 9,      8,      0,      "",                     STATE_HEAD_RAISE4,      0,      0},
{true,  STATE_HEAD_RAISE4,      "HEAD", 8,      8,      0,      "",                     STATE_HEAD_RAISE5,      0,      0},
{true,  STATE_HEAD_RAISE5,      "HEAD", 7,      8,      0,      "",                     STATE_HEAD_RAISE6,      0,      0},
{true,  STATE_HEAD_RAISE6,      "HEAD", 6,      8,      0,      "",                     STATE_HEAD_RUN1,        0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_defn head_defn =
{                       // MT_HEAD
  3005,                 // doomednum
  head_normal_states,   // spawnstate
  400,                  // spawnhealth
  head_run_states,      // seestate
  //sfx_cacsit,         // seesound
  8,                    // reactiontime
  //0,                  // attacksound
  head_pain_states,     // painstate
  128,                  // painchance
  //sfx_dmpain,         // painsound
  0,                    // meleestate
  head_attack_states,   // missilestate
  head_die_states,      // deathstate
  NULL,                 // xdeathstate
  //sfx_cacdth,         // deathsound
  8,                    // speed
  31,                   // radius
  56,                   // height
  400,                  // mass
  0,                    // damage
  //sfx_dmact,          // activesound
  MF_SOLID |
  MF_SHOOTABLE |
  MF_FLOAT |
  MF_NOGRAVITY |
  MF_COUNTKILL,         // flags
  head_raise_states     // raisestate
};

/******************************************************************************
 * MT_BRUISER
 ******************************************************************************/

map_obj_state bruiser_normal_states[] =
{
{true,  STATE_BOSS_STND,        "BOSS", 0,      10,     0,      "A_Look",               STATE_BOSS_STND2,       0,      0},
{true,  STATE_BOSS_STND2,       "BOSS", 1,      10,     0,      "A_Look",               STATE_BOSS_STND,        0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_state bruiser_run_states[] =
{
{true,  STATE_BOSS_RUN1,        "BOSS", 0,      3,      0,      "A_Chase",              STATE_BOSS_RUN2,        0,      0},
{true,  STATE_BOSS_RUN2,        "BOSS", 0,      3,      0,      "A_Chase",              STATE_BOSS_RUN3,        0,      0},
{true,  STATE_BOSS_RUN3,        "BOSS", 1,      3,      0,      "A_Chase",              STATE_BOSS_RUN4,        0,      0},
{true,  STATE_BOSS_RUN4,        "BOSS", 1,      3,      0,      "A_Chase",              STATE_BOSS_RUN5,        0,      0},
{true,  STATE_BOSS_RUN5,        "BOSS", 2,      3,      0,      "A_Chase",              STATE_BOSS_RUN6,        0,      0},
{true,  STATE_BOSS_RUN6,        "BOSS", 2,      3,      0,      "A_Chase",              STATE_BOSS_RUN7,        0,      0},
{true,  STATE_BOSS_RUN7,        "BOSS", 3,      3,      0,      "A_Chase",              STATE_BOSS_RUN8,        0,      0},
{true,  STATE_BOSS_RUN8,        "BOSS", 3,      3,      0,      "A_Chase",              STATE_BOSS_RUN1,        0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_state bruiser_pain_states[] =
{
{true,  STATE_BOSS_PAIN,        "BOSS", 7,      2,      0,      "",                     STATE_BOSS_PAIN2,       0,      0},
{true,  STATE_BOSS_PAIN2,       "BOSS", 7,      2,      0,      "A_Pain",               STATE_BOSS_RUN1,        0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_state bruiser_attack_states[] =
{
{true,  STATE_BOSS_ATK1,        "BOSS", 4,      8,      0,      "A_FaceTarget",         STATE_BOSS_ATK2,        0,      0},
{true,  STATE_BOSS_ATK2,        "BOSS", 5,      8,      0,      "A_FaceTarget",         STATE_BOSS_ATK3,        0,      0},
{true,  STATE_BOSS_ATK3,        "BOSS", 6,      8,      0,      "A_BruisAttack",        STATE_BOSS_RUN1,        0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_state bruiser_die_states[] =
{
{true,  STATE_BOSS_DIE1,        "BOSS", 8,      8,      0,      "",                     STATE_BOSS_DIE2,        0,      0},
{true,  STATE_BOSS_DIE2,        "BOSS", 9,      8,      0,      "A_Scream",             STATE_BOSS_DIE3,        0,      0},
{true,  STATE_BOSS_DIE3,        "BOSS", 10,     8,      0,      "",                     STATE_BOSS_DIE4,        0,      0},
{true,  STATE_BOSS_DIE4,        "BOSS", 11,     8,      0,      "A_Fall",               STATE_BOSS_DIE5,        0,      0},
{true,  STATE_BOSS_DIE5,        "BOSS", 12,     8,      0,      "",                     STATE_BOSS_DIE6,        0,      0},
{true,  STATE_BOSS_DIE6,        "BOSS", 13,     8,      0,      "",                     STATE_BOSS_DIE7,        0,      0},
{true,  STATE_BOSS_DIE7,        "BOSS", 14,     -1,     0,      "A_BossDeath",          STATE_NULL,             0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_state bruiser_raise_states[] =
{
{true,  STATE_BOSS_RAISE1,      "BOSS", 14,     8,      0,      "",                     STATE_BOSS_RAISE2,      0,      0},
{true,  STATE_BOSS_RAISE2,      "BOSS", 13,     8,      0,      "",                     STATE_BOSS_RAISE3,      0,      0},
{true,  STATE_BOSS_RAISE3,      "BOSS", 12,     8,      0,      "",                     STATE_BOSS_RAISE4,      0,      0},
{true,  STATE_BOSS_RAISE4,      "BOSS", 11,     8,      0,      "",                     STATE_BOSS_RAISE5,      0,      0},
{true,  STATE_BOSS_RAISE5,      "BOSS", 10,     8,      0,      "",                     STATE_BOSS_RAISE6,      0,      0},
{true,  STATE_BOSS_RAISE6,      "BOSS", 9,      8,      0,      "",                     STATE_BOSS_RAISE7,      0,      0},
{true,  STATE_BOSS_RAISE7,      "BOSS", 8,      8,      0,      "",                     STATE_BOSS_RUN1,        0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_defn bruiser_defn =
{                       // MT_BRUISER
  3003,                 // doomednum
  bruiser_normal_states,// spawnstate
  1000,                 // spawnhealth
  bruiser_run_states,   // seestate
  //sfx_brssit,         // seesound
  8,                    // reactiontime
  //0,                  // attacksound
  bruiser_pain_states,  // painstate
  50,                   // painchance
  //sfx_dmpain,         // painsound
  bruiser_attack_states,// meleestate
  bruiser_attack_states,// missilestate
  bruiser_die_states,   // deathstate
  NULL,                 // xdeathstate
  //sfx_brsdth,         // deathsound
  8,                    // speed
  24,                   // radius
  64,                   // height
  1000,                 // mass
  0,                    // damage
  //sfx_dmact,          // activesound
  MF_SOLID |
  MF_SHOOTABLE |
  MF_COUNTKILL,         // flags
  bruiser_raise_states  // raisestate
};

/******************************************************************************
 * MT_KNIGHT
 ******************************************************************************/

map_obj_state knight_normal_states[] =
{
{true,  STATE_BOS2_STND,        "BOS2", 0,      10,     0,      "A_Look",               STATE_BOS2_STND2,       0,      0},
{true,  STATE_BOS2_STND2,       "BOS2", 1,      10,     0,      "A_Look",               STATE_BOS2_STND,        0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_state knight_run_states[] =
{
{true,  STATE_BOS2_RUN1,        "BOS2", 0,      3,      0,      "A_Chase",              STATE_BOS2_RUN2,        0,      0},
{true,  STATE_BOS2_RUN2,        "BOS2", 0,      3,      0,      "A_Chase",              STATE_BOS2_RUN3,        0,      0},
{true,  STATE_BOS2_RUN3,        "BOS2", 1,      3,      0,      "A_Chase",              STATE_BOS2_RUN4,        0,      0},
{true,  STATE_BOS2_RUN4,        "BOS2", 1,      3,      0,      "A_Chase",              STATE_BOS2_RUN5,        0,      0},
{true,  STATE_BOS2_RUN5,        "BOS2", 2,      3,      0,      "A_Chase",              STATE_BOS2_RUN6,        0,      0},
{true,  STATE_BOS2_RUN6,        "BOS2", 2,      3,      0,      "A_Chase",              STATE_BOS2_RUN7,        0,      0},
{true,  STATE_BOS2_RUN7,        "BOS2", 3,      3,      0,      "A_Chase",              STATE_BOS2_RUN8,        0,      0},
{true,  STATE_BOS2_RUN8,        "BOS2", 3,      3,      0,      "A_Chase",              STATE_BOS2_RUN1,        0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_state knight_pain_states[] =
{
{true,  STATE_BOS2_PAIN,        "BOS2", 7,      2,      0,      "",                     STATE_BOS2_PAIN2,       0,      0},
{true,  STATE_BOS2_PAIN2,       "BOS2", 7,      2,      0,      "A_Pain",               STATE_BOS2_RUN1,        0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_state knight_attack_states[] =
{
{true,  STATE_BOS2_ATK1,        "BOS2", 4,      8,      0,      "A_FaceTarget",         STATE_BOS2_ATK2,        0,      0},
{true,  STATE_BOS2_ATK2,        "BOS2", 5,      8,      0,      "A_FaceTarget",         STATE_BOS2_ATK3,        0,      0},
{true,  STATE_BOS2_ATK3,        "BOS2", 6,      8,      0,      "A_BruisAttack",        STATE_BOS2_RUN1,        0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_state knight_die_states[] =
{
{true,  STATE_BOS2_DIE1,        "BOS2", 8,      8,      0,      "",                     STATE_BOS2_DIE2,        0,      0},
{true,  STATE_BOS2_DIE2,        "BOS2", 9,      8,      0,      "A_Scream",             STATE_BOS2_DIE3,        0,      0},
{true,  STATE_BOS2_DIE3,        "BOS2", 10,     8,      0,      "",                     STATE_BOS2_DIE4,        0,      0},
{true,  STATE_BOS2_DIE4,        "BOS2", 11,     8,      0,      "A_Fall",               STATE_BOS2_DIE5,        0,      0},
{true,  STATE_BOS2_DIE5,        "BOS2", 12,     8,      0,      "",                     STATE_BOS2_DIE6,        0,      0},
{true,  STATE_BOS2_DIE6,        "BOS2", 13,     8,      0,      "",                     STATE_BOS2_DIE7,        0,      0},
{true,  STATE_BOS2_DIE7,        "BOS2", 14,     -1,     0,      "",                     STATE_NULL,             0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_state knight_raise_states[] =
{
{true,  STATE_BOS2_RAISE1,      "BOS2", 14,     8,      0,      "",                     STATE_BOS2_RAISE2,      0,      0},
{true,  STATE_BOS2_RAISE2,      "BOS2", 13,     8,      0,      "",                     STATE_BOS2_RAISE3,      0,      0},
{true,  STATE_BOS2_RAISE3,      "BOS2", 12,     8,      0,      "",                     STATE_BOS2_RAISE4,      0,      0},
{true,  STATE_BOS2_RAISE4,      "BOS2", 11,     8,      0,      "",                     STATE_BOS2_RAISE5,      0,      0},
{true,  STATE_BOS2_RAISE5,      "BOS2", 10,     8,      0,      "",                     STATE_BOS2_RAISE6,      0,      0},
{true,  STATE_BOS2_RAISE6,      "BOS2", 9,      8,      0,      "",                     STATE_BOS2_RAISE7,      0,      0},
{true,  STATE_BOS2_RAISE7,      "BOS2", 8,      8,      0,      "",                     STATE_BOS2_RUN1,        0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_defn knight_defn =
{                       // MT_KNIGHT
  69,                   // doomednum
  knight_normal_states, // spawnstate
  500,                  // spawnhealth
  knight_run_states,    // seestate
  //sfx_kntsit,         // seesound
  8,                    // reactiontime
  //0,                  // attacksound
  knight_pain_states,   // painstate
  50,                   // painchance
  //sfx_dmpain,         // painsound
  knight_attack_states, // meleestate
  knight_attack_states, // missilestate
  knight_die_states,    // deathstate
  NULL,                 // xdeathstate
  //sfx_kntdth,         // deathsound
  8,                    // speed
  24,                   // radius
  64,                   // height
  1000,                 // mass
  0,                    // damage
  //sfx_dmact,          // activesound
  MF_SOLID |
  MF_SHOOTABLE |
  MF_COUNTKILL,         // flags
  knight_die_states     // raisestate
};

/******************************************************************************
 * MT_SKULL
 ******************************************************************************/

map_obj_state skull_normal_states[] =
{
{true,  STATE_SKULL_STND,       "SKUL", 0,      10,     1,      "A_Look",               STATE_SKULL_STND2,      0,      0},
{true,  STATE_SKULL_STND2,      "SKUL", 1,      10,     1,      "A_Look",               STATE_SKULL_STND,       0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_state skull_run_states[] =
{
{true,  STATE_SKULL_RUN1,       "SKUL", 0,      6,      1,      "A_Chase",              STATE_SKULL_RUN2,       0,      0},
{true,  STATE_SKULL_RUN2,       "SKUL", 1,      6,      1,      "A_Chase",              STATE_SKULL_RUN1,       0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_state skull_pain_states[] =
{
{true,  STATE_SKULL_PAIN,       "SKUL", 4,      3,      1,      "",                     STATE_SKULL_PAIN2,      0,      0},
{true,  STATE_SKULL_PAIN2,      "SKUL", 4,      3,      1,      "A_Pain",               STATE_SKULL_RUN1,       0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_state skull_attack_states[] =
{
{true,  STATE_SKULL_ATK1,       "SKUL", 2,      10,     1,      "A_FaceTarget",         STATE_SKULL_ATK2,       0,      0},
{true,  STATE_SKULL_ATK2,       "SKUL", 3,      4,      1,      "A_SkullAttack",        STATE_SKULL_ATK3,       0,      0},
{true,  STATE_SKULL_ATK3,       "SKUL", 2,      4,      1,      "",                     STATE_SKULL_ATK4,       0,      0},
{true,  STATE_SKULL_ATK4,       "SKUL", 3,      4,      1,      "",                     STATE_SKULL_ATK3,       0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_state skull_die_states[] =
{
{true,  STATE_SKULL_DIE1,       "SKUL", 5,      6,      1,      "",                     STATE_SKULL_DIE2,       0,      0},
{true,  STATE_SKULL_DIE2,       "SKUL", 6,      6,      1,      "A_Scream",             STATE_SKULL_DIE3,       0,      0},
{true,  STATE_SKULL_DIE3,       "SKUL", 7,      6,      1,      "",                     STATE_SKULL_DIE4,       0,      0},
{true,  STATE_SKULL_DIE4,       "SKUL", 8,      6,      1,      "A_Fall",               STATE_SKULL_DIE5,       0,      0},
{true,  STATE_SKULL_DIE5,       "SKUL", 9,      6,      0,      "",                     STATE_SKULL_DIE6,       0,      0},
{true,  STATE_SKULL_DIE6,       "SKUL", 10,     6,      0,      "",                     STATE_NULL,             0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_defn skull_defn =
{                       // MT_SKULL
  3006,                 // doomednum
  skull_normal_states,  // spawnstate
  100,                  // spawnhealth
  skull_run_states,     // seestate
  //0,                  // seesound
  8,                    // reactiontime
  //sfx_sklatk,         // attacksound
  skull_pain_states,    // painstate
  256,                  // painchance
  //sfx_dmpain,         // painsound
  0,                    // meleestate
  skull_attack_states,  // missilestate
  skull_die_states,     // deathstate
  NULL,                 // xdeathstate
  //sfx_firxpl,         // deathsound
  8,                    // speed
  16,                   // radius
  56,                   // height
  50,                   // mass
  3,                    // damage
  //sfx_dmact,          // activesound
  MF_SOLID |
  MF_SHOOTABLE |
  MF_FLOAT |
  MF_NOGRAVITY,         // flags
  NULL,                 // raisestate
};

/******************************************************************************
 * MT_SPIDER
 ******************************************************************************/

map_obj_state spider_normal_states[] =
{
{true,  STATE_SPID_STND,        "SPID", 0,      10,     0,      "A_Look",               STATE_SPID_STND2,       0,      0},
{true,  STATE_SPID_STND2,       "SPID", 1,      10,     0,      "A_Look",               STATE_SPID_STND,        0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_state spider_run_states[] =
{
{true,  STATE_SPID_RUN1,        "SPID", 0,      3,      0,      "A_Metal",              STATE_SPID_RUN2,        0,      0},
{true,  STATE_SPID_RUN2,        "SPID", 0,      3,      0,      "A_Chase",              STATE_SPID_RUN3,        0,      0},
{true,  STATE_SPID_RUN3,        "SPID", 1,      3,      0,      "A_Chase",              STATE_SPID_RUN4,        0,      0},
{true,  STATE_SPID_RUN4,        "SPID", 1,      3,      0,      "A_Chase",              STATE_SPID_RUN5,        0,      0},
{true,  STATE_SPID_RUN5,        "SPID", 2,      3,      0,      "A_Metal",              STATE_SPID_RUN6,        0,      0},
{true,  STATE_SPID_RUN6,        "SPID", 2,      3,      0,      "A_Chase",              STATE_SPID_RUN7,        0,      0},
{true,  STATE_SPID_RUN7,        "SPID", 3,      3,      0,      "A_Chase",              STATE_SPID_RUN8,        0,      0},
{true,  STATE_SPID_RUN8,        "SPID", 3,      3,      0,      "A_Chase",              STATE_SPID_RUN9,        0,      0},
{true,  STATE_SPID_RUN9,        "SPID", 4,      3,      0,      "A_Metal",              STATE_SPID_RUN10,       0,      0},
{true,  STATE_SPID_RUN10,       "SPID", 4,      3,      0,      "A_Chase",              STATE_SPID_RUN11,       0,      0},
{true,  STATE_SPID_RUN11,       "SPID", 5,      3,      0,      "A_Chase",              STATE_SPID_RUN12,       0,      0},
{true,  STATE_SPID_RUN12,       "SPID", 5,      3,      0,      "A_Chase",              STATE_SPID_RUN1,        0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_state spider_attack_states[] =
{
{true,  STATE_SPID_ATK1,        "SPID", 0,      20,     1,      "A_FaceTarget",         STATE_SPID_ATK2,        0,      0},
{true,  STATE_SPID_ATK2,        "SPID", 6,      4,      1,      "A_SPosAttack",         STATE_SPID_ATK3,        0,      0},
{true,  STATE_SPID_ATK3,        "SPID", 7,      4,      1,      "A_SPosAttack",         STATE_SPID_ATK4,        0,      0},
{true,  STATE_SPID_ATK4,        "SPID", 7,      1,      1,      "A_SpidRefire",         STATE_SPID_ATK2,        0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_state spider_pain_states[] =
{
{true,  STATE_SPID_PAIN,        "SPID", 8,      3,      0,      "",                     STATE_SPID_PAIN2,       0,      0},
{true,  STATE_SPID_PAIN2,       "SPID", 8,      3,      0,      "A_Pain",               STATE_SPID_RUN1,        0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_state spider_die_states[] =
{
{true,  STATE_SPID_DIE1,        "SPID", 9,      20,     0,      "A_Scream",             STATE_SPID_DIE2,        0,      0},
{true,  STATE_SPID_DIE2,        "SPID", 10,     10,     0,      "A_Fall",               STATE_SPID_DIE3,        0,      0},
{true,  STATE_SPID_DIE3,        "SPID", 11,     10,     0,      "",                     STATE_SPID_DIE4,        0,      0},
{true,  STATE_SPID_DIE4,        "SPID", 12,     10,     0,      "",                     STATE_SPID_DIE5,        0,      0},
{true,  STATE_SPID_DIE5,        "SPID", 13,     10,     0,      "",                     STATE_SPID_DIE6,        0,      0},
{true,  STATE_SPID_DIE6,        "SPID", 14,     10,     0,      "",                     STATE_SPID_DIE7,        0,      0},
{true,  STATE_SPID_DIE7,        "SPID", 15,     10,     0,      "",                     STATE_SPID_DIE8,        0,      0},
{true,  STATE_SPID_DIE8,        "SPID", 16,     10,     0,      "",                     STATE_SPID_DIE9,        0,      0},
{true,  STATE_SPID_DIE9,        "SPID", 17,     10,     0,      "",                     STATE_SPID_DIE10,       0,      0},
{true,  STATE_SPID_DIE10,       "SPID", 18,     30,     0,      "",                     STATE_SPID_DIE11,       0,      0},
{true,  STATE_SPID_DIE11,       "SPID", 18,     -1,     0,      "A_BossDeath",          STATE_NULL,             0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_defn spider_defn =
{                       // MT_SPIDER
  7,                    // doomednum
  spider_normal_states, // spawnstate
  3000,                 // spawnhealth
  spider_run_states,    // seestate
  //sfx_spisit,         // seesound
  8,                    // reactiontime
  //sfx_shotgn,         // attacksound
  spider_pain_states,   // painstate
  40,                   // painchance
  //sfx_dmpain,         // painsound
  0,                    // meleestate
  spider_attack_states, // missilestate
  spider_die_states,    // deathstate
  NULL,                 // xdeathstate
  //sfx_spidth,         // deathsound
  12,                   // speed
  128,                  // radius
  100,                  // height
  1000,                 // mass
  0,                    // damage
  //sfx_dmact,          // activesound
  MF_SOLID |
  MF_SHOOTABLE |
  MF_COUNTKILL,         // flags
  NULL,                 // raisestate
};

/******************************************************************************
 * MT_BABY
 ******************************************************************************/

map_obj_state baby_normal_states[] =
{
{true,  STATE_BSPI_STND,        "BSPI", 0,      10,     0,      "A_Look",               STATE_BSPI_STND2,       0,      0},
{true,  STATE_BSPI_STND2,       "BSPI", 1,      10,     0,      "A_Look",               STATE_BSPI_STND,        0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_state baby_run_states[] =
{
{true,  STATE_BSPI_SIGHT,       "BSPI", 0,      20,     0,      "",                     STATE_BSPI_RUN1,        0,      0},
{true,  STATE_BSPI_RUN1,        "BSPI", 0,      3,      0,      "A_BabyMetal",          STATE_BSPI_RUN2,        0,      0},
{true,  STATE_BSPI_RUN2,        "BSPI", 0,      3,      0,      "A_Chase",              STATE_BSPI_RUN3,        0,      0},
{true,  STATE_BSPI_RUN3,        "BSPI", 1,      3,      0,      "A_Chase",              STATE_BSPI_RUN4,        0,      0},
{true,  STATE_BSPI_RUN4,        "BSPI", 1,      3,      0,      "A_Chase",              STATE_BSPI_RUN5,        0,      0},
{true,  STATE_BSPI_RUN5,        "BSPI", 2,      3,      0,      "A_Chase",              STATE_BSPI_RUN6,        0,      0},
{true,  STATE_BSPI_RUN6,        "BSPI", 2,      3,      0,      "A_Chase",              STATE_BSPI_RUN7,        0,      0},
{true,  STATE_BSPI_RUN7,        "BSPI", 3,      3,      0,      "A_BabyMetal",          STATE_BSPI_RUN8,        0,      0},
{true,  STATE_BSPI_RUN8,        "BSPI", 3,      3,      0,      "A_Chase",              STATE_BSPI_RUN9,        0,      0},
{true,  STATE_BSPI_RUN9,        "BSPI", 4,      3,      0,      "A_Chase",              STATE_BSPI_RUN10,       0,      0},
{true,  STATE_BSPI_RUN10,       "BSPI", 4,      3,      0,      "A_Chase",              STATE_BSPI_RUN11,       0,      0},
{true,  STATE_BSPI_RUN11,       "BSPI", 5,      3,      0,      "A_Chase",              STATE_BSPI_RUN12,       0,      0},
{true,  STATE_BSPI_RUN12,       "BSPI", 5,      3,      0,      "A_Chase",              STATE_BSPI_RUN1,        0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_state baby_attack_states[] =
{
{true,  STATE_BSPI_ATK1,        "BSPI", 0,      20,     1,      "A_FaceTarget",         STATE_BSPI_ATK2,        0,      0},
{true,  STATE_BSPI_ATK2,        "BSPI", 6,      4,      1,      "A_BspiAttack",         STATE_BSPI_ATK3,        0,      0},
{true,  STATE_BSPI_ATK3,        "BSPI", 7,      4,      1,      "",                     STATE_BSPI_ATK4,        0,      0},
{true,  STATE_BSPI_ATK4,        "BSPI", 7,      1,      1,      "A_SpidRefire",         STATE_BSPI_ATK2,        0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_state baby_pain_states[] =
{
{true,  STATE_BSPI_PAIN,        "BSPI", 8,      3,      0,      "",                     STATE_BSPI_PAIN2,       0,      0},
{true,  STATE_BSPI_PAIN2,       "BSPI", 8,      3,      0,      "A_Pain",               STATE_BSPI_RUN1,        0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_state baby_die_states[] =
{
{true,  STATE_BSPI_DIE1,        "BSPI", 9,      20,     0,      "A_Scream",             STATE_BSPI_DIE2,        0,      0},
{true,  STATE_BSPI_DIE2,        "BSPI", 10,     7,      0,      "A_Fall",               STATE_BSPI_DIE3,        0,      0},
{true,  STATE_BSPI_DIE3,        "BSPI", 11,     7,      0,      "",                     STATE_BSPI_DIE4,        0,      0},
{true,  STATE_BSPI_DIE4,        "BSPI", 12,     7,      0,      "",                     STATE_BSPI_DIE5,        0,      0},
{true,  STATE_BSPI_DIE5,        "BSPI", 13,     7,      0,      "",                     STATE_BSPI_DIE6,        0,      0},
{true,  STATE_BSPI_DIE6,        "BSPI", 14,     7,      0,      "",                     STATE_BSPI_DIE7,        0,      0},
{true,  STATE_BSPI_DIE7,        "BSPI", 15,     -1,     0,      "A_BossDeath",          STATE_NULL,             0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_state baby_raise_states[] =
{
{true,  STATE_BSPI_RAISE1,      "BSPI", 15,     5,      0,      "",                     STATE_BSPI_RAISE2,      0,      0},
{true,  STATE_BSPI_RAISE2,      "BSPI", 14,     5,      0,      "",                     STATE_BSPI_RAISE3,      0,      0},
{true,  STATE_BSPI_RAISE3,      "BSPI", 13,     5,      0,      "",                     STATE_BSPI_RAISE4,      0,      0},
{true,  STATE_BSPI_RAISE4,      "BSPI", 12,     5,      0,      "",                     STATE_BSPI_RAISE5,      0,      0},
{true,  STATE_BSPI_RAISE5,      "BSPI", 11,     5,      0,      "",                     STATE_BSPI_RAISE6,      0,      0},
{true,  STATE_BSPI_RAISE6,      "BSPI", 10,     5,      0,      "",                     STATE_BSPI_RAISE7,      0,      0},
{true,  STATE_BSPI_RAISE7,      "BSPI", 9,      5,      0,      "",                     STATE_BSPI_RUN1,        0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_defn baby_defn =
{                       // MT_BABY
  68,                   // doomednum
  baby_normal_states,   // spawnstate
  500,                  // spawnhealth
  baby_run_states,      // seestate
  //sfx_bspsit,         // seesound
  8,                    // reactiontime
  //0,                  // attacksound
  baby_pain_states,     // painstate
  128,                  // painchance
  //sfx_dmpain,         // painsound
  0,                    // meleestate
  baby_attack_states,   // missilestate
  baby_die_states,      // deathstate
  NULL,                 // xdeathstate
  //sfx_bspdth,         // deathsound
  12,                   // speed
  64,                   // radius
  64,                   // height
  600,                  // mass
  0,                    // damage
  //sfx_bspact,         // activesound
  MF_SOLID |
  MF_SHOOTABLE |
  MF_COUNTKILL,         // flags
  baby_raise_states     // raisestate
};

/******************************************************************************
 * MT_CYBORG
 ******************************************************************************/

map_obj_state cyborg_normal_states[] =
{
{true,  STATE_CYBER_STND,       "CYBR", 0,      10,     0,      "A_Look",               STATE_CYBER_STND2,      0,      0},
{true,  STATE_CYBER_STND2,      "CYBR", 1,      10,     0,      "A_Look",               STATE_CYBER_STND,       0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_state cyborg_run_states[] =
{
{true,  STATE_CYBER_RUN1,       "CYBR", 0,      3,      0,      "A_Hoof",               STATE_CYBER_RUN2,       0,      0},
{true,  STATE_CYBER_RUN2,       "CYBR", 0,      3,      0,      "A_Chase",              STATE_CYBER_RUN3,       0,      0},
{true,  STATE_CYBER_RUN3,       "CYBR", 1,      3,      0,      "A_Chase",              STATE_CYBER_RUN4,       0,      0},
{true,  STATE_CYBER_RUN4,       "CYBR", 1,      3,      0,      "A_Chase",              STATE_CYBER_RUN5,       0,      0},
{true,  STATE_CYBER_RUN5,       "CYBR", 2,      3,      0,      "A_Chase",              STATE_CYBER_RUN6,       0,      0},
{true,  STATE_CYBER_RUN6,       "CYBR", 2,      3,      0,      "A_Chase",              STATE_CYBER_RUN7,       0,      0},
{true,  STATE_CYBER_RUN7,       "CYBR", 3,      3,      0,      "A_Metal",              STATE_CYBER_RUN8,       0,      0},
{true,  STATE_CYBER_RUN8,       "CYBR", 3,      3,      0,      "A_Chase",              STATE_CYBER_RUN1,       0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_state cyborg_attack_states[] =
{
{true,  STATE_CYBER_ATK1,       "CYBR", 4,      6,      0,      "A_FaceTarget",         STATE_CYBER_ATK2,       0,      0},
{true,  STATE_CYBER_ATK2,       "CYBR", 5,      12,     0,      "A_CyberAttack",        STATE_CYBER_ATK3,       0,      0},
{true,  STATE_CYBER_ATK3,       "CYBR", 4,      12,     0,      "A_FaceTarget",         STATE_CYBER_ATK4,       0,      0},
{true,  STATE_CYBER_ATK4,       "CYBR", 5,      12,     0,      "A_CyberAttack",        STATE_CYBER_ATK5,       0,      0},
{true,  STATE_CYBER_ATK5,       "CYBR", 4,      12,     0,      "A_FaceTarget",         STATE_CYBER_ATK6,       0,      0},
{true,  STATE_CYBER_ATK6,       "CYBR", 5,      12,     0,      "A_CyberAttack",        STATE_CYBER_RUN1,       0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_state cyborg_pain_states[] =
{
{true,  STATE_CYBER_PAIN,       "CYBR", 6,      10,     0,      "A_Pain",               STATE_CYBER_RUN1,       0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_state cyborg_die_states[] =
{
{true,  STATE_CYBER_DIE1,       "CYBR", 7,      10,     0,      "",                     STATE_CYBER_DIE2,       0,      0},
{true,  STATE_CYBER_DIE2,       "CYBR", 8,      10,     0,      "A_Scream",             STATE_CYBER_DIE3,       0,      0},
{true,  STATE_CYBER_DIE3,       "CYBR", 9,      10,     0,      "",                     STATE_CYBER_DIE4,       0,      0},
{true,  STATE_CYBER_DIE4,       "CYBR", 10,     10,     0,      "",                     STATE_CYBER_DIE5,       0,      0},
{true,  STATE_CYBER_DIE5,       "CYBR", 11,     10,     0,      "",                     STATE_CYBER_DIE6,       0,      0},
{true,  STATE_CYBER_DIE6,       "CYBR", 12,     10,     0,      "A_Fall",               STATE_CYBER_DIE7,       0,      0},
{true,  STATE_CYBER_DIE7,       "CYBR", 13,     10,     0,      "",                     STATE_CYBER_DIE8,       0,      0},
{true,  STATE_CYBER_DIE8,       "CYBR", 14,     10,     0,      "",                     STATE_CYBER_DIE9,       0,      0},
{true,  STATE_CYBER_DIE9,       "CYBR", 15,     30,     0,      "",                     STATE_CYBER_DIE10,      0,      0},
{true,  STATE_CYBER_DIE10,      "CYBR", 15,     -1,     0,      "A_BossDeath",          STATE_NULL,             0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_defn cyborg_defn =
{                       // MT_CYBORG
  16,                   // doomednum
  cyborg_normal_states, // spawnstate
  4000,                 // spawnhealth
  cyborg_run_states,    // seestate
  //sfx_cybsit,         // seesound
  8,                    // reactiontime
  //0,                  // attacksound
  cyborg_pain_states,   // painstate
  20,                   // painchance
  //sfx_dmpain,         // painsound
  0,                    // meleestate
  cyborg_attack_states, // missilestate
  cyborg_die_states,    // deathstate
  NULL,                 // xdeathstate
  //sfx_cybdth,         // deathsound
  16,                   // speed
  40,                   // radius
  110,                  // height
  1000,                 // mass
  0,                    // damage
  //sfx_dmact,          // activesound
  MF_SOLID |
  MF_SHOOTABLE |
  MF_COUNTKILL,         // flags
  NULL,                 // raisestate
};

/******************************************************************************
 * MT_PAIN
 ******************************************************************************/

map_obj_state pain_normal_states[] =
{
{true,  STATE_PAIN_STND,        "PAIN", 0,      10,     0,      "A_Look",               STATE_PAIN_STND,        0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_state pain_run_states[] =
{
{true,  STATE_PAIN_RUN1,        "PAIN", 0,      3,      0,      "A_Chase",              STATE_PAIN_RUN2,        0,      0},
{true,  STATE_PAIN_RUN2,        "PAIN", 0,      3,      0,      "A_Chase",              STATE_PAIN_RUN3,        0,      0},
{true,  STATE_PAIN_RUN3,        "PAIN", 1,      3,      0,      "A_Chase",              STATE_PAIN_RUN4,        0,      0},
{true,  STATE_PAIN_RUN4,        "PAIN", 1,      3,      0,      "A_Chase",              STATE_PAIN_RUN5,        0,      0},
{true,  STATE_PAIN_RUN5,        "PAIN", 2,      3,      0,      "A_Chase",              STATE_PAIN_RUN6,        0,      0},
{true,  STATE_PAIN_RUN6,        "PAIN", 2,      3,      0,      "A_Chase",              STATE_PAIN_RUN1,        0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_state pain_attack_states[] =
{
{true,  STATE_PAIN_ATK1,        "PAIN", 3,      5,      0,      "A_FaceTarget",         STATE_PAIN_ATK2,        0,      0},
{true,  STATE_PAIN_ATK2,        "PAIN", 4,      5,      0,      "A_FaceTarget",         STATE_PAIN_ATK3,        0,      0},
{true,  STATE_PAIN_ATK3,        "PAIN", 5,      5,      1,      "A_FaceTarget",         STATE_PAIN_ATK4,        0,      0},
{true,  STATE_PAIN_ATK4,        "PAIN", 5,      0,      1,      "A_PainAttack",         STATE_PAIN_RUN1,        0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_state pain_pain_states[] =
{
{true,  STATE_PAIN_PAIN,        "PAIN", 6,      6,      0,      "",                     STATE_PAIN_PAIN2,       0,      0},
{true,  STATE_PAIN_PAIN2,       "PAIN", 6,      6,      0,      "A_Pain",               STATE_PAIN_RUN1,        0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_state pain_die_states[] =
{
{true,  STATE_PAIN_DIE1,        "PAIN", 7,      8,      1,      "",                     STATE_PAIN_DIE2,        0,      0},
{true,  STATE_PAIN_DIE2,        "PAIN", 8,      8,      1,      "A_Scream",             STATE_PAIN_DIE3,        0,      0},
{true,  STATE_PAIN_DIE3,        "PAIN", 9,      8,      1,      "",                     STATE_PAIN_DIE4,        0,      0},
{true,  STATE_PAIN_DIE4,        "PAIN", 10,     8,      1,      "",                     STATE_PAIN_DIE5,        0,      0},
{true,  STATE_PAIN_DIE5,        "PAIN", 11,     8,      1,      "A_PainDie",            STATE_PAIN_DIE6,        0,      0},
{true,  STATE_PAIN_DIE6,        "PAIN", 12,     8,      1,      "",                     STATE_NULL,             0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_state pain_raise_states[] =
{
{true,  STATE_PAIN_RAISE1,      "PAIN", 12,     8,      0,      "",                     STATE_PAIN_RAISE2,      0,      0},
{true,  STATE_PAIN_RAISE2,      "PAIN", 11,     8,      0,      "",                     STATE_PAIN_RAISE3,      0,      0},
{true,  STATE_PAIN_RAISE3,      "PAIN", 10,     8,      0,      "",                     STATE_PAIN_RAISE4,      0,      0},
{true,  STATE_PAIN_RAISE4,      "PAIN", 9,      8,      0,      "",                     STATE_PAIN_RAISE5,      0,      0},
{true,  STATE_PAIN_RAISE5,      "PAIN", 8,      8,      0,      "",                     STATE_PAIN_RAISE6,      0,      0},
{true,  STATE_PAIN_RAISE6,      "PAIN", 7,      8,      0,      "",                     STATE_PAIN_RUN1,        0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_defn pain_defn =
{                       // MT_PAIN
  71,                   // doomednum
  pain_normal_states,   // spawnstate
  400,                  // spawnhealth
  pain_run_states,      // seestate
  //sfx_pesit,          // seesound
  8,                    // reactiontime
  //0,                  // attacksound
  pain_pain_states,     // painstate
  128,                  // painchance
  //sfx_pepain,         // painsound
  0,                    // meleestate
  pain_attack_states,   // missilestate
  pain_die_states,      // deathstate
  NULL,                 // xdeathstate
  //sfx_pedth,          // deathsound
  8,                    // speed
  31,                   // radius
  56,                   // height
  400,                  // mass
  0,                    // damage
  //sfx_dmact,          // activesound
  MF_SOLID |
  MF_SHOOTABLE |
  MF_FLOAT |
  MF_NOGRAVITY |
  MF_COUNTKILL,         // flags
  pain_raise_states     // raisestate
};

/******************************************************************************
 * MT_WOLFSS
 ******************************************************************************/

map_obj_state wolfss_normal_states[] =
{
{true,  STATE_SSWV_STND,        "SSWV", 0,      10,     0,      "A_Look",               STATE_SSWV_STND2,       0,      0},
{true,  STATE_SSWV_STND2,       "SSWV", 1,      10,     0,      "A_Look",               STATE_SSWV_STND,        0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_state wolfss_run_states[] =
{
{true,  STATE_SSWV_RUN1,        "SSWV", 0,      3,      0,      "A_Chase",              STATE_SSWV_RUN2,        0,      0},
{true,  STATE_SSWV_RUN2,        "SSWV", 0,      3,      0,      "A_Chase",              STATE_SSWV_RUN3,        0,      0},
{true,  STATE_SSWV_RUN3,        "SSWV", 1,      3,      0,      "A_Chase",              STATE_SSWV_RUN4,        0,      0},
{true,  STATE_SSWV_RUN4,        "SSWV", 1,      3,      0,      "A_Chase",              STATE_SSWV_RUN5,        0,      0},
{true,  STATE_SSWV_RUN5,        "SSWV", 2,      3,      0,      "A_Chase",              STATE_SSWV_RUN6,        0,      0},
{true,  STATE_SSWV_RUN6,        "SSWV", 2,      3,      0,      "A_Chase",              STATE_SSWV_RUN7,        0,      0},
{true,  STATE_SSWV_RUN7,        "SSWV", 3,      3,      0,      "A_Chase",              STATE_SSWV_RUN8,        0,      0},
{true,  STATE_SSWV_RUN8,        "SSWV", 3,      3,      0,      "A_Chase",              STATE_SSWV_RUN1,        0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_state wolfss_attack_states[] =
{
{true,  STATE_SSWV_ATK1,        "SSWV", 4,      10,     0,      "A_FaceTarget",         STATE_SSWV_ATK2,        0,      0},
{true,  STATE_SSWV_ATK2,        "SSWV", 5,      10,     0,      "A_FaceTarget",         STATE_SSWV_ATK3,        0,      0},
{true,  STATE_SSWV_ATK3,        "SSWV", 6,      4,      1,      "A_CPosAttack",         STATE_SSWV_ATK4,        0,      0},
{true,  STATE_SSWV_ATK4,        "SSWV", 5,      6,      0,      "A_FaceTarget",         STATE_SSWV_ATK5,        0,      0},
{true,  STATE_SSWV_ATK5,        "SSWV", 6,      4,      1,      "A_CPosAttack",         STATE_SSWV_ATK6,        0,      0},
{true,  STATE_SSWV_ATK6,        "SSWV", 5,      1,      0,      "A_CPosRefire",         STATE_SSWV_ATK2,        0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_state wolfss_pain_states[] =
{
{true,  STATE_SSWV_PAIN,        "SSWV", 7,      3,      0,      "",                     STATE_SSWV_PAIN2,       0,      0},
{true,  STATE_SSWV_PAIN2,       "SSWV", 7,      3,      0,      "A_Pain",               STATE_SSWV_RUN1,        0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_state wolfss_die_states[] =
{
{true,  STATE_SSWV_DIE1,        "SSWV", 8,      5,      0,      "",                     STATE_SSWV_DIE2,        0,      0},
{true,  STATE_SSWV_DIE2,        "SSWV", 9,      5,      0,      "A_Scream",             STATE_SSWV_DIE3,        0,      0},
{true,  STATE_SSWV_DIE3,        "SSWV", 10,     5,      0,      "A_Fall",               STATE_SSWV_DIE4,        0,      0},
{true,  STATE_SSWV_DIE4,        "SSWV", 11,     5,      0,      "",                     STATE_SSWV_DIE5,        0,      0},
{true,  STATE_SSWV_DIE5,        "SSWV", 12,     -1,     0,      "",                     STATE_NULL,             0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_state wolfss_xdie_states[] =
{
{true,  STATE_SSWV_XDIE1,       "SSWV", 13,     5,      0,      "",                     STATE_SSWV_XDIE2,       0,      0},
{true,  STATE_SSWV_XDIE2,       "SSWV", 14,     5,      0,      "A_XScream",            STATE_SSWV_XDIE3,       0,      0},
{true,  STATE_SSWV_XDIE3,       "SSWV", 15,     5,      0,      "A_Fall",               STATE_SSWV_XDIE4,       0,      0},
{true,  STATE_SSWV_XDIE4,       "SSWV", 16,     5,      0,      "",                     STATE_SSWV_XDIE5,       0,      0},
{true,  STATE_SSWV_XDIE5,       "SSWV", 17,     5,      0,      "",                     STATE_SSWV_XDIE6,       0,      0},
{true,  STATE_SSWV_XDIE6,       "SSWV", 18,     5,      0,      "",                     STATE_SSWV_XDIE7,       0,      0},
{true,  STATE_SSWV_XDIE7,       "SSWV", 19,     5,      0,      "",                     STATE_SSWV_XDIE8,       0,      0},
{true,  STATE_SSWV_XDIE8,       "SSWV", 20,     5,      0,      "",                     STATE_SSWV_XDIE9,       0,      0},
{true,  STATE_SSWV_XDIE9,       "SSWV", 21,     -1,     0,      "",                     STATE_NULL,             0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_state wolfss_raise_states[] =
{
{true,  STATE_SSWV_RAISE1,      "SSWV", 12,     5,      0,      "",                     STATE_SSWV_RAISE2,      0,      0},
{true,  STATE_SSWV_RAISE2,      "SSWV", 11,     5,      0,      "",                     STATE_SSWV_RAISE3,      0,      0},
{true,  STATE_SSWV_RAISE3,      "SSWV", 10,     5,      0,      "",                     STATE_SSWV_RAISE4,      0,      0},
{true,  STATE_SSWV_RAISE4,      "SSWV", 9,      5,      0,      "",                     STATE_SSWV_RAISE5,      0,      0},
{true,  STATE_SSWV_RAISE5,      "SSWV", 8,      5,      0,      "",                     STATE_SSWV_RUN1,        0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_defn wolfss_defn =
{                       // MT_WOLFSS
  84,                   // doomednum
  wolfss_normal_states, // spawnstate
  50,                   // spawnhealth
  wolfss_run_states,    // seestate
  //sfx_sssit,          // seesound
  8,                    // reactiontime
  //0,                  // attacksound
  wolfss_pain_states,   // painstate
  170,                  // painchance
  //sfx_popain,         // painsound
  0,                    // meleestate
  wolfss_attack_states, // missilestate
  wolfss_die_states,    // deathstate
  wolfss_xdie_states,   // xdeathstate
  //sfx_ssdth,          // deathsound
  8,                    // speed
  20,                   // radius
  56,                   // height
  100,                  // mass
  0,                    // damage
  //sfx_posact,         // activesound
  MF_SOLID |
  MF_SHOOTABLE |
  MF_COUNTKILL,         // flags
  wolfss_raise_states   // raisestate
};

/******************************************************************************
 * MT_KEEN
 ******************************************************************************/

map_obj_state keen_normal_states[] =
{
{true,  STATE_KEENSTND,         "KEEN", 0,      -1,     0,      "",                     STATE_KEENSTND,         0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_state keen_pain_states[] =
{
{true,  STATE_KEENPAIN,         "KEEN", 12,     4,      0,      "",                     STATE_KEENPAIN2,        0,      0},
{true,  STATE_KEENPAIN2,        "KEEN", 12,     8,      0,      "A_Pain",               STATE_KEENSTND,         0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_state keen_die_states[] =
{
{true,  STATE_COMMKEEN,         "KEEN", 0,      6,      0,      "",                     STATE_COMMKEEN2,        0,      0},
{true,  STATE_COMMKEEN2,        "KEEN", 1,      6,      0,      "",                     STATE_COMMKEEN3,        0,      0},
{true,  STATE_COMMKEEN3,        "KEEN", 2,      6,      0,      "A_Scream",             STATE_COMMKEEN4,        0,      0},
{true,  STATE_COMMKEEN4,        "KEEN", 3,      6,      0,      "",                     STATE_COMMKEEN5,        0,      0},
{true,  STATE_COMMKEEN5,        "KEEN", 4,      6,      0,      "",                     STATE_COMMKEEN6,        0,      0},
{true,  STATE_COMMKEEN6,        "KEEN", 5,      6,      0,      "",                     STATE_COMMKEEN7,        0,      0},
{true,  STATE_COMMKEEN7,        "KEEN", 6,      6,      0,      "",                     STATE_COMMKEEN8,        0,      0},
{true,  STATE_COMMKEEN8,        "KEEN", 7,      6,      0,      "",                     STATE_COMMKEEN9,        0,      0},
{true,  STATE_COMMKEEN9,        "KEEN", 8,      6,      0,      "",                     STATE_COMMKEEN10,       0,      0},
{true,  STATE_COMMKEEN10,       "KEEN", 9,      6,      0,      "",                     STATE_COMMKEEN11,       0,      0},
{true,  STATE_COMMKEEN11,       "KEEN", 10,     6,      0,      "A_KeenDie",            STATE_COMMKEEN12,       0,      0},
{true,  STATE_COMMKEEN12,       "KEEN", 11,     -1,     0,      "",                     STATE_NULL,             0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_defn keen_defn =
{                       // MT_KEEN
  72,                   // doomednum
  keen_normal_states,   // spawnstate
  100,                  // spawnhealth
  NULL,                 // seestate
  //sfx_None,           // seesound
  8,                    // reactiontime
  //sfx_None,           // attacksound
  keen_pain_states,     // painstate
  256,                  // painchance
  //sfx_keenpn,         // painsound
  NULL,                 // meleestate
  NULL,                 // missilestate
  keen_die_states,      // deathstate
  NULL,                 // xdeathstate
  //sfx_keendt,         // deathsound
  0,                    // speed
  16,                   // radius
  72,                   // height
  10000000,             // mass
  0,                    // damage
  //sfx_None,           // activesound
  MF_SOLID |
  MF_SPAWNCEILING |
  MF_NOGRAVITY |
  MF_SHOOTABLE |
  MF_COUNTKILL,         // flags
  NULL,                 // raisestate
};

/******************************************************************************
 * MT_BOSSBRAIN
 ******************************************************************************/

map_obj_state bossbrain_normal_states[] =
{
{true,  STATE_BRAIN,            "BBRN", 0,      -1,     0,      "",                     STATE_NULL,             0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_state bossbrain_pain_states[] =
{
{true,  STATE_BRAIN_PAIN,       "BBRN", 1,      36,     0,      "A_BrainPain",          STATE_BRAIN,            0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_state bossbrain_die_states[] =
{
{true,  STATE_BRAIN_DIE1,       "BBRN", 0,      100,    0,      "A_BrainScream",        STATE_BRAIN_DIE2,       0,      0},
{true,  STATE_BRAIN_DIE2,       "BBRN", 0,      10,     0,      "",                     STATE_BRAIN_DIE3,       0,      0},
{true,  STATE_BRAIN_DIE3,       "BBRN", 0,      10,     0,      "",                     STATE_BRAIN_DIE4,       0,      0},
{true,  STATE_BRAIN_DIE4,       "BBRN", 0,      -1,     0,      "A_BrainDie",           STATE_NULL,             0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_defn bossbrain_defn =
{                       // MT_BOSSBRAIN
  88,                   // doomednum
  bossbrain_normal_states,// spawnstate
  250,                  // spawnhealth
  NULL,                 // seestate
  //sfx_None,           // seesound
  8,                    // reactiontime
  //sfx_None,           // attacksound
  bossbrain_pain_states,// painstate
  255,                  // painchance
  //sfx_bospn,          // painsound
  NULL,                 // meleestate
  NULL,                 // missilestate
  bossbrain_die_states, // deathstate
  NULL,                 // xdeathstate
  //sfx_bosdth,         // deathsound
  0,                    // speed
  16,                   // radius
  16,                   // height
  10000000,             // mass
  0,                    // damage
  //sfx_None,           // activesound
  MF_SOLID |
  MF_SHOOTABLE,         // flags
  NULL,                 // raisestate
};

/******************************************************************************
 * MT_BOSSSPIT
 ******************************************************************************/

map_obj_state bosspit_normal_states[] =
{
{true,  STATE_BRAINEYE,         "SSWV", 0,      10,     0,      "A_Look",               STATE_BRAINEYE,         0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_state bosspit_see_states[] =
{
{true,  STATE_BRAINEYESEE,      "SSWV", 0,      181,    0,      "A_BrainAwake",         STATE_BRAINEYE1,        0,      0},
{true,  STATE_BRAINEYE1,        "SSWV", 0,      150,    0,      "A_BrainSpit",          STATE_BRAINEYE1,        0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_defn bosspit_defn =
{                       // MT_BOSSSPIT
  89,                   // doomednum
  bosspit_normal_states,// spawnstate
  1000,                 // spawnhealth
  bosspit_see_states,   // seestate
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

// THINGS BELOW HERE NEED TO BE ADDED TO LIST AT BOTTOM OF FILE

#if 0
/******************************************************************************
 * MT_SHOTGUY
 ******************************************************************************/

map_obj_state shotguy_normal_states[] =
{
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_state shotguy_run_states[] =
{
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_state shotguy_attack_states[] =
{
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_state shotguy_pain_states[] =
{
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_state shotguy_die_states[] =
{
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_state shotguy_xdie_states[] =
{
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_state shotguy_raise_states[] =
{
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_defn shotguy_defn =
};
#endif

map_obj_defn const *map_obj_being_defns[] = 
{
  &player_defn,
  &possessed_defn,
  &shotguy_defn,
  &vile_defn,
  &undead_defn,
  &fatso_defn,
  &chainguy_defn,
  &troop_defn,
  &sergeant_defn,
  &shadows_defn,
  &head_defn,
  &bruiser_defn,
  &knight_defn,
  &skull_defn,
  &spider_defn,
  &baby_defn,
  &cyborg_defn,
  &pain_defn,
  &wolfss_defn,
  &keen_defn,
  &bossbrain_defn,
  &bosspit_defn,
  &shotguy_defn,
  NULL
};

