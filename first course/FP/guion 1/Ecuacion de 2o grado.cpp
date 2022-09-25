//Ejercicio guio b)2


#include<iostream>
#include<cmath.>

using namespace std;


int main(){
	
	
	double a, b, c, x1, x2;
	
	
	cout << "Introduzca el coeficiente del monomio de grado 2: ";
	cin >> a;
	
    cout << "\nIntroduzca el coeficiente del monomio de grado 1 : ";
	cin >> b;
	
	cout << "\nIntroduzca el coeficiente del termino independiente: ";
	cin >> c;
	
	
	x1 = (-b + sqrt(b * b - 4 * a * c))/(2 * a);
	
	x2 = (-b - sqrt(b * b - 4 * a * c))/(2 * a);
	
	
	cout << "\n\nx1 = " << x1;
	cout << "\nx2 = " << x2;
	
	
	
	
	
}
