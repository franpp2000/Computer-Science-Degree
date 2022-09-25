#include <iostream>
#include "bintree.h"

using namespace std;

template<typename T> void reflexion(bintree<T> &arb){
  bintree<T> izda, dcha;

  if(!arb.empty()){
    arb.prune_left(arb.root(), izda);
    arb.prune_right(arb.root(), dcha);

    reflexion(izda);
    reflexion(dcha);

    arb.insert_right(arb.root(), izda);
    arb.insert_left(arb.root(), dcha);
  }
}

template<typename T> void inorden_binario(const bintree<T> & A,typename bintree<T>::node v){
  if (!v.null()) {
    inorden_binario(A, v.left());
    cout << *v << " "; //acción sobre el nodo v.
    inorden_binario(A, v.right());
  }
}

int main(){
  bintree<int> t(5);

  t.insert_left(t.root(), 7);
  t.insert_right(t.root(), 9);

  t.insert_left(t.root().left(), 6);
  t.insert_right(t.root().left(), 8);

  t.insert_left(t.root().right(), 10);
  t.insert_right(t.root().right(), 12);

  cout << endl;
  inorden_binario(t, t.root());

  reflexion(t);

  cout << endl;
  inorden_binario(t, t.root());

  cout << endl;

}