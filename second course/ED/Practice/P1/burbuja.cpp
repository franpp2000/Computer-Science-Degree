#include <iostream>
#include <ctime>// Recursos para medir tiempos
#include <cstdlib> // Para generación de números pseudoaleatorios

using namespace std;

void ordenar(int *v, int n){
  for(int i = 0; i < n-1; i++)
    for(int j = 0; j < n-i-1; j++)
      if(v[j] > v[j+1]){
         int aux = v[j];
         v[j] = v[j+1];
         v[j+1] = aux;
      }
}

void sintaxis()
{
  cerr << "Sintaxis:" << endl;
  cerr << " TAM: Tamaño del vector (>0)" << endl;
  cerr << "Se genera un vector de tamaño TAM con elementos aleatorios" << endl;
  exit(EXIT_FAILURE);
}

int main(int argc, char * argv[])
{
   // Lectura de parámetros
   if(argc!=2)
     sintaxis();

   int tam=atoi(argv[1]); // Tamaño del vector
   
   // Generación del vector aleatorio
   int *v=new int[tam];
   srand(time(0));  // Inicialización del generador de números pseudoaleatorios

   for(int i=0; i<tam; i++)
   {
     int n = rand() % tam;   
     v[i] = tam - i; // Genera un vector aleatorio
   }

   clock_t tini;
   tini=clock();  // Anotamos el tiempo de inicio

   ordenar(v,tam); //Aplicamos algoritmo

   clock_t tfin;

   tfin=clock();// Anotamos el tiempo de finalización

   // Mostramos resultado
   cout << tam << "\t" << (tfin-tini)/(double)CLOCKS_PER_SEC << endl;

   delete [] v; //Liberamos memoria
}
