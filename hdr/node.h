#ifndef __NODE_H
#define __NODE_H

#include <stdint.h>

#define NODE_NUM_BYTES 4 // size on disk (in the lump)

#define NODE_CHILD_NUM_MASK       0x7fff
#define NODE_CHILD_TYPE_MASK      0x8000
#define NODE_CHILD_TYPE_SUBSECTOR 0x8000
#define NODE_CHILD_TYPE_NODE      0x0000

class partition_line
{
public:
  int16_t x;
  int16_t y;
  int16_t dx;
  int16_t dy;
};

class bbox
{
public:
  int16_t y_top;
  int16_t y_bottom;
  int16_t x_left;
  int16_t x_right;
};

class node_child_link
{
public:
  bbox     _bbox;
  uint16_t child_type;
  uint16_t child_num;

  bool is_subsector() const { return (child_type == NODE_CHILD_TYPE_SUBSECTOR); }
  bool is_node() const      { return (child_type == NODE_CHILD_TYPE_NODE); }
};

class node
{
public:
  node();
  ~node();

  bool read_from_lump_data(uint8_t const *lump_data);

  partition_line const *get_partition(void) const { return &partition; }
  node_child_link const *get_left(void) const { return &left; }
  node_child_link const *get_right(void) const { return &right; }

private:
  partition_line partition;
  node_child_link left;
  node_child_link right;
};

#endif
