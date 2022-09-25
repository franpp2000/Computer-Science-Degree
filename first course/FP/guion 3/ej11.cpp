/*

	Realizar un programa que lea 10 valores reales, calcule su media y determine el número de
	elementos que superan la media.

*/

#include<iostream>
using namespace std;

int main()
{	
	//Declaracion de variables:
	
	double n1, n2, n3, n4, n5, n6, n7, n8, n9, n10;
	double suma, media;
	
	int n_introducidos = 10, contador = 0;
	
	//Introduccion de valores de varibles n1, n2, ... , n10:
	
	cout << "Digite un numero real: ";
	cin >> n1;
	
	cout << "Digite otro numero real: ";
	cin >> n2; 
	
	cout << "Digite otro numero real: ";
	cin >> n3; 
	
	cout << "Digite otro numero real: ";
	cin >> n4; 
	
	cout << "Digite otro numero real: ";
	cin >> n5; 
	
	cout << "Digite otro numero real: ";
	cin >> n6; 
	
	cout << "Digite otro numero real: ";
	cin >> n7; 
	
	cout << "Digite otro numero real: ";
	cin >> n8; 
	
	cout << "Digite otro numero real: ";
	cin >> n9; 
	
	cout << "Digite otro numero real: ";
	cin >> n10; 

	//Asignacion de variables suma y media:
	
	suma = n1 + n2 + n3 + n4 + n5 + n6 + n7 + n8 + n9 + n10;
	
	media = suma / n_introducidos;

	//Estructura condicional para ver cuales n introducidos superan la media:
	
	if(n1 > media)
	{
		contador++;
	}

	if(n2 > media)
	{
		contador++;
	}
	
	if(n3 > media)
	{
		contador++;
	}
	
	if(n4 > media)
	{
		contador++;
	}
	
	if(n5 > media)
	{
		contador++;
	}
	
	if(n6 > media)
	{
		contador++;
	}
	
	if(n7 > media)
	{
		contador++;
	}
	
	if(n8 > media)
	{
		contador++;
	}
	
	if(n9 > media)
	{
		contador++;
	}
	
	if(n10 > media)
	{
		contador++;
	}
	
	//Salida deseada, es decir, numero de elementos que superan la media:
	
	cout << "\n\nLa media es: " << media;
	
	cout << "\nNumero de elementos que superan la media: " << contador;
	
}
