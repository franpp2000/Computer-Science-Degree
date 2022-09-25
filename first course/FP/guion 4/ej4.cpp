/*

												Realizar un programa para determinar si un entero positivo n es primo.

*/


#include <iostream>

using namespace std;

int main()
{
	int entero_positivo, i = 2;
	bool es_primo = true;
	bool condicion_no_primo;
	
		do
		{                                                   // Recurso para asegurar que se introduzca un entero positivo.
			cout << "Introduzca un entero POSITIVO: ";    
			cin >> entero_positivo;
		}
		
			while(entero_positivo < 0);
			

	condicion_no_primo =	(entero_positivo % i == 0);	
	

	while(i < entero_positivo && es_primo)
	{
		if(condicion_no_primo)
		{
			es_primo = false;
		}
	
		i++;
	}  
	
		if(es_primo)
				
}
