/*

							Para todo entero positivo n, el factorial de n se define como el producto de todos los números
							enteros positivos desde 1 hasta n (n! = 1*2*3*4*…*(n-1)*n). Se pide crear un programa que pida
							por pantalla un numero y devuelva el factorial de n. El factorial de cero es por definición uno.
							Probar dar la salida usando int y también “long long”.

*/


#include<iostream>

using namespace std;

int main()
{
	
	long long n, factorial = 1;
	
	
	cout << "Introduzca un entero positivo: ";
	cin >> n;
	
	 
	 if(n == 0)
	 	
	 	cout << "El factorial de " << n << " es: " << 1;
	 	
	 	else
		 {
		 
	 			for(int i = 1; i <= n; i++)
				 {
		
					factorial *= i;
		
     			 }
     
     				cout << "El factorial de " << n << " es: " << factorial;
   
		 }
		
}
