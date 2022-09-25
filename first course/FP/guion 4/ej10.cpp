/*

		Determinar si n términos de entrada están ordenados de forma creciente.

*/

#include<iostream>

using namespace std;

int main()
{
	double numero,numero_siguiente ;
	int n_introducidos;
	bool OrdenCreciente = true;
	
	cout << "Cantidad de numeros que va a ingresar: ";
	cin >> n_introducidos;
	
	cout << "\n\nDigite un numero: ";
	cin >> numero;
	
	for(int i = 1; i < n_introducidos; i++)
	{
		cout << "\nDigite otro numero: ";
		cin >> numero_siguiente;
		
		if(numero > numero_siguiente)
		{
			OrdenCreciente = false;
		}
			
		numero = numero_siguiente;		
	}
	
	if(OrdenCreciente)
	{
		cout << "\n\nEstan en orden creciente.";
	}
	
		else
		{
			cout << "\n\nNO estan en orden creciente.";
		}
		

}
