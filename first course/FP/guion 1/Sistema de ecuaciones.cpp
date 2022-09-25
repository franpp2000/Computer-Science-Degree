//Ejercicio guion b)5


#include<iostream>


using namespace std;


int main(){
	
	
	double a, b, c, d, e, f, x, y;
	
	
	cout << "Vamos a resolver un sistema de ecuaciones del tipo:" << endl << endl << "ax + by = c" << endl << "dx + ey = f";
	cout << "\n\nA continuacion se le pedira los valores de a, b, c, d, e, f";
	
	cout << "\n\na = ";
	cin >> a; 
	
	cout << "b = ";
	cin >> b; 
	
	cout << "c = ";
	cin >> c;
	
	cout << "d = ";
	cin >> d;
	
	cout << "e = ";
	cin >> e;
	
	cout << "f = ";
	cin >> f; 
	
	
	x = (e * c - f * b) / (e * a - b * d);
	
	y = (c - a * x) / (b);
	
	cout << "\nx = " << x;
	cout << "\ny = " << y;
	
	
}
