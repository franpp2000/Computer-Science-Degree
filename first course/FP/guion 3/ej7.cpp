/*

												Desarrollar un programa que lea cuatro enteros distintos a cero y determine el mayor de los
												pares (tener en cuenta la circunstancia de que el usuario no introduzca ningún par).

*/


#include <iostream>

using namespace std;

int main()
{
	int a, b, c, d, posiblePar1 = 0, posiblePar2 = 0, posiblePar3 = 0, posiblePar4 = 0, Candidato1, Candidato2;
	
	
	cout << "Digite un numero entero +: ";
	cin >> a;
	
	cout << "Digite otro numero entero +: ";
	cin >> b;
	
	cout << "Digite otro numero entero +: ";
	cin >> c;
	
	cout << "Digite otro numero entero +: ";
	cin >> d;
	
	if(a == 0 || b == 0 || c == 0 || d == 0)
	{
		cout << "Debe digitar solamente enteros positivos.";
	}
	
	if(a % 2 != 0 && b % 2 != 0 && c % 2 != 0 && d % 2 != 0)
	{
		cout << "No ha digitado ningun entero positivo par.";
	}
	
	if(a % 2 == 0)
	{
		posiblePar1 = a;
	}
	
	if(b % 2 == 0)
	{
		posiblePar2 = b;
	}

	if(c % 2 == 0)
	{
		posiblePar3 = c;
	}
	
	if(d % 2 == 0)
	{
		posiblePar4 = d;
	}


	if(posiblePar1 > posiblePar2)
	{
		Candidato1 = posiblePar1;
	}
		else
		{
			Candidato1 = posiblePar2;
		}
		
	
	if(posiblePar3 > posiblePar4)
	{
		Candidato2 = posiblePar3;
	}
		else
		{
			Candidato2 = posiblePar4;
		}
		
	
	if(Candidato1 > Candidato2)
	{
		cout << "El mayor par es " << Candidato1;
	}
		else
		{
			cout << "El mayor par es " << Candidato2;
		}	
 







}
