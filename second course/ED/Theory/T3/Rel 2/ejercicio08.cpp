#include <iostream>
#include <list>

using namespace std;

template<typename T> list<T> inversa(const list<T> &l){
  list<T> invertida;

  for(typename list<T>::const_iterator it = l.begin(); it != l.end(); it++)
    invertida.push_front(*it);

  return invertida;  
}

int main(){
  list<int> l;
  l.push_back(0);
  l.push_back(1);
  l.push_back(2);
  l.push_back(3);
  l.push_back(4);
  l.push_back(5);
  l.push_back(6);
  l.push_back(7);
  l.push_back(8);
  l.push_back(9);

  for(list<int>::iterator it = l.begin(); it != l.end(); ++it)
    cout << *it << " ";

  cout << endl; 

  l = inversa(l);

  for(list<int>::iterator it = l.begin(); it != l.end(); ++it)
    cout << *it << " ";

  cout << endl; 

}