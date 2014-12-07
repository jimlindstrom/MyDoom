#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#include "ui.h"
#include "games.h"

// NOTE: This has to be the main thread for Cocoa not to freak out
void run_ui_thread()
{
  ui_run_cocoa_app(); // doesn't return until window is closed
}

void *game_main(void *data) 
{
  sleep(1); // FIXME: crappy way (Race condition) of waiting till the UI's up and running.

  game_init();
  game_run();
  game_destroy();

  exit(0);

  return NULL;
}

// this spawns a new thread and runs the game in it
void run_game_thread(void)
{
    pthread_attr_t  attr;
    pthread_t       posixThreadID;

    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    pthread_create(&posixThreadID, &attr, &game_main, NULL);
    pthread_attr_destroy(&attr);
}

int main(int argc, char **argv)
{
  run_game_thread();
  run_ui_thread();

  return 0;
}

