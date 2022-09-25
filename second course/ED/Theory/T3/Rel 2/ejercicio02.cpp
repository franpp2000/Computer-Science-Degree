#include <iostream>
#include <map>
#include <string>

using namespace std;

string desencripta(string cad, const map<char, char> &codigo){
  bool encontrado;

  for(int i = 0; i < cad.size(); ++i){
    encontrado = false;
    
    for(map<char, char>::const_iterator it = codigo.begin(); it != codigo.end() && !encontrado; ++it){
      if(it->second == cad[i]){
        encontrado = true;
        cad[i] = it->first;
      }
    }
  }

  return cad;
}

int main(){
  map<char, char> codigo;
  codigo['a'] = 'b';
  codigo['b'] = 'a';
  codigo['c'] = 'w';
  codigo['d'] = 'x';
  codigo['e'] = 'p';
  codigo['f'] = 'o';
  codigo['g'] = 'm';
  codigo['h'] = 'e';
  codigo['i'] = 'q';
  codigo['j'] = 'r';
  codigo['k'] = 't';
  codigo['l'] = 'y';
  codigo['m'] = 'u';
  codigo['n'] = 'i';
  codigo['o'] = 's';
  codigo['p'] = 'd';
  codigo['q'] = 'f';
  codigo['r'] = 'g';
  codigo['s'] = 'h';
  codigo['t'] = 'j';
  codigo['u'] = 'k';
  codigo['v'] = 'l';
  codigo['w'] = 'z';
  codigo['x'] = 'c';
  codigo['y'] = 'v';
  codigo['z'] = 'b';

  string cadena = "esyb";

  cout << "Cadena encriptada: " << cadena << endl;
  
  cadena = desencripta(cadena, codigo);

  cout << "Cadena desencriptada: " << cadena << endl;
}