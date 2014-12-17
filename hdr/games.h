#ifndef __GAMES_H
#define __GAMES_H

#include <stdint.h>
#include "key_codes.h"

#define MAX_SCREEN_WIDTH  768
#define MAX_SCREEN_HEIGHT 480

void game_init(void);
void game_run(void);
void game_destroy(void);

#ifdef __cplusplus
extern "C" {
#endif
void game_post_event_key_up(int key_code);
void game_post_event_key_down(int key_code);
#ifdef __cplusplus
}
#endif

int16_t games_get_screen_width(void);
int16_t games_get_screen_height(void);

#endif
