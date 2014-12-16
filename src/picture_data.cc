#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "picture_data.h"

#define ROTATE_AFTER_LOADING

picture_data::picture_data()
{
  pixel_columns = NULL;
}

picture_data::~picture_data()
{
  if(pixel_columns) { 
    #ifdef ROTATE_AFTER_LOADING
    for(int y=0; y<width; y++)
    #else
    for(int y=0; y<height; y++)
    #endif
    {
      delete[] pixel_columns[y]; 
    }
    delete[] pixel_columns; 
  }
}

bool picture_data::set_from_lump_data(uint8_t const *data)
{
  uint8_t const *_data = data;
  uint32_t *column_offsets;
  uint8_t const *col_ptr;
  int x, y, j;
  uint8_t rowstart, pixel_count, dummy_value;

  // read metadata
  width  = *((uint16_t*)_data); _data += 2; // See: http://doom.wikia.com/wiki/Picture_format
  height = *((uint16_t*)_data); _data += 2;
  left   = *((uint16_t*)_data); _data += 2;
  top    = *((uint16_t*)_data); _data += 2;

  // read column offsets
  column_offsets = new uint32_t[width];
  for(y=0; y<width; y++)
  {
    column_offsets[y] = *((uint32_t*)(_data)); _data += 4;
  }

  // read pixels
  pixel_columns = new uint8_t*[width];
  for(x=0; x<width; x++)
  {
    pixel_columns[x] = new uint8_t[height];
    col_ptr = data + column_offsets[x];

    rowstart = 0;
    while(rowstart != 255)
    {
      rowstart = *(col_ptr++);
      if(rowstart == 255) { break; }
      pixel_count = *(col_ptr++);
      dummy_value = *(col_ptr++);
      for(j=0; j<pixel_count; j++)
      {
        int y = rowstart+j;
        if(y<0 || y>height)
        {
          printf("ERROR: picture_data tried to write to (%d,%d) > (%d,%d)\n", x,y,width,height);
          return false;
        }
        pixel_columns[x][y] = *(col_ptr++);
      }
      dummy_value = *(col_ptr++);
    }
  }

  delete[] column_offsets;
  return true;
}

uint8_t const picture_data::get_pixel(int x, int y) const
{
  return pixel_columns[x][y];
}

void picture_data::print_html_file(char const *filename, palette const *pal)
{
  FILE *f;
  color_rgb const *color;

  f = fopen(filename, "wt");
  fprintf(f, "<html>\n");
  fprintf(f, "<body>\n");
  fprintf(f, "<table>\n");
  for(int y=0; y<height; y++)
  {
    fprintf(f, "<tr>\n");
    for(int x=0; x<width; x++)
    {
      color = pal->get_color(pixel_columns[y][x]);
      fprintf(f, "<td style=\"width: 8px; height: 8px; background-color:#%02x%02x%02x;\"></td>\n", color->r, color->g, color->b);
    }
    fprintf(f, "</tr>\n");
  }
  fprintf(f, "</table>\n");
  fprintf(f, "</body>\n");
  fprintf(f, "</html>\n");
  fclose(f);
}
