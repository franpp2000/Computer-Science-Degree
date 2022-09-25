/*
	7. Realizar un programa que inserte un vector dentro de otro a partir de una posición determinada.
*/

#include<iostream>

using namespace std;

int main()
{
	
	// DECLARACION DE VARIABLES:
	
	const int MAX = 1000;      //<----- numero de elementos maximos del vector
	
	int v1[MAX], v2[MAX];      //<----- vectores v1, v2
	
	int tam_v1, tam_v2;        //<----- tamaño de los vectores v1, v2
	                      
	int posicion_insercion;    //<----- posicion desde donde se inserta una posicion de v2 en v1
	
	
	// NUMERO DE ELEMENTOS DEL VECTOR V1:
	
	cout << "Numero de elementos del vector 1: ";
	cin >> tam_v1;
	
	
	// INTRODUCIMOS LOS ELEMENTOS DEL VECTOR V1:
	
	for(int i = 0; i < tam_v1; i++)
	{
		cout << "\nPosicion " << i << ": ";
		cin >> v1[i];
	} 
	
	
	// NUMERO DE ELEMENTOS DEL VECTOR V2:
	
	cout << "\n\nNumero de elementos del vector 2: ";
	cin >> tam_v2;
	
	
	// INTRODUCIMOS LOS ELEMENTOS DEL VECTOR V2:
	
	for(int i = 0; i < tam_v2; i++)
	{
		cout << "\nPosicion " << i << ": ";
		cin >> v2[i];
	} 
	
	
	//POSICION DESDE DONDE SE VA A INSERTAR V2 EN V1:
	
	cout << "Posicion desde donde se va a insertar v2 en v1: ";
	cin >> posicion_insercion;
	
	
	//ESTRUCTURA QUE IRA INSERTANDO UNO A UNO CADA ELEMENTO DEL VECTOR QUE SE VA INSERTAR, PARA ELLO POR CADA ITERACION DEBEREMOS
	//AUMENTAR EN UNO EL TAMAÑO DEL VECTOR DONDE SE VA A IRSERTAR EL OTRO, Y TRAS ESTO DEPLAZAR A LA DERECHA LOS ELEMENTOS DEL VECTOR
	//DESDE DONDE SE HARA LA INSERCION 
	
	for(int i = 0; i < tam_v2; i++)
	{
		tam_v1++;
		
		for(int j = tam_v1 - 2; j >= posicion_insercion; j--)   // 
		{                                                       // Bucle que desplaza los elementos de un vector desde una posicion
			v1[j + 1] = v1[j];                                   // dada hacia la derecha
		}                                                       //
		                                                        
		v1[posicion_insercion] = v2[i];                         // Insercion de los elementos de v2 en v1 desde una posicion preparada
		                                                        // para que no se machaque ningun valor añadido previamente
		
		posicion_insercion++;	                                // asignacion necesaria para insertar el proximo elemento de v2 en una
		                                                        // posicion siguiente al que se ha insertado previamente 
	}	
	
	
	//MOSTRAR VECTOR V1:
	
	cout << "\n\nEl vector v1 con los elementos de v2 desde la posicion " << posicion_insercion << " es:" << endl;
	
	for(int i = 0; i < tam_v1; i++)
	{
		cout << v1[i] << endl;
	} 
	
	













}
