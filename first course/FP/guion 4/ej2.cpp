/*

								Mostrar todos los números pares comprendidos entre dos variables enteras leídas por teclado.

*/

#include<iostream>

using namespace std;

int main()
{

	int cota_inferior, cota_superior;

	cout << "A continuacion se le va a pedir un intervalo en el que se buscara todos los numeros pares dentro de este.";
	cout << "\n\nIntroduzca la cota inferior del intervalo: ";
	cin >> cota_inferior;
	
	cout << "\nIntroduzca la cota superior del intervalo: ";
	cin >> cota_superior;
	
	cout << "\n\nLos numeros pares que esta dentro de este intervalo son: " << endl;
	
		
		for(int i = cota_inferior; i <= cota_superior; i++)
		{
		  if(i % 2 == 0)
		  {
		   cout << i << endl;
		  }
		  		
		}
	
}
