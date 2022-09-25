/*
	8. Realizar un programa que lea un vector de caracteres y elimine los elementos repetidos.
*/

#include<iostream>

using namespace std;

int main()
{
	
	const int MAX = 1000;            //<----- tamaño maximo de los vectores
	
	char v[MAX];                     //<----- vector v1
	
	int tam_v;                       //<----- tamaño de v1
	
	int posicion_comprobacion = 0;
	
	
	
	// NUMERO DE ELEMENTOS DEL VECTOR V1:
	
	cout << "Numero de elementos del vector: ";
	cin >> tam_v;
	
	
	
	// INTRODUCIMOS LOS ELEMENTOS DEL VECTOR:
	
	for( int i = 0; i < tam_v; i++ )
	{
		cout << "Posicion " << i << ": ";
		cin >> v[ i ];
	} 
	
	
	
	// ESTRUCTURA QUE SE ENCARGARA DE COMPROBAR SI POR IZQUIERDA O DERECHA DEL ELEMENTO QUE ESTAMOS COMPROBANDO TIENE COINCIDENCIA
	// CON OTRO ELEMENTO EN OTRA POSICION:

	while( posicion_comprobacion < tam_v)
	{
		
		for(int i = 0; i < posicion_comprobacion; i++)
		{
			
			if(v[posicion_comprobacion] == v[i])
			{
				
				v[i] = v[i + 1];
				
				posicion_comprobacion--;
				
				tam_v--;
				
			}
		
		}
		
		for(int j = tam_v - 1; j > posicion_comprobacion; j--)
		{
			
				if(v[posicion_comprobacion] == v[j])
				{
						v[j] = v[j + 1];
												
						tam_v--;
				
				}
		}
		
		posicion_comprobacion++;
	}
	
	//Mostarmos los elementos del vector:
	
	for (int i = 0; i < tam_v; i++)
	{
		cout << v[i] << endl;
	}		
	
		

}
