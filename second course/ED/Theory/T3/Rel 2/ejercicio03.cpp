#include <iostream>
#include <map>
#include <string>
#include <ctype.h>

using namespace std;

map<string, int> contar(string texto){
  map<string, int> ocurrencias;
  string palabra;
  map<string, int>::iterator it;

  for(int i = 0; i < texto.size(); i++){

    if(texto[i] >= 'a' && texto[i] <= 'z' || texto[i] >= 'A' && texto[i] <= 'Z')
      palabra.push_back(texto[i]);
    else{
      if(palabra.size() > 0){
        it = ocurrencias.find(palabra);

        if(it == ocurrencias.end())
          ocurrencias[palabra] = 1;
        else
          it->second++;

        palabra = "";
      }  
    }
  }

  return ocurrencias;
}
int main(){
  string texto = ",Hola Don Pepito!, hola Don Jose?";

  map<string, int> ocurrencias = contar(texto);

  for(map<string, int>::iterator it = ocurrencias.begin(); it != ocurrencias.end(); ++it)
    cout << it->first << " ---> " << it->second << endl;

}