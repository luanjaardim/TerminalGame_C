#include "lib.h"
#include <ncurses.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

pthread_mutex_t screen_mut = PTHREAD_MUTEX_INITIALIZER,
                snake_mut  = PTHREAD_MUTEX_INITIALIZER;

PairPos foodPair;

void initializeWindow() {
  initscr();          //initalizes the terminal screen, start curses mode
  raw();              //turn off line buffering, so we don't to press Enter on getch, by example
  noecho();           //what we type doesn't appears on the screen
  srand(time(NULL));
  start_color();

  //initialize color pairs -> (the identifier of the pair, foreground  color, and background color)
  init_pair(SNAKE_COLOR, COLOR_BLACK, COLOR_GREEN);
  init_pair(FOOD_COLOR, COLOR_BLACK, COLOR_RED);
  init_pair(POINTS_COLOR, COLOR_BLACK, COLOR_WHITE);
  init_pair(BACKGROUND_COLOR, COLOR_BLACK, COLOR_BLACK);

  //first food
  foodPair = generate_food();
}

void freeWindow() {
  endwin(); //destroy the window created with initscr
}

void *drawThread(void *arg) {
  Snake *s = (Snake *) arg;
  
  while(snake_get_curr_direction(s) != 'q' && snake_get_curr_direction(s) != 'Q') {
    PairPos head_pair = snake_get_head(s), tail_pair = snake_get_tail(s);

    attron(COLOR_PAIR(SNAKE_COLOR));
    mvprintw(head_pair.x, head_pair.y, "*");
    attroff(COLOR_PAIR(SNAKE_COLOR));
    //attron(COLOR_PAIR(BACKGROUND_COLOR));
    //mvprintw(tail_pair.x, tail_pair.y, " ");
    //attroff(COLOR_PAIR(BACKGROUND_COLOR));

    refresh();
    if(head_pair.x == foodPair.x && head_pair.y == foodPair.y) {

    }   
    pthread_mutex_lock(&snake_mut);
    snake_move(s);
    pthread_mutex_unlock(&snake_mut);
    usleep(100000);
  }

  return (void *) NULL;
}

void *keyboardThread(void *arg) {
  Snake *s = (Snake *) arg;
  char c;
  while(snake_get_curr_direction(s) != 'q' && snake_get_curr_direction(s) != 'Q') {
    c = getch();
    pthread_mutex_lock(&snake_mut);
    snake_change_curr_direction(s, c);
    pthread_mutex_unlock(&snake_mut);
  }

  return (void *) NULL;
}

int main() {
  initializeWindow();
  Snake *s = snake_create();

  pthread_t draw, keyboard;
  pthread_create(&draw, NULL, &drawThread, (void *) s);
  pthread_create(&keyboard, NULL, &keyboardThread, (void *) s);

  pthread_join(draw, NULL);
  pthread_join(keyboard, NULL);

  sleep(1);
  snake_destroy(s);
  freeWindow();
  return 0;
}
 // init_pair(1, COLOR_RED, COLOR_GREEN);
 // mvprintw(9, 10, "A Big string which i didn't care to type fully ");
 // mvchgat(9, 10, 100, A_BOLD, 1, NULL);
 // refresh();

 // int x, y;
 // getmaxyx(stdscr, x, y);
 // for(int i = 5; i < x-5; i++) {
 //   usleep(10000);
 //   mvchgat(10, i, 1, A_BOLD, SNAKE_COLOR, NULL);
 //   refresh();
 // }
 // refresh();
 // //printw("%d %d", x, y);
 // char ch;
 // scanf("%c", &ch);
 // mvprintw(10, 10, "%d", ch);
 // refresh();

 // sleep(2);
