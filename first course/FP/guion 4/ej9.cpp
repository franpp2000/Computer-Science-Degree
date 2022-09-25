/*

	Un número se define como perfecto si es igual a la suma de sus divisores, excluido él mismo.
	Por ejemplo, 6 es perfecto, ya que 6 = 1+2+3. Escribir un programa que pida un número y
	devuelva por pantalla un mensaje diciendo si es o no perfecto.

*/


#include<iostream>

using namespace std;


// Funcion que comprueba si un numero es perfecto o no.

bool Perfecto(int x)
{
	int suma = 0;
	bool esPerfecto;
	
	for(int i = 1; i < x; i++)
	{
		if(x % i == 0)
		{
			suma += i;
		}
	}
	
	esPerfecto = (suma == x);
	
	if(esPerfecto)
	{
		return true;
	}
	
		else
		{
			return false;	
		}

}


// Funcion Principal.

int main()
{
	int numero; 
	
	
	
	cout << "Digite un numero entero positivo: ";
	cin >> numero;
	

	if(Perfecto(numero) == true)
	{
		cout << endl << numero << " Es perfecto.";
	}
		else
		{
			cout << endl << numero << " No es perfecto.";	
		}
}






