#include <iostream>
#include <map>
#include <string>

using namespace std;

string encripta(string cad, const map<char, char> &codigo){
  map<char, char>::const_iterator it;

  for(int i = 0; i < cad.size(); ++i){
    it = codigo.find(cad[i]);

    if(it != codigo.end())
      cad[i] = it->second;
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

  string cadena = "hola";

  cout << "Cadena sin encriptar: " << cadena << endl;

  cadena = encripta(cadena, codigo);

  cout << "\nCadena encriptada: " << cadena << endl;
}