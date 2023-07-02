#include "lib.h"

typedef struct Snake {
  char currDirection;
  unsigned len, capacity;
  PairPos *bodyPositions;
} Snake;

Snake *snake_create(unsigned max_x, unsigned max_y) {
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
  s->bodyPositions[0].x = max_x/2;
  s->bodyPositions[0].y = max_y/2;

  return s;
}

void snake_destroy(Snake *s) {
  free(s->bodyPositions);
  free(s);
}

void snake_realloc(Snake *s) {
  if(s->len == s->capacity) {
    s->capacity *= 2;
    s->bodyPositions = (PairPos *) realloc((void *) s->bodyPositions, s->capacity * sizeof(PairPos));
    if(s->bodyPositions == NULL) {
      perror("Error trying to realloc Snake");
      exit(1);
    }
  }
}

PairPos snake_get_head(Snake *s) {
  return s->bodyPositions[0];
}

PairPos snake_get_tail(Snake *s) {
  return s->bodyPositions[s->len - 1];
}

char snake_get_curr_direction(Snake *s) {
  return s->currDirection;
}

uint8_t snake_get_len(Snake *s) {
  return s->len;
}

void snake_push_pair(Snake *s, PairPos pair) {
  snake_realloc(s);
  s->bodyPositions[s->len++] = pair;
}

void snake_change_curr_direction(Snake *s, char c) {
  char ch = tolower(c);
  if(ch == 'a' || ch == 's' || ch == 'w' || ch == 'd' || ch == 'q')
    s->currDirection = ch;
}

/* This function moves every position of the snake body one position backward
 * and put the new head on the first
 */
void move_prev_pos_back(PairPos *pos, size_t len, PairPos new_pos) {
  memmove(pos + 1, pos, len);
  pos[0] = new_pos;
}

void snake_move(Snake* s) {
  PairPos newPos;
  PairPos head = snake_get_head(s);
  switch(s->currDirection) {
    case 'w':
      newPos.x = head.x - 1;
      newPos.y = head.y;
    break;
    case 'a':
      newPos.x = head.x;
      newPos.y = head.y - 1;
    break;
    case 's':
      newPos.x = head.x + 1;
      newPos.y = head.y;
    break;
    case 'd':
      newPos.x = head.x;
      newPos.y = head.y + 1;
    break;
    default:
    break;
  }
  move_prev_pos_back(s->bodyPositions, (s->len-1) * sizeof(PairPos), newPos);
}

int snake_check_body_colisions(Snake *s, PairPos colisionPair) {
  for(int pos = 4; pos < s->len; pos++) {
    if(s->bodyPositions[pos].x == colisionPair.x
      && s->bodyPositions[pos].y == colisionPair.y)
      return 1;
  }
  return 0;
}
