#ifndef __FRAME_BUF_H
#define __FRAME_BUF_H

#include "color.h"

bool frame_buf_init(int _width, int _height);
void frame_buf_destroy(void);
void frame_buf_clear(void);
void frame_buf_flush_to_ui(void);
void frame_buf_draw_point(int x, int y, color_rgba const *color);
void frame_buf_draw_line(int x1, int y1, int x2, int y2, color_rgba const *color);

#endif
