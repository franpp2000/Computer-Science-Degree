#include <iostream>
#include <list>

using namespace std;

template<typename T> list<T> lista_posiciones(const list<T> &l, const list< typename list<T>::iterator> &li){
  list<T> result;

  for(typename list<typename list<T>::iterator>::const_iterator it = li.cbegin(); it != li.cend(); it++)
    result.push_back(**it);

  return result;  
}

int main(){
  list<int> l1;
  l1.push_back(1);
  l1.push_back(2);
  l1.push_back(3);
  l1.push_back(4);
  l1.push_back(5);

  list< typename list<int>::iterator> l2;
  list<int>::iterator it = l1.begin();

  l2.push_back(it);
  it++;
  l2.push_back(it);
  it++;
  it++;
  l2.push_back(it);

  list<int> result;
  result = lista_posiciones(l1, l2);

  for(list<int>::iterator it = result.begin(); it != result.end(); it++)
    cout << *it << " ";

  cout << endl;  


}