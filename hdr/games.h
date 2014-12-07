#ifndef __GAMES_H
#define __GAMES_H

#include "key_codes.h"

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

#endif
