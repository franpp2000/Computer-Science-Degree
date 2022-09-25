#include<iostream>
#include "ruta.h"

using namespace std;

Punto & Ruta::operator[](int n){
  list<Punto>::iterator it = puntos.begin();

  for(int i = 1; i <= n; i++)
    it++;

  return *it;  
}

ostream & operator<<(ostream & os, const Ruta &r){

  for(list<Punto>::const_iterator it = r.cbegin(); it != r.cend(); it++){
    os << *it << " ";
  }

  return os;
}

istream & operator>>(istream &is, Ruta &r){
  int n;
  Punto aux;
  string codigo;

  is >> codigo;
  is >> n;

  r.SetCodigo(codigo);

  for(int i = 0; i < n; i++){
    is >> aux;
    r.push_back(aux);
  }

  return is;
}