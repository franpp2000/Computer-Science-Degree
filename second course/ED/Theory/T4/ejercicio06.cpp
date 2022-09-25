/*
  ARBOL BINARIO

  BASANDOME EN ESTE MISMO ALGORITMO HE DISEÑADO LA SOLUCION EN CODIGO.

  G EAIB MCLDFKJH (pre)
  IABE G LDCFMKHJ (ino)

  izda G:

  E AIB (pre)
  IAB E (ino)

  A IB (pre)
  I A B (ino)

  dcha G:

  M CLDFKJH (pre)
  LDCF M KHJ (ino)

  C LDF (pre)    K JH (pre)
  LD C F (ino)   K HJ (ino)

  L D (pre)           J H (pre)
  L D (ino)          H J (ino)

                  G
               /      \
              E        M
             /        /  \
            A        C    K
          /   \     / \    \
         I     B   L   F    J
                    \      /
                     D    H

  Postorden: IBAEDLFCHJKMG.                  
*/

#include <iostream>
#include <string>
#include "bintree.h"

using namespace std;

string postorden(string preorden, string inorden){

  string result;
  string aux1, aux2;
  int raiz;

  //Buscamos la raiz en el recorrido inorden
  bool fin = false;
  for(int i = 0; i < inorden.size() && !fin; i++)
    if(inorden[i] == preorden[0]){
      raiz = i;
      fin = true;
    }

  //Si la raiz tiene hijos a la izda
  if(raiz != 0){
    aux1 = preorden.substr(1, raiz);
    aux2 = inorden.substr(0, raiz);

    result += postorden(aux1, aux2);
  }
  
  //Si la raiz tiene hijos a la dcha
  if(raiz != inorden.size() - 1){
    aux1 = preorden.substr(raiz + 1, preorden.size() - 1);
    aux2 = inorden.substr(raiz + 1, inorden.size() - 1);

    result += postorden(aux1, aux2);
  }

  //insertamos al final la raiz
  result += preorden[0];

  return result;
}

int main(){

  string postorden_arbol = postorden("GEAIBMCLDFKJH", "IABEGLDCFMKHJ");

  cout << postorden_arbol << endl;
}
