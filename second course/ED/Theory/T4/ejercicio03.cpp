#include <iostream>
#include "bintree.h"

using namespace std;

template<typename T> int get_profundidad(const typename bintree<T>::node &n){
  int prof = 0;

  typename bintree<T>::node aux = n;

  while(!aux.parent().null()){
    aux = aux.parent();
    ++prof;
  }
  
  return prof;
}

template<typename T> typename bintree<T>::node ancestro_comun(typename bintree<T>::node n1, typename bintree<T>::node n2){

  typename bintree<T>::node ancestro;

  bool fin = false;

  if(n1.parent() == n2.parent()){
    ancestro = n1.parent();
  }
  else{
    while(!fin){
      if(get_profundidad<T>(n1) > get_profundidad<T>(n2))
        n1 = n1.parent();
      else if(get_profundidad<T>(n1) < get_profundidad<T>(n2))
        n2 = n2.parent();
      else{
        if(n1.parent() == n2.parent()){
          fin = true;
          ancestro = n1.parent();
        }
        else{
          n1 = n1.parent();
          n2 = n2.parent();
        }
      }    
    }
  }

  return ancestro;
}

int main(){
  
  bintree<int> a(1);
  a.insert_left(a.root(), 2);
  a.insert_right(a.root(), 3);
  a.insert_left(a.root().left(), 4);
  a.insert_right(a.root().left(), 5);
  a.insert_left(a.root().left().right(), 6);

  typename bintree<int>::node n1 = a.root().left().right().left();
  typename bintree<int>::node n2 = a.root().left().left();
  typename bintree<int>::node ancestro;

  ancestro = ancestro_comun<int>(n1, n2);

  cout << *ancestro << endl;
}