#ifndef __FPS_TRACKER_H
#define __FPS_TRACKER_H

#include <stdint.h>
#include <sys/time.h>

class fps_tracker
{
public:
  fps_tracker();
  ~fps_tracker();

  void tick(void);
  uint32_t get_frame_count(void) const { return frame_count; }

private:
  #define FRAME_TIMES_COUNT 50
  struct timeval frame_times[FRAME_TIMES_COUNT];
  int frame_time_idx;
  uint32_t frame_count;
};

#endif
