#include "lib.h"

PairPos generate_food(unsigned max_x, unsigned max_y) {
  PairPos pair = { .x = rand()%max_x, .y = rand()%max_y };

  attron(COLOR_PAIR(FOOD_COLOR));
  mvprintw(pair.x, pair.y, "$");
  attroff(COLOR_PAIR(FOOD_COLOR));

  refresh();
  return pair;
}
