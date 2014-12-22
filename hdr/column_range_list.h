#ifndef __COLUMN_RANGE_LIST_H
#define __COLUMN_RANGE_LIST_H

#include <stdint.h>
#include "segment_projection.h"
#include "wall_projection.h"

class column_range_list
{
public:
  column_range_list();
  ~column_range_list();

  bool insert(wall_projection *col_range);

  wall_projection **clip_segment(segment_projection const *seg_proj, // in
                                 int *num_clipped_crs);              // out
  bool any_unclipped_columns_in_range(int16_t x_left, int16_t x_right) const;

  wall_projection const *get_left_range() const;

private:
  wall_projection *left_range;
};

void column_range_list_test(void);

#endif
