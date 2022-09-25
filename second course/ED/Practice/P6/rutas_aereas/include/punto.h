#ifndef _PUNTO_
#define _PUNTO_

#include<iostream>
#include<cassert>

using namespace std;

/**
 * @brief TDA Punto
 * 
 * @page repConjunto Rep del TDA Punto
 * 
 * @section invConjunto Invariante de la representacion
 * 
 * El invariante es: -90 <= rep.latitud <= 90
 *                   -180 <= rep.longitud <= 180
 * 
 * Un objeto valido rep del TDA Punto representa el valor:
 * (rep.latitud, rep.longitud)
 */
class Punto{
  private:
    double latitud; //latitud del punto. 
    double longitud; //longitud del punto.
  
  public:
  
  /**
   * @brief Construct a new Punto object
   * 
   */
    Punto(){}

  /**
   * @brief Construct a new Punto object
   * 
   * @param latitud que tendra el punto
   * @param longitud que tendra el punto
   * 
   * @pre -90 <= latitud <= 90
   * @pre -180 <= longitud <= 180 
   */
    Punto(const double latitud, const double longitud);
  
  /**
   * @brief Constructor de copia
   * 
   * @param otro punto objeto de copia
   */
    Punto(const Punto &otro)
    :latitud(otro.latitud), longitud(otro.longitud)
    {}

  /**
   * @brief Get the Latitud object
   * 
   * @return la latitud del punto 
   */
    double GetLatitud() const;

  /**
   * @brief Get the Longitud object
   * 
   * @return la longitud del punto
   */
    double GetLongitud() const;

  /**
   * @brief Set the Latitud object
   * 
   * @param latitud que va a tener el punto
   * 
   * @pre -90 <= latitud <= 90
   */
    void setLatitud(const double latitud);

  /**
   * @brief Set the Longitud object
   * 
   * @param longitud que va a tener el punto
   * 
   * @pre -180 <= longitud <= 180 
   */
    void setLongitud(const double longitud);
    
  /**
   * @brief sobrecarga de operador de igualdad
   * 
   * @param p el punto con el que se va a comparar el objeto implicito
   * @return true si son iguales
   * @return false si no son iguales
   */
    bool operator==(const Punto &p) const;

  /**
   * @brief sobrecarga de operador de flujo de salida de datos
   * 
   * @param os flujo de salida
   * @param p punto que del que se va a mostrar los datos
   * 
   * @return el flujo de salida 
   */
    friend ostream & operator<<(ostream &os, const Punto &p);

  /**
   * @brief sobrecarga del operador de flujo de entrada de datos 
   * 
   * @param is flujo de entrada
   * @param p punto en el que se van a insertar los datos obtenidos del flujo
   * 
   * @return el flujo de entrada 
   */
    friend istream & operator>>(istream &is, Punto &p);
};

#endif  