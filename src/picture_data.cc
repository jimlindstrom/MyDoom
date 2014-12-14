#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "picture_data.h"

picture_data::picture_data()
{
  pixel_columns = NULL;
}

picture_data::~picture_data()
{
  if(pixel_columns) { 
    for(int y=0; y<height; y++)
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
  int y, j;
  uint8_t rowstart, pixel_count, dummy_value;

  // read metadata
  height = *((uint16_t*)_data); _data += 2; // This reads h,w in reverse order from http://doom.wikia.com/wiki/Picture_format
  width  = *((uint16_t*)_data); _data += 2; // but it corresponds to the unrotated, original w/h
  left   = *((uint16_t*)_data); _data += 2;
  top    = *((uint16_t*)_data); _data += 2;

  // read column offsets
  column_offsets = new uint32_t[height];
  for(y=0; y<height; y++)
  {
    column_offsets[y] = *((uint32_t*)(_data)); _data += 4;
  }

  // read pixels
  pixel_columns = new uint8_t*[height];
  for(y=0; y<height; y++)
  {
    pixel_columns[y] = new uint8_t[width];
    col_ptr = data + column_offsets[y];

    rowstart = 0;
    while(rowstart != 255)
    {
      rowstart = *(col_ptr++);
      if(rowstart == 255) { break; }
      pixel_count = *(col_ptr++);
      dummy_value = *(col_ptr++);
      for(j=0; j<pixel_count; j++)
      {
        int x = rowstart+j;
        if(x<0 || x>=width)
        {
          printf("ERROR: picture_data tried to write to (%d,%d) > (%d,%d)\n", x,y,width,height);
          return false;
        }
        pixel_columns[y][x] = *(col_ptr++);
      }
      dummy_value = *(col_ptr++);
    }
  }

  delete[] column_offsets;
  return true;
}

uint8_t const picture_data::get_pixel(int x, int y) const
{
  // FIXME: assert x,y are sane
  return pixel_columns[y][x];
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
