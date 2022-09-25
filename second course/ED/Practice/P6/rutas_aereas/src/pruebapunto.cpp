#include<iostream>
#include "punto.h"

using namespace std;

int main(){
  Punto p;
  int n;
  cin >> n;

  for(int i = 0; i < n; i++){
    cin >> p;
    cout << p << " ";
  }

  cout << endl;

  Punto copia(p);

  if(copia == p)
    cout << "Son iguales" << endl;

  cout << copia << endl;
  copia.setLatitud(0.334);
  copia.setLongitud(123.43);
  cout << copia << endl;
  cout << copia.GetLatitud();
  cout << endl;
  cout << copia.GetLongitud() << endl;

  return 0;
}