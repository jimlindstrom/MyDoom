#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "palettes.h"
#include "flats.h"
#include "wad_file.h"
#include "flat.h"

/******************************************************************************
 * file-level variables
 ******************************************************************************/

typedef struct 
{
  char last_name[9];
  char first_name[9];
} anim_def;

anim_def anim_defs[] =
{
    {"NUKAGE3",      "NUKAGE1"	},
    {"FWATER4",      "FWATER1"	},
    {"SWATER4",      "SWATER1"	},
    {"LAVA4",        "LAVA1"	},
    {"BLOOD3",       "BLOOD1"	},
    {"RROCK08",      "RROCK05"	},
    {"SLIME04",      "SLIME01"	},
    {"SLIME08",      "SLIME05"	},
    {"SLIME12",      "SLIME09"	}
};

static int32_t num_flats = 0;
static flat *flats = NULL;

static int32_t num_animations = 0;
static flat_animation *flat_animations = NULL;

/******************************************************************************
 * file-level functions
 ******************************************************************************/

void count_flats(wad_file const *wad)
{
  wad_lump const *flat_lump = NULL;

  num_flats = 0;
  for(flat_lump = wad->get_next_lump(wad->find_lump_by_name("F_START"));
      flat_lump && !flat_lump->is_named("F_END");
      flat_lump = wad->get_next_lump(flat_lump))
  {
    if (flat_lump->get_num_bytes() > 0)
    {
      num_flats++;
    }
  }
}

void read_flats(wad_file const *wad)
{
  wad_lump const *flat_lump = NULL;
  int i;

  flats = new flat[num_flats];

  i=0;
  for(flat_lump = wad->get_next_lump(wad->find_lump_by_name("F_START"));
      flat_lump && !flat_lump->is_named("F_END");
      flat_lump = wad->get_next_lump(flat_lump))
  {
    if (flat_lump->get_num_bytes() > 0)
    {
      flats[i].set_data(flat_lump->get_data());
      flats[i].set_name(flat_lump->get_name());
      i++;
    }
  }
}

void create_animations(void)
{
  int16_t flat_idx;
  int num_anim_defs = sizeof(anim_defs)/sizeof(anim_defs[0]);
  anim_def *cur_anim_def = NULL;

  flat_animations = new flat_animation[num_flats]; // allocate enough memory for worst case (all single-frame animations)

  flat_idx = 0;
  num_animations = 0;

  for(int i=0; i<num_flats; i++)
  {
    // if we're not already in a defined animation, check whether this is the beginning of a defined animation
    if(!cur_anim_def)
    {
      for(int j=0; !cur_anim_def && j<num_anim_defs; j++)
      {
        if(strcasecmp(anim_defs[j].first_name, flats[i].get_name())==0)
        {
          cur_anim_def = &anim_defs[j];
        }
      }
    }

    flat_animations[num_animations].set_name(flats[i].get_name());
    flat_animations[num_animations].set_flat(flat_idx, &flats[i]);

    // if we're not already in a defined animation, check whether this is the beginning of a defined animation
    if(cur_anim_def)
    {
      if(strcasecmp(cur_anim_def->last_name, flats[i].get_name())==0)
      {
        cur_anim_def = NULL;
        flat_idx = 0;
        num_animations++;
      }
      else
      {
        flat_idx++;
      }
    }
    else
    {
      flat_idx = 0;
      num_animations++;
    }
  }
}

/******************************************************************************
 * public interface
 ******************************************************************************/

bool flats_init(wad_file const *wad)
{
  count_flats(wad);
  read_flats(wad);
  create_animations();

  return true;
}

flat_animation const *flats_find_by_name(char const *name)
{
  for(int i=0; i<num_animations; i++)
  {
    for(int j=0; j<flat_animations[i].get_num_flats(); j++)
    {
      if(strcasecmp(flat_animations[i].get_nth_flat(j)->get_name(), name) == 0)
      {
        return &flat_animations[i];
      }
    }
  }

  return NULL;
}

void flats_animate(void)
{
  static int delay=0;
  if(delay++ > 5)
  {
    for(int i=0; i<num_animations; i++)
    {
      flat_animations[i].increment();
    }
    delay = 0;
  }
}

void flats_destroy(void)
{
  if (flats          ) { delete[] flats;           }
  if (flat_animations) { delete[] flat_animations; }
}

