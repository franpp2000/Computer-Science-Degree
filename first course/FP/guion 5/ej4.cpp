/*
	Dados dos enteros D y d determinar D/d y D%d sin usar las operaciones “/” y “%” (con un ciclo while).
*/

#include<iostream>
using namespace std;


int main()
{
	
	/// Declaracion de variables:
	
	int D, d, i = 0, cociente, resto;
	
	
	/// Peticion al usuario del valor de las variables D y d (dividendo y divisor reapectivamente): 
	
	cout << "Introduzca el valor del dividendo: ";
	cin >> D;
	
	cout << "Introduzca el valor del divisor: ";
	cin >> d;
	
	
	/// Estructura repetitiva que calculara el numero que multiplicado por el 
	/// divisor es igual o el primero que se pasa de este:					  	  
	
	while( d * i <= D )
	{
		i++;
	}

	
	/// Si el producto nos da exactamente el valor del dividendo:
	 
	if( d * i == D )
	{
		cociente = i;
		resto = 0;
	}
	
	
	// Si el producto se pasa del valor del dividendo, el cociente seria el numero menos 
	// la unidad y el resto lo que falta del este nuevo producto para ser el dividendo:
	
	if( d * i > D )
	{
		cociente = i - 1;
		resto = D - cociente * d;
	}
	
	
	// Salida de resultakdos:
	
	cout << "Cociente: " << cociente << endl;
	cout << "Resto: " << resto << endl;

}
