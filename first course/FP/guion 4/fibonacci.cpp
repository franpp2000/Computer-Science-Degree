																			//Sucesion de fibonacci//
																			
#include<iostream>

using namespace std;

int main()
{
	int f, f_1, f_2, n;
	
	cout << "Valor de la posicion n que quiere saber de la sucesion de Fibonacci: ";
	cin >> n;
	
	f_2 = f_1 = f = 1;
	
	for(int i = 2; i<=n; i++)
	{
		f = f_1 + f_2;
	
		f_2 = f_1;
		
		f_1 = f;
	
	}

	cout << "El valor es: " << f;







}
