#ifndef __UI_H
#define __UI_H

#ifdef __cplusplus
extern "C" {
#endif
void ui_run_cocoa_app(void);
void ui_resize_window(int width, int height);
void ui_draw_image(unsigned char *image_data, int width, int height);
#ifdef __cplusplus
}
#endif

#endif
