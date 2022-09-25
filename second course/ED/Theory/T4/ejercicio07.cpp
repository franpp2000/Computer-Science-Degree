#include <iostream>
#include "bintree.h"
#include <math.h>
#include <stack>

using namespace std;

template<typename T> bool es_hoja(const bintree<T> &a, const typename bintree<T>::node &n){
  return n.left().null() && n.right().null();
}

template<typename T> int get_profundidad(const bintree<T> &a, const typename bintree<T>::node &n){
  int prof = 0;

  typename bintree<T>::node aux = n;

  while(aux != a.root()){
    aux = aux.parent();
    ++prof;
  }
  
  return prof;
}

template<typename T> int altura(const bintree<T> &arb){
  int prof_actual = 0, altura_arbol = -1;
  typename bintree<T>::node n = arb.root();
  stack<typename bintree<T>::node> stk;

  if(!n.null()){
    stk.push(n);

    while(!stk.empty()){
      n = stk.top();
      stk.pop();

      if(es_hoja(arb, n)){
        prof_actual = get_profundidad(arb, n);

        if(prof_actual >= altura_arbol){
          altura_arbol = prof_actual;
        }
      }

      if(!n.right().null())
        stk.push(n.right());
      if(!n.left().null())
        stk.push(n.left());
    }
  }

  return altura_arbol + 1;
}


template<typename T> bool completo(const bintree<T> &arb){

  int altura_arbol = altura(arb);

  return (pow(2, altura_arbol) - 1) == arb.size();
}

int main(){
  int prof = 0;
  typename bintree<string>::node hoja_max_prof;
  
  bintree<string> a("Hola");
  a.insert_left(a.root(), "Juan");
  a.insert_right(a.root(), "Pepe");
  a.insert_left(a.root().left(), "Perico");
  a.insert_right(a.root().left(), "Jose");
  a.insert_left(a.root().right(), "Koke");
  a.insert_right(a.root().right(), "Fran");

  bool result = completo(a); 

  if(result)
    cout << endl << "Completo" << endl;
  else
    cout << endl << "No completo" << endl;
  
}