#include "lib.h"
#include <ncurses.h>

PairPos generate_food() {
  PairPos pair = { .x = rand()%MAX_X, .y = rand()%MAX_Y };
  attron(COLOR_PAIR(FOOD_COLOR));
  //mvchgat(pair.x, pair.y, 1, A_NORMAL, FOOD_COLOR, NULL);
  mvprintw(pair.x, pair.y, "$");
  attroff(COLOR_PAIR(FOOD_COLOR));
  refresh();
  return pair;
}

void update_snake() {

}

void update_points() {

}
