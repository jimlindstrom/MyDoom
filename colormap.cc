#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "colormap.h"

colormap::colormap()
{
  brightnesses = NULL;
}

colormap::~colormap()
{
  if(brightnesses) { delete[] brightnesses; }
}

bool colormap::set_data(uint8_t const *data, uint32_t _num_brightnesses)
{
  int idx;

  num_brightnesses = _num_brightnesses;
  brightnesses = new uint8_t[num_brightnesses];
  
  memcpy(&brightnesses[0], data, num_brightnesses);

  return true;
}

uint8_t const *colormap::get_brightness(int idx)
{
  // FIXME: assert idx<num_brightnesses
  return &brightnesses[idx];
}

void colormap::print_html_file(char const *filename)
{
  FILE *f;
  f = fopen(filename, "wt");
  fprintf(f, "<html>\n");
  fprintf(f, "<body>\n");
  fprintf(f, "<table>\n");
  fprintf(f, "<tr>\n");
  for(int i=0; i<num_brightnesses; i++)
  {
    fprintf(f, "<td style=\"width: 8px; height: 8px; background-color:#%02x%02x%02x;\"></td>\n", brightnesses[i], brightnesses[i], brightnesses[i]);
    if(i%16 == 15) { fprintf(f, "</tr><tr>\n"); }
  }
  fprintf(f, "</tr>\n");
  fprintf(f, "</table>\n");
  fprintf(f, "</body>\n");
  fprintf(f, "</html>\n");
  fclose(f);
}
