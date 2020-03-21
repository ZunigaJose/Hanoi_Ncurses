#include <ncurses.h>
#include <string>
using namespace std;

WINDOW *win;
int mx, my;

void iniwin() {
  cbreak();
  noecho();
  nonl();
  start_color();
  string mArriba = " T O R R E S  D E  H A N O I ";
  string mAbajo = " P R O G R A M A C I O N  I I I ";
  intrflush(win, FALSE);
  keypad(win, TRUE);
  win = newwin(my, mx, 0, 0);
  box(win, ACS_VLINE, ACS_HLINE);
  mvwprintw(win, 0, (mx - mArriba.size()) / 2, mArriba.c_str());
  mvwprintw(win, my - 1, (mx - mAbajo.size()) / 2, mAbajo.c_str());
  touchwin(win);
  init_pair(1, COLOR_BLUE, COLOR_YELLOW);
  wattron(win, COLOR_PAIR(1));
  string movi = "MOVIMIENTO # ";
  wattroff(win, COLOR_PAIR(1));
  mvwprintw(win, 1, (mx - movi.size() + 2) / 2, movi.c_str());
  wrefresh(win);
}

void agujas(int lbase) {
  int distancia = (lbase  - 3) / 4;
  int h = my - 14;
  int vAnt = distancia  ; //porque comienza en cuatro;
  init_pair(1, COLOR_WHITE, COLOR_WHITE);
  init_pair(3 , COLOR_BLACK, COLOR_BLUE);
  for (int i = 0; i < 3; i++) {
    for (size_t j = 0; j <= h; j++) {
      if (j == 0) {
        wattron(win, COLOR_PAIR(3));
        mvwprintw(win, my - 6, 4 + vAnt, to_string(i + 1).c_str());
        wattroff(win, COLOR_PAIR(3));
      }
      wattron(win, COLOR_PAIR(1));
      mvwprintw(win, my - 6 - j, 4 + vAnt, " ");
      wattroff(win, COLOR_PAIR(1));
    }
    vAnt += 1 + distancia;
  }
}

void base () {
    //"\u25AE"
    int lBase = (mx - 8);
    //my - 6
    init_pair(1, COLOR_WHITE, COLOR_WHITE);
    for (size_t i = 0; i < lBase; i++) {
      wattron(win, COLOR_PAIR(1));
      mvwprintw(win, my - 6, 4 + i, " ");
      wattroff(win, COLOR_PAIR(1));
    }
    agujas(lBase);
    wrefresh(win);
}

int main () {
  initscr();
  getmaxyx(stdscr, my, mx);
  iniwin(); 
  start_color();
  base();
  getchar();
  endwin();
  return 0;
}
