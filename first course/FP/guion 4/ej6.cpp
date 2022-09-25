/*

							Realizar un programa que lea n números reales y muestre por pantalla el real leído más cercano
							al cero (utilizar la función fabs).

*/


#include<iostream>
#include<math.h>

using namespace std;

int main()
{
	double real, n_reales, i = 1, MasCercano0;
	
	cout << "Numero de reales que va a introducir: ";
	cin >> n_reales;
	
	cout << "\n\nDigite un numero real:";
	cin >> real;
	
	MasCercano0 = real;
		
		while(i < n_reales)
		{
			cout << "\nDigite otro numero real:";
			cin >> real;
			
				if(fabs(MasCercano0) > fabs(real))
				{
					MasCercano0 = real;
				}
		
			i++;
		}
	
	cout << "El numero mas cercano a cero de todos los digitados es: " << MasCercano0;
}
