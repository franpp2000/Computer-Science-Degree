#include <iostream>
#include <list>

using namespace std;

template<typename T> list<T> mezclar(const list<T> &l1, const list<T> &l2){

  list<T> aux1, aux2;

  if(l1.size() <= l2.size()){
    aux1 = l1;
    aux2 = l2;
  }
  else{
    aux1 = l2;
    aux2 = l1;
  }

  bool insertado;

  for(typename list<T>::iterator i = aux2.begin(); i != aux2.end(); i++){
    insertado = false;

    for(typename list<T>::iterator j = aux1.begin(); j != aux1.end() && !insertado; j++){
      if(*j >= *i){
        aux1.insert(j, *i);
        insertado = true;
      }
    }

    if(!insertado)
      aux1.push_back(*i);
  }

  return aux1;
}

int main(){
  list<int> l1, l2;

  l1.push_back(2);
  l1.push_back(4);
  l1.push_back(6);
  l1.push_back(8);

  l2.push_back(1);
  l2.push_back(3);
  l2.push_back(5);
  l2.push_back(7);

  list<int> mezcla; 
  mezcla = mezclar(l1, l2);

  for(list<int>::iterator it = mezcla.begin(); it != mezcla.end(); it++)
    cout << *it << " ";

  cout << endl;  
  
}