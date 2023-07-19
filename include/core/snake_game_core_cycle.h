#ifndef SNAKE_GAME_CORE_CYCLE_H
#define SNAKE_GAME_CORE_CYCLE_H
#include "snake_game_core.h"
typedef enum { KEEP, GAME_OVER, CLEAR } TickResult;

TickResult tick_game(GameData *);

void set_player_direction(GameData *, Direction);

void create_one_bait(GameData *);

#endif
