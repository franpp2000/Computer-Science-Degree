/*

			Realizar un programa que lea 20 letras ('a' … 'z') y determine si el número de veces que ha
			aparecido 'a' es mayor al numero de veces de 'z'. Considerar que puede darse la circunstancia
			de que alguno de ellos, o ambos, no aparezcan.

*/

#include <iostream>

using namespace std;

int main()
{   
	char letra;
	int contador_letras = 0, contador_a = 0, contador_z = 0;

		
		while(contador_letras < 20)
		{
			cout << "Introduzca una letra: ";
			cin >> letra;
			
				if(letra == 'a')
				{
					contador_a++;
				}
				
				if(letra == 'z')
				{
					contador_z++;
				}
			
			contador_letras++;
			
		}

		
		if(contador_a < contador_z)
		{
			cout << "Se han digitado mas veces z que a.";
		}
			else
				if(contador_a > contador_z)
				{
					cout << "Se han digitado mas veces a que z.";
				}
					else
						if(contador_a = contador_z)
						{
							cout << "Se han digitado igual de veces a y b.";
						}
		
		if((contador_a == 0 && contador_z == 0) || (contador_a == 0 || contador_z == 0))
		{
			cout << "\nO a o z o las dos no se han digitado ninguna vez.";
									
		}


}
