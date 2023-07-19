#include "core/snake_game_core.h"

#include <stdio.h>

#include "share/snake_game_data.h"

void create_tile_grid(TileGrid grid, AreaSize size) {
  for (int i = 0; i < size + 2; i++) {
    for (int j = 0; j < size + 2; j++) {
      grid[i][j] = (Tile){EMPTY};
    }
  }

  for (int i = 0; i < size + 2; i++) {
    grid[i][0] = (Tile){WALL};
    grid[0][i] = (Tile){WALL};
    grid[size + 1][i] = (Tile){WALL};
    grid[i][size + 1] = (Tile){WALL};
  }

  for (int i = 0; i < 4; i++) {
    grid[size / 2 + 1][size / 2 + 1 - i] =
        (Tile){SNAKE, (SnakeData){RIGHT, LEFT}};
  }

  grid[size / 2 + 1][size / 2 + 1].snake_data.front = NONE;
  grid[size / 2 + 1][size / 2 + 1 - 3].snake_data.back = NONE;
}

GameData init_game_data(AreaSize size) {
  TileGrid tile_grid;
  GameData data;
  data.snake_size = 4;
  data.snake_direction = RIGHT;
  data.pos = (Pos2d){size / 2 + 1, size / 2 + 1};
  data.area_size = size;
  create_tile_grid(data.grid, size);

  return data;
}
