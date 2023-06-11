#include "lib.h"

typedef struct Snake {
  char currDirection;
  int8_t len, capacity;
  PairPos *bodyPositions;
} Snake;

Snake *snake_create() {
  Snake *s = (Snake *) malloc(sizeof(Snake));
  if(s == NULL) {
    perror("Fail to malloc Snake");
    exit(1);
  }

  s->bodyPositions = (PairPos *) malloc(sizeof(PairPos));
  if(s->bodyPositions == NULL) {
    perror("Fail to malloc Snake");
    exit(1);
  }

  s->len = 1;
  s->capacity = 1;
  s->currDirection = 's';
  s->bodyPositions[0].x = MAX_X/2;
  s->bodyPositions[0].y = MAX_Y/2;

  return s;
}

void snake_destroy(Snake *s) {
  free(s->bodyPositions);
  free(s);
}

void snake_realloc(Snake *s) {
  if(s->len == s->capacity) {
    s->capacity *= 2;
    s->bodyPositions = realloc(s->bodyPositions, s->capacity);
    if(s->bodyPositions == NULL) {
      perror("Error trying to realloc Snake");
      exit(1);
    }
  }
}

void push_pair(Snake *s, PairPos pair) {
  snake_realloc(s);
  s->bodyPositions[s->len++] = pair;
}
