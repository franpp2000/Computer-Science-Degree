//Implementa una función que inserte un elemento en una cola Q en la posición pos.

#include <iostream>
#include <queue>

using namespace std;

template <typename T> void insertar(queue<T> &P, int pos, const T &x){

  queue <T> aux;

  while(!P.empty()){
    aux.push(P.front());
    P.pop();
  }

  while(!aux.empty()){
    if(P.size() == pos)
      P.push(x);
    else{
      P.push(aux.front());
      aux.pop();
    }
  }

}

int main(){

  queue<int> q;
  int elemento = 32, pos_insertar = 0;

  for(int i = 0; i < 10; i++)
    q.push(i);

  insertar(q, pos_insertar, elemento);

  while(!q.empty()){
    cout << q.front() << ' ';
    q.pop();
  }  

  cout << endl;
}