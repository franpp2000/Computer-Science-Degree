/*

	1. Realizar un programa que lea un entero y muestre por pantalla su representación en binario.

*/

#include<iostream> 

using namespace std;

int main()
{
	//DECLARACION DE VARIABLES
	
	const int MAX = 1000;                // <--------- numero de elementos maximos del vector
	
	int v[MAX];                          // <--------- vector v
	
	int numero, resto, cociente;         // <--------- variables utiles para el calculo de los digitos del numero binario
	
	int tam_v = 0;                       // <--------- tamaño del vector v, inicializada en cero porque no se cual sera su 
                                        // 				extension
	
	int pos_v = 0;                       // <--------- variable que representa una posicion de v
	
	
	// INTRODUCCION DE NUMERO EN BASE DECIMAL
	
	cout << "Digite un numero entero en base decimal: ";
	cin >> numero; 
	
	
	// ESTRUCTURA QUE IRÁ INTRODUCIENDO LOS RESTOS DE LA DIVISION DEL NUMERO ENTRE 2, EL CONCIENTE DE LA DIVISION
	// ANTERIOR ENTRE 2...
	
	while(numero >= 2)
	{	
		resto = numero % 2;
		
		cociente = numero / 2;
		
		v[pos_v] = resto;
		
		numero = cociente;            
		
		pos_v++;
		
		tam_v++;
		
		// Condicion necesaria para que en la ultima division tome el cociente correspondiente a
		// esta pues tambien forma parte de los digitos del numero en binario. 	
		
		if(numero < 2)          
		{                           
			v[pos_v] = cociente;            
			tam_v++;               
		}
		
	}
	
	
	// MOSTRAMOS LOS ELEMETOS DEL VECTOR EN ORDEN INVERSO QUE SERA LA REPRESENTACION
	// DEL NUMERO INTRODUCIDO ANTERIORMENTE EN BASE 2:

	cout << "\n\nEl numero introducido en base 2 es:\n" << endl;
	
	for (int i = tam_v - 1; i >= 0; i--)
	{
		cout << v[i];
	}		

}
