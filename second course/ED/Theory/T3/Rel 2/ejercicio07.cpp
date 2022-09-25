#include <iostream>
#include <list>

using namespace std;

template<typename T> void elimina_duplicados(list<T> &l){
  typename list<T>::iterator j;

  for(typename list<T>::iterator i = l.begin(); i != l.end(); i++){
    j = i;
    ++j;

    while(j != l.end()){
      if(*j == *i)
        j = l.erase(j);
      else
        ++j;
    }
  }
}

int main(){
  list<int> l;
  l.push_back(1);
  l.push_back(1);
  l.push_back(1);
  l.push_back(2);
  l.push_back(3);
  l.push_back(3);
  l.push_back(1);
  l.push_back(4);
  l.push_back(2);
  l.push_back(4);

  for(list<int>::iterator it = l.begin(); it != l.end(); it++)
    cout << *it << " ";

  cout << endl;

  elimina_duplicados(l);

  for(list<int>::iterator it = l.begin(); it != l.end(); it++)
    cout << *it << " ";

  cout << endl;
}