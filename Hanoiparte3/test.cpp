#include <ncurses.h>
#include <string>
#include <iostream>
using namespace std;
WINDOW *win;
int main() {
  initscr();
  start_color();
  win = newwin(100, 100, 0, 0);
  init_pair(1, COLOR_BLUE, COLOR_YELLOW);
  wattron(win, COLOR_PAIR(1));
  wprintw(win, "Deberia de tener color");
  wattroff(win, COLOR_PAIR(1));
  wrefresh(win);
  getchar();
  refresh();
  getchar();
  endwin();
  return 0;
}
