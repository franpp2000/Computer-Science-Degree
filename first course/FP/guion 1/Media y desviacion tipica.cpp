//Ejercicio guion b)1

#include<iostream>
#include<cmath.>

using namespace std;


int main(){
	
	
	double a, b, c, media, desviacion;
	
	
	cout << "Introduzca un primer numero real: ";
	cin >> a;
	
	cout << "Introduzca un segundo numero real: ";
	cin >> b;
	
	cout << "Introduzca un tercer numero real: ";
	cin >> c;
	
	
	media = (a + b + c) / 3;
	
	desviacion = sqrt(((a - media) * (a - media) + (b - media) * (b - media) + (c - media) * (c - media))/3); 
	
	
	cout << "\nLa media aritmetica es: " << media;
	cout << "\nLa desviacion tipica es: " << desviacion;
	
	
	
	
}
