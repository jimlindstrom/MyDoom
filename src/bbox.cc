#include "bbox.h"

bool bbox::includes(vertex const *v) const
{
  return (v->get_x() >= x_left  ) &&
         (v->get_x() <= x_right ) &&
         (v->get_y() >= y_top   ) &&
         (v->get_y() <= y_bottom);
}
