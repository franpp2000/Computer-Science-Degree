/*

	3. Realizar un programa que lea un vector de enteros positivos y busque la posición del mayor de los
	primos que contiene.

*/

#include<iostream>

using namespace std;

int main()
{
	
	//DECLARACION DE VARIABLES:
	
	const int MAX = 1000;           // <----- Numero de componentes maximo del vector
	
	int v[MAX];                     // <----- Vector v
	
	bool es_primo = true;           // <----- Booleano que determinara si un numero es primo
	
	int mayor = 0;                  // <----- Varible que guardara al mayor de los primos
	
	int n;                          // <----- Numero de componentes del vector
	
	int j = 2;                      // <----- Iterador del bucle que comprobara si un numero es primo
	
	int posicion_mayor = 0;         // <----- Variable que guardara la posicion del mayor de los primos 
	
	
	//NUMERO DE COMPONENTES DEL VECTOR:
	
	cout << "Numero de componentes del vector: ";
	cin >> n;
	
	
	//INTRODUCCION DE LAS COMPONENTES DEL VECTOR:
	
	for(int i = 0; i < n; i++)
	{
		cout << "\n\nComponente " << i << ": ";
		cin >> v[i];
	}
	
	
	//ESTRUCTURA QUE IRA REVISANDO COMPONENTE A COMPONENTE SI ES UN NUMERO PRIMO, TRAS ESTO TAMBIEN SE COMPROBARA
	//SI ES MAYOR QUE EL ANTERIOR PRIMO QUE ERA EL MAYOR HASTA AHORA:
	
	for(int i = 0; i < n; i++)
	{                                      
		while(j < v[i] && es_primo == true)   //
		{                                     // 
			if(v[i] % j == 0)                  // Bucle que comprobara si el numero de cada
			{                                  // componente es primo o no
				es_primo = false;               //
			}                                  //
	                                         //
			j++;                               //
		}                                     //
		  
		  j = 2;         // <----- asignacion necesaria para que vuelva a probar a dividir desde 2 con la proxima posicion                     
		
		
		if(es_primo == true)             //
		{                                //
			if(v[i] > mayor)              //
			{                             // En el caso de que dicho valor de una componente
				mayor = v[i];              // sea primo, se comprobara si es mayor que el mayor
				                           // primo anterior, ademas de guardar la posicion de dicho primo
				posicion_mayor = i;        //
			}                             //
		}                                //
	
		es_primo = true;  // <---- Reestablecemos el valor del booleano a true para que el proximo numero se compruebe      
	}
	
	
	//SALIDA DEL PROGRAMA:
	
	cout << "\n\nEl mayor de los primos introducidos es: " << mayor << endl;
	cout << "Este se encuentra en la posicion " << posicion_mayor << endl;
		
}
