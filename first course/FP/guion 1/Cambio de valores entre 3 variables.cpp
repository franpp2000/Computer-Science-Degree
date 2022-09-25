//Ejercicio guion b)6


#include<iostream>


using namespace std;


int main(){
	
	
	int a, b, c, temp1, temp2;
	
	
	cout << "Introduzca un primer entero: ";
	cin >> a;
	
	cout << "Introduzca un segundo entero: ";
	cin >> b;   
	
	cout << "Introduzca un tercer entero: ";
	cin >> c;
	
	
	temp1 = a;
	
	temp2 = b;
	
	b = temp1;
	
	a = c;
	
	c = temp2;
	
	
	cout << a;
	cout << endl << b;
	cout << endl << c; 
	
	
}
