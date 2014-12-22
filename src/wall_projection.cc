#include "common.h"
#include "lighting.h"
#include "wall_projection.h"

// NOTE: assumes dist_* has been set
void wall_projection::project_vertically(projector const *_projector, player const *_player)
{
  _projector->project_z_to_y(-_player->get_view_height(), dist_l, &y0_l, &dy_l);
  _projector->project_z_to_y(-_player->get_view_height(), dist_r, &y0_r, &dy_r);
}

void wall_projection::render_1sided(void) const
{
  int16_t h=games_get_screen_height();

  if(x_l == x_r) { return; }

  for(int x=x_l; x<=x_r; x++)
  {
    int   ldx  = ldx_l      + (ldx_r     - ldx_l   )*(x-x_l)/(x_r-x_l);
    float yt   = mid.yt_l   + (mid.yt_r  - mid.yt_l)*(x-x_l)/(x_r-x_l);
    float yb   = mid.yb_l   + (mid.yb_r  - mid.yb_l)*(x-x_l)/(x_r-x_l);
    float dist = dist_l     + (dist_r    - dist_l  )*(x-x_l)/(x_r-x_l);
    float pct_darkened = DIST_TO_PCT_DARKENED(dist) * // Darken for distance (FIXME: How does Doom do this?)
                         (light_level/255.0);         // Darken for sector light level

    int clipped_yt = MAX(yt, vp->get_ceiling_clip(x)+1);
    int clipped_yb = MIN(yb, vp->get_floor_clip(  x)-1);
    if(ceiling && clip_ceiling)
    {
      int16_t ceil_yt = vp->get_ceiling_clip(x)+1;
      int16_t ceil_yb = MIN(yt-1, vp->get_floor_clip(x)-1);
      if(ceil_yt  <= ceil_yb ) { ceiling->update_clip(x, ceil_yb,  ceil_yt ); }
    }
    if(floor && clip_floor)
    {
      int16_t floor_yt = MAX(yb+1, vp->get_ceiling_clip(x)+1);
      int16_t floor_yb = vp->get_floor_clip(x)-1;
      if(floor_yt <= floor_yb) { floor  ->update_clip(x, floor_yb, floor_yt); }
    }

    vp->update_ceiling_clip(x, h); // FIXME: this should only be "view height" not "screen height"
    vp->update_floor_clip(  x, -1);

    mid.tex->render_col(ldx, mid.dz, x, yt, yb, clipped_yt, clipped_yb, dist, mid.tx_offset, mid.ty_offset, pct_darkened);
  }
}

void wall_projection::render_2sided(void) const
{
  if(x_l >= x_r) { return; }

  for(int x=x_l; x<=x_r; x++)
  {
    int   ldx  = ldx_l        + (ldx_r       - ldx_l     )*(x-x_l)/(x_r-x_l);
    float yt   = upper.yt_l   + (upper.yt_r  - upper.yt_l)*(x-x_l)/(x_r-x_l);
    float ymt  = mid  .yt_l   + (mid  .yt_r  - mid  .yt_l)*(x-x_l)/(x_r-x_l);
    float ymb  = mid  .yb_l   + (mid  .yb_r  - mid  .yb_l)*(x-x_l)/(x_r-x_l);
    float yb   = lower.yb_l   + (lower.yb_r  - lower.yb_l)*(x-x_l)/(x_r-x_l);
    float dist = dist_l       + (dist_r      - dist_l    )*(x-x_l)/(x_r-x_l);
    float pct_darkened = DIST_TO_PCT_DARKENED(dist) * // Darken for distance (FIXME: How does Doom do this?)
                         (light_level/255.0);         // Darken for sector light level

    int clipped_yt = MAX(yt, vp->get_ceiling_clip(x)+1);
    int clipped_yb = MIN(yb, vp->get_floor_clip(  x)-1);
    if(ceiling && clip_ceiling)
    {
      int16_t ceil_yt = vp->get_ceiling_clip(x)+1;
      int16_t ceil_yb = MIN(yt-1, vp->get_floor_clip(x)-1);
      if(ceil_yt  <= ceil_yb ) { ceiling->update_clip(x, ceil_yb,  ceil_yt ); }
    }
    if(floor && clip_floor)
    {
      int16_t floor_yt = MAX(yb+1, vp->get_ceiling_clip(x)+1);
      int16_t floor_yb = vp->get_floor_clip(x)-1;
      if(floor_yt <= floor_yb) { floor  ->update_clip(x, floor_yb, floor_yt); }
    }

    if(upper.tex)
    {
      int mid = MIN(ymt-1, vp->get_floor_clip(x)-1);
      if(mid >= clipped_yt)
      {
        upper.tex->render_col(ldx, upper.dz, x, yt, mid, clipped_yt, mid, dist, upper.tx_offset, upper.ty_offset, pct_darkened);
        vp->update_ceiling_clip(x, mid);
      }
      else
      {
        vp->update_ceiling_clip(x, clipped_yt-1);
      }
    }
    else if(clip_ceiling)
    {
      vp->update_ceiling_clip(x, clipped_yt-1);
    }

    if(lower.tex)
    {
      int mid = MAX(ymb+1, vp->get_ceiling_clip(x)+1);
      if(clipped_yb >= mid)
      {
        lower.tex->render_col(ldx, lower.dz, x, mid, yb, mid, clipped_yb, dist, upper.tx_offset, upper.ty_offset, pct_darkened);
        vp->update_floor_clip(x, mid);
      }
      else
      {
        vp->update_floor_clip(x, clipped_yb+1);
      }
    }
    else if(clip_floor)
    {
      vp->update_floor_clip(x, clipped_yb+1);
    }

    //if(mid.tex) { mid.tex->render_col(ldx, mid  .dz, x, clipped_yt, clipped_yb, dist, mid  .tx_offset, mid  .ty_offset, pct_darkened); }
  }
}

