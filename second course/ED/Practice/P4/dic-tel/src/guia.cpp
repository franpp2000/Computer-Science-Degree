#include "guia.h"
#include <iostream>

using namespace std;

char obtiene_Inicial(const string &nombre){
  return toupper(nombre[0]);
}

char obtiene_Primer_Digito(const string &numero){
  return numero[0];
}

istream & operator>>(istream &is, pair<string, string> &d){
  getline(is, d.first, '\t');
  getline(is, d.second);

  return is;
}

string Guia_Tlf::gettelefono(const string &nombre){
  map<string, string>::iterator it = datos.find(nombre);
  if(it == datos.end())
    return string("");
  else
    return it->second;
}

pair<map<string, string>::iterator, bool> Guia_Tlf::insert(string nombre, string tlf){
  pair<string, string> p(nombre, tlf);
  pair<map<string, string>::iterator, bool> ret;

  ret = datos.insert(p);

  return ret;
}  

pair<map<string, string>::iterator, bool> Guia_Tlf::insert(pair<string, string> p){
  pair<map<string, string>::iterator, bool> ret;

  ret = datos.insert(p);

  return ret;
}

void Guia_Tlf::borrar(const string &nombre){
  map<string, string>::iterator itlow = datos.lower_bound(nombre);
  map<string, string>::iterator itupper = datos.upper_bound(nombre);

  datos.erase(itlow, itupper);
}

void Guia_Tlf::borrar(const string &nombre, const string &tlf){
  map<string, string>::iterator itlow = datos.lower_bound(nombre);
  map<string, string>::iterator itupper = datos.upper_bound(nombre);
  map<string, string>::iterator it;
  bool salir = false;
  for(it = itlow; it != itupper && !salir; ++it){
    if(it->second == tlf){
      datos.erase(it);
      salir = true;
    }
  }
}

Guia_Tlf Guia_Tlf::operator+(const Guia_Tlf &g){
  Guia_Tlf aux(*this);
  
  map<string, string>::const_iterator it;
  for(it = g.datos.begin(); it != g.datos.end(); ++it)
    aux.insert(it->first, it->second);

  return aux;   
}

Guia_Tlf Guia_Tlf::operator-(const Guia_Tlf &g){
  Guia_Tlf aux(*this);

  map<string, string>::const_iterator it;
  for(it = g.datos.begin(); it != g.datos.end(); ++it)
    aux.borrar(it->first, it->second);

  return aux;  
}

istream & operator>>(istream &is, Guia_Tlf &g){
  pair<string, string> p;
  Guia_Tlf aux;

  while(is >> p)
    aux.insert(p);

  g = aux;

  return is;  
}

ostream & operator<<(ostream &os, Guia_Tlf &g){
  map<string, string>::iterator it;
  for(it = g.datos.begin(); it != g.datos.end(); ++it)
    os <<  it->first << "\t" << it->second << endl;

  return os;  
}  

Guia_Tlf Guia_Tlf::buscar_Por_Inicial(char letra){
  Guia_Tlf result;
  char mayus = toupper(letra), c;

  map<string, string>::iterator it;
  for(it = datos.begin(); it != datos.end(); ++it){
    c = obtiene_Inicial(it->first);

    if(c == mayus)
      result.insert(*it);
  }

  return result;
}

bool Guia_Tlf::cambia_Numero_Telefono(string nombre, string nuevo_numero){
  map<string, string>::iterator it = datos.find(nombre);
  
  if(it == datos.end())
    return false;
  else{
    it->second = nuevo_numero;
    return true;
  }

}

pair<string, string> Guia_Tlf::buscar_Por_Numero(string numero){
  pair<string, string> result;

  map<string, string>::iterator it;
  for(it = datos.begin(); it != datos.end(); ++it){
    if(it->second == numero){
      result.first = it->first;
      result.second = it ->second;
    }
  }

  return result;
}

