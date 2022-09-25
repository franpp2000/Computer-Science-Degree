//Escribe un programa que evalúe una expresión en postfijo.

#include <iostream>
#include <stack>
#include <string>
#include <cmath>

using namespace std;

float evalua(string expresion, pair<char, float> *variables, int num_variables){

  stack<float> stk;
	float x;
  bool encontrada;
  float operando1, operando2, operacion;
  char operador;

	
  for(int i = 0; i < expresion.size(); i++){

    encontrada = false;

    for(int j = 0; j < num_variables && !encontrada; j++)
      if(variables[j].first == expresion[i]){
        encontrada = true;
        stk.push(variables[j].second);
      }  

    if(!encontrada && (expresion[i] == '+' || expresion[i] == '-' || expresion[i] == '*' || expresion[i] == '/' || expresion[i] == '^'))
    {
      operador = expresion[i];

      operando2 = stk.top();
      stk.pop();

      operando1 = stk.top();
      stk.pop();

      switch (operador)
      {
      case '+':
        operacion = operando1 + operando2;
        break;
      
      case '-':
        operacion = operando1 - operando2;
        break;

      case '*':
        operacion = operando1 * operando2;
        break;

      case '/':
        operacion = operando1 / operando2;
        break;

      case '^':
        operacion = pow(operando1, operando2);
        break;      
      }

			stk.push(operacion);
    }
    else if(!encontrada)
        exit(-1);
  }

  return stk.top();
}

int main(){

  int tam = 5;
  pair<char, float> v[tam];
  pair<char, float> valor;

  valor.first = 'a';
  valor.second = 2.0;
  v[0] = valor;

  valor.first = 'b';
  valor.second = 6.0;
  v[1] = valor;

  valor.first = 'c';
  valor.second = 3.0;
  v[2] = valor;

  valor.first = 'd';
  valor.second = 5.0;
  v[3] = valor;

  valor.first = 'e';
  valor.second = 9.0;
  v[4] = valor; 

  
  float sol = 0;
  string expresion = "";

  sol = evalua(expresion, v, tam);

  cout << sol << endl;
}
