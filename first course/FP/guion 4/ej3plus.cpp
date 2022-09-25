/*

										Para hallar los múltiplos de un número n, basta multiplicar n por cada uno de los números
										naturales 0, 1, 2,... Crear un programa que muestre por pantalla los 1000 primeros múltiplos de
										5.

*/

#include <iostream>

using namespace std;

int main()
{
	int x_primeros_multiplos, n, producto = 1;
	
	cout << "Numero del que quiere que muestre sus x primeros multiplos: ";
	cin >> n;
	
	cout << "\nx primeros multiplos que quiere que muestre: ";
	cin >> x_primeros_multiplos;
	
	cout << "\n\nLos " << x_primeros_multiplos << " primeros multiplos son: " << endl << endl;
	
	
		for(int i = 1; i <= x_primeros_multiplos; i++)
		{
			
			producto = n * i;
			
			cout << producto << endl;
			
		}
	
}
