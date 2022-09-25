//Ejercicio guion b)3


#include<iostream>


using namespace std;


int main(){
	
	
	int n, unidades, decenas, centenas;
	
	
	cout << "Digite un numero entero de 3 cifras: ";
	cin >> n;

	
	unidades = n % 10;
	n /= 10;
	
	decenas = n % 10;
   n /= 10;
	
	centenas = n % 10;
	n /= 10;
	
	
	cout << "\nUnidades: " << unidades;
	cout << "\nDecenas: " << decenas;  
	cout << "\nCentenas: " << centenas;
	
	
}
