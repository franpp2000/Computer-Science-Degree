#include <iostream>
#include <ctype.h>
#include <stack>
#include <queue>
#include <string>

using namespace std;

bool palindromo(string cadena){

  queue<char> q;
  stack<char> stk;
  string sin_espacios;

  for(int i = 0; i < cadena.size(); i++){
    if(cadena[i] != ' '){
      cadena[i] = tolower(cadena[i]);
      sin_espacios.push_back(cadena[i]);
    }
  }

  for(int i = 0; i < sin_espacios.size(); i++){
    q.push(sin_espacios[i]);
    stk.push(sin_espacios[i]);
  }

  bool coinciden = true;

  for(int i = 0; i < sin_espacios.size() / 2 + 1 && coinciden; i++){
    coinciden = (stk.top() == q.front());
    stk.pop();
    q.pop();
  }

  return coinciden;
}

int main(){
  string cadena = "Yo dono Rosas oro no doy";

  bool es_palindromo = palindromo(cadena);

  if(es_palindromo)
    cout << "\nEs Palindromo" << endl;
  else
    cout << "\nNo es Palindromo" << endl;
  
}
