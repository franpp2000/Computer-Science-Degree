

#include<iostream>
using namespace std;


int main(){

char c;
bool esDig, esMay, esMin, esSimArit;


cout << "Digite un caracter cualquiera: ";
cin >> c;


esDig = (c >= '0' && c <= '9');
esMay = (c >= 'A' && c <= 'Z');
esMin = (c >= 'a' && c <= 'z');
esSimArit = (c == '+' || c == '-' || c == '*' || c == '/');


if(esDig)
      cout << c << " es un digito";
      
      else
         if(esMay)
               cout << c << " es mayuscula";
               
               else
                  if(esMin)
                        cout << c << " es minuscula";
                        
                        else
                           if(esSimArit)
                                 cout << c << " es un simbolo aritmetico";









}
