#include "lib.h"
#include <ncurses.h>

PairPos generate_food(unsigned max_x, unsigned max_y) {
  PairPos pair = { .x = rand()%max_x, .y = rand()%max_y };
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
