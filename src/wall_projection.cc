#include "common.h"
#include "wall_projection.h"

void wall_projection::clip_2sided_upper(void) const
{
  for(int x=x_l; x<=x_r; x++)
  {
    float yt = yt_l + (yt_r-yt_l)*(x-x_l)/(x_r-x_l);
    float dist = dist_l + (dist_r-dist_l)*(x-x_l)/(x_r-x_l);
    if(ceiling)
    {
      int16_t ceil_yt = vp->get_ceiling_clip(x)+1;
      int16_t ceil_yb = MIN(vp->get_floor_clip(x)-1, yt-1);
      if(ceil_yt  <= ceil_yb ) { ceiling->update_clip(x, ceil_yb,  ceil_yt ); }
    }
  }
}

void wall_projection::clip_2sided_lower(void) const
{
  for(int x=x_l; x<=x_r; x++)
  {
    float yb = yb_l + (yb_r-yb_l)*(x-x_l)/(x_r-x_l);
    float dist = dist_l + (dist_r-dist_l)*(x-x_l)/(x_r-x_l);
    if(floor)
    {
      int16_t floor_yt = MAX(vp->get_ceiling_clip(x)+1, yb+1);
      int16_t floor_yb = vp->get_floor_clip(x)-1;
      if(floor_yt <= floor_yb) { floor  ->update_clip(x, floor_yb, floor_yt); }
    }
  }
}

void wall_projection::render_1sided_mid(  void) const
{
  tex->render(ldx_l, ldx_r, ld_h,
              x_l, x_r, 
              yt_l, yb_l, yt_r, yb_r, 
              dist_l, dist_r, 
              tx_offset, ty_offset, 
              light_level,
              vp, floor, ceiling, true, true);
}

void wall_projection::render_2sided_upper(void) const
{
  tex->render(ldx_l, ldx_r, ld_h,
              x_l, x_r, 
              yt_l, yb_l, yt_r, yb_r, 
              dist_l, dist_r, 
              tx_offset, ty_offset, 
              light_level,
              vp, NULL, ceiling, true, false);
}

void wall_projection::render_2sided_mid(  void) const
{
  tex->render(ldx_l, ldx_r, ld_h,
              x_l, x_r, 
              yt_l, yb_l, yt_r, yb_r, 
              dist_l, dist_r, 
              tx_offset, ty_offset, 
              light_level,
              vp, floor, NULL, false, true);
}

void wall_projection::render_2sided_lower(void) const
{
  tex->render(ldx_l, ldx_r, ld_h,
              x_l, x_r, 
              yt_l, yb_l, yt_r, yb_r, 
              dist_l, dist_r, 
              tx_offset, ty_offset, 
              light_level,
              vp, floor, NULL, false, true);
}

