#include <iostream>
#include <list>

using namespace std;

template<typename T>list<pair<T, int> > comprimir(const list<T> &l){
  list<pair<T, int>> comprimida;

  typename list<T>::const_iterator it = l.cbegin();
  
  int n = *it;
  pair<T, int> aux(n, 0);
  aux.second++;
  it++;
  int i = 1;

  while(i < l.size()){
    if(*it == n){
      aux.second++;
      it++;
    }
    else{
      comprimida.push_back(aux);
      n = *it;
      aux.first = n;
      aux.second = 0;
      aux.second++;
      it++;
    }
    if(i == l.size() - 1)
      comprimida.push_back(aux);

    i++;  
  }

  return comprimida;
}

template<typename T>list<T> descomprimir(const list<pair<T, int>> &lc){
  list<T> descomprimida;
  int n = 0, numero;

  for(typename list<pair<T, int>>::const_iterator it = lc.cbegin(); it != lc.end(); it++){
    n = it->second;
    numero = it->first;

    for(int i = 0; i < n; i++){
      descomprimida.push_back(numero);
    }
  }

  return descomprimida;
}

int main(){

  list<int> l;
  l.push_back(1);
  l.push_back(1);
  l.push_back(1);
  l.push_back(2);
  l.push_back(2);
  l.push_back(3);
  l.push_back(3);
  l.push_back(4);

  list<pair<int, int>> comprimida;
  comprimida = comprimir(l);

  for(list<int>::iterator it = l.begin(); it != l.end(); it++)
    cout << *it << " ";

  cout << endl << endl;

  for(list<pair<int, int>>::iterator it = comprimida.begin(); it != comprimida.end(); it++)
    cout << it->first << " -----> " << it->second << endl;

  cout << endl;  

  list<int> descomprimida;
  descomprimida = descomprimir(comprimida);

  for(list<int>::iterator it = descomprimida.begin(); it != descomprimida.end(); it++)
    cout << *it << " ";

  cout << endl;

}