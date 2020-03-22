#include <iostream>
#include <vector>

using namespace std;

vector<int> vect;

string disk(int x) {
  string disk = "";
  x = (x + 1) * 2;
  for (size_t i = 0; i < x; i++) {
    disk += "*";
  }
  return disk;
}

void imprimir() {
  int impresas = 0; //my - (7 + impresas)
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < vect.size(); j++) {
      if (vect[j] == (i + 1)) {
        cout << disk(j).c_str();
        //printw(win, my - (7 + impresas), vAnt - (j + 1), disk(j).c_str());
      }
      cout << endl;
    }
  }
}

int main() {
    char c;
    cout << "Ingrese n: ";
    cin >> c;
    int x  = (int)c - 48;
    vect.resize(x);
    fill(vect.begin(), vect.end(), 1);
    cout << vect.size();
    imprimir();
    return 0;
}