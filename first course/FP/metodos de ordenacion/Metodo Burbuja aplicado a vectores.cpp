/*

	METODO BURBUJA

*/

#include<iostream>

using namespace std;

int main()
{
	
	// Definicion de variables:
	
	const int MAX = 1000;
	
	int v[MAX];
	
	int util_v;
	
	int intercambia;
	
	bool cambio = true;

	
	// Nº DE ELEMENTOS DEL VECTOR 
	 
	do
	{
       cout << "Introduzca número de componentes: ";
       cin >> util_v;
       
   }while (util_v > MAX || util_v < 0);
   
   
   // INTRODUCCION DE LOS ELEMENTOS DEL VECTOR:
   
   for (int i=0 ; i<util_v ; i++)
   {
      cout << "Posición " << i << ": ";
      cin >> v[i];
   }
	
	
	// Estructura que recorrera el vector tantas veces como sea necesario hasta finalmente ordenarlo, esto comparando el valor de una posicion
	// con el de la anterior posicion, en el caso que el valor de la anterior sea mayor ambos valores se intercambiaran la posicion.

	
	for(int i = 0; i < util_v && cambio == true; i++)
	{
		cambio = false;
		
		for(int j = util_v - 1; j > i ; j--)
		{		
			if(v[j] < v[j - 1])
			{	
				cambio = true;
				
				intercambia = v[j];
				
				v[j] = v[j - 1];
				
				v[j - 1] = intercambia;
			}
			
		}
		
	}	
   
   
	//MOSTRAMOS VECTOR V:
	
	cout << "\n\nEl vector ordenado es:" << endl;
	
	for(int i = 0; i < util_v; i++)
	{
		cout << v[i] << endl;
	}











}
