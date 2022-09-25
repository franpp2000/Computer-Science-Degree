#include <iostream>
#include <string>
#include <queue>
#include <cstring>

using namespace std;

struct compStrings{
  bool operator()(const string &s1, const string &s2){
    if(s1.size() < s2.size())
      return true;
    else if(s2.size() < s1.size())
      return false;
    else
      return s1 > s2;    
  }
};

int main(){

  priority_queue<string, vector<string>, compStrings> cadenas;

  cadenas.push("olas");
  cadenas.push("a");
  cadenas.push("hola");
  cadenas.push("zzzzzzzzzzy");
  cadenas.push("zzzzzzzzzzz");

  while(!cadenas.empty()){
    cout << cadenas.top() << endl;
    cadenas.pop();
  }
}