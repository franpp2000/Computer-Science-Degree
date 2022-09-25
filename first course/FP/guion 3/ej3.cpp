/*

					Realizar un programa que lea desde el teclado tres enteros y los muestre ordenados

*/


#include<iostream>

using namespace std;

int main(){
	
	int n1, n2, n3;
	
	
	cout << "Digite un entero cualquiera: ";
	cin >> n1;
	
	cout << "Digite otro entero cualquiera: ";
	cin >> n2;
	
	cout << "Digite otro entero cualquiera: ";
	cin >> n3;
	
	
	if(n1 > n2 && n1 > n3)
	{
		
		
		if(n2 > n3)
		{
			cout << n1 << endl << n2 << endl << n3;
		}
		
			else
			{
					cout << n1 << endl << n3 << endl << n2;
			}
		
	}
	
	if(n2 > n1 && n2 > n3)
	{
		
		
		if(n1 > n3)
		{
			cout << n2 << endl << n1 << endl << n3;
		}
		
			else
			{
					cout << n2 << endl << n3 << endl << n1;
			}
		
	}
	
	if(n3 > n1 && n3 > n2)
	{
		
		
		if(n1 > n2)
		{
			cout << n3 << endl << n1 << endl << n2;
		}
		
			else
			{
					cout << n3 << endl << n2 << endl << n1;
			}
		
	}
	
	
	
}
