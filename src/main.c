#include <stdio.h>
#include <stdlib.h>

#include "core/snake_game_core.h"
#include "core/snake_game_core_cycle.h"
#include "utils/argparser.h"
#include "view/snake_controle.h"
#include "view/snake_view.h"

void kbd_up_event(void);
void kbd_left_event(void);
void kbd_down_event(void);
void kbd_right_event(void);
void kbd_exit_event(void);

void exit_event(void);
GameData d;

int main(int argc, char const *argv[]) {
  // hello'
  Options opt = args_load(argc, argv);

  d = init_game_data(opt.size);
  create_one_bait(&d);

  // init kbd event
  SetDirectionFuncP funcp = {
      kbd_up_event,    kbd_left_event, kbd_down_event,
      kbd_right_event, kbd_exit_event,
  };

  while (1) {
    view(&d);
    init_controle();
    tick_wait(opt.delay_ms, funcp);
    final_controle();

    if (tick_game(&d) != KEEP) {
      break;
    }
  }
  exit_event();
}

void kbd_up_event(void) { set_player_direction(&d, UP); }

void kbd_left_event(void) { set_player_direction(&d, LEFT); }

void kbd_down_event(void) { set_player_direction(&d, DOWN); }

void kbd_right_event(void) { set_player_direction(&d, RIGHT); }

void kbd_exit_event(void) { exit_event(); }

void exit_event() {
  final_controle();
  printf("\033[0m\033[0J");
  exit(EXIT_SUCCESS);
}
