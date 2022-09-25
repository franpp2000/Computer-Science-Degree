#include <iostream>
#include <list>

using namespace std;

template<typename T> class vector_dinamico {
  private:
    list<T> lista;

  public:
    typedef typename list<T>::iterator iterator;

    iterator insert(iterator it, const T &x){
      return lista.insert(it, x);
    }

    iterator erase(iterator it){
      return lista.erase(it);
    }

    iterator erase(int n){
      typename list<T>::iterator it = lista.begin();
      for(int i = 1; i <= n; i++)
        it++;

      return lista.erase(it);  
    }

    void push_back(const T &x){
      lista.push_back(x);
    }

    T& operator[](int n){
      typename list<T>::iterator it = lista.begin();
      for(int i = 1; i <= n; i++)
        it++;

      return *it;  
    }

    int size() const{
      return lista.size();
    }

    iterator begin(){
      return lista.begin();
    }

    iterator end(){
      return lista.end();
    }
};

int main(){
  vector_dinamico<int> vd;

  vd.push_back(1);
  vd.push_back(2);
  vd.push_back(3);
  vd.push_back(4);
  vd.push_back(5);
  vd.push_back(6);
  vd.push_back(7);

  for(vector_dinamico<int>::iterator it = vd.begin(); it != vd.end(); it++)
    cout << *it << " ";

  cout << endl; 

  cout << vd[0] << endl; 

  cout << vd.size() << endl;
  
  vector_dinamico<int>::iterator it = vd.begin();
  it = vd.insert(it, 0);

  for(vector_dinamico<int>::iterator it = vd.begin(); it != vd.end(); it++)
    cout << *it << " ";

  cout << endl;

  it = vd.insert(it, 32); 

  for(vector_dinamico<int>::iterator it = vd.begin(); it != vd.end(); it++)
    cout << *it << " ";

  cout << endl;  

  it = vd.erase(it);  

  for(vector_dinamico<int>::iterator it = vd.begin(); it != vd.end(); it++)
    cout << *it << " ";

  cout << endl;

  it = vd.erase(5); 

  for(vector_dinamico<int>::iterator it = vd.begin(); it != vd.end(); it++)
    cout << *it << " ";

  cout << endl; 
}
