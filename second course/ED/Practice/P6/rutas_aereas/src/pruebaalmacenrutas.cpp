#include <iostream>
#include "almacen_rutas.h"

using namespace std;

int main(){
  Almacen_Rutas almacen;

  cin >> almacen;

  cout << almacen << endl;

  Ruta r = almacen.GetRuta("R1");

  cout << "La ruta R1 es:" << endl << r << endl;

  Almacen_Rutas almacen2(almacen);


  cout << endl << "Ruta copia con una nueva ruta: R6" << endl;

  Ruta r6("R6");
  Punto pto1(40.40051528912146, -3.5916460749999635);

  r6.insert(r6.begin(), pto1);

  almacen2.insertar_ruta(r6);

  cout << almacen2;

  cout << endl << "Elimino r6:" << endl;

  almacen2.erase("R6");

  cout << almacen2;

  cout << endl;
  cout << "---Prueba sobre un punto dado:---" << endl;
  Almacen_Rutas Ar_lim;
  Punto pto(40.40051528912146, -3.5916460749999635);
  cout << "El punto " << pto << "esta incluido en las rutas:" << endl;
  Ar_lim = almacen2.GetRutas_Con_Punto(pto);
  cout << Ar_lim;
}