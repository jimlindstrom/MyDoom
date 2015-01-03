#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#include "ui.h"
#include "game.h"
#include "games.h"
#include "tests.h"

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
  for(int i=1; i<argc; i++)
  {
    if(strcmp(argv[i], "--test")==0)
    {
      tests_run();
      return 0;
    }
    else if(strcmp(argv[i], "--wad")==0)
    {
      strcpy(wad_filename, argv[++i]);
    }
    else if(strcmp(argv[i], "--headless")==0)
    {
      ui_set_headless_mode(true);
    }
    else if(strcmp(argv[i], "--player-at")==0)
    {
      game_custom_start_pos = true;
      game_custom_start_x = atof(argv[++i]);
      game_custom_start_y = atof(argv[++i]);
      game_custom_start_r = atof(argv[++i]);
    }
    else if(strcmp(argv[i], "--map")==0)
    {
      strcpy(map_name, argv[++i]);
    }
  }

  run_game_thread();
  run_ui_thread();

  return 0;
}

