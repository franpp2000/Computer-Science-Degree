/* 																			
                                                            EJERCICIO 7 GUION B		
								
								Leed desde teclado tres variables correspondientes a un número de horas, minutos y segundos,
								respectivamente. Diseñar un algoritmo que calcule las horas, minutos y segundos dentro de su
								rango correspondiente. Por ejemplo, dadas 10 horas, 119 minutos y 280 segundos, debería dar
								como resultado 12 horas, 3 minutos y 40 segundos.
*/


#include <iostream>
using namespace std;


int main(){
	
	
	int horas, minutos , segundos , resto_segundos, resto_minutos;     //Declaracion de variables


	cout << "Introduzca un numero de horas determinado: ";
	cin >> horas;
	                                                                       
	cout << "Introduzca un numero de minutos determinado: ";
	cin >> minutos;
	
	cout << "Introduzca un numero de segundos determinado: ";
	cin >> segundos;


	resto_segundos = segundos % 60;
	segundos = segundos / 60;

   minutos += resto_segundos;
  
	
	
	cout << minutos;


		
}
