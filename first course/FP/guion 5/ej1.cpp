/*

	 Realizar un programa que lea enteros hasta que se introduzca un elemento par y muestre por pantalla la media de los datos leídos (el par no debe contar para calcular la media).


*/


#include<iostream>

using namespace std;

int main()
{
	int n, suma = 0;
	double contador_n_introducidos = 0, media = 1;
	
	cout << "Introduzca un numero entero: ";
	cin >> n;
	
	suma += n;
	 
	while(n % 2 != 0)
	{
		cout << "Introduzca otro numero entero: ";
		cin >> n;
		
			suma += n;
			
			contador_n_introducidos++;	
	}

	media = (suma - n) / contador_n_introducidos;
		
	cout << "La media de los numeros introducidos antes del numero par es: " << media;
		
}
