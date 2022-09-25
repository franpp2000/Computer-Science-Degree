//Implementa una función que inserte un elemento en una pila P en la posición

#include<iostream>
#include<stack>

using namespace std;

template< typename T > void insertar(stack<T> &P, int pos, const T &x){
  
  stack<T> aux;
  
  while(aux.size() < pos){
    aux.push(P.top());
    P.pop();
  }

  P.push(x);

  while(!aux.empty()){
    P.push(aux.top());
    aux.pop();
  }
}

int main(){

  stack<int> stk;
  int elemento = 32, pos_insertar = 2;

  for(int i = 0; i < 10; i++)
    stk.push(i);

  insertar(stk, pos_insertar, elemento);

  while(!stk.empty()){
    cout << stk.top() << endl;
    stk.pop();
  }

}