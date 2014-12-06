#include <stdio.h>

#include "game.h"

int main(int argc, char **argv)
{
  game_init();
  game_run();
  game_destroy();

  return 0;
}
