#ifndef __SUBSECTOR_H
#define __SUBSECTOR_H

#include <stdint.h>

#include "projector.h"
#include "wad_segment.h"
#include "sector.h"
#include "camera.h"
#include "clipped_segment_projections.h"
#include "vis_planes.h"
#include "vis_things.h"
#include "thing.h"

#define SUBSECTOR_NUM_BYTES 4 // size on disk (in the lump)

class subsector
{
public:
  subsector();
  ~subsector();

  bool read_from_lump_data(uint8_t const *lump_data);

  uint16_t get_num_segments(void) const { return num_segments; }
  uint16_t get_first_segment_num(void) const { return first_segment_num; }
  wad_segment const *get_nth_segment(int n) const { return segments[n]; }
  sector const *get_sector(void) const { return get_nth_segment(0)->get_front_sector(); }

  void allocate_segments(void);
  void set_nth_segment(int n, wad_segment const *_segment);

  void render_player_view(camera const *_camera,
                          clipped_segment_projections *clipped_seg_projs, 
                          vis_planes *vp, 
                          thing *things, int16_t num_things, vis_things *vt) const;

  uint16_t subsector_num;
private:
  uint16_t num_segments;
  uint16_t first_segment_num;
  wad_segment const **segments;
};

#endif
