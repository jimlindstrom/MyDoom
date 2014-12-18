#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "common.h"
#include "sprite.h"

sprite::sprite()
 : picture_data()
{
  num_orientations = 0;
}

sprite::~sprite()
{
}

void sprite::set_name_prefix(char const *_name_prefix)
{
  strcpy(name_prefix, _name_prefix); 
  name_prefix[4]=0;
}

void sprite::set_frame_idx(uint8_t orientation, uint8_t _frame_idx)
{
  frame_idx[orientation] = _frame_idx; 
  num_orientations = MAX(num_orientations, orientation+1);
}

void sprite::set_rotation_idx(uint8_t orientation, uint8_t _rotation_idx)
{
  rotation_idx[orientation] = _rotation_idx;
  num_orientations = MAX(num_orientations, orientation+1);
}
