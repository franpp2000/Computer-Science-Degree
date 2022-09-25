#include <iostream>
#include <cassert>
#include <thread>
#include <mutex>
#include <random>
#include "Semaphore.h"

using namespace std ;
using namespace SEM ;

//**********************************************************************
// variables compartidas

const int num_items = 40 ,   // número de items
	  tam_vec   = 10 ;   // tamaño del buffer

unsigned  cont_prod[num_items] = {0}, // contadores de verificación: producidos
          cont_cons[num_items] = {0}; // contadores de verificación: consumidos

int buffer[tam_vec]; //vector de variables compartidas

Semaphore puedo_escribir = tam_vec; //Semaforo que muestra el numero de posiciones del buffer donde
                                    //escribir un dato sin que se pierda otro sin ser consumido

Semaphore puedo_leer = 0; //Semaforo que muestra el numero de posiciones del buffer donde se puede
                          //leer un dato que no se ha consumido aun

int ocupado = 0, //posicion de primera posicion ocupada
    libre = 0; //posicion de primera posicion libre

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

//**********************************************************************
// funciones comunes a las dos soluciones (fifo y lifo)
//----------------------------------------------------------------------

int producir_dato()
{
   static int contador = 0 ;
   this_thread::sleep_for( chrono::milliseconds( aleatorio<20,100>() ));

   cout << "producido: " << contador << endl << flush ;

   cont_prod[contador] ++ ;
   return contador++ ;
}
//----------------------------------------------------------------------

void consumir_dato( unsigned dato )
{
   assert( dato < num_items );
   cont_cons[dato] ++ ;
   this_thread::sleep_for( chrono::milliseconds( aleatorio<20,100>() ));

   cout << "                  consumido: " << dato << endl ;

}


//----------------------------------------------------------------------

void test_contadores()
{
   bool ok = true ;
   cout << "comprobando contadores ...." ;
   for( unsigned i = 0 ; i < num_items ; i++ )
   {  if ( cont_prod[i] != 1 )
      {  cout << "error: valor " << i << " producido " << cont_prod[i] << " veces." << endl ;
         ok = false ;
      }
      if ( cont_cons[i] != 1 )
      {  cout << "error: valor " << i << " consumido " << cont_cons[i] << " veces" << endl ;
         ok = false ;
      }
   }
   if (ok)
      cout << endl << flush << "solución (aparentemente) correcta." << endl << flush ;
}

//----------------------------------------------------------------------

void  funcion_hebra_productora(  )
{
   for( unsigned i = 0 ; i < num_items ; i++ )
   {
      int dato = producir_dato(); //produzco dato

      sem_wait(puedo_escribir); //tengo donde escribir un dato?

      buffer[libre] = dato; //escribo en la primera posicion libre
      libre += 1; //actualizo primera posicion libre
      libre %= tam_vec; //por si llego a final del vector, vuelvo al principio

      sem_signal(puedo_leer); //señalizo a hebra consumidora que hay un dato que se puede consumir
   }
}

//----------------------------------------------------------------------

void funcion_hebra_consumidora(  )
{
   for( unsigned i = 0 ; i < num_items ; i++ )
   {
      int dato ;

      sem_wait(puedo_leer); //hay datos que consumir?

      dato = buffer[ocupado]; //me hago con el dato
      ocupado += 1; //actualizo primera posicion ocupada
      ocupado %= tam_vec; //por si llego al final del vector, vuelvo al principio

      sem_signal(puedo_escribir); //señalizo a hebra productora de que puede escribir un dato

      consumir_dato( dato ) ; //consumo dato
    }
}
//----------------------------------------------------------------------

int main()
{
   cout << "--------------------------------------------------------" << endl
        << "Problema de los productores-consumidores (solución FIFO)." << endl
        << "--------------------------------------------------------" << endl
        << flush ;

   thread hebra_productora ( funcion_hebra_productora ),
          hebra_consumidora( funcion_hebra_consumidora );

   hebra_productora.join() ;
   hebra_consumidora.join() ;

  cout << endl << "\tFIN" << endl << endl;

   test_contadores();
}
