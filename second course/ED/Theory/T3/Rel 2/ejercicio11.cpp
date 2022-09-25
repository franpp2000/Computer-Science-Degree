#include <iostream>
#include <list>

using namespace std;

void inserta_despues(list<int> &l, int x){

  for(list<int>::iterator it = l.begin();it != l.end(); it++){
    if(*it == x){
      it++;
      l.insert(it, x - 1);
      it--;
    }
  }
}

int main(){
  list<int> l;
  l.push_back(1);
  l.push_back(2);
  l.push_back(3);
  l.push_back(4);
  l.push_back(5);
  l.push_back(6);
  l.push_back(7);

  for(list<int>::iterator it = l.begin(); it != l.end(); it++)
    cout << *it << " ";

  cout << endl;

  inserta_despues(l, 4);

  for(list<int>::iterator it = l.begin(); it != l.end(); it++)
    cout << *it << " ";

  cout << endl;

}