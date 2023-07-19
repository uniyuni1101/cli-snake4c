#ifndef ARGPARSER_H
#define ARGPARSER_H
#include "share/snake_game_data.h"

typedef struct {
  int delay_ms;
  AreaSize size;
} Options;

Options args_load(int argc, char const *argv[]);

#endif
