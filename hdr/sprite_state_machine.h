#ifndef __SPRITE_STATE_MACHINE_H

#include "sprites.h"

typedef struct
{
  bool valid;                   // false indicates the end of an array of sprite_state_machine_state[]
  int state_id;                 // unique state ID (within a single state machine)
  char sprite_anim_prefix[5];   // 4 + NULL
  sprite_animation *anim;       // animation (to be wired up later)
  int flags;                    // special flags
  int frame_idx;                // which frame of the animation to show
  int num_ticks;                // how many ticks to show it for
  int sprite_over_event_id;     // when sprite ends, the state machine will emit this event to itself
} sprite_state_machine_state;

typedef struct
{
  bool valid;                   // false indicates the end of array of sprite_state_machine_transition[]
  int state_id;
  int event_id;
  int next_state_id;
} sprite_state_machine_transition;

class sprite_state_machine
{
public:
  sprite_state_machine(char const *_name,
                       int initial_state_id,
                       sprite_state_machine_state *_states, 
                       sprite_state_machine_transition *_transitions);
  ~sprite_state_machine();

  virtual bool handle_event(int event_id);
  virtual void tick(void);

protected:
  char *name;
  sprite_state_machine_state *cur_state;
  sprite_state_machine_state *states;
  sprite_state_machine_transition *transitions;
  int cur_tick;

  sprite_state_machine_state *find_state(int state_id) const;
  sprite_state_machine_transition *find_transition(int state_id, int event_id) const;
  sprite const *get_cur_sprite(int angle) const;
};

#endif
