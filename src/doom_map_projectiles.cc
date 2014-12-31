#include "map_object.h"

/******************************************************************************
 * MT_TRACER
 ******************************************************************************/

map_obj_state tracer_normal_states[] =
{
{true,  STATE_TRACER,           "FATB", 0,      2,      1,      "A_Tracer",             STATE_TRACER2,          0,      0},
{true,  STATE_TRACER2,          "FATB", 1,      2,      1,      "A_Tracer",             STATE_TRACER,           0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_state tracer_die_states[] =
{
{true,  STATE_TRACEEXP1,        "FBXP", 0,      8,      1,      "",                     STATE_TRACEEXP2,        0,      0},
{true,  STATE_TRACEEXP2,        "FBXP", 1,      6,      1,      "",                     STATE_TRACEEXP3,        0,      0},
{true,  STATE_TRACEEXP3,        "FBXP", 2,      4,      1,      "",                     STATE_NULL,             0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_defn tracer_defn =
{                       // MT_TRACER
  -1,                   // doomednum
  tracer_normal_states, // spawnstate
  1000,                 // spawnhealth
  NULL,                 // seestate
  //sfx_skeatk,         // seesound
  8,                    // reactiontime
  //sfx_None,           // attacksound
  NULL,                 // painstate
  0,                    // painchance
  //sfx_None,           // painsound
  NULL,                 // meleestate
  NULL,                 // missilestate
  tracer_die_states,    // deathstate
  NULL,                 // xdeathstate
  //sfx_barexp,         // deathsound
  10,                   // speed
  11,                   // radius
  8,                    // height
  100,                  // mass
  10,                   // damage
  //sfx_None,           // activesound
  MF_NOBLOCKMAP |
  MF_MISSILE |
  MF_DROPOFF |
  MF_NOGRAVITY,         // flags
  NULL,                 // raisestate
};

/******************************************************************************
 MT_FATSHOT
 ******************************************************************************/

map_obj_state fatshot_normal_states[] =
{
{true,  STATE_FATSHOT1,         "MANF", 0,      4,      1,      "",                     STATE_FATSHOT2,         0,      0},
{true,  STATE_FATSHOT2,         "MANF", 1,      4,      1,      "",                     STATE_FATSHOT1,         0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_state fatshot_die_states[] =
{
{true,  STATE_FATSHOTX1,        "MISL", 1,      8,      1,      "",                     STATE_FATSHOTX2,        0,      0},
{true,  STATE_FATSHOTX2,        "MISL", 2,      6,      1,      "",                     STATE_FATSHOTX3,        0,      0},
{true,  STATE_FATSHOTX3,        "MISL", 3,      4,      1,      "",                     STATE_NULL,             0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_defn fatshot_defn =
{                       // MT_FATSHOT
  -1,                   // doomednum
  fatshot_normal_states,// spawnstate
  1000,                 // spawnhealth
  NULL,                 // seestate
  //sfx_firsht,         // seesound
  8,                    // reactiontime
  //sfx_None,           // attacksound
  NULL,                 // painstate
  0,                    // painchance
  //sfx_None,           // painsound
  NULL,                 // meleestate
  NULL,                 // missilestate
  fatshot_die_states,   // deathstate
  NULL,                 // xdeathstate
  //sfx_firxpl,         // deathsound
  20,                   // speed
  6,                    // radius
  8,                    // height
  100,                  // mass
  8,                    // damage
  //sfx_None,           // activesound
  MF_NOBLOCKMAP |
  MF_MISSILE |
  MF_DROPOFF |
  MF_NOGRAVITY,         // flags
  NULL,                 // raisestate
};

/******************************************************************************
 * MT_BRUISERSHOT
 ******************************************************************************/

map_obj_state bruisershot_normal_states[] =
{
{true,  STATE_BRBALL1,          "BAL7", 0,      4,      1,      "",                     STATE_BRBALL2,          0,      0},
{true,  STATE_BRBALL2,          "BAL7", 1,      4,      1,      "",                     STATE_BRBALL1,          0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_state bruisershot_die_states[] =
{
{true,  STATE_BRBALLX1,         "BAL7", 2,      6,      1,      "",                     STATE_BRBALLX2,         0,      0},
{true,  STATE_BRBALLX2,         "BAL7", 3,      6,      1,      "",                     STATE_BRBALLX3,         0,      0},
{true,  STATE_BRBALLX3,         "BAL7", 4,      6,      1,      "",                     STATE_NULL,             0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_defn bruisershot_defn =
{                       // MT_BRUISERSHOT
  -1,                   // doomednum
  bruisershot_normal_states,// spawnstate
  1000,                 // spawnhealth
  NULL,                 // seestate
  //sfx_firsht,         // seesound
  8,                    // reactiontime
  //sfx_None,           // attacksound
  NULL,                 // painstate
  0,                    // painchance
  //sfx_None,           // painsound
  NULL,                 // meleestate
  NULL,                 // missilestate
  bruisershot_die_states,// deathstate
  NULL,                 // xdeathstate
  //sfx_firxpl,         // deathsound
  15,                   // speed
  6,                    // radius
  8,                    // height
  100,                  // mass
  8,                    // damage
  //sfx_None,           // activesound
  MF_NOBLOCKMAP |
  MF_MISSILE |
  MF_DROPOFF |
  MF_NOGRAVITY,         // flags
  NULL,                 // raisestate
};

/******************************************************************************
 * MT_SPAWNSHOT
 ******************************************************************************/

map_obj_state spawnshot_normal_states[] =
{
{true,  STATE_SPAWN1,           "BOSF", 0,      3,      1,      "A_SpawnSound",         STATE_SPAWN2,           0,      0},
{true,  STATE_SPAWN2,           "BOSF", 1,      3,      1,      "A_SpawnFly",           STATE_SPAWN3,           0,      0},
{true,  STATE_SPAWN3,           "BOSF", 2,      3,      1,      "A_SpawnFly",           STATE_SPAWN4,           0,      0},
{true,  STATE_SPAWN4,           "BOSF", 3,      3,      1,      "A_SpawnFly",           STATE_SPAWN1,           0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_defn spawnshot_defn =
{                       // MT_SPAWNSHOT
  -1,                   // doomednum
  spawnshot_normal_states, // spawnstate
  1000,                 // spawnhealth
  NULL,                 // seestate
  //sfx_bospit,         // seesound
  8,                    // reactiontime
  //sfx_None,           // attacksound
  NULL,                 // painstate
  0,                    // painchance
  //sfx_None,           // painsound
  NULL,                 // meleestate
  NULL,                 // missilestate
  NULL,                 // deathstate
  NULL,                 // xdeathstate
  //sfx_firxpl,         // deathsound
  10,                   // speed
  6,                    // radius
  32,                   // height
  100,                  // mass
  3,                    // damage
  //sfx_None,           // activesound
  MF_NOBLOCKMAP |
  MF_MISSILE |
  MF_DROPOFF |
  MF_NOGRAVITY |
  MF_NOCLIP,            // flags
  NULL,                 // raisestate
};

/******************************************************************************
 * MT_SPAWNFIRE
 ******************************************************************************/

map_obj_state spawnfire_normal_states[] =
{
{true,  STATE_SPAWNFIRE1,       "FIRE", 0,      4,      1,      "A_Fire",               STATE_SPAWNFIRE2,       0,      0},
{true,  STATE_SPAWNFIRE2,       "FIRE", 1,      4,      1,      "A_Fire",               STATE_SPAWNFIRE3,       0,      0},
{true,  STATE_SPAWNFIRE3,       "FIRE", 2,      4,      1,      "A_Fire",               STATE_SPAWNFIRE4,       0,      0},
{true,  STATE_SPAWNFIRE4,       "FIRE", 3,      4,      1,      "A_Fire",               STATE_SPAWNFIRE5,       0,      0},
{true,  STATE_SPAWNFIRE5,       "FIRE", 4,      4,      1,      "A_Fire",               STATE_SPAWNFIRE6,       0,      0},
{true,  STATE_SPAWNFIRE6,       "FIRE", 5,      4,      1,      "A_Fire",               STATE_SPAWNFIRE7,       0,      0},
{true,  STATE_SPAWNFIRE7,       "FIRE", 6,      4,      1,      "A_Fire",               STATE_SPAWNFIRE8,       0,      0},
{true,  STATE_SPAWNFIRE8,       "FIRE", 7,      4,      1,      "A_Fire",               STATE_NULL,             0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_defn spawnfire_defn =
{                       // MT_SPAWNFIRE
  -1,                   // doomednum
  spawnfire_normal_states,// spawnstate
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
 * MT_TROOPSHOT
 ******************************************************************************/

map_obj_state troopshot_normal_states[] =
{
{true,  STATE_TBALL1,           "BAL1", 0,      4,      1,      "",                     STATE_TBALL2,           0,      0},
{true,  STATE_TBALL2,           "BAL1", 1,      4,      1,      "",                     STATE_TBALL1,           0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_state troopshot_die_states[] =
{
{true,  STATE_TBALLX1,          "BAL1", 2,      6,      1,      "",                     STATE_TBALLX2,          0,      0},
{true,  STATE_TBALLX2,          "BAL1", 3,      6,      1,      "",                     STATE_TBALLX3,          0,      0},
{true,  STATE_TBALLX3,          "BAL1", 4,      6,      1,      "",                     STATE_NULL,             0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_defn troopshot_defn =
{                       // MT_TROOPSHOT
  -1,                   // doomednum
  troopshot_normal_states,// spawnstate
  1000,                 // spawnhealth
  NULL,                 // seestate
  //sfx_firsht,         // seesound
  8,                    // reactiontime
  //sfx_None,           // attacksound
  NULL,                 // painstate
  0,                    // painchance
  //sfx_None,           // painsound
  NULL,                 // meleestate
  NULL,                 // missilestate
  troopshot_die_states, // deathstate
  NULL,                 // xdeathstate
  //sfx_firxpl,         // deathsound
  10,                   // speed
  6,                    // radius
  8,                    // height
  100,                  // mass
  3,                    // damage
  //sfx_None,           // activesound
  MF_NOBLOCKMAP |
  MF_MISSILE |
  MF_DROPOFF |
  MF_NOGRAVITY,         // flags
  NULL,                 // raisestate
};

/******************************************************************************
 * MT_HEADSHOT
 ******************************************************************************/

map_obj_state headshot_normal_states[] =
{
{true,  STATE_RBALL1,           "BAL2", 0,      4,      1,      "",                     STATE_RBALL2,           0,      0},
{true,  STATE_RBALL2,           "BAL2", 1,      4,      1,      "",                     STATE_RBALL1,           0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_state headshot_die_states[] =
{
{true,  STATE_RBALLX1,          "BAL2", 2,      6,      1,      "",                     STATE_RBALLX2,          0,      0},
{true,  STATE_RBALLX2,          "BAL2", 3,      6,      1,      "",                     STATE_RBALLX3,          0,      0},
{true,  STATE_RBALLX3,          "BAL2", 4,      6,      1,      "",                     STATE_NULL,             0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_defn headshot_defn =
{                       // MT_HEADSHOT
  -1,                   // doomednum
  headshot_normal_states,// spawnstate
  1000,                 // spawnhealth
  NULL,                 // seestate
  //sfx_firsht,         // seesound
  8,                    // reactiontime
  //sfx_None,           // attacksound
  NULL,                 // painstate
  0,                    // painchance
  //sfx_None,           // painsound
  NULL,                 // meleestate
  NULL,                 // missilestate
  headshot_die_states,  // deathstate
  NULL,                 // xdeathstate
  //sfx_firxpl,         // deathsound
  10,                   // speed
  6,                    // radius
  8,                    // height
  100,                  // mass
  5,                    // damage
  //sfx_None,           // activesound
  MF_NOBLOCKMAP |
  MF_MISSILE |
  MF_DROPOFF |
  MF_NOGRAVITY,         // flags
  NULL,                 // raisestate
};

/******************************************************************************
 * MT_ROCKET
 ******************************************************************************/

map_obj_state rocket_normal_states[] =
{
{true,  STATE_ROCKET,           "MISL", 0,      1,      1,      "",                     STATE_ROCKET,           0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_state rocket_die_states[] =
{
{true,  STATE_EXPLODE1,         "MISL", 1,      8,      1,      "A_Explode",            STATE_EXPLODE2,         0,      0},
{true,  STATE_EXPLODE2,         "MISL", 2,      6,      1,      "",                     STATE_EXPLODE3,         0,      0},
{true,  STATE_EXPLODE3,         "MISL", 3,      4,      1,      "",                     STATE_NULL,             0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_defn rocket_defn =
{                       // MT_ROCKET
  -1,                   // doomednum
  rocket_normal_states, // spawnstate
  1000,                 // spawnhealth
  NULL,                 // seestate
  //sfx_rlaunc,         // seesound
  8,                    // reactiontime
  //sfx_None,           // attacksound
  NULL,                 // painstate
  0,                    // painchance
  //sfx_None,           // painsound
  NULL,                 // meleestate
  NULL,                 // missilestate
  rocket_die_states,    // deathstate
  NULL,                 // xdeathstate
  //sfx_barexp,         // deathsound
  20,                   // speed
  11,                   // radius
  8,                    // height
  100,                  // mass
  20,                   // damage
  //sfx_None,           // activesound
  MF_NOBLOCKMAP |
  MF_MISSILE |
  MF_DROPOFF |
  MF_NOGRAVITY,         // flags
  NULL,                 // raisestate
};

/******************************************************************************
 * MT_PLASMA
 ******************************************************************************/

map_obj_state plasma_normal_states[] =
{
{true,  STATE_PLASBALL,         "PLSS", 0,      6,      1,      "",                     STATE_PLASBALL2,        0,      0},
{true,  STATE_PLASBALL2,        "PLSS", 1,      6,      1,      "",                     STATE_PLASBALL,         0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_state plasma_die_states[] =
{
{true,  STATE_PLASEXP,          "PLSE", 0,      4,      1,      "",                     STATE_PLASEXP2,         0,      0},
{true,  STATE_PLASEXP2,         "PLSE", 1,      4,      1,      "",                     STATE_PLASEXP3,         0,      0},
{true,  STATE_PLASEXP3,         "PLSE", 2,      4,      1,      "",                     STATE_PLASEXP4,         0,      0},
{true,  STATE_PLASEXP4,         "PLSE", 3,      4,      1,      "",                     STATE_PLASEXP5,         0,      0},
{true,  STATE_PLASEXP5,         "PLSE", 4,      4,      1,      "",                     STATE_NULL,             0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_defn plasma_defn =
{                       // MT_PLASMA
  -1,                   // doomednum
  plasma_normal_states, // spawnstate
  1000,                 // spawnhealth
  NULL,                 // seestate
  //sfx_plasma,         // seesound
  8,                    // reactiontime
  //sfx_None,           // attacksound
  NULL,                 // painstate
  0,                    // painchance
  //sfx_None,           // painsound
  NULL,                 // meleestate
  NULL,                 // missilestate
  plasma_die_states,    // deathstate
  NULL,                 // xdeathstate
  //sfx_firxpl,         // deathsound
  25,                   // speed
  13,                   // radius
  8,                    // height
  100,                  // mass
  5,                    // damage
  //sfx_None,           // activesound
  MF_NOBLOCKMAP |
  MF_MISSILE |
  MF_DROPOFF |
  MF_NOGRAVITY,         // flags
  NULL,                 // raisestate
};

/******************************************************************************
 * MT_BFG
 ******************************************************************************/

map_obj_state bfg_normal_states[] =
{
{true,  STATE_BFGSHOT,          "BFS1", 0,      4,      1,      "",                     STATE_BFGSHOT2,         0,      0},
{true,  STATE_BFGSHOT2,         "BFS1", 1,      4,      1,      "",                     STATE_BFGSHOT,          0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_state bfg_die_states[] =
{
{true,  STATE_BFGLAND,          "BFE1", 0,      8,      1,      "",                     STATE_BFGLAND2,         0,      0},
{true,  STATE_BFGLAND2,         "BFE1", 1,      8,      1,      "",                     STATE_BFGLAND3,         0,      0},
{true,  STATE_BFGLAND3,         "BFE1", 2,      8,      1,      "A_BFGSpray",           STATE_BFGLAND4,         0,      0},
{true,  STATE_BFGLAND4,         "BFE1", 3,      8,      1,      "",                     STATE_BFGLAND5,         0,      0},
{true,  STATE_BFGLAND5,         "BFE1", 4,      8,      1,      "",                     STATE_BFGLAND6,         0,      0},
{true,  STATE_BFGLAND6,         "BFE1", 5,      8,      1,      "",                     STATE_NULL,             0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_defn bfg_defn =
{                       // MT_BFG
  -1,                   // doomednum
  bfg_normal_states,    // spawnstate
  1000,                 // spawnhealth
  NULL,                 // seestate
  //0,                  // seesound
  8,                    // reactiontime
  //sfx_None,           // attacksound
  NULL,                 // painstate
  0,                    // painchance
  //sfx_None,           // painsound
  NULL,                 // meleestate
  NULL,                 // missilestate
  bfg_die_states,       // deathstate
  NULL,                 // xdeathstate
  //sfx_rxplod,         // deathsound
  25,                   // speed
  13,                   // radius
  8,                    // height
  100,                  // mass
  100,                  // damage
  //sfx_None,           // activesound
  MF_NOBLOCKMAP |
  MF_MISSILE |
  MF_DROPOFF |
  MF_NOGRAVITY,         // flags
  NULL,                 // raisestate
};

/******************************************************************************
 * MT_ARACHPLAZ
 ******************************************************************************/

map_obj_state arachplaz_normal_states[] =
{
{true,  STATE_ARACH_PLAZ,       "APLS", 0,      5,      1,      "",                     STATE_ARACH_PLAZ2,      0,      0},
{true,  STATE_ARACH_PLAZ2,      "APLS", 1,      5,      1,      "",                     STATE_ARACH_PLAZ,       0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_state arachplaz_die_states[] =
{
{true,  STATE_ARACH_PLEX,       "APBX", 0,      5,      1,      "",                     STATE_ARACH_PLEX2,      0,      0},
{true,  STATE_ARACH_PLEX2,      "APBX", 1,      5,      1,      "",                     STATE_ARACH_PLEX3,      0,      0},
{true,  STATE_ARACH_PLEX3,      "APBX", 2,      5,      1,      "",                     STATE_ARACH_PLEX4,      0,      0},
{true,  STATE_ARACH_PLEX4,      "APBX", 3,      5,      1,      "",                     STATE_ARACH_PLEX5,      0,      0},
{true,  STATE_ARACH_PLEX5,      "APBX", 4,      5,      1,      "",                     STATE_NULL,             0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_defn arachplaz_defn =
{                       // MT_ARACHPLAZ
  -1,                   // doomednum
  arachplaz_normal_states,// spawnstate
  1000,                 // spawnhealth
  NULL,                 // seestate
  //sfx_plasma,         // seesound
  8,                    // reactiontime
  //sfx_None,           // attacksound
  NULL,                 // painstate
  0,                    // painchance
  //sfx_None,           // painsound
  NULL,                 // meleestate
  NULL,                 // missilestate
  arachplaz_die_states, // deathstate
  NULL,                 // xdeathstate
  //sfx_firxpl,         // deathsound
  25,                   // speed
  13,                   // radius
  8,                    // height
  100,                  // mass
  5,                    // damage
  //sfx_None,           // activesound
  MF_NOBLOCKMAP |
  MF_MISSILE |
  MF_DROPOFF |
  MF_NOGRAVITY,         // flags
  NULL,                 // raisestate
};

/******************************************************************************
 * MT_PUFF
 ******************************************************************************/

map_obj_state puff_normal_states[] =
{
{true,  STATE_PUFF1,            "PUFF", 0,      4,      1,      "",                     STATE_PUFF2,            0,      0},
{true,  STATE_PUFF2,            "PUFF", 1,      4,      0,      "",                     STATE_PUFF3,            0,      0},
{true,  STATE_PUFF3,            "PUFF", 2,      4,      0,      "",                     STATE_PUFF4,            0,      0},
{true,  STATE_PUFF4,            "PUFF", 3,      4,      0,      "",                     STATE_NULL,             0,      0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_defn puff_defn =
{                       // MT_PUFF
  -1,                   // doomednum
  puff_normal_states,   // spawnstate
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

// THINGS BELOW HERE NEED TO BE ADDED TO LIST AT BOTTOM OF FILE

#if 0
/******************************************************************************
 * MT_TRACER
 ******************************************************************************/

map_obj_state tracer_normal_states[] =
{
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_state tracer_die_states[] =
{
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

map_obj_defn tracer_defn =
};
#endif

map_obj_defn const *map_obj_projectile_defns[] = 
{
  &tracer_defn,
  &fatshot_defn,
  &bruisershot_defn,
  &spawnshot_defn,
  &spawnfire_defn,
  &troopshot_defn,
  &headshot_defn,
  &rocket_defn,
  &plasma_defn,
  &bfg_defn,
  &arachplaz_defn,
  &puff_defn,
  &tracer_defn,
  NULL
};
