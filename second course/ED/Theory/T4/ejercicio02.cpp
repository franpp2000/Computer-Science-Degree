#include <iostream>
#include <stack>
#include "bintree.h"

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

  return altura_arbol;
}

int main(){

  int alt = 0;
  
  bintree<int> a(1);
  a.insert_left(a.root(), 2);
  a.insert_right(a.root(), 3);
  a.insert_left(a.root().left(), 4);
  a.insert_right(a.root().left(), 5);
  a.insert_left(a.root().left().right(), 6);

  alt = altura(a);

  cout << alt << endl;
}