#include "sprite_state_machine.h"
#include "sprites.h"

//#define DEBUG_PRINTING
#include "debug.h"

sprite_state_machine::sprite_state_machine(char const *_name,
                                           int initial_state_id,
                                           sprite_state_machine_state *_states,
                                           sprite_state_machine_transition *_transitions)
{
  debug_printf("initializing a \"%s\" sprite state machine\n", _name);
  name = new char[strlen(_name)+1];
  strcpy(name, _name);

  states = _states;
  transitions = _transitions;

  for(sprite_state_machine_state *s = states; s->valid; s++)
  {
    if(!s->anim)
    {
      s->anim = sprites_lookup_animation(s->sprite_anim_prefix);
    }
  }

  cur_state     = find_state(initial_state_id);
  if(!cur_state) { debug_printf("\"%s\" is starting in NULL state\n", _name); }
  cur_tick      = 0;
}

sprite_state_machine::~sprite_state_machine()
{
  if(name) { delete[] name; }
}

void sprite_state_machine::handle_event(int event_id)
{
  debug_printf("\"%s\": handle_event(%d)\n", name, event_id);
  if(!cur_state) { return; }

  sprite_state_machine_transition *t = find_transition(cur_state->state_id, event_id);
  if(t)
  {
    debug_printf("\"%s\": handle_event() transitioning to %d\n", name, t->next_state_id);
    cur_state     = find_state(t->next_state_id);
    cur_tick      = 0;
  }
  else
  {
    debug_printf("\"%s\": handle_event() transitioning to NULL state\n", name);
    cur_state = NULL; // done
  }
}

void sprite_state_machine::tick(void)
{
  debug_printf("\"%s\": tick()\n", name);
  if(!cur_state) { return; }

  cur_tick++;
  if(cur_tick >= cur_state->num_ticks)
  {
    cur_tick = 0;
    debug_printf("\"%s\": tick() sprite finished\n", name);
    handle_event(cur_state->sprite_over_event_id);
  }
}

sprite_state_machine_state *sprite_state_machine::find_state(int state_id) const
{
  for(sprite_state_machine_state *s = states; s->valid; s++)
  {
    if(s->state_id == state_id)
    {
      return s;
    }
  }
  return NULL;
}

sprite_state_machine_transition *sprite_state_machine::find_transition(int state_id, int event_id) const
{
  for(sprite_state_machine_transition *t = transitions; t->valid; t++)
  {
    if((t->state_id == state_id) && (t->event_id == event_id))
    {
      return t;
    }
  }
  return NULL;
}

sprite const *sprite_state_machine::get_cur_sprite(int angle_idx) const
{
  if(!cur_state) { return NULL; }

  return cur_state->anim->get_frame(cur_state->frame_idx)->get_sprite(angle_idx);
}
