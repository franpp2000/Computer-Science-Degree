#include<iostream>
#include "ruta.h"

using namespace std;

int main(){

  Ruta r;

  cin >> r;

  cout << r;

  cout << endl;
  
  Punto p(34.89, 17.64);

  Ruta::iterator it = r.begin();
  it++;

  it = r.insert(it, p);

  cout << r;

  cout << endl;

  it = r.erase(it);

  cout << r;

  cout << endl;

  r[0].setLatitud(10.4);

  cout << r;

  cout << endl;
}
