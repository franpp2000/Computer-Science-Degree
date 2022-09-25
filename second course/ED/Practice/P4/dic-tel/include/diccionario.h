#ifndef _DICCIONARIO_H
#define _DICCIONARIO_H

#include <iostream>
#include <fstream>
#include <string>
#include <list>

using namespace std;

/**
  @brief struct con templates
 
  Tipo elemento que define el diccionario. T es el tipo de dato asociado a una clave que
  no se repite y list<U> es una lista de datos asociados a la clave
  de tipo T. El diccionario está ordenado de menor a mayor clave.
*/
template <typename T, typename U> 
struct data{
  T clave;
  list<U> info_asoci;
};

/**
  @brief Sobrecarga de operador <

  Compara dos struct para los que el operador < tiene sentido

  @param d1 argumento a la izda de el operador
  @param d2 argumento a la dcha de el operador
  @return true si d1 < d2, false en caso  contrario
 */
template <typename T, typename U> 
bool operator<(const data<T, U> &d1,  const data<T, U> &d2){
  if(d1.clave < d2.clave)
    return true;
  else
    return false;
}

/**
  @brief T.D.A. Diccionario
 
  @page repDiccionario Rep del TDA Diccionario
 
  @section invDiccionario Invariante de la representación
 
  El invariante es que ninguno tiene valores de struct de la lista repetidos.
 */
template <typename T, typename U>
class Diccionario{

  private:
    list<data<T, U>> datos;
    
/**
  @brief Funcion auxiliar para copiar diccionarios
  @param D: otro diccionario
*/
    void Copiar(const Diccionario<T, U> &D){
      datos.assign(D.datos.begin(), D.datos.end());
    }

/**
	@brief Funcion auxiliar para borrar un diccionario 
*/
    void Borrar(){
      datos.erase(datos.begin(), datos.end());
    }

  public:
    typedef typename list<data<T, U>>::iterator iterator;
    typedef typename list<data<T, U>>::const_iterator const_iterator;

  /**
    @brief Inicializa un iterator al comienzo de la guia
  */
    typename list<data<T, U>>::iterator begin(){
      datos.begin();
    }

  /**
    @brief Inicializa un iterator al final de la guia
  */
    typename list<data<T, U>>:: iterator end(){
      datos.end();
    }

  /**
    @brief Inicializa un iterator constante al comienzo de la guia
  */
    typename list<data<T, U>>::const_iterator cbegin(){
      datos.begin();
    }

  /**
    @brief Inicializa un iterator constante al final de la guia
  */
    typename list<data<T, U>>::const_iterator cend(){
      datos.end();
    }

  /**
    @brief Constructor por defecto 
  */
    Diccionario()
    :datos(list<data<T, U>>())
    {}

  /**
    @brief Constructor por copia 
    @param D: otro Diccionario
  */
    Diccionario(const Diccionario &D)
    {
      Copiar(D);
    }

  /**
	  @brief Destructor de la clase 
	*/
    ~Diccionario(){}

  /**
	  @brief Sobrecarga del operador de asignación 
	  @param D: Objeto del que se quiere compiar los atributos
	  @return retorna la referencia al objeto implicito
	*/
    Diccionario<T, U> & operator= (const Diccionario<T, U> &D){
      if(this != &D){
        Borrar();
        Copiar(D);
      }

      return *this;
    }

  /**
	  @brief Comprueba si una palabra se encuentra en el diccionario y escribe su posición en el iterador pasado por argumento
	  @param p: palabra del diccionario que se comprueba se esta
	  @param it_out: iterador que va a iterar sobre el diccionario
	  @return retorna true si se ha encontrado la palabra, false en caso contrario
	*/
    bool Esta_Clave(const T &p, typename list<data<T, U>>::iterator &it_out){
      if(datos.size() > 0){
        typename list<data<T, U>>::iterator it;
        for(it = datos.begin(); it != datos.end(); ++it){
          if((*it).clave == p){
            it_out = it;
            return true;
          }
          else if((*it).clave > p){
            it_out = it;
            return false;
          }
        }
      }
      else{
        it_out = datos.end();
        return false;
      }
    }

