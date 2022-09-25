#include <iostream>
#include <map>
#include "bintree.h"

using namespace std;

double evaluar(bintree<char>::node n, const bintree<char> &arb, const map<char, double> &valores){
  double operando_izda = 0, operando_dcha = 0, result = 0;
  char caracter;

  if(!n.null()){
    caracter = *n;

    if(valores.find(caracter) == valores.cend()){
      operando_izda = evaluar(n.left(), arb, valores);
      operando_dcha = evaluar(n.right(), arb, valores);

      switch (caracter){
        case '+':
          result += operando_izda + operando_dcha;
        break;

        case '-':
          result += operando_izda - operando_dcha;
        break;

        case '*':
          result += operando_izda * operando_dcha;
        break;

        case '/':
          result += operando_izda / operando_dcha;
        break;
      }
    }
    else{
      return valores.at(caracter);
    }
  }

  return result;
}

int main(){

  map<char, double> valores;
  valores['e'] = 1;
  valores['f'] = 2;
  valores['a'] = 3;
  valores['b'] = 4;
  valores['c'] = 1;

  bintree<char> a('+');
  
  a.insert_left(a.root(), '+');
  a.insert_left(a.root().left(), '+');
  a.insert_right(a.root().left(), 'a');
  a.insert_left(a.root().left().left(), 'e');
  a.insert_right(a.root().left().left(), 'f');

  a.insert_right(a.root(), '/');
  a.insert_left(a.root().right(), 'b');
  a.insert_right(a.root().right(), 'c');

  double result = evaluar(a.root(), a, valores);

  cout << result << endl;
}