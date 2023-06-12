#ifndef LIB_DEF
#define LIB_DEF

#include <curses.h>
#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <stdint.h>
#include <ctype.h>
#include <string.h>

enum COLORS {
  SNAKE_COLOR = 1,
  FOOD_COLOR,
  POINTS_COLOR,
  BACKGROUND_COLOR
};

typedef struct {
  uint8_t x, y;
} PairPos;

//snake functions
typedef struct Snake Snake;
Snake *snake_create();
void snake_destroy(Snake *s);
PairPos snake_get_head(Snake *s);
PairPos snake_get_tail(Snake *s);
char snake_get_curr_direction(Snake *s);
uint8_t snake_get_len(Snake *s);
void snake_push_pair(Snake *s, PairPos pair);
void snake_change_curr_direction(Snake *s, char c);
void snake_move(Snake* s);
int snake_check_body_colisions(Snake *s);

//screen functions
PairPos generate_food();
void update_snake();
void update_points();

#endif
