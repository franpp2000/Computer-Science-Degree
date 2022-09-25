#include <iostream>
#include <cassert>
#include <climits>
#include "pila_max_cola.h"

using namespace std;

ostream& operator <<(ostream &os, const Elemento &e){
  os << "<" << e.valor << " | " << e.max << ">" << "\n";
  return os;
}

PilaMax::PilaMax(const PilaMax &orig):
cola(orig.cola)
{}

PilaMax& PilaMax::operator= (const PilaMax &orig){
  if(&orig != this)
    cola = orig.cola;
  return *this;
}

bool PilaMax::empty() const{
  return cola.vacia();
}

Elemento& PilaMax:: top(){
  return cola.frente();
}

const Elemento& PilaMax:: top() const{
  return cola.frente();
}

void PilaMax:: push(const int &n){

  Elemento e;
  e.valor = n;
  e.max = (n > maximo())? n : maximo();

  PilaMax aux(*this);

  while(!empty())
    pop();

  cola.poner(e);

  while(!aux.empty()){
    cola.poner(aux.top());
    aux.pop();
  }
}

void PilaMax::pop(){
  cola.quitar();
}

int PilaMax::size() const{
  return cola.num_elementos();
}

int PilaMax::maximo() const{

  if(cola.vacia()) return INT_MIN;
    return top().max;
}
