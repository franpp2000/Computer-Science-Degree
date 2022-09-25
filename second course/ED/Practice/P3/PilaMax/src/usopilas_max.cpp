#include <iostream>
#include "pila_max.h"

using namespace std;

int main(){
    PilaMax p;

    p.push(3);
    p.push(0);

    int i;
    for ( i=10; i>=0 ; i--)
    p.push(i);


    while (!p.empty())
    {
        Elemento x = p.top();
        cout << x << endl;
        p.pop();
    }

    return 0;
}
