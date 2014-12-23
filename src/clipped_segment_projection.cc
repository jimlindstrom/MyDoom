#include <stdio.h>

#include "common.h"
#include "lighting.h"
#include "clipped_segment_projection.h"

//#define DEBUG_PRINTING
#include "debug.h"

// NOTE: assumes dist_*, and [upper/mid/lower].z_* have been set
void clipped_segment_projection::project_vertically(camera const *_camera)
{
  float y0_l, dy_l, y0_r, dy_r;
  _projector->project_z_to_y(-_camera->get_view_height(), dist_l, &y0_l, &dy_l);
  _projector->project_z_to_y(-_camera->get_view_height(), dist_r, &y0_r, &dy_r);

  upper.yt_l = y0_l + (upper.z_t * dy_l); // it'd be nice if upper, mid, and lower had this as a member fn
  upper.yt_r = y0_r + (upper.z_t * dy_r);
  upper.yb_l = y0_l + (upper.z_b * dy_l);
  upper.yb_r = y0_r + (upper.z_b * dy_r);

  mid.yt_l   = y0_l + (mid.z_t   * dy_l);
  mid.yt_r   = y0_r + (mid.z_t   * dy_r);
  mid.yb_l   = y0_l + (mid.z_b   * dy_l);
  mid.yb_r   = y0_r + (mid.z_b   * dy_r);

  lower.yt_l = y0_l + (lower.z_t * dy_l);
  lower.yt_r = y0_r + (lower.z_t * dy_r);
  lower.yb_l = y0_l + (lower.z_b * dy_l);
  lower.yb_r = y0_r + (lower.z_b * dy_r);
}

void clipped_segment_projection::render(vis_planes *vp, vis_plane *floor, vis_plane *ceiling)
{
  if(is_one_sided) { render_1sided(vp, floor, ceiling); }
  else             { render_2sided(vp, floor, ceiling); }
}

void clipped_segment_projection::render_1sided(vis_planes *vp, vis_plane *floor, vis_plane *ceiling)
{
  int16_t h=games_get_screen_height();

  if(x_l >= x_r) { return; }

  for(int x=x_l; x<=x_r; x++)
  {
    int   ldx  = ldx_l      + (ldx_r     - ldx_l   )*(x-x_l)/(x_r-x_l);
    float yt   = mid.yt_l   + (mid.yt_r  - mid.yt_l)*(x-x_l)/(x_r-x_l);
    float yb   = mid.yb_l   + (mid.yb_r  - mid.yb_l)*(x-x_l)/(x_r-x_l);
    float dist = dist_l     + (dist_r    - dist_l  )*(x-x_l)/(x_r-x_l);
    float pct_darkened1 = DIST_TO_PCT_DARKENED(dist); // Darken for distance
    float pct_darkened2 = ((255-light_level)/255.0);  // Darken for sector light level
    float pct_darkened = 1.0 - ((1.0-pct_darkened1)*(1.0-pct_darkened2));

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
    sprite_clip_top[x] = h;
    sprite_clip_bot[x] = -1;

    mid.tex->render_col(ldx, mid.get_dz(), x, yt, yb, clipped_yt, clipped_yb, dist, mid.tx_offset, mid.ty_offset, pct_darkened);
  }
}

void clipped_segment_projection::render_2sided(vis_planes *vp, vis_plane *floor, vis_plane *ceiling)
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
    float pct_darkened1 = DIST_TO_PCT_DARKENED(dist); // Darken for distance
    float pct_darkened2 = ((255-light_level)/255.0);  // Darken for sector light level
    float pct_darkened = 1.0 - ((1.0-pct_darkened1)*(1.0-pct_darkened2));

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

    if(upper.tex && (upper.z_t > upper.z_b))
    {
      int mid = MIN(ymt-1, vp->get_floor_clip(x)-1);
      if(mid >= clipped_yt)
      {
        debug_printf("UPPER: ldx:%d, dz:%d x:%d, y:[%.1f,%.1f], clipped_y:[%d,%d], dist:%.1f, t-off:[%d,%d], darkening:%.1f\n", 
                     ldx, upper.get_dz(), x, yt, ymt-1, clipped_yt, mid, dist, upper.tx_offset, upper.ty_offset, pct_darkened);
        upper.tex->render_col(ldx, upper.get_dz(), x, yt, ymt-1, clipped_yt, mid, dist, upper.tx_offset, upper.ty_offset, pct_darkened);
        vp->update_ceiling_clip(x, mid);
        sprite_clip_top[x] = mid;
      }
      else
      {
        vp->update_ceiling_clip(x, clipped_yt-1);
        sprite_clip_top[x] = clipped_yt-1;
      }
    }
    else if(clip_ceiling)
    {
      vp->update_ceiling_clip(x, clipped_yt-1);
      sprite_clip_top[x] = clipped_yt-1;
    }

    if(lower.tex && (lower.z_t > lower.z_b))
    {
      int mid = MAX(ymb+1, vp->get_ceiling_clip(x)+1);
      if(clipped_yb >= mid)
      {
        debug_printf("LOWER: ldx:%d, dz:%d x:%d, y:[%.1f,%.1f], clipped_y:[%d,%d], dist:%.1f, t-off:[%d,%d], darkening:%.1f\n", 
                     ldx, lower.get_dz(), x, ymb+1, yb, mid, clipped_yb, dist, lower.tx_offset, lower.ty_offset, pct_darkened);
        lower.tex->render_col(ldx, lower.get_dz(), x, ymb+1, yb, mid, clipped_yb, dist, lower.tx_offset, lower.ty_offset, pct_darkened);
        vp->update_floor_clip(x, mid);
        sprite_clip_bot[x] = mid;
      }
      else
      {
        vp->update_floor_clip(x, clipped_yb+1);
        sprite_clip_bot[x] = clipped_yb+1;
      }
    }
    else if(clip_floor)
    {
      vp->update_floor_clip(x, clipped_yb+1);
      sprite_clip_bot[x] = clipped_yb+1;
    }

    //if(mid.tex) { mid.tex->render_col(ldx, mid  .dz, x, clipped_yt, clipped_yb, dist, mid  .tx_offset, mid  .ty_offset, pct_darkened); }
  }
}

