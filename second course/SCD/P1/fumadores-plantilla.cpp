#include <iostream>
#include <cassert>
#include <thread>
#include <mutex>
#include <random> // dispositivos, generadores y distribuciones aleatorias
#include <chrono> // duraciones (duration), unidades de tiempo
#include "Semaphore.h"

using namespace std ;
using namespace SEM ;


const int num_fumadores = 3;     //numero de fumadores
Semaphore mostr_vacio = 1;    //semaforo que informa si en el mostrador hay disponible un ingrediente
Semaphore fumador[num_fumadores] = {0, 0, 0};    //vector de semaforos de fumadores

//**********************************************************************
// plantilla de función para generar un entero aleatorio uniformemente
// distribuido entre dos valores enteros, ambos incluidos
// (ambos tienen que ser dos constantes, conocidas en tiempo de compilación)
//----------------------------------------------------------------------
template< int min, int max > int aleatorio()
{
  static default_random_engine generador( (random_device())() );
  static uniform_int_distribution<int> distribucion_uniforme( min, max ) ;
  return distribucion_uniforme( generador );
}

//-------------------------------------------------------------------------
// Función que simula la acción de producir un ingrediente, como un retardo
// aleatorio de la hebra (devuelve número de ingrediente producido)
int producir_ingrediente()
{
   // calcular milisegundos aleatorios de duración de la acción de fumar)
   chrono::milliseconds duracion_produ( aleatorio<10,100>() );

   // informa de que comienza a producir
   cout << "Estanquero : empieza a producir ingrediente (" << duracion_produ.count() << " milisegundos)" << endl;

   // espera bloqueada un tiempo igual a ''duracion_produ' milisegundos
   this_thread::sleep_for( duracion_produ );

   const int num_ingrediente = aleatorio<0,num_fumadores-1>() ;

   // informa de que ha terminado de producir
   cout << "Estanquero : termina de producir ingrediente " << num_ingrediente << endl;

   return num_ingrediente ;
}

//----------------------------------------------------------------------
// función que ejecuta la hebra del estanquero
void funcion_hebra_estanquero()
{
  while(true){
    int i = producir_ingrediente(); //producir ingrediente i.

    sem_wait(mostr_vacio); //mostrador vacio?

    cout << "Ingrediente " << i << " puesto en el mostrador.\n";

    sem_signal(fumador[i]); //señalizacion a fumador[i] de que su ingrediente
                            //esta disponible
  }
}

//-------------------------------------------------------------------------
// Función que simula la acción de fumar, como un retardo aleatoria de la hebra
void fumar( int num_fumador )
{

   // calcular milisegundos aleatorios de duración de la acción de fumar)
   chrono::milliseconds duracion_fumar( aleatorio<20,200>() );

   // informa de que comienza a fumar
    cout << "Fumador " << num_fumador << "  :"
          << " empieza a fumar (" << duracion_fumar.count() << " milisegundos)" << endl;

   // espera bloqueada un tiempo igual a ''duracion_fumar' milisegundos
   this_thread::sleep_for( duracion_fumar );

   // informa de que ha terminado de fumar
    cout << "Fumador " << num_fumador << "  : termina de fumar, comienza espera de ingrediente." << endl;
}

//----------------------------------------------------------------------
// función que ejecuta la hebra del fumador
void  funcion_hebra_fumador( int num_fumador )
{
   while( true )
   {
     sem_wait(fumador[num_fumador]); //esta ingrediente de fumador[num_fumador] disponible?

     cout << "Retirado ingrediente numero " << num_fumador << "\n";

     sem_signal(mostr_vacio); //señalizacion a estanquero de que puede poner un
                              //ingrediente en la mesa

     fumar(num_fumador); //fumador[num_fumador] fuma
   }
}

//----------------------------------------------------------------------

int main()
{
   // declarar hebras y ponerlas en marcha
   // ......

   thread hebra_estanquero(funcion_hebra_estanquero); //lanzo hebra estanquero
   thread hebra_fumador[num_fumadores];//declaro vector de hebras de fumadores

   for(int i = 0; i < num_fumadores; i++) //lanzo hebras de fumadores
     hebra_fumador[i] = thread(funcion_hebra_fumador, i);

   hebra_estanquero.join(); //finalizo hebra estanquero

   for(int i = 0; i < num_fumadores; i++) //finalizo hebras de fumadores
     hebra_fumador[i].join();

}