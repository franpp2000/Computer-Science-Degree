#include <iostream>
#include <queue>
#include <string>
#include <stack>

using namespace std;


bool parentizada(const string s){
  stack<char> stk;
  bool ok = true;

  for(int i = 0; i < s.size() && ok; i++){
    if(s[i] == '(')
      stk.push(s[i]);
    else if(s[i] == ')'){
      if(!stk.empty())
        stk.pop();
      else
        ok = false;
    }    
  }

  if(!stk.empty() && ok)
    ok = false;

  return ok;  
}

int main() {
  string expresion = "(())()";

  bool bien_parentizada = parentizada(expresion);

  if(bien_parentizada)
    cout << "Bien parentizada" << endl;

  else
    cout << "Mal parentizada" << endl; 
}