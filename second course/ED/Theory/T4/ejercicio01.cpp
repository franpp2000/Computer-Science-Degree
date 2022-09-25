#include <iostream>
#include <queue>
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

template<typename T> typename bintree<T>::node mas_profunda(const bintree<T> &arb){
  typename bintree<T>::node n = arb.root();
  queue<typename bintree<T>::node> cola;

  if(!n.null()){
    cola.push(n);

    while(!cola.empty()){
      n = cola.front();
      cola.pop();

      if (!n.left().null()) 
        cola.push(n.left());
      if (!n.right().null())
        cola.push(n.right());
    }
  }
  
  return n;
}

int main(){

  int prof = 0;
  typename bintree<int>::node hoja_max_prof;
  
  bintree<int> a(1);
  a.insert_left(a.root(), 2);
  a.insert_right(a.root(), 3);
  a.insert_left(a.root().left(), 4);
  a.insert_right(a.root().left(), 5);
  a.insert_left(a.root().left().right(), 6);

  hoja_max_prof = mas_profunda(a);

  cout << *hoja_max_prof << endl;
}