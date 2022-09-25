/*
	9. Diseñar un programa que lea un vector de enteros y busque la secuencia de unos seguidos más larga. El
	programa debe devolver la posición donde comienza la secuencia y su longitud.
*/


#include<iostream>

using namespace std;

int main()
{
	
	// DECLARACION DE VARIABLES
	
	const int MAX = 1000;
	
	int v[ MAX ];
	
	int contador_actual = 0, contador_secuencia_mayor = 0;
	
	int posicion_primer_1_sec_M = 0, posicion_primer_1_sec_actual = 0;
	
	int tam_v;
	
	
	
	// NUMERO DE ELEMENTOS DEL VECTOR V1:
	
	cout << "Numero de elementos del vector: ";
	cin >> tam_v;
	
	
	
	// INTRODUCIMOS LOS ELEMENTOS DEL VECTOR:
	
	for( int i = 0; i < tam_v; i++ )
	{
		cout << "Posicion " << i << ": ";
		cin >> v[ i ];
	} 
	
	
	
	// ESTRUCTURA QUE LEERA EL VECTOR DE IZDA A DCHA Y EN EL MOMENTO EN EL QUE ENCUENTRE UN UNO, GUARDARA LA POSICION EN LA QUE
	// LO ENCONTRO Y SI ENCUENTRA UNOS SUCESIVAMENTE IRA GUARDANDO EL NUMERO DE ESTO EN UN CONTADOR, EN EL CASO DE QUE ENCUENTRE OTRO 
	// NUMERO DISTINTO DE 1 Y TRAS ESTE O MUCHOS OTROS ENCONTRARA OTRA CADENA DE UNOS LA MEDIRIA TAMBIEN Y LA COMPARARIA CON LA 
	// ANTERIOR, LA CUAL SE GUARDARIA PREVIAMENTE EN OTRA VARIABLE PARA NO PERDER SU VALOR
	
	for( int i = 0; i < tam_v; i++ )
	{
		
		if( v[ i ] == 1 )											//
		{		                                          //
			                                             // Conjunto de condiciones relativas a cuando encontramos un 1:
			contador_actual++;                           //
			                                             // - Condicion especial para cuando el primer 1 se encuentra en la
		                                          //   en otra posicion que no sea la 0
			                                             //
			if( v[ i - 1 ] != 1 )              // - Contador de unos
			{                                            //
				posicion_primer_1_sec_actual = i;         //
			}	                                          //
	                                                   //
		}                                               //
		
		
		if( v[ i ] != 1 || i == tam_v - 1 )                                //
		{                                                                  // Conjunto de condiciones relativos al termino de una secuencia de unos:
			                                                                //
			if( contador_actual > contador_secuencia_mayor )                // - Condicion especial para cuando nos encontamos en la ultima posicion
			{                                                               //   del vector
				                                                             //
				contador_secuencia_mayor = contador_actual;                  // - Condicion que compara la cadena de 1 actual con la cadena de longitud
				                                                             //   mayor hasta ahora
				posicion_primer_1_sec_M = posicion_primer_1_sec_actual;      //	
			                                                                //
			}	                                                             //
			
			contador_actual = 0;   //<---- Asignacion clave para que cada vez que termine una secuencias de 1 la proxima que encuentre
			                       //      empiece a contarla desde 0.
		
		}
	
	}


	// SALIDA DEL PROGRAMA:
	
	cout << "\n\nLa longitud de la cadena mas larga de 1 seguidos es: " << contador_secuencia_mayor;
	cout << "\nLa posicion en la que se encontro el primer uno de dicha cadena es " << posicion_primer_1_sec_M;



}
