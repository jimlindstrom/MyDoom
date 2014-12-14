Segment Render
  Outputs
    - x_l  .. x_r   (screen horizontal: range of unclipped columns)
    - yt_l .. yt_r  (screen vertical: wall top at left and right column)   --- TBD
    - yb_l .. yb_r  (screen vertical: wall bot at left and right column)   --- TBD
    - t_l  .. t_r   (0..1 parametric val along segment length)
  Limitations
    - Doesn't take into account 'direction' yet. (t = 1-t ?)
    - Doesn't take into account 'offset' yet. A linedef may consist of multiple (partial) segments.
    - Doesn't yet produce y values
    - Doesn't allow further-back walls to poke through transparent sections

Linedef Render

Sidedef Render
  - Clip against ceiling/floor

WallTexture Render
  Inputs
    - x_l  .. x_r   (screen horizontal: destination range)
    - yt_l .. yt_r  (screen vertical: wall top at left and right column)   --- TBD
    - yb_l .. yb_r  (screen vertical: wall bot at left and right column)   --- TBD
    - t_l  .. t_r   (texture horizontal: source range)
    - ut_l .. ut_r  (texture vertical top : source range)
    - ub_l .. ub_r  (texture vertical bot : source range)

Patch (PictureData) Render
  - GetPixel(x,y)
 

