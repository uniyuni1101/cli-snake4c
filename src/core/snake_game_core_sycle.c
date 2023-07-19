#include <stdlib.h>
#include <time.h>

#include "core/snake_game_core_cycle.h"

Tile *get_tile_p(GameData *data, Pos2d pos) {
  return &(data->grid[pos.y][pos.x]);
}

void set_player_direction(GameData *data, Direction direction) {
  if (get_tile_p(data, data->pos)->snake_data.back == direction) {
    return;
  }
  data->snake_direction = direction;
}

int get_rand(int min, int count) {
  int d = rand();
  if (d % 100 == 0) {
    srand((unsigned int)time(NULL));
  }
  return min + d % count;
}

void create_one_bait(GameData *data) {
  Pos2d *empty_tiles;
  empty_tiles =
      (Pos2d *)calloc((data->area_size * data->area_size), sizeof(Pos2d));

  int empty_count = 0;
  for (int y = 0; y < data->area_size + 2; y++) {
    for (int x = 0; x < data->area_size + 2; x++) {
      if (data->grid[y][x].type == EMPTY) {
        empty_tiles[empty_count++] = (Pos2d){x, y};
      }
    }
  }

  Pos2d select_pos = empty_tiles[get_rand(0, empty_count)];
  *get_tile_p(data, select_pos) = (Tile){BAIT};
};

Pos2d get_next_head_pos(GameData *data) {
  Pos2d res;
  switch (data->snake_direction) {
    case UP:
      res.x = data->pos.x;
      res.y = data->pos.y - 1;
      break;

    case DOWN:
      res.x = data->pos.x;
      res.y = data->pos.y + 1;
      break;

    case LEFT:
      res.x = data->pos.x - 1;
      res.y = data->pos.y;
      break;

    case RIGHT:
      res.x = data->pos.x + 1;
      res.y = data->pos.y;
      break;
  }
  return res;
}

int can_eat_bait(GameData *data) {
  if (get_tile_p(data, get_next_head_pos(data))->type == BAIT) {
    return 1;
  } else {
    return 0;
  }
}

Pos2d get_snake_tail_pos(GameData *data) {
  Pos2d now_pos = data->pos;
  while (get_tile_p(data, now_pos)->snake_data.back != NONE) {
    switch (get_tile_p(data, now_pos)->snake_data.back) {
      case UP:
        now_pos.y--;
        break;

      case DOWN:
        now_pos.y++;
        break;

      case LEFT:
        now_pos.x--;
        break;

      case RIGHT:
        now_pos.x++;
        break;
    }
  }
  return now_pos;
}

int can_touch_object(GameData *data) {
  switch (get_tile_p(data, get_next_head_pos(data))->type) {
    case WALL:
    case SNAKE:
      return 1;
    default:
      return 0;
  }
}

Pos2d next_direction_pos(Direction d, Pos2d pos) {
  switch (d) {
    case UP:
      pos.y--;
      break;

    case DOWN:
      pos.y++;
      break;

    case LEFT:
      pos.x--;
      break;

    case RIGHT:
      pos.x++;
      break;
  }
  return pos;
}

int move_snake(GameData *data, int bait) {  // return is_touch_object;
  Pos2d next_pos = get_next_head_pos(data);
  *get_tile_p(data, next_pos) =
      (Tile){SNAKE, (SnakeData){NONE, (data->snake_direction + 2) % 4}};

  get_tile_p(data, data->pos)->snake_data.front = data->snake_direction;

  data->pos = next_pos;

  Pos2d tail_pos = get_snake_tail_pos(data);
  if (bait == 0) {
    Tile *t_p = get_tile_p(data, tail_pos);
    get_tile_p(data, next_direction_pos(t_p->snake_data.front, tail_pos))
        ->snake_data.back = NONE;

    t_p->type = EMPTY;
  }
}

int clear_game(GameData *data) {
  for (int i = 1; i < data->area_size + 1; i++) {
    for (int j = 1; j < data->area_size + 1; j++) {
      switch (get_tile_p(data, (Pos2d){i, j})->type) {
        case EMPTY:
        case BAIT:
          return 0;
        default:
          continue;
      }
    }
  }
  return 1;
}

TickResult tick_game(GameData *data) {  // return is_game_over;
  int can_bait = can_eat_bait(data);
  if (can_touch_object(data)) {
    return GAME_OVER;
  }
  move_snake(data, can_bait);
  if (clear_game(data)) {
    return CLEAR;
  }
  if (can_bait) {
    data->snake_size++;
    create_one_bait(data);
  }
  return KEEP;
}
