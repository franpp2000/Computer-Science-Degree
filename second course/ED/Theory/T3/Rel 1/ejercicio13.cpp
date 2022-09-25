#include <iostream>
#include <queue>
#include <string>

using namespace std;

struct CompareS{
  bool operator()(const string &s1, const string &s2){

    int cont1 = 0, cont2 = 0;

    for(int i = 0; i < s1.size(); i++)
      if(s1[i] == 'a' || s1[i] == 'e' || s1[i] == 'i' || s1[i] == 'o' || s1[i] == 'u')
        cont1++;

    for(int i = 0; i < s2.size(); i++)
      if(s2[i] == 'a' || s2[i] == 'e' || s2[i] == 'i' || s2[i] == 'o' || s2[i] == 'u')
        cont2++;

    if(cont1 < cont2)
      return true;
    else if(cont1 == cont2){
      return s1 > s2;
    }
    else
      return false;         
  }
};

int main(){
  priority_queue<string, vector<string>, CompareS> stk;

  stk.push("caillou");
  stk.push("hola");
  stk.push("adios");
  stk.push("rosa");

  cout << endl;

  while(!stk.empty()){
    cout << stk.top() << endl;
    stk.pop();
  }

}
