/*

				Diseñar un programa que lea un entero y determine si es un múltiplo de 5 mayor a 1000.

*/


#include<iostream>

using namespace std;

int main(){
	
	int n;
	bool EsMultiplo5, Mayor1000;
	
	cout << "Digite u numero entero: ";
	cin >> n;
	
	EsMultiplo5 = (n % 5 == 0);
	Mayor1000 = (n > 1000);
	
		
	if(EsMultiplo5)
		cout << "El entero introducido es multiplo de 5";
		
		else
			cout << "El numero introducido no es multiplo de 5";
			
	
	if(Mayor1000)
		cout << " y es mayor a 1000";
		
		else 
			cout << " pero no es mayor a 1000";		
	
	
	
	
	
	
	
	
	
}
