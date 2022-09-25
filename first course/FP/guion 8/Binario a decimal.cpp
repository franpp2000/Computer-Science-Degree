/*

 2. Realizar un programa que lea un vector con ceros y unos y muestre por pantalla su valor en decimal.

*/

#include<iostream>
#include<math.h>

using namespace std;

int main()
{
	
	// DEFINICION DE VARIABLES:
	
	const int MAX = 1000;    // <------- Numero de elementos maximo
	
	int v[MAX];              // <------- Vector v
	
	int n;                   // <------- numero de elementos del vector
	
	int producto = 1;
	
	int suma = 0;
	
	
	// Nº DE ELEMENTOS DEL VECTOR 
	 
	cout << "Digitos del numero binario: ";
	cin >> n;
	cout << endl;

	
	// INTRODUCCION DE LOS ELEMENTOS DEL VECTOR:
	
	for (int i = 0; i < n; i++)
	{
		cout << "\nDigito " << i << " -----> ";
		cin >> v[i];
	}
	
	// ESTRUCTURA QUE IRA CALCULANDO EL PRODUCTO QUE RESULTA DE MULTIPLICAR EL VALOR DE CADA POSICION POR
	// DOS ELEVADO A LA POSICION QUE OCUPA EN ORDEN INVERSO AL QUE ENTIENDE C++, CADA UNO DE ESTOS PRODUCTOS
	// SE ACUMULAN EN LA VARIABLE SUMA LO QUE NOS DARA LA CONVERSION A BASE DECIMAL.  
	
	for(int i = 0; i < n; i++)
	{
		producto = v[i] * pow(2, (n - 1) - i);
		
		suma += producto;
	}
		cout << "\n\nDicho numero binario en base decimal es: " << suma;

}
