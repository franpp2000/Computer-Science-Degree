//Implementa el TDA pila usando dos colas.

#include <iostream>
#include <queue>

using namespace std;

template<typename T> class pila{

  private:
    queue<T> q;
    queue<T> aux;

  public:
    pila(){};
    pila(const pila<T> &);
    pila& operator = (const pila<T> &);
    bool empty() const; 
    T top() const;
    void pop();
    void push(const T &); 
};

template<typename T> pila<T>::pila(const pila<T> &orig)
:q(orig.q)
{}

template<typename T> pila<T>& pila<T>::operator = (const pila<T> &orig){
  if(&orig != this) //Evitar autorreferencia
    q = orig.q;

  return *this;
}

template<typename T> bool pila<T>::empty() const{
  return q.empty();
}

template<typename T> T pila<T>::top() const{
  return q.front();
}

template<typename T> void pila<T>::pop(){
  q.pop();
}

template<typename T> void pila<T>::push(const T &x){
  aux = q;

  while(!q.empty())
    q.pop();

  q.push(x);  

  while(!aux.empty()){
    q.push(aux.front());
    aux.pop();
  }  
}

int main(){
  pila<int> p;

    p.push(3);
    p.push(0);

    int i;
    for ( i=10; i>=0 ; i--)
    p.push(i);

    int x;
    while (!p.empty())
    {
      x = p.top();
      cout << "<" << x << ">" << endl;
      p.pop();
    }

    return 0;

}

