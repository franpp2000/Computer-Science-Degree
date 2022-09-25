/*

											Crear una calculadora que sea capaz de pedir dos números reales a y b y que muestre un menú
											con cuatro opciones: -S (sumar) R (restar) M (multiplicar) -D (dividir). El programa debe
											permitir la elección de una operación y mostrar el resultado por pantalla.


*/

#include<iostream>
using namespace std;


int main()
{
	//Declaracion de variables:
	
	double n1, n2, operacion;
	char option;
		
	//Entrada de valores de variables n1, n2:
	
	cout << "Digite un numero real: ";
	cin >> n1;
	
	cout << "Digite otro numero real: ";
	cin >> n2;
	
	//Menú para elegir la operacion deseada:
	
	cout << "\n\t\tCalculadora:";
	cout << "\n\nOperaciones disponibles:";
	cout << "\nSUMA (S)";
	cout << "\nRESTA (R)";
	cout << "\nMULTIPLICACION (M)";
	cout << "\nDIVISION (D)";
	
	cout << "\n\nOpcion: ";
	cin >> option;
	
	//Estructura condicional la cual segun el valor de option realizara una operacion u otra, o ninguna en 
	//el caso de no introducir ninguna de las opciones:
	
	if(option == 'S')
	{
		operacion = n1 + n2;	
	} 
		
		else if(option == 'R')
		{
			operacion = n1 - n2;
		}
			
			
			else if(option == 'M')
			{
		 		operacion = n1 * n2;
			}
	
			
				else if(option == 'D')
				{
		 			operacion = n1 / n2;
				}
	
	//En caso de que no digite el usuario una opcion existente:
			
	else
	{
		cout << "\nOpcion no existente." << endl;
	}		
	
	//En caso de que el usuario digite una opcion existente:
	
	if(option == 'S' || option == 'R' || option == 'M' || option == 'D')
	{
		cout << "\n\nEl resultado de la operacion es: " << operacion << endl;
	}
		
}
