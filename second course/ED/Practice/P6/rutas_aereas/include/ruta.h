#ifndef _RUTA_
#define _RUTA_

#include <iostream>
#include <list>
#include "punto.h"

using namespace std;

/**
 * @brief TDA Ruta
 * 
 * @page repConjunto Rep del TDA Ruta
 * 
 * @section invConjunto Invariante de la representacion
 * 
 * El invariante es que solo se puede acceder a los elementos comprendidos entre rep.puntos.begin() y el anterior de rep.puntos.end()
 * 
 * Un objeto valido rep del TDA Ruta representa el valor
 * 
 * (rep.codigo, rep.puntos)
 */
class Ruta{
  private:
    string codigo; // codigo de la ruta
    list<Punto> puntos; // lista de puntos por los que pasa la ruta

  public:
    typedef typename list<Punto>::iterator iterator;
    typedef typename list<Punto>::const_iterator const_iterator;

  /**
   * @brief Construct a new Ruta object
   * 
   */
    Ruta(){}

  /**
   * @brief Construct a new Ruta object
   * 
   * @param codigo codigo de la ruta 
   */
    Ruta(const string codigo)
    :codigo(codigo)
    {}

  /**
   * @brief Constructor de copia
   * 
   * @param otra ruta objeto de copia
   */
    Ruta(const Ruta & otra)
    :codigo(otra.codigo), puntos(otra.puntos)
    {}

  /**
   * @brief devuelve el codigo de la ruta
   * 
   * @return string 
   */
    string GetCodigo() const{
      return codigo;
    }

  /**
   * @brief Set the Codigo object
   * 
   * @param codigo 
   */
    void SetCodigo(const string codigo){
      this->codigo = codigo;
    }

  /**
   * @brief añade al final del la lista un nuevo punto
   * 
   * @param p Punto a añadir
   */
    void push_back(const Punto &p){
      puntos.push_back(p);
    }
    
  /**
   * @brief inserta un punto en una posicion dada
   * 
   * @param it iterador de la posicion donde se quiere insertar
   * @param p punto a insertar
   * @return el iterador que apunta a dicho punto 
   */
    iterator insert(iterator it, const Punto &p){
      return puntos.insert(it, p);
    }

  /**
   * @brief elimina un punto dada su posicion
   * 
   * @param it iterador que apunta a la posicion de dicho punto
   * @return iterator que apunta al punto que estaba en la posicion siguiente al borrado
   */
    iterator erase(iterator it){
      return puntos.erase(it);
    }

  /**
   * @brief sobrecarga del operador []
   * 
   * @param n posicion a la que se pretende acceder
   * @return Referencia al objeto que reside en dicha posicion
   */
    Punto & operator[](int n);

  /**
   * @brief devuelve el tamaño de la lista de puntos
   */
    int size() const{
      return puntos.size();
    }

  /**
   * @brief devuelve el iterador que apunta al primer objeto de la lista de puntos. NO CONST
   */
    iterator begin(){
      return puntos.begin();
    }

  /**
   * @brief devuelve el iterador que apunta a la siguiente posicion tras el ultimo punto de la listas de punto .NO CONST
   */
    iterator end(){
      return puntos.end();
    }

  /**
   * @brief devuelve el iterador que apunta al primer objeto de la lista de puntos. CONST
   */
    const_iterator cbegin() const{
      return puntos.cbegin();
    }

  /**
   * @brief devuelve el iterador que apunta a la siguiente posicion tras el ultimo punto de la listas de punto . CONST
   */
    const_iterator cend() const{
      return puntos.cend();
    }

  /**
   * @brief sobrecarga del operador del flujo de salida
   * 
   * @param os flujo de salida
   * @param r ruta a mostrar
   * 
   * @return el flujo de salida
   */
    friend ostream & operator<<(ostream &os, const Ruta &r);

  /**
   * @brief sobrecarga del operador del flujo de entrada
   * 
   * @param is flujo de entrada
   * @param r ruta el la que se va a insertar los datos extraidos del flujo
   * @return el flujo de entrada
   */
    friend istream & operator>>(istream &is, Ruta &r);
};

#endif