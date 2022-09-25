/*

										Desarrollar un programa para mostrar los divisores propios de n.

*/

#include<iostream>

using namespace std;


// Módulo que muestra los divisores de un numero introducido:

void Divisores(int x)
{
	for(int i = 1; i < x; i++)
	{
		if(x % i == 0)
		{
			cout  << i << endl;
		}
	}
}


// Funcion principal.

int main()
{	
	
	// Declaracion de variables.
	
	int n;
	
	
	// Introduccion del numero entero del que se calcularan sus divisores.
	
	cout << "Digite un numero entero: ";
	cin >> n;
	
	
	// Llamada a funcion que muestra los divisores de n:
	
	cout << "Los divisores de " << n << " son: " << endl;
	
	Divisores(n);  
	
}
