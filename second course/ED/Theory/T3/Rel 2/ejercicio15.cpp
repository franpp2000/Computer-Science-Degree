#include <iostream>
#include <list>
#include <vector>

using namespace std;

template <typename T> class vdisperso {
  private:
    list<pair<int, T>> coefs;
    int n;
    T valor_nulo;
  
  public:
    vdisperso(const T &valor)
    :n(0), coefs(), valor_nulo(valor)
    {};
    vdisperso(const vector<T> &, const T &);
    void asignar_coeficiente(int i, const T &);
    T operator[] (int) const;
    vector<T> convertir() const;
    int size() const{
      return n;
    };
    int size_not_nulls() const{
      return coefs.size();
    };
    void cambiar_nulo(const T &);
};

template<typename T> vdisperso<T>::vdisperso(const vector<T> &v, const T &valor){
  n = v.size();
  valor_nulo = valor;

  pair<int, T> aux;

  for(int i = 0; i < n; i++){
    if(v[i] != valor_nulo){
      aux.first = i;
      aux.second = v[i];
      coefs.push_back(aux);
    }
  }
}

template<typename T> void vdisperso<T>::asignar_coeficiente(int i, const T &x){
  typename list<pair<int, T>>::iterator it = coefs.begin();

  while(it != coefs.end() && it->first < i)
    it++;

  if(it == coefs.end()){
    pair<int, T> aux(i, x);
    coefs.push_back(aux);
    n++;
  }
  else{
    if(it->first == i)
      it->second = x;
    else{
      coefs.insert(it, pair<int, T>(i, x));
      n++;
    }
  }  
}

template<typename T> T vdisperso<T>::operator[](int pos)const{
  typename list<pair<int, T>>::const_iterator it = coefs.cbegin();
  T result;

  if(pos == 0)
    result = it->second;
  else{  
    for(int i = 1; i <= pos; i++)
      it++;

    result = it->second;  
  }

  return result;
}

template<typename T> vector<T> vdisperso<T>::convertir()const{
  vector<T> result;
  typename list<pair<int, T>>::const_iterator it = coefs.cbegin();

  for(int i = 0; i < n; i++){
    if(i == it->first){
      result.push_back(it->second);
      it++;
    }
    else{
      result.push_back(valor_nulo);
    }
  }

  return result;
}

template<typename T> void vdisperso<T>::cambiar_nulo(const T &valor){
  valor_nulo = valor;
}

int main(){
  vector<int> v(10, int());
  v[0] = 1;
  v[1] = 10;
  v[2] = 2;
  v[3] = 10;
  v[4] = 3;
  v[5] = 10;
  v[6] = 4;
  v[7] = 10;
  v[8] = 5;
  v[9] = 10;

  for(vector<int>::iterator it = v.begin(); it != v.end(); it++)
    cout << *it << " ";

  cout << endl;

  vdisperso<int> vd(v, 10);

  cout << vd.size_not_nulls() << endl; 

  cout << vd.size() << endl;   

  for(int i = 0; i < vd.size_not_nulls(); i++){
    cout << vd[i] << " ";
  }
  cout << endl;  

  vd.asignar_coeficiente(10, 32);

  for(int i = 0; i < vd.size_not_nulls(); i++){
    cout << vd[i] << " ";
  }
  cout << endl;

  vd.cambiar_nulo(66);

  vector<int> convertido = vd.convertir();

  for(vector<int>::iterator it = convertido.begin(); it != convertido.end(); it++)
    cout << *it << " ";

  cout << endl;  
}
