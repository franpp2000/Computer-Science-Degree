/*
                           Realizar un programa que lea un entero y determine si tiene al 2 y al 3 como factores primos. Nota: debe
                                                                  usar una variable booleana.
*/


#include <iostream>
using namespace std;


int main(){
   
   int numero;
   bool factor2, factor3;
   
   
   cout << "Digite un numero: ";
   cin >> numero;
   
   
   factor2 = (numero % 2 == 0);
   factor3 = (numero % 3 == 0);
   
   
   if(factor2)
          cout << "\nTiene como factor primo a 2";
         
   if(factor3)
          cout << "\nTiene como factor primo a 3";
                







}
