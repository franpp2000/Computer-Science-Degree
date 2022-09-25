#include <iostream>
#include "almacen_rutas.h"

using namespace std;

Almacen_Rutas Almacen_Rutas::GetRutas_Con_Punto(const Punto &p){
  Almacen_Rutas result;

  for(map<string, Ruta>::const_iterator i = rutas.cbegin(); i != rutas.cend(); ++i){
    for(Ruta::const_iterator j = i->second.cbegin(); j != i->second.cend(); j++){
      if(*j == p){
        result.insertar_ruta(i->second);
      }
    }
  }

  return result;
}

ostream & operator<<(ostream &os, const Almacen_Rutas &almacen){
  for(map<string, Ruta>::const_iterator it = almacen.rutas.cbegin(); it != almacen.rutas.cend(); ++it){
    os << it->first << " " << it->second << endl;
  }

  return os;
}

istream & operator>>(istream &is, Almacen_Rutas &almacen){
  string codigo, palabramagica;
  
  is >> palabramagica;

  is.ignore(1);

  while(!is.eof()){
    Ruta aux;

    is >> aux;
    almacen.insertar_ruta(aux);
  
    is.ignore(1);
  }

  return is;
}