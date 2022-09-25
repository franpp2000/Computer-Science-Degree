#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <ctype.h>

using namespace std;

vector<string> veces(const map<string,int> &palabras, int num){
  vector<string> v;

  for(map<string, int>::const_iterator it = palabras.begin(); it != palabras.end(); ++it)
    if(it->second == num)
      v.push_back(it->first);

  return v;
}

int main(){

  map<string , int> ocurrencias;
  ocurrencias["don"] = 2;
  ocurrencias["hola"] = 2;
  ocurrencias["jose"] = 1;
  ocurrencias["pepito"] = 1;

  vector<string> encontrados = veces(ocurrencias, 2);

  cout << endl << "Ocurrencias encontradas:" << endl;
  for(vector<string>::iterator it = encontrados.begin(); it != encontrados.end(); ++it)
    cout << *it << endl;
}