#ifndef __COLUMN_RANGE_LIST_H
#define __COLUMN_RANGE_LIST_H

#include <stdint.h>
#include "segment_projection.h"
#include "wall_projection.h"

// FXIME: either this class's name or wall_projection's should change. It no longer matches up like it used to.
class column_range_list
{
public:
  column_range_list();
  ~column_range_list();

  bool insert_solid(wall_projection *col_range);
  void insert_nonsolid(wall_projection *col_range);

  wall_projection **clip_segment(segment_projection const *seg_proj, // in
                                 int *num_clipped_crs);              // out
  bool any_unclipped_columns_in_range(int16_t x_left, int16_t x_right) const;

  wall_projection const *get_left_solid_range() const;
  wall_projection const *get_first_nonsolid_range() const;

private:
  wall_projection *left_solid_range;     // single-linked list, of solid segment, sorted left-to-right
  wall_projection *first_nonsolid_range; // single-linked list, of windows, unsorted (FIXME: this doesn't bleong in this class...)
};

void column_range_list_test(void);

#endif
