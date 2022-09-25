/*

	Diseñar un programa que lea n números reales y muestre por pantalla el segundo elemento
	mayor (el más cercano al mayor dato que es menor a éste).

*/

#include<iostream>

using namespace std;

int main()
{
	
	// Declaracion de variables:
	
	double real, real2, Mayor, Segundo_Mayor;
	int contador_reales;
	
	
	// Introduccion del numero de reales que se van a digitar:
	
	cout << "Numero de reales que va a introducir: ";
	cin >> contador_reales;
	
	
	// Lectura anticipada de de dos reales, tras esto los compararemos y asignaremos el mayor 
	// a la variable Mayor y el menor a la variable Segundo_Menor:
	
	cout << "Digite un numero real: ";
	cin >> real;
	
	cout << "Digite un segundo numero real: ";
	cin >> real2;
	
	
	if(real > real2)
	{
		Mayor = real;
		Segundo_Mayor = real2;
	}
		
		else
		{
			Mayor = real2;
			Segundo_Mayor = real;	
		}
		
	
	// Estructura repetitiva que en la que se ira introduciendo reales y por medio de condiciones
	//	asignaremos cuales son el mayor y segundo mayor de todos ellos
 	
	for(int i = 2; i < contador_reales; i++)
	{
		cout << "Digite otro numero real: ";
		cin >> real;
		
		if(real > Mayor)
		{
			Mayor = real;
		}
		
		if(real < Mayor && real > Segundo_Mayor)
		{
			Segundo_Mayor = real;
		}
	
	}
	
	
	// Salida: 
	
	cout << "El numero mas cercano al mayor ( " << Mayor << " )" << " es: " << Segundo_Mayor; 
	

















}
