#include <stdio.h>
#include <math.h>

#include "fps_tracker.h"

//#define DEBUG_PRINTING
#include "debug.h"

fps_tracker::fps_tracker()
{
  frame_time_idx = 0;
  frame_count = 0;
}

fps_tracker::~fps_tracker()
{
}

void fps_tracker::tick(void)
{
  double delta_sec, fps;
  int idx_prev = (frame_time_idx+1)%FRAME_TIMES_COUNT;
  int num_frames = FRAME_TIMES_COUNT - 1;

  gettimeofday(&frame_times[frame_time_idx], NULL);

  delta_sec =  (frame_times[frame_time_idx].tv_sec - frame_times[idx_prev].tv_sec) +
              ((frame_times[frame_time_idx].tv_usec- frame_times[idx_prev].tv_usec)/1000000.0);
  if(delta_sec>0.00001 && delta_sec<10.0)
  {
    fps = (double)num_frames / delta_sec;
    debug_printf("  %.2f frames/sec (%d frames in %.3fsec)\n", fps, (FRAME_TIMES_COUNT-1), delta_sec);
  }

  frame_time_idx = ((frame_time_idx+1) % FRAME_TIMES_COUNT);
  frame_count++;
}
