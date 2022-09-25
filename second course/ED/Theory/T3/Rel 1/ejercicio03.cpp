//Implementa un TDA cola usando como representación dos pilas.

#include <iostream>
#include <stack>

using namespace std;

template<typename T> class cola{
  
  private:
    stack<T> stk;
    stack<T> aux;
  
  public:
    cola(){};
    cola(const cola<T> &);
    cola& operator = (const cola<T> &);
    bool empty() const;
    T front() const;
    T back();
    void pop();
    void push(const T &);
};

template<typename T> cola<T>::cola(const cola<T> &orig)
:stk(orig.q)
{}

template<typename T> cola<T>& cola<T>::operator=(const cola<T> & orig){
  if(&orig != this)
    stk = orig.stk;

  return *this;  
}

template<typename T> bool cola<T>::empty() const{
  return stk.empty();
}

template<typename T> T cola<T>::front() const{
  return stk.top();
}

template<typename T> T cola<T>::back(){
  
  T x;

  while(!stk.empty()){
    aux.push(stk.top());
    stk.pop();
  }

  x = aux.top();

  while(!aux.empty()){
    stk.push(aux.top());
    aux.pop();
  }

  return x;
}

template<typename T> void cola<T>::pop(){
  stk.pop();
}

template<typename T> void cola<T>::push(const T &x){

  while(!stk.empty()){
    aux.push(stk.top());
    stk.pop();
  }

  aux.push(x);

  while(!aux.empty()){
    stk.push(aux.top());
    aux.pop();
  }
}

int main(){
  cola<int> c;
    
    c.push(3);
    c.push(0);

    int i;
    for ( i=10; i>=0 ; i--)
    c.push(i);

    cout << "<" << c.back() << ">" << endl << endl;

    int x;
    while (!c.empty())
    {
      x = c.front();
      cout << "<" << x << ">" << endl;
      c.pop();
    }

    return 0;
}
