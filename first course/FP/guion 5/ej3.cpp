/*

	Escribir un programa para determinar si un n�mero entero es un cuadrado perfecto. Recordar
	que estos n�meros son de la forma n2, es decir, los n�meros 1, 4, 9, 16, � Para ello, no se puede
	hacer uso de la funci�n sqrt, sino que tendremos que ir calculando los cuadrados de los
	n�meros desde el 1 en adelante.

*/


#include<iostream>

using namespace std;

int main()
{
	int n;
	bool esCuadrado = false;
	
	cout << "Digite un numero entero: ";
	cin >> n;
	
	for(int i = 1; i < n && esCuadrado == false; i++)
	{
		if(i * i == n)
		{
			esCuadrado = true;
		}
	}
	
	if(esCuadrado == true)
	{
		cout << endl << n << " Es cuadrado";
	}
	
		else
		{
			cout << endl << n << " No es cuadrado";
		}
	
}
