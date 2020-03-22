#include <ncurses.h>
#include <string>
#include <vector>
using namespace std;
vector<int> vect;
WINDOW *win;
int mx, my, nMovi;
int lBase;

void iniWin() {
  noecho();
  start_color();
  string mArriba = " T O R R E S  D E  H A N O I ";
  string mAbajo = " P R O G R A M A C I O N  I I I ";
  win = newwin(my, mx, 0, 0);
  box(win, ACS_VLINE, ACS_HLINE);
  mvwprintw(win, 0, (mx - mArriba.size()) / 2, mArriba.c_str());
  mvwprintw(win, my - 1, (mx - mAbajo.size()) / 2, mAbajo.c_str());
  touchwin(win);
  string movi = "MOVIMIENTO # ";
  string muestra = "MUESTRA DE MOVIMIENTOS NECESARIOS PASO A PASO";
  wattron(win, A_REVERSE);
  mvwprintw(win, 1, (mx - muestra.size() + 2) / 2, muestra.c_str());
  wattroff(win, A_REVERSE);
  mvwprintw(win, 2, (mx - movi.size() + 2) / 2, movi.c_str());
  wrefresh(win);
}

void agujas() {
  int distancia = (lBase  - 3) / 4;
  int h = my - 14;
  int vAnt = distancia  ; //porque comienza en cuatro;
  start_color();
  init_pair(1, COLOR_WHITE, COLOR_WHITE);
  init_pair(3 , COLOR_BLACK, COLOR_WHITE);
  if (lBase < 0) {
    return;
  }
  for (int i = 0; i < 3; i++) {
    for (size_t j = 0; j <= h; j++) {
      wattron(win, COLOR_PAIR(1));
      mvwprintw(win, my - 6 - j, 4 + vAnt, " ");
      wattroff(win, COLOR_PAIR(1));
      if (j == 0) {
        wattron(win,COLOR_PAIR(3));
        mvwprintw(win, my - 6, 4 + vAnt, to_string(i + 1).c_str());
        wattroff(win,COLOR_PAIR(3));
      }
    }
    vAnt += 1 + distancia;
  }
  wrefresh(win);
}

//1 -> funcion busque cuales estan en la fila ej(vect[j] == i) 
//2 -> recorrer inverso de esas coincidencias, asi se imprimen los de mayor tamaño
//3 -> color dependiendo de j

string disk(int x) {
  string disk = "";
  x = (x + 1) * 2 + 1;
  for (size_t i = 0; i < x; i++) {
    disk += "*";
  }
  return disk;
}

void imprimir() {
  int distancia = (lBase  - 3) / 4 + 4;
  int vAnt = distancia;
  int impresas = 0; //my - (7 + impresas)
  init_pair(4, COLOR_RED, COLOR_RED);
  for (int i = 0; i < 3; i++) {
    for (int j = vect.size() - 1; j >= 0; j--) {
      if (vect[j] == (i + 1)) {
        wattron(win, COLOR_PAIR(4));
        mvwprintw(win, my - (7 + impresas++), vAnt - (j + 1), disk(j).c_str());
        wattroff(win, COLOR_PAIR(4));
      }
    }
    vAnt += 1 + distancia;
    impresas = 0;
  }
  getch();
}

void hanoi(int n, int A, int B, int C) {
    if (n == 1) {
        vect[0] = C;
        //imprimir();
    }
    else {
        hanoi (n - 1, A, C, B);
        vect[n - 1] = C;
        //imprimir();
        hanoi (n - 1, B, A, C);
    }
}

void base () {
    //"\u25AE"
    //my - 6
    lBase = mx - 8;
    init_pair(1, COLOR_WHITE, COLOR_WHITE);
    for (size_t i = 0; i < lBase; i++) {
      wattron(win, COLOR_PAIR(1));
      mvwprintw(win, my - 6, 4 + i, " ");
      wattroff(win, COLOR_PAIR(1));
    }
    agujas();
    wrefresh(win);
}

int main () {
  char c;
  int num;  
  start_color();
  initscr();
  int distancia = (lBase  - 3) / 4;
  int vAnt = distancia;
  printw("Ingrese la cantidad de discos: ");
  c = getch();
  num = (int)c - 48;
  while (num < 0 || num > 9) {
    mvprintw(0, 0, "Ingreso invalido favor vuelva a ingresar: ");
    c = getch();   
    num = (int)c - 48;
  }
  getmaxyx(stdscr, my, mx);
  iniWin();
  base();
  vect.resize(num);
  fill(vect.begin(), vect.end(), 1);
  init_pair(2, COLOR_RED, COLOR_RED);
  /*wattron(win, COLOR_PAIR(2));
  mvwprintw(win, my - (7), 4 + vAnt, disk(1).c_str());
  wattroff(win, COLOR_PAIR(2));
  wrefresh(win);*/
  //hanoi(num,1, 2, 3);
  imprimir();
  wrefresh(win);
  getchar();
  refresh();
  getch();
  endwin();
  return 0;
}
