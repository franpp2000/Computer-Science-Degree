#include <iostream>
#include <vector>

using namespace std;

template<typename T> void intercalar(vector<T> &v, vector<pair<int, T>> pos){

  T x;
  int posicion;
  typename vector<T>::iterator it;

  for(int i = 0; i < pos.size(); i++){
    posicion = pos[i].first;
    x = pos[i].second;
  
    if(posicion == v.size())
      v.push_back(x);
    else{
      it = v.begin();

      for(int i = 1; i <= posicion; i++)
        it++;

      v.insert(it, x);      
    }    
  }
}

int main(){
  vector<int> v;
  v.push_back(1);
  v.push_back(3);
  v.push_back(7);
  v.push_back(3);
  
  vector<pair<int, int>> pos;
  pos.push_back(pair<int, int>(1, 5));
  pos.push_back(pair<int, int>(0, 7));
  pos.push_back(pair<int, int>(4, 12));

  for(int i = 0; i < v.size(); i++)
    cout << v[i] << " ";

  cout << endl;

  intercalar(v, pos);

  for(int i = 0; i < v.size(); i++)
    cout << v[i] << " ";

  cout << endl;

}