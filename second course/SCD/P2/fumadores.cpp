#include <iostream>
#include <iomanip>
#include <cassert>
#include <thread>
#include <mutex>
#include <random>
#include "HoareMonitor.h"

using namespace std;
using namespace HM;

constexpr int num_items = 40; // numero de items a consumir

const int num_fumadores = 3;
mutex mtx;

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

class Estanco: public HoareMonitor{

	private:
		int ingrediente;  //ingrediente i consumido por el fumador i
		CondVar estanquero,  // cola donde espera el productor a que el ingrdiente sea consumido
						fumadores[num_fumadores];  // cola donde esperan los fumadores por su ingrediente

	public:
		Estanco();
		void obtenerIngrediente(int i);
		void ponerIngrediente(int i);
		void esperarRecogidaIngrediente();
};

// Constructor de la clase (Sin parametros)
Estanco::Estanco(){
	ingrediente = -1;  // valor fuera de rango

	estanquero = newCondVar();

	for(int y = 0; y < num_fumadores; y++)
		fumadores[y] = newCondVar();
}

// Metodo por el que los fumador i toma el ingrediente i del mostrador
void Estanco::obtenerIngrediente(int i){

	if(ingrediente != i)  // Si no le corresponde el ingrediente
		fumadores[i].wait();

	ingrediente = -1;  // Toma el ingrediente

	estanquero.signal();  // Avisa al estanquero de que el mostrador esta vacio
}

//Metodo por el que el estanquero coloca un ingrediente en el mostrador
void Estanco::ponerIngrediente(int i){

	ingrediente = i;  // Coloca el ingrediente

	fumadores[i].signal();  // Avisa al fumador correspondiente de que su ingrediente esta listo
}

void Estanco::esperarRecogidaIngrediente(){

	if(ingrediente != -1)  // Si no esta el mostrador libre
		estanquero.wait();
}


////////////// FUNCIONES DE LAS HEBRAS /////////////////

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

void funcion_hebra_fumador(MRef<Estanco> monitor, int i){

	while(true){
		monitor->obtenerIngrediente(i);
		fumar(i);
	}
}

void funcion_hebra_estanquera(MRef<Estanco> monitor){

	while(true){
		int ingrediente = producir_ingrediente();
		monitor->ponerIngrediente(ingrediente);

		mtx.lock();
		cout << "Puesto el ingrediente: " << ingrediente << endl << flush;
		mtx.unlock();

		monitor->esperarRecogidaIngrediente();
	}
}

////////////////////////////////////////////////////////

int main(){

	cout << "----------------- PROBLEMA DE LOS FUMADORES --------------------" << endl << flush;

	MRef<Estanco> monitor = Create<Estanco>();

	thread hebra_estanquero(funcion_hebra_estanquera, monitor);

	thread hebra_fumadores[num_fumadores];
	for(int i = 0; i < num_fumadores; i++)
		hebra_fumadores[i] = thread(funcion_hebra_fumador, monitor, i);

	hebra_estanquero.join();
	
	for(int i = 0; i < num_fumadores; i++){
		hebra_fumadores[i].join();
	}

}
