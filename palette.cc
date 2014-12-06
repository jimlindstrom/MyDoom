#include <stdlib.h>
#include <stdio.h>
#include "palette.h"

palette::palette()
{
  colors = NULL;
}

palette::~palette()
{
  if(colors) { delete[] colors; }
}

bool palette::from_linear_256_array(uint8_t const *data)
{
  int color_idx, i;

  num_colors = 256;
  colors = new color_rgb[num_colors];
  
  for(color_idx=0, i=0; color_idx<num_colors; color_idx++)
  {
    colors[color_idx].r = data[i++];
    colors[color_idx].g = data[i++];
    colors[color_idx].b = data[i++];
  }

  return true;
}

color_rgb const *palette::get_color(int color_idx) const
{
  // FIXME: assert color_idx<num_colors
  return &colors[color_idx];
}

void palette::print_html_file(char const *filename)
{
  FILE *f;
  f = fopen(filename, "wt");
  fprintf(f, "<html>\n");
  fprintf(f, "<body>\n");
  fprintf(f, "<table>\n");
  fprintf(f, "<tr>\n");
  for(int i=0; i<num_colors; i++)
  {
    fprintf(f, "<td style=\"width: 8px; height: 8px; background-color:#%02x%02x%02x;\"></td>\n", colors[i].r, colors[i].g, colors[i].b);
    if(i%16 == 15) { fprintf(f, "</tr><tr>\n"); }
  }
  fprintf(f, "</tr>\n");
  fprintf(f, "</table>\n");
  fprintf(f, "</body>\n");
  fprintf(f, "</html>\n");
  fclose(f);
}
