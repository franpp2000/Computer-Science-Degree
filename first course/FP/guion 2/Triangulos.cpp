/*
                     Haga un programa que lea las coordenadas de tres puntos en un espacio cartesiano 2D y que nos diga si
                     forman o no un triángulo. Además, debe indicar si el triángulo es equilátero. Si llamamos a los puntos A,
                     B y C, sabemos que forman un triángulo cuando la mayor de las distancias AB, AC, BC es menor que la
                     suma de las otras dos. El triángulo es equilátero si las tres distancias son iguales.

*/

#include <iostream>
#include <cmath.>

using namespace std;

int main(){

   double AB , AC , BC , ax, bx, cx, ay, by, cy, MayorDistancia = 0 ,SumaDistMenores = 0;
   bool EsTriangulo, EsEquilatero;
   
   
   cout << "Digite la compontente x del punto A: ";
   cin >> ax;
   
   cout << "Digite la compontente x del punto B: ";
   cin >> bx;
   
   cout << "Digite la compontente x del punto C: ";
   cin >> cx;
   
   cout << "Digite la compontente y del punto A: ";
   cin >> ay;
   
   cout << "Digite la compontente y del punto B: ";
   cin >> by;
   
   cout << "Digite la compontente y del punto C: ";
   cin >> cy;
   

	
	AB = sqrt((bx - ax) * (bx - ax) + (by - ay) * (by - ay));
	AC = sqrt((cx - ax) * (cx - ax) + (cy - ay) * (cy - ay));
	BC = sqrt((cx - bx) * (cx - bx) + (cy - by) * (cy - by));
	MayorDistancia = AB;
	SumaDistMenores = AC + BC;
	EsTriangulo = (MayorDistancia < SumaDistMenores);
	EsEquilatero = (AB == AC && AB == BC && AC == BC);
	
	
	
	if(MayorDistancia < AC){
		
				MayorDistancia = AC;
				SumaDistMenores = AB + BC; 
	}
				
	if(MayorDistancia < BC){
		
				MayorDistancia = BC;
				SumaDistMenores = AB + AC; 
	}
	
   if(EsTriangulo)
				cout << "Forman un triangulo";
				
				else
					cout << "No forman un triangulo";
					
	
	if(EsTriangulo && EsEquilatero)
				cout << ", ademas este es equilatero.";				

			

}
