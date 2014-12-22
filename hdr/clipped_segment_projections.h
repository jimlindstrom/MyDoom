#ifndef __CLIPPED_SEGMENT_PROJECTIONS_H
#define __CLIPPED_SEGMENT_PROJECTIONS_H

#include <stdint.h>
#include "segment_projection.h"
#include "clipped_segment_projection.h"

// FXIME: either this class's name or clipped_segment_projection's should change. It no longer matches up like it used to.
class clipped_segment_projections
{
public:
  clipped_segment_projections();
  ~clipped_segment_projections();

  bool insert_solid(clipped_segment_projection *csp);
  void insert_nonsolid(clipped_segment_projection *csp);

  clipped_segment_projection **clip_segment(segment_projection const *seg_proj, // in
                                            int *num_csp);                      // out
  bool any_unclipped_columns_in_range(int16_t x_left, int16_t x_right) const;

  clipped_segment_projection const *get_left_solid_csp() const;
  clipped_segment_projection const *get_first_nonsolid_csp() const;

private:
  clipped_segment_projection *left_solid_csp;     // single-linked list, of solid segment, sorted left-to-right
  clipped_segment_projection *first_nonsolid_csp; // single-linked list, of windows, unsorted (FIXME: this doesn't bleong in this class...)
};

void clipped_segment_projections_test(void);

#endif
