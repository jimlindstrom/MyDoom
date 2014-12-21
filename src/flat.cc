#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "flat.h"

flat::flat()
{
  data = NULL;
}

flat::~flat()
{
  if(data) { delete[] data; }
}

bool flat::set_data(uint8_t const *_data)
{
  data = new uint8_t[FLAT_NUM_BYTES];
  
  memcpy(&data[0], _data, FLAT_NUM_BYTES);

  return true;
}

uint8_t flat::get_pixel(int x, int y) const
{
  #define RANGE_CHECKING
  #ifdef RANGE_CHECKING
  if(x<0 || x>=FLAT_WIDTH )
  {
    printf("ERROR: x is %d, not in [%d,%d]\n", x, 0, FLAT_WIDTH -1); 
    exit(0);
  }
  if(y<0 || y>=FLAT_HEIGHT)
  {
    printf("ERROR: y is %d, not in [%d,%d]\n", y, 0, FLAT_HEIGHT-1); 
    exit(0);
  }
  #endif
  // FIXME: assert x,y are sane
  return data[(y*FLAT_WIDTH)+x];
}

void flat::print_html_file(char const *filename, palette const *pal)
{
  FILE *f;
  color_rgb const *color;

  f = fopen(filename, "wt");
  fprintf(f, "<html>\n");
  fprintf(f, "<body>\n");
  fprintf(f, "<table>\n");
  fprintf(f, "<tr>\n");
  for(int i=0; i<FLAT_NUM_BYTES; i++)
  {
    color = pal->get_color(data[i]);
    fprintf(f, "<td style=\"width: 8px; height: 8px; background-color:#%02x%02x%02x;\"></td>\n", color->r, color->g, color->b);
    if(i%FLAT_WIDTH == (FLAT_WIDTH-1)) { fprintf(f, "</tr><tr>\n"); }
  }
  fprintf(f, "</tr>\n");
  fprintf(f, "</table>\n");
  fprintf(f, "</body>\n");
  fprintf(f, "</html>\n");
  fclose(f);
}
