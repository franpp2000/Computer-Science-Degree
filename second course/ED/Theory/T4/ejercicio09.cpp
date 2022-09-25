#include <iostream>
#include "bintree.h"

using namespace std;

template<typename T> bool es_hoja(const bintree<T> &a, const typename bintree<T>::node &n){
  return n.left().null() && n.right().null();
}

template<typename T> bool similares(const bintree<T> &arb1, typename bintree<T>::node n1, const bintree<T> &arb2 , typename bintree<T>::node n2){
  static bool iguales = true;
  
  if(!n1.null() && !n2.null() && iguales){
    if(!n1.left().null() && !n2.left().null())
      similares(arb1, n1.left(), arb2, n2.left());
    else if(!es_hoja(arb1, n1));
      iguales = false;

    if(!n1.right().null() && !n2.right().null())
      similares(arb1, n1.left(), arb2, n2.left());
    else if(!es_hoja(arb2, n2));
      iguales = false;
  }

  return iguales;
}

template<typename T> bool similares(const bintree<T> &arb1, const bintree<T> &arb2){
  return similares(arb1, arb1.root(), arb2, arb2.root());
}

int main(){

  bintree<int> a(1);
  bintree<int> b(2);

  bool iguales = similares(a, b);

  if(iguales)
    cout << "similares" << endl;
  else 
    cout << "no similares" << endl; 
}