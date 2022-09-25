#include <iostream>
#include <stack>
#include <string>

using namespace std;

template <typename T> void modificar(stack<T> &P, const T &x, const T &y){

	stack <T> aux;

	while(!P.empty()){

		if(P.top() == x)
			aux.push(y);
		else
			aux.push(P.top());

		P.pop();
	}

	while(!aux.empty()){

		P.push(aux.top());
		aux.pop();
	}
}

int main(){

	int x = 0, y = 1, elemento;
	int n;
	stack <int> P;

	cout << "Elementos a insertar en la pila: ";
	cin >> n;

	for(int i = 0; i < n ; i++){

		cout << "\nElemento a insertar: ";
		cin >> elemento;

		P.push(elemento);
	}

	cout << "\nPila antes de modificar: " << endl;

	modificar(P, x, y);

	cout << "\nPila modificada:" << endl;

	while(!P.empty()){

		cout << " " << P.top() << endl;
		P.pop();
	}

	return 0;
}
