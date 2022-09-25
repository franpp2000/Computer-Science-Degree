/*
	5. Realizar un programa que lea un vector de caracteres (con posibles repeticiones) y construya otro con los elementos del primero sin repetir.
*/



#include<iostream>

using namespace std;

int main()
{
	
	// DECLARACION DE VARIABLES:
	
	const int MAX = 1000;            //<----- tamaño maximo de los vectores
	
	char v1[MAX], v2[MAX];           //<----- vectores v1 y v2
	
	int tam_v1, tam_v2 = 0;          //<----- tamaño de v1 y v2 (v2 = 0 porque no se el tamaño que tendra)
	
	bool coincidencia = false;       //<----- booleano que indica si hay coincidencias o no
	
	int indice_v2 = 0;               //<----- indicador de una posicion de v2
	
	
	// NUMERO DE ELEMENTOS DEL VECTOR V1:
	
	cout << "Numero de elementos del vector 1: ";
	cin >> tam_v1;
	
	
	// INTRODUCIMOS LOS ELEMENTOS DEL VECTOR:
	
	for(int i = 0; i < tam_v1; i++)
	{
		cout << "Posicion " << i << ": ";
		cin >> v1[i];
	} 
	
	
	//ESTRUCTURA EN LA QUE SE VAYA COMPROBANDO SI UN ELEMENTO DE V1 ESTA EN V2, EN CASO NEGATIVO ESTE SE INTRODUCIRA
	//EN ESTE:
	
	for(int i = 0; i < tam_v1; i++)
	{
		
		for(int j = 0; j < tam_v2 && coincidencia == false; j++)   //
		{                                                          // Bucle que comprobara elemento a elemento de v1 si este se 
			if(v1[i] == v2[j])                                      // encuentra en v2, donde la respuesta a esto queda en la
			{                                                       // variable coincidencia.
				coincidencia = true;                                 //
			}                                                       //
		}                                                          //
		
		
		if(coincidencia == false)   //
		{                           //
			tam_v2++;                // En el caso de que no haya encontrado ninguna repeticion ( coincidencia == false )
			                         // el valor de dicha posicion se introduce en el vector v2, no sin antes aumentar en 
			v2[indice_v2] = v1[i];   // uno el tamaño del vector y del indice de v2 que me indicara donde se debe introducir
			                         // el siguiente caracter que no se repita.
			indice_v2++;	          //
		}                           //
	
	
		coincidencia = false;	//<----- asignacion necesaria para que haga la comprobacion con todas las posiciones.
	}
	
	
	//MOSTRAR VECTOR V2:
	
	cout << "\n\nEl vector sin caracteres coincidentes es:" << endl;
	
	for(int i = 0; i < tam_v2; i++)
	{
		cout << v2[i] << endl;
	}
			
} 
	





