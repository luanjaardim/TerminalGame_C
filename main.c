#include "lib.h"
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

pthread_mutex_t screen_mut = PTHREAD_MUTEX_INITIALIZER;

void initializeWindow() {
  initscr();          //initalizes the terminal screen, start curses mode
  raw();              //turn off line buffering, so we don't to press Enter on getch, by example
  noecho();           //what we type doesn't appears on the screen
  srand(time(NULL));
  start_color();

  //initialize color pairs -> (the identifier of the pair, foreground  color, and background color)
  init_pair(SNAKE_COLOR, COLOR_BLACK, COLOR_RED);
  init_pair(FOOD_COLOR, COLOR_BLACK, COLOR_RED);
  init_pair(POINTS_COLOR, COLOR_BLACK, COLOR_RED);
}

void freeWindow() {
  endwin(); //destroy the window created with initscr
}

void *drawThread(void *arg) {
  //for(int i = 5; i < 30; i++) {
  //  pthread_mutex_lock(&screen_mut);
  //    mvprintw(i, 0, "c");
  //    refresh();
  //  pthread_mutex_unlock(&screen_mut);
  //usleep(10000);
  //}

  return (void *) NULL;
}

void *keyboardThread(void *arg) {
  //for(int i = 5; i < 30; i++) {
  //  pthread_mutex_lock(&screen_mut);
  //    mvprintw(i, 1, "u");
  //    refresh();
  //  pthread_mutex_unlock(&screen_mut);
  //usleep(10000);
  //}

  return (void *) NULL;
}

int main() {
  initializeWindow();
  Snake *s = snake_create();

  pthread_t draw, keyboard;
  pthread_create(&draw, NULL, &drawThread, NULL);
  pthread_create(&keyboard, NULL, &keyboardThread, NULL);

  pthread_join(draw, NULL);
  pthread_join(keyboard, NULL);

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
