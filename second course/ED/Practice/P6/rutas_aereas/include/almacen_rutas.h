#ifndef _ALMACEN_RUTAS_
#define _ALMACEN_RUTAS_

#include <iostream>
#include <map>
#include "ruta.h"

using namespace std;

/**
 * @brief TDA Almacen_Rutas
 * 
 * @page repConjunto Rep del TDA Almacen Rutas
 * 
 * @section invConjunto Invariate de la representacion
 * 
 * El invariante es en el rep.rutas no pueden haber elementos con clave repetida
 * 
 * Un objeto valido rep del TDA representa el valor rep.rutas
 * 
 */
class Almacen_Rutas{
  private:
    map<string, Ruta> rutas; //almacen con las rutas
    
  public:
    typedef typename map<string, Ruta>::iterator iterator;
    typedef typename map<string, Ruta>::const_iterator const_iterator;

 /**
  * @brief Construct a new Almacen_Rutas object
  * 
  */
    Almacen_Rutas(){}

  /**
   * @brief Constructor de copia
   * 
   * @param otra almacen objeto de copia
   */
    Almacen_Rutas(const Almacen_Rutas &otra)
    :rutas(otra.rutas)
    {}

 /**
  * @brief Get the Ruta object
  * 
  * @param codigo 
  * @return ruta buscada, o end() en caso negativo
  */
    Ruta GetRuta(string codigo){
      map<string, Ruta>::const_iterator it = rutas.find(codigo);

      return it->second;
    }

 /**
  * @brief inserta una ruta en su lugar correspondiente
  * 
  * @param codigo 
  * @param r 
  */
    void insertar_ruta(const Ruta r){
      rutas[r.GetCodigo()] = r;
    }

  /**
   * @brief borrar una ruta dado su codigo
   * 
   * @param codigo de la ruta
   */
    void erase(const string codigo){
      rutas.erase(codigo);
    }

  /**
   * @brief busca las rutas que pasan por una determinada posicion y lo guardan en un almacen de rutas
   * 
   * @param p posicion que se busca en las rutas
   * 
   * @return el almacen de rutas con las rutas que pasan por dicho punto
   */
    Almacen_Rutas GetRutas_Con_Punto(const Punto &p);

 /**
  * @brief sobrecarga del operador de extraccion del flujo
  * 
  * @param os flujo de salida
  * @param almacen 
  * @return el flujo de salida
  */
    friend ostream & operator<<(ostream &os, const Almacen_Rutas &almacen);

  /**
   * @brief sobrecarga del operador de insercion del flujo
   * 
   * @param is flujo de entrada
   * @param almacen 
   * @return el flujo de entrada 
   */
    friend istream & operator>>(istream &is, Almacen_Rutas &almacen);

};

#endif