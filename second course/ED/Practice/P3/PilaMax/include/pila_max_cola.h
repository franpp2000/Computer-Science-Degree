/**
 * @file pila_max_cola.h
 * @brief Fichero cabecera del TDA Pila
 *
 * Gestiona una secuencia de elementos con facilidades para la inserción y
 * borrado de elemento
 *
 */
#ifndef __PilaMax_Cola__
#define __PilaMax_Cola__

#include <cassert>
#include <iostream>
#include "cola.h"

using namespace std;

/**
  * @brief struct Elemento
  * 
  * Una instancia del tipo Elemento es un elemento formado por el valor
  * asociado dicho elemento y el máximo de los valores de todos las Elementos
  * almacenados
  */
struct Elemento{
  /**
    * @page repConjunto Representativo del struct Elemento
    *
    */
  int valor = 0; /**< valor del elemento */
  int max = 0;   /**< valor máximo almacenado en la pila */
};

/**
  * @brief Sobrecarga del operador <<
  * @param os Flujo de salida
  * @param e Elemento que se quiere escribir
  */
ostream & operator << (ostream &, const Elemento &);

/**
 *  @brief T.D.A. PilaMax
 *
 * Una instancia del tipo de dato abstracto PilaMax es
 * una lista de elementos con un funcionamiento LIFO (Last In,
 * First Out). Una pila de longitud @e n la representamos como:
 *
 * - [a1,a2,a3,..,an>
 *
 * donde @e ai es el elemento de la posición i-ésima.
 *
 * En esta pila, tendremos acceso únicamente al elemento del @e tope, es decir,
 * a @e an. El borrado o consulta de un elemento será sobre dicho @e tope, y la
 * inserción de un nuevo elemento se hará sobre éste, quedando el elemento
 * insertado como @e tope de la pila.
 *
 * Si @e n=0 representa que la pila está vacía.
 *
 * Esta Pila almacena datos de tipo @e Elemento de @b valor | @b max, donde máximo
 * denota el valor máximo de los elementos inferiores en la Pila. Esto permite
 * conocer el máximo de los valores de la pila en todo momento.
 *
 * Internamente dicha pila esta representada como una cola, donde hemos
 * situado el tope de la Pila en el frente de la Cola. Esto hace fácil la
 * operación de pop, pero complica el push.
 */
class PilaMax{
  private:
  /**
     * @page repConjunto Representativo del TDA PilaMax
     *
     */
  Cola<Elemento> cola; /**< Cola con elementos del tipo Elemento*/

  public:
  
  /**
   * @brief Constructor por defecto
   */
  PilaMax()
  :cola()
  {}

  /**
   * @brief Constructor de copia
   * @param orig pila de la que se hará la copia. 
   */
  PilaMax(const PilaMax &);

  /**
   * @brief Sobrecarga del operador de asignación
   * @param otra La pila que se va a asignar.
   * @pre la pila a la que se asigna el objeto asignado no
   * puede ser el mismo
   */
  PilaMax & operator= (const PilaMax &);

  /**
   * @brief Comprueba si la pila está vacía
   * @return true si esta vacia, false en caso contrario
   */
  bool empty() const;

  /**
   * @brief Devuelve el elemento del tope de la pila
   * @pre la pila debe contener al menos un elemento
   * @return el elemento tope de la pila
   */
  Elemento & top();

  /**
   * @brief Devuelve el elemento del tope de una pila constante
   * @pre la pila debe contener al menos un elemento
   * @return el elemento tope de la pila
   */
  const Elemento & top() const;

  /**
   * @brief Añade un elemento "encima" del tope de la pila, conviertiendose
   * este ahora en el tope de la pila
   * @param n Elemento que se va a añadir.
   */
  void push(const int &);

  /**
   * @brief Quita el elemento del tope de la pila, siendo ahora el tope
   * de la pila el que habia añadido antes del que que se ha quitado
   *
   * @pre la pila debe poseer al menos un elemento    
   */
  void pop();

  /**
   * @brief Devuelve el número de elementos de la pila
   * @return el tamaño de la pila
   */
  int size() const;

  /**
   * @brief Devuelve el valor máximo almacenado en la pila
   * @pre debe haber al menos un elemento en la pila, en caso
   * contrario devolvera el minimo valor int posible
   * 
   * @return el maximo de los valores de la pila
   */
  int maximo() const;
};

#endif // __PilaMax_Cola__
