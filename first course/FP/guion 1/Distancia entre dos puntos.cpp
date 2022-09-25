//Ejercicio guion b)4


#include<iostream>
#include<cmath.>


using namespace std;


int main(){
	
	
	double ax, ay, bx, by, distancia;
	
	
	cout << "Introduzca la componente x del punto a: ";
	cin >> ax;
	
	cout << "Introduzca la componente y del punto a: ";
	cin >> ay;
	
	cout << "Introduzca la componente x del punto b: ";
	cin >> bx;
	
	cout << "Introduzca la componente y del punto b: ";
	cin >> by;
	
	
	distancia = sqrt((bx-ax) * (bx-ax) + (by-ay) * (by-ay));
	
	cout << "\nDistancia: " << distancia;
	
}
