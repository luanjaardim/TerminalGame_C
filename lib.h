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

#define MAX_X 46
#define MAX_Y 72

#define SNAKE_COLOR   1
#define FOOD_COLOR    2
#define POINTS_COLOR  3

typedef struct {
  int8_t x, y;
} PairPos;

typedef struct Snake Snake;
Snake *snake_create();
void snake_destroy(Snake *s);
void push_pair(Snake *s, PairPos pair);

#endif
