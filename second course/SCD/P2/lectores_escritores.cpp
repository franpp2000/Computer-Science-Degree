#include <iostream>
#include <iomanip>
#include <cassert>
#include <thread>
#include <mutex>
#include <random>
#include "HoareMonitor.h"

using namespace std;
using namespace HM;

const int num_lectores = 3;
const int num_escritores = 3;


//**********************************************************************
// plantilla de función para generar un entero aleatorio uniformemente
// distribuido entre dos valores enteros, ambos incluidos
// (ambos tienen que ser dos constantes, conocidas en tiempo de compilación)
//----------------------------------------------------------------------
template< int min, int max > int aleatorio(){

  static default_random_engine generador( (random_device())() );
  static uniform_int_distribution<int> distribucion_uniforme( min, max ) ;
  return distribucion_uniforme( generador );
}

void tomarLibro(){

	chrono::milliseconds duracion(aleatorio<20, 200>());
	this_thread::sleep_for(duracion);
}

//************************************************************************
// Funcion que simula la accion de escribir a traves de la implementacion
// de retardos aleatorios
//------------------------------------------------------------------------
void escribir(int num_escritor){

	chrono::milliseconds duracion_escribir(aleatorio<10, 100>());

	cout << "Escritor " << num_escritor << " empieza a escribir."
			 << " (" << duracion_escribir.count() << " milliseconds)" << endl;

	this_thread::sleep_for(duracion_escribir);

	cout << "Escritor " << num_escritor << " ha terminado de escribir" << endl;
}

//*******************************************************************
// Funcion que simula la accion de leer a traves de la implementacion
// de retardos aleatorios
//-------------------------------------------------------------------
void leer(int num_lector){

	chrono::milliseconds duracion_leer(aleatorio<20, 200>());

	cout << "Lector " << num_lector << " empieza a leer."
			 << " (" << duracion_leer.count() << " milliseconds)" << endl;

	this_thread::sleep_for(duracion_leer);

	cout << "Lector " << num_lector << " ha terminado de leer." << endl;
}

//**********************************************
// Clase de lectores y escritores (semantica SU)
//----------------------------------------------
class LectoresEscritores: public HoareMonitor{

	private:
		int n_lec; // numero de lectores leyendo
		bool escrib; // escritor escribiendo?
		CondVar lectura, // cola de espera de lectores
						escritura; // cola de espera de escritores

	public:
		LectoresEscritores();
		void ini_lectura();
		void ini_escritura();
		void fin_lectura();
		void fin_escritura();
};

//*****************************************
// Constructor de la clase (sin parametros)
//-----------------------------------------
LectoresEscritores::LectoresEscritores(){

	n_lec = 0;
	escrib = false;
	lectura = newCondVar();
	escritura = newCondVar();
}

//********************************************************
// Metodo publico por el que se ponen los lectores a leer
//--------------------------------------------------------
void LectoresEscritores::ini_lectura(){

	if(escrib) // Si hay un escritor escribiendo
		lectura.wait();

	n_lec++;

	lectura.signal(); // lectores se despiertan entre si para leer
										// (varios lectores pueden leer simultaneamente)
}

//*********************************************************
// Metodo publico por el que un escritor se pone a escribir
//---------------------------------------------------------
void LectoresEscritores::ini_escritura(){

	if(n_lec > 0 || escrib) // si hay lectores leyendo o un escritor escribiendo
		escritura.wait();

	escrib = true;
}

//************************************************************************
// Metodo publico por el que un lector termina de leer, ademas si este era
// el ultimo despierta a un lector para que escriba
//------------------------------------------------------------------------
void LectoresEscritores::fin_lectura(){

	n_lec--;

	if(n_lec == 0) // Si era el ultimo lector leyendo
		escritura.signal();
}

//***************************************************************************
// Metodo por el que un escritor termina de leer, despertando bien a lectores
// si estan esperando, o si no lo estan a otro escritor
//---------------------------------------------------------------------------
void LectoresEscritores::fin_escritura(){

	escrib = false;

	if(lectura.get_nwt() != 0) // Si hay lectores esperando para leer
		lectura.signal();
	else
		escritura.signal();
}

///////////////// FUNCIONES DE LAS HEBRAS //////////////////

void funcion_hebra_lector(MRef<LectoresEscritores> monitor, int num_lector){

	while(true){
		tomarLibro();
		monitor->ini_lectura();
		leer(num_lector);
		monitor->fin_lectura();
	}
}

void funcion_hebra_escritor(MRef<LectoresEscritores> monitor, int num_escritor){

	while(true){
		monitor->ini_escritura();
		escribir(num_escritor);
		monitor->fin_escritura();
	}
}


int main(){

	cout << "---------------- PROBLEMA LECTORES-ESCRITORES ------------------" << endl << endl;

	MRef<LectoresEscritores> monitor = Create<LectoresEscritores>();

	thread hebra_escritores[num_escritores];
	for(int i = 0; i < num_escritores; i++)
		hebra_escritores[i] = thread(funcion_hebra_escritor, monitor, i);

	thread hebra_lectores[num_lectores];
	for(int i = 0; i < num_lectores; i++)
		hebra_lectores[i] = thread(funcion_hebra_lector, monitor, i);

	for(int i = 0; i < num_escritores; i++)
		hebra_escritores[i].join();

	for(int i = 0; i < num_lectores; i++)
		hebra_lectores[i].join();
}
