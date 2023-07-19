#ifndef SNAKE_GAME_DATA_H
#define SNAKE_GAME_DATA_H
#define GRID_SIZE 30

typedef enum { UP = 0, LEFT = 1, DOWN = 2, RIGHT = 3, NONE = 4 } Direction;

typedef enum { EMPTY, BAIT, WALL, SNAKE } TileType;

typedef struct {
  Direction front;
  Direction back;
} SnakeData;

typedef struct {
  TileType type;
  SnakeData snake_data;
} Tile;

typedef Tile TileGrid[GRID_SIZE][GRID_SIZE];

typedef struct {
  int x;
  int y;
} Pos2d;

typedef enum {
  x9 = 9,
  x15 = 15,
  x21 = 21,
} AreaSize;

typedef struct {
  int snake_size;
  Direction snake_direction;
  Pos2d pos;
  TileGrid grid;
  AreaSize area_size;
} GameData;

#endif
