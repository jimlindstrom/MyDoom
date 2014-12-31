REAL DOOM
======================================================================================

Object model
--------------------------------------------------------------------------------------
- info.h:
	- spritenum_t: an enumeration of all sprite IDs (e.g., SPR_TLMP)
	- sprnames[]: an array that maps sprite IDs to sprite prefixes. (e.g., 
	  SPR_TROO => "TROO")

	- statenum_t: an enumeration of all state IDs (e.g., S_TECHLAMP)
	- state_t: has a spritenum_t, tick counts, an action, and a next state
	- states[]: an array of state_t's

	- mobjtype_t: an enumeration of object type IDs (e.g., MT_PLAYER)
	- mobjinfo_t: the definition of a map object. height, radius, state IDs for
	  normal state, pain state, dead state, etc.
	- mobjinfo[]: an array of mobjinfo_t's.


Notes
----
	- I'd really like person to become a thing, and not be treated any differently
		- has a normal "think" function
		- shows up in the map, for collision detection purposes
	- And I'd really like thing to be some kind of state machine, so it doesn't 
	  have to count frames, etc.


MYDOOM
======================================================================================

Object model
--------------------------------------------------------------------------------------
- thing_definition (FIXME: prune. And expand from mobjinfo_t)
- thing_instance
	- can read from lump
- thing_factory
	- takes a thing instance and instantiates the right kind of thing subclass
- thing
	- inherits from actor (or just has its own interface)
	- subclassed to provide logic to each kind of thing
- actor
	- used for whatever needs to to be called each frame (e.g., strobe lights)
- sprite_state_machine
	- used for logic-free things (e.g., weapons)
	- it's basically a state machine, but it:
		- has animations
		- auto-increments frames and counts ticks
		- knows how to draw sprites centered at the bottom, at the right scale

Things I don't like
--------------------------------------------------------------------------------------
- I don't see sprite_state_machine getting used for anything else. is it?
- assuming that thing doesn't subclass actor, things and actors are badly named
