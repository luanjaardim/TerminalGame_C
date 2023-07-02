#include "lib.h"

unsigned MAX_X, MAX_Y;
PairPos foodPair;

pthread_cond_t cond_var = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER;

void initializeWindow() {
	initscr();          //initalizes the terminal screen, start curses mode
	raw();              //turn off line buffering, so we don't to press Enter on getch, by example
	noecho();           //what we type doesn't appears on the screen
  getmaxyx(stdscr, MAX_X, MAX_Y);
	srand(time(NULL));
	start_color();
	curs_set(0);

	//initialize color pairs -> (the identifier of the pair, foreground  color, and background color)
	init_pair(SNAKE_COLOR, COLOR_BLACK, COLOR_GREEN);
	init_pair(FOOD_COLOR, COLOR_BLACK, COLOR_RED);
	init_pair(POINTS_COLOR, COLOR_BLACK, COLOR_WHITE);
	init_pair(BACKGROUND_COLOR, COLOR_BLACK, COLOR_BLACK);

	//first food
  foodPair = generate_food(MAX_X, MAX_Y);
	while(foodPair.x == MAX_X/2 && foodPair.y == MAX_Y/2) foodPair = generate_food(MAX_X, MAX_Y);
}

void freeWindow() {
	endwin(); //destroy the window created with initscr
}

void *drawThread(void *arg) {
	Snake *s = (Snake *) arg;

	while(snake_get_curr_direction(s) != 'q' && snake_get_curr_direction(s) != 'Q') {
		PairPos tail_pair = snake_get_tail(s);
		snake_move(s);
		PairPos head_pair = snake_get_head(s);

    if(snake_check_body_colisions(s, head_pair) || 
        head_pair.x >= MAX_X || head_pair.y >= MAX_Y ||
        head_pair.x < 0 || head_pair.y < 0) {

      //thisThread will stay waking up the keyboard thread till the user press to exit
      while(snake_get_curr_direction(s) != 'q' && snake_get_curr_direction(s) != 'Q') pthread_cond_broadcast(&cond_var);
      break;
    }

		attron(COLOR_PAIR(SNAKE_COLOR));
		mvprintw(head_pair.x, head_pair.y, "*");
		attroff(COLOR_PAIR(SNAKE_COLOR));

		if(head_pair.x == foodPair.x && head_pair.y == foodPair.y) {
			snake_push_pair(s, tail_pair);
			foodPair = generate_food(MAX_X, MAX_Y);
      while(snake_check_body_colisions(s, foodPair)) //if the food is generated over some snake body position, regenerate it
			  foodPair = generate_food(MAX_X, MAX_Y);

      attron(COLOR_PAIR(POINTS_COLOR));
      mvprintw(MAX_X - 1, 0, "Points: %d", snake_get_len(s));
      attroff(COLOR_PAIR(POINTS_COLOR));
		} else {
			attron(COLOR_PAIR(BACKGROUND_COLOR));
			mvprintw(tail_pair.x, tail_pair.y, " ");
			attroff(COLOR_PAIR(BACKGROUND_COLOR));
		}
		refresh();
    pthread_cond_broadcast(&cond_var);

    //mvprintw(0, 0, "%c     ", snake_get_curr_direction(s));
    if(snake_get_curr_direction(s) != 'a' && snake_get_curr_direction(s) != 'd') usleep((int)1e5);
    else usleep((int) 7e4);
  }

  return (void *) NULL;
}

void *keyboardThread(void *arg) {
  Snake *s = (Snake *) arg;
  char c;
  while(snake_get_curr_direction(s) != 'q' && snake_get_curr_direction(s) != 'Q') {
    c = tolower(getch());
    if(
    (c == 'a' && snake_get_curr_direction(s) != 'd') ||
    (c == 'w' && snake_get_curr_direction(s) != 's') ||
    (c == 'd' && snake_get_curr_direction(s) != 'a') ||
    (c == 's' && snake_get_curr_direction(s) != 'w') ||
     c=='q') 
        snake_change_curr_direction(s, c);
        //even if the curr direction is shared between the two threads
        //only this one writes on the data
    pthread_mutex_lock(&mut);
    if(c != 'q') pthread_cond_wait(&cond_var, &mut);
    pthread_mutex_unlock(&mut);
    usleep((int)1e4);
  }

  return (void *) NULL;
}

int main() {
  initializeWindow();
  Snake *s = snake_create(MAX_X, MAX_Y);

  pthread_t draw, keyboard;
  pthread_create(&draw, NULL, &drawThread, (void *) s);
  pthread_create(&keyboard, NULL, &keyboardThread, (void *) s);

  pthread_join(draw, NULL);
  pthread_join(keyboard, NULL);

  snake_destroy(s);
  freeWindow();
  return 0;
}
