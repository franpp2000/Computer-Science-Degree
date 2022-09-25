/*
                                       Realizar un programa que determine si un punto (p, q) pertenece a una recta y=ax+b.

*/



#include<iostream>
using namespace std;


int main(){

double a, b, x, y;
bool Pertenece_a_recta;


cout << "\tPROGRAMA QUE CALCULA SI UN PUNTO DADO PERTENECE A U RECTA DE LA FORMA:" << endl << "\t y=ax+b";

cout << "\n\nDigite el valor de a: ";
cin >> a;

cout << "\nDigite el balor de b: ";
cin >> b;

cout << "\n\nLa recta es la siguiente: " << "y" << "=" << a << "x" << "+" << b;

cout << "\n\nDigite la componente x de el punto a estudiar: ";
cin >> x;

cout << "\n\nDigite la componente y de el punto a estudiar: ";
cin >> y;


Pertenece_a_recta = (y == a * x + b);


if(Pertenece_a_recta)
            
      cout << "\n\nEl punto pertenece a la recta.";
            
else
      
      cout << "\n\nNo pertenece a la recta.";
         












}
