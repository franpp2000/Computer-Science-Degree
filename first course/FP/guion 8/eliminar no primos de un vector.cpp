/*

	4. Realizar un programa que lea un vector de enteros positivos y borre todos aquellos que no sean primos.

*/

#include<iostream>

using namespace std;

int main()
{
	
	// DEFINICION DE VARIABLES:
	
	const int MAX = 1000;    // <------- Numero de elementos maximo
	
	int v[MAX];          // <------- Vector v
	
	int n;               // <------- numero de elementos del vector
	
	bool es_primo = true;
	
	int posicion_no_primo;
	
	int j = 2;
	
	// Nº DE ELEMENTOS DEL VECTOR 
	 
	cout << "Numero de elementos del vector: ";
	cin >> n;
	cout << endl;

	// INTRODUCCION DE LOS ELEMENTOS DEL VECTOR:
	
	for (int i = 0; i < n; i++)
	{
		cout << "\nElemento " << i << " -----> ";
		cin >> v[i];
	}
	
	
	// ESTRUCTURA QUE IRA COMPROBANDO COMPONENTE A COMPONENTE SI EL NUMERO QUE CONTIENE ES PRIMO
	// PARA QUE EN EL CASO DE QUE NO LO SEA BORRAR DICHA COMPONENTE:
	
	for(int i = 0; i < n; i++)
	{                                      
		while(j < v[i] && es_primo == true)   //
		{                                     // 
			if(v[i] % j == 0)                  // Bucle que comprobara si el numero de cada
			{                                  // componente es primo o no
				es_primo = false;               //
				                                //
				posicion_no_primo = i;          //
			}                                  //
			                                   //
			j++;                               //
		}                                     //
		 
		  j = 2;       // <----- asignacion necesaria para que vuelva a probar a dividir desde 2 con la proxima posicion  
		
		
		if(es_primo == false)             
		{                                
			if (posicion_no_primo >= 0 && posicion_no_primo < n)
			{
				for (int i = posicion_no_primo; i < n; i++)
				{
					v[i] = v[i+1];
				}
			}		
	
			n--;	
		}                                
	
		es_primo = true;  // <---- Reestablecemos el valor del booleano a true para que el proximo numero se compruebe      
	}
		
	
	// MOSTRAMOS LOS ELEMETOS DEL VECTOR CON SU POSICION ASOCIADA:
	
	for (int i = 0; i < n; i++)
	{
		cout << "\n\nPosicion " << i << " -----> " <<  v[i] << endl;
	}	

}