  /**
	  @brief Inserta una nueva referencia en el diccionario 
	  @param clave: palabra que va a ser insertada
	  @param info: lista con toda la información asociada a la clave 
	*/
    void Insertar(const T& clave,const list<U> &info){
      typename list<data<T,U> >::iterator it;
      if (!Esta_Clave(clave,it)){
        data<T,U> p;
        p.clave = clave;
        p.info_asoci=info;
        datos.insert(it,p);
      }
    }

  /**
	  @brief Añade una nueva informacion asociada a una clave dentro del diccionario 
	  @param s: palabra a la que va a añadirse significado
	  @param p: dato de tipo T con la informacion asociada
	*/
    void AddSignificado_Palabra(const U &s, T const &p){
      typename list<data<T,U> >::iterator it;
      if (!Esta_Clave(p,it)){
          data<T,U> d;
          d.clave = p;
          list<U> aux;
          aux.push_back(s);
          d.info_asoci = aux;
          datos.insert(it,d);
      }
      else
        (*it).info_asoci.insert((*it).info_asoci.end(), s);
    }

  /**
	  @brief Muestra la informacion asociada a una clave
	  @param p: clave de la que se quiere obtener informacion
	  @return Devuelve una lista con la información de la clave p
	*/
    list<U> getInfo_Asoc(const T &p){
      typename list<data<T, U>>::iterator it;

      if(!Esta_Clave(p, it))
        return list<U>();
      else
        return (*it).info_asoci;
    }
  
  /**
	  @brief Tamaño del diccionario 
	*/
    int size() const{
      return datos.size();
    }

  /**
	  @brief Borra las definiciones (y la palabra) de una palabra del diccionario
	  @param c: clave a eliminar
	*/
    void Elimina_Palabra(const T &c){
      typename list<data<T, U>>::iterator it;

      if(Esta_Clave(c, it))
        datos.erase(it);
    }

  /**
	  @brief Union de dos diccionarios
	  @param d: diccionario que se une
	  @return: un nuevo diccionario resultado de unir el objeto implicito y d
	*/  
    Diccionario & operator+ (const Diccionario &D){
      typename list<data<T, U>>::const_iterator it;
      for(it = D.datos.begin(); it != D.datos.end(); ++it)
        Insertar((*it).clave, (*it).info_asoci);

      return *this;  

    }

  /**
    @brief Invierte el orden del diccionario
  */ 
    void Invierte_Diccionario(){
			datos.reverse();
		}

  /**
    @brief Ordena el diccionario (por si se aplicado Invierte_Diccionario)
  */ 
    void Ordena_Diccionario(){
      datos.sort();
    }
  
  /**
    @brief sobrecarga de flujo de entrada
    @param is flujo de entrada
    @param D Diccionario al que se le va a introducir datos
    @return flujo de entrada 
  */
    template <typename sT, typename sU>
    friend istream & operator>> (istream & is, Diccionario<sT, sU> &D){

      int np;
      is >> np;
      is.ignore();

      Diccionario<sT,sU> Daux;

      for(int i = 0; i < np; i++){
        string c;
        getline(is, c);

        int ns;
        is >> ns;
        is.ignore();

        list<sU> laux;
        for(int j = 0; j < ns; j++){
          string s;
          getline(is, s);

          laux.insert(laux.end(), s);
        }
        Daux.Insertar(c, laux);
      }

      D = Daux;

      return is;
    }
  
  /**
    @brief sobrecarga de flujo de salida
    @param is flujo de salida
    @param D Diccionario del que se va a mostrar datos
    @return flujo de salida
  */
    template <typename sT,typename sU>
    friend ostream & operator<< (ostream & os, const Diccionario<sT, sU> &D){
      
      typename list<data<sT, sU>>::const_iterator it;
      for(it = D.datos.begin(); it != D.datos.end(); ++it){
        os << endl << (*it).clave << endl;
        os << "Definiciones:" << endl;

        typename list<sU>::const_iterator it_s;
        for(it_s = (*it).info_asoci.begin(); it_s != (*it).info_asoci.end(); ++it_s)
          os << *it_s << endl;
      }

      return os;

    }
	
};

#endif