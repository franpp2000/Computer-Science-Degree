/*

		Realizar un programa que lea 3 enteros distintos a cero y determine cuál es el signo predominante (positivo o negativo).

*/


#include<iostream>

using namespace std;

int main(){
	
	
	int n1, n2, n3, Numero_Positivos = 0, Numero_Negativos = 0;
	
	
	cout << "Digite un numero distinto de 0: ";
	cin >> n1;
	
	cout << "Digite otro numero distinto de 0: ";
	cin >> n2;
	
	cout << "Digite otro numero distinto de 0: ";
	cin >> n3;
	
	
	if(n1 != 0 && n2 != 0 && n3 != 0){
		
			if(n1 > 0)
				Numero_Positivos++;
		
				else
					if(n2 > 0)
						Numero_Positivos++;
						
						else
							if(n3 > 0)
								Numero_Positivos++;
	
			if(n1 < 0)
				Numero_Negativos++;
		
				else
					if(n2 < 0)
						Numero_Negativos++;
		
						else
							if(n3 < 0)
								Numero_Negativos++;
			
			
			if(Numero_Positivos > Numero_Negativos)	
				cout << "El signo predominante es +";
		
				else 
					cout << "El signo predominante es -";					
			}
			
			else
				cout << "Los tres numeros deben ser distintos de 0!!";
	
		
}
