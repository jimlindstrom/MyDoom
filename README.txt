Data structs:

Variables:
  - visplane  visplanes[MAXVISPLANES];
  - visplane *floorplane;
  - visplane *ceilingplane;
  - short floorclip[SCREENWIDTH];	// at a given x, don't draw floors below this height
					// (it's how far up from the bottom of screen we've drawn a floor here)
  - short ceilingclip[SCREENWIDTH];	// at a given x, don't draw ceilings above this height 
					// (it's how far down from the top of screen we've drawn a ceiling here)

Before a frame:
  - Initialize floorclip to SCREENHEIGHT // not clipped
  - Initialize ceilingclip to -1 // not clipped

In Node::Render
  - Find/create a vis_plane for the floor and ceiling [r_bsp.c:513]
    - match on {height, picnum, lightlevel}
    - unless floor   > viewheight
    - unless ceiling < viewheight

In Segment::Render
  - Determine whether/not to mark the floor and ceiling [R_StoreWallRange(), r_segs.c:371]
    - For one-sided segments or closed doors, the answer to both is yes
    - For two-sided segments: yes if any of {pic,lighting,height} differ; no otherise.

  - Call R_CheckPlane for the floor, over the segment's x-range
  - Call R_CheckPlane for the ceiling, over the segment's x-range
  - render the segment's x-range

In CheckPlane
  - Stretch the visplane horizontally to cover the new segment, if needed
  - If the new segment is incompatible, fork a new plane instead

In the inner column renderer:
  - For the ceiling (if marked):
    - Set visplane, at this x, to have top of ceiling be: one pixel lower than the [bottom of the lowest ceiling]
    - Set visplane, at this x, to have bot of ceiling be: one pixel above the wall (or [ceil], if lower) (or [floor], if higher) 
  - For the floor (if marked);
    - Set visplane, at this x, to have bot of floor be: one pixel higher than the [top of the tallest floor]
    - Set visplane, at this x, to have top of floor be: one pixel below the wall (or [floor], if higher) (or [ceil], if lower)
  - Update floorclip and ceilclip with wall top and bottom

Render all Visplanes [R_DrawPlanes]
  - Get the texture
  - Calculate the lighting
  - Calculate the angle
  - Calculate the distance
  - Iterate over x range and call [R_MakeSpans]
    - Iterate over some y ranges (?) and call [R_MapPlane]
      - Calculate some slopes and call [R_DrawSpan]
