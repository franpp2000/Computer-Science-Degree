#include <iostream>
#include <iomanip>
#include <cassert>
#include <thread>
#include <mutex>
#include "HoareMonitor.h"
#include <random>

using namespace std;
using namespace HM;

constexpr int num_items = 40;
mutex mtx;
unsigned cont_prod[num_items],
				 cont_cons[num_items];

static const int num_consumidores = 5;
static const int num_productores = 5;

int vector_producidos[num_productores] = {0};

template< int min, int max > int aleatorio(){
	static default_random_engine generador((random_device())());
	static uniform_int_distribution<int> distribucion_uniforme(min, max);

	return distribucion_uniforme(generador);
}

int producir_dato(int i){

	int contador = i * (num_items / num_productores) + vector_producidos[i];
	mtx.lock();
	cout << "Producido " << contador << endl << flush;
	mtx.unlock();
	this_thread::sleep_for(chrono::milliseconds(aleatorio<20, 100>()));
	vector_producidos[i]++;
	cont_prod[contador]++;

	return contador;
}

void consumir_dato( unsigned dato ){
   if(num_items <= dato){
      cout << " dato === " << dato << ", num_items == " << num_items << endl ;
      assert( dato < num_items );
   }

   cont_cons[dato] ++ ;
   this_thread::sleep_for( chrono::milliseconds( aleatorio<20,100>() ));
   mtx.lock();
   cout << "                  consumido: " << dato << endl ;
   mtx.unlock();
}

void ini_contadores()
{
   for( unsigned i = 0 ; i < num_items ; i++ ){
   	 cont_prod[i] = 0 ;
   	 cont_cons[i] = 0 ;
   }
}

void test_contadores()
{
   bool ok = true ;
   cout << "comprobando contadores ...." << flush ;

   for( unsigned i = 0 ; i < num_items ; i++ )
   {
      if ( cont_prod[i] != 1 )
      {
         cout << "error: valor " << i << " producido " << cont_prod[i] << " veces." << endl ;
         ok = false ;
      }
      if ( cont_cons[i] != 1 )
      {
         cout << "error: valor " << i << " consumido " << cont_cons[i] << " veces" << endl ;
         ok = false ;
      }
   }
   if (ok)
      cout << endl << flush << "solución (aparentemente) correcta." << endl << flush ;
}

class ProdCons1SU: public HoareMonitor
{
 private:
 static const int           // constantes:
   num_celdas_total = 10;   //  núm. de entradas del buffer
 int                        // variables permanentes
   buffer[num_celdas_total],//  buffer de tamaño fijo, con los datos
   primera_libre,
   primera_ocupada,
   cantidad;         //  indice de celda de la próxima inserción
 mutex
   cerrojo_monitor ;        // cerrojo del monitor
 CondVar         // colas condicion:
   ocupadas,                //  cola donde espera el consumidor (n>0)
   libres ;                 //  cola donde espera el productor  (n<num_celdas_total)

 public:                    // constructor y métodos públicos
   ProdCons1SU(  ) ;           // constructor
   int  leer();                // extraer un valor (sentencia L) (consumidor)
   void escribir( int valor );
} ;

ProdCons1SU::ProdCons1SU(  )
{
   primera_libre = 0 ;
   primera_ocupada = 0;
   ocupadas = newCondVar();
   libres = newCondVar();
   cantidad = 0;
}

int ProdCons1SU::leer(  )
{
   // esperar bloqueado hasta que 0 < num_celdas_ocupadas
   if( cantidad == 0 )
      ocupadas.wait();

	 assert(cantidad > 0);
   // hacer la operación de lectura, actualizando estado del monitor
	 cantidad--;
   const int valor = buffer[primera_libre] ;
   primera_libre++;
   primera_libre %= num_celdas_total;


   // señalar al productor que hay un hueco libre, por si está esperando
   libres.signal();

   // devolver valor
   return valor ;
}

void ProdCons1SU::escribir( int valor )
{
   // esperar bloqueado hasta que num_celdas_ocupadas < num_celdas_total
   if( cantidad == num_celdas_total )
      libres.wait();

	 assert(cantidad < num_celdas_total);
   //cout << "escribir: ocup == " << num_celdas_ocupadas << ", total == " << num_celdas_total << endl ;

   // hacer la operación de inserción, actualizando estado del monitor
   cantidad++;
   buffer[primera_ocupada] = valor ;
   primera_ocupada++ ;
   primera_ocupada %= num_celdas_total;

   // señalar al consumidor que ya hay una celda ocupada (por si esta esperando)
   ocupadas.signal();
}

void funcion_hebra_productora( MRef<ProdCons1SU> monitor, int n)
{
   for( unsigned i = 0 ; i < num_items / num_productores ; i++ )
   {
      int valor = producir_dato(n) ;
      monitor->escribir( valor );
   }
}

void funcion_hebra_consumidora( MRef<ProdCons1SU> monitor, int n )
{
   for( unsigned i = 0 ; i < num_items / num_consumidores ; i++ )
   {
      int valor = monitor->leer();
      consumir_dato( valor ) ;
   }
}

int main()
{
   cout << "-------------------------------------------------------------------------------" << endl
        << "Problema de los productores-consumidores (1 prod/cons, Monitor SC, buffer FIFO). " << endl
        << "-------------------------------------------------------------------------------" << endl
        << flush ;
   
   MRef<ProdCons1SU> monitor = Create<ProdCons1SU>();     
        
   thread hebra_productora[num_productores];
   for(int i = 0; i < num_productores; i++)
     hebra_productora[i] = thread(funcion_hebra_productora, monitor, i);
     
   thread hebra_consumidora[num_consumidores];
   for(int i = 0; i < num_consumidores; i++)
     hebra_consumidora[i] = thread(funcion_hebra_consumidora, monitor, i);  
   
   for(int i = 0; i < num_consumidores; i++)
     hebra_consumidora[i].join();
     
   for(int i = 0; i < num_productores; i++)
     hebra_productora[i].join();
       
   // comprobar que cada item se ha producido y consumido exactamente una vez
   test_contadores() ;
}
