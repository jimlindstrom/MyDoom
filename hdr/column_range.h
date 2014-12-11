#ifndef __COLUMN_RANGE_H
#define __COLUMN_RANGE_H

#include <stdint.h>

class column_range
{
public:
  int16_t x_left, x_right;
  column_range *next_range;
};

class column_range_list
{
public:
  column_range_list();
  ~column_range_list();

  bool insert(column_range *col_range);

  column_range **insert_with_clipping(int16_t x_left, int16_t x_right, int *num_clipped_crs);
  bool any_unclipped_columns_in_range(int16_t x_left, int16_t x_right) const;

  column_range const *get_left_range() const;

private:
  column_range *left_range;
};

void column_range_list_test(void);

#endif
