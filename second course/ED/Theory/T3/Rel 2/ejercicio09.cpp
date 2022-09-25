#include <iostream>
#include <list>

using namespace std;

template<typename T> void inversa(list<T> &l){

  int tam = l.size();
  typename list<T>::iterator it2 = l.begin();

  for(typename list<T>::iterator it = l.begin(); it != l.end(); it++)
    l.push_front(*it);

  for(int i = 0; i < tam ; i++)
    it2 = l.erase(it2);

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

  inversa(l);

  for(list<int>::iterator it = l.begin(); it != l.end(); ++it)
    cout << *it << " ";

  cout << endl; 
}