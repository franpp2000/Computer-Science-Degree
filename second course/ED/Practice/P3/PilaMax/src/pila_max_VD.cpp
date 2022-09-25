#include <iostream>
#include <climits>
#include <cassert>
#include "pila_max_VD.h"

using namespace std;

ostream& operator << (ostream &os, const Elemento &e){
  os << "<" << e.valor << " | " << e.max << ">" << "\n";
  return os;
}


PilaMax::PilaMax(const PilaMax &orig)
:cola(orig.cola)
{}


PilaMax& PilaMax::operator = (const PilaMax& orig){
  if(&orig != this)
    cola = orig.cola;
  return *this;
}

bool PilaMax::empty() const{
  return cola.empty();
}

Elemento& PilaMax:: top(){
  assert(!cola.empty());
  return cola[cola.size() - 1];
}

const Elemento& PilaMax:: top() const{
  assert(!cola.empty());
  return cola[cola.size() - 1];
}

void PilaMax:: push(const int &n){

  Elemento e;
  e.valor = n;
  e.max = (n > maximo())? n : maximo();

  cola.push_back(e);
}

void PilaMax::pop(){

  assert(!cola.empty());
  cola.pop_back();
}

int PilaMax::size() const{
  return cola.size();
}

int PilaMax::maximo() const{

  if(cola.empty()) 
    return INT_MIN;
    
  return top().max;
}
