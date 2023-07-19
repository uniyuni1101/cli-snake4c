#include "view/snake_view.h"

#include <stdio.h>

#include "share/snake_game_data.h"

typedef char TileStr[30];
typedef struct {
  TileStr EMPRTY_TILE_1;
  TileStr EMPRTY_TILE_2;
  TileStr WALL_TILE;
  TileStr BAIT_TILE;
  TileStr SNAKE_TILE;
} TileStrList;

int print_game_state(int score) { /*return int is write line len*/
  printf("Snake Size: %d\n\n", score);
  return 2;
}

TileStr *get_tile_string(TileType tile_type, int is_even_row, int is_even_col) {
  static TileStrList TILE_PRINT_DATA = {
      "\033[48;2;40;40;40m  \033[0m",    "\033[48;2;80;80;80m  \033[0m",
      "\033[48;2;122;122;122m  \033[0m", "\033[48;2;224;36;64m  \033[0m",
      "\033[48;2;255;255;255m  \033[0m",
  };
  switch (tile_type) {
    case EMPTY:
      if (is_even_col == 1) {
        if (is_even_row == 1) {
          return &TILE_PRINT_DATA.EMPRTY_TILE_1;
        } else {
          return &TILE_PRINT_DATA.EMPRTY_TILE_2;
        }
      } else {
        if (is_even_row == 0) {
          return &TILE_PRINT_DATA.EMPRTY_TILE_1;
        } else {
          return &TILE_PRINT_DATA.EMPRTY_TILE_2;
        }
      }
      break;
    case WALL:
      return &TILE_PRINT_DATA.WALL_TILE;
    case BAIT:
      return &TILE_PRINT_DATA.BAIT_TILE;
    case SNAKE:
      return &TILE_PRINT_DATA.SNAKE_TILE;
  }
}

int print_line_view(Tile *tile, int tile_len, int is_even_row) {
  static char buf[1028];
  setvbuf(stdout, buf, _IOLBF, sizeof(buf));
  for (int i = 0; i < tile_len; i++) {
    TileStr *s = get_tile_string(tile[i].type, is_even_row, i % 2);
    printf("%s", *s);
  }
  printf("\n");
  return 1;
}

void print_grid_view(GameData *data) {
  int write_line_len = 0;
  write_line_len += print_game_state(data->snake_size);

  for (int tile_grid_y = 0; tile_grid_y < data->area_size + 2; tile_grid_y++) {
    write_line_len += print_line_view(data->grid[tile_grid_y],
                                      data->area_size + 2, tile_grid_y % 2);
  }

  printf("\033[%dF", write_line_len);
}

void view(GameData *data) { print_grid_view(data); }
