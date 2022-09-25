#include "punto.h"

using namespace std;

Punto::Punto(const double latitud, const double longitud){
  setLatitud(latitud);
  setLongitud(longitud);
}

double Punto::GetLatitud() const{
  return latitud;
}

double Punto::GetLongitud() const{
  return longitud;
}

void Punto::setLatitud(const double latitud){
  assert(latitud >= -90 && latitud <= 90);
  this->latitud = latitud;
}

void Punto::setLongitud(const double longitud){
  assert(longitud >= -180 && longitud <= 180);
  this->longitud = longitud;
}

bool Punto::operator==(const Punto &p)const{
  return (latitud == p.latitud) && (longitud == p.longitud);
}

ostream & operator<<(ostream &os, const Punto &p){
  os << "(" << p.latitud << "," << p.longitud << ") ";

  return os;
}

istream & operator>>(istream &is, Punto &p){

  string cadena;
  double n;

  is.ignore(2);
  getline(is, cadena, ',');
  n = stod(cadena);
  p.setLatitud(n); 
  getline(is, cadena, ')');
  n = stod(cadena);
  p.setLongitud(n);

  return is;
}

