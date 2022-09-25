/*
							A un conjunto de tres valores enteros (a, b, c) que cumplen que a2+b2=c2 se le llama Triple de
							Pitágoras. Esto es así porque se pueden considerar los lados de un triángulo rectángulo.
							Implementar un programa que lea tres valores y determine si es un triple de Pitágoras.

*/

#include <iostream>

using namespace std;


int main()
{
	int a, b, c;

	bool esTriplePitagorica; 
		
	cout << "Digite el primer entero: ";
	cin >> a;
	
	cout << "Digite el segundo entero: ";
	cin >> b;
	
	cout << "Digite el tercer entero: ";
	cin >> c;
	
	
	esTriplePitagorica = ( a*a + b*b == c*c );
	
	
	if( esTriplePitagorica )
	{
		cout << "\nLos tres enteros forman una triple pitagorica";
	}
		else
		{
			cout << "\nLos tres enteros no forman una triple pitagorica.";
		}
	
}
