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
