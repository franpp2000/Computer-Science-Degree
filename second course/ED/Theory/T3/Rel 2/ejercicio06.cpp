#include <iostream>
#include <list>
#include <vector>

using namespace std;

template<typename T> void elimina(list<T> &l, const vector<T> &v){
  typename list<T>::iterator it = l.begin();

  for(int i = 0; i < v.size(); i++){
    while(it != l.end()){
      if(*it == v[i])
        it = l.erase(it);
      else
        ++it;  
    }
    it = l.begin();
  }
}

int main(){

  list<int> l;
  l.push_back(2);
  l.push_back(1);
  l.push_back(1);
  l.push_back(1);
  l.push_back(1);
  l.push_back(5);
  l.push_back(3);
  l.push_back(6);

  vector<int> v;
  v.push_back(1);
  v.push_back(6);

  for(list<int>::iterator it = l.begin(); it != l.end(); it++)
    cout << *it << " ";

  cout << endl;

  elimina(l, v);

  for(list<int>::iterator it = l.begin(); it != l.end(); it++)
    cout << *it << " ";

  cout << endl;

}
