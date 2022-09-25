#ifndef _GUIA_TLF_H
#define _GUIA_TLF_H

#include <map>
#include <iostream>
#include <string>

using namespace std;

/**
  @brief Lectura de un contacto de la guia
  @param is flujo de entrada
  @param d contacto a insertar
  @return retorna el flujo de entrada 
 */
istream & operator>>(istream &is, pair<string, string> &d);

/**
  @brief Obtiene el primer digito de un numero de telefono
  @param numero: numero de telefono del que se quiere obtener el digito
 */
char obtiene_Primer_Digito(const string &numero);

/**
  @brief Obtiene la primera letra de un nombre pasado como parametro
  @param nombre: nombre del que se quiere obtener la inicial
 */
char obtiene_Inicial(const string &nombre);

/**
  @brief T.D.A. Guia_Tlf
 
  @page repGuia_Tlf Rep del TDA Guia_Tlf
 
  @section invGuia_Tlf Invariante de la representación
 
  El invariante es el propio de un map, es decir que los datos que lo contienen no se pueden repetir.
 */
class Guia_Tlf{
  private:
    map<string, string> datos;

  public:
    typedef typename map<string, string>::iterator iterator;
    typedef typename map<string, string>::const_iterator const_iterator;
  
  /**
	  @brief Inicializa un iterator al comienzo de la guia
	*/
    typename map<string, string>::iterator begin(){
      datos.begin();
    }

  /**
	  @brief Inicializa un iterator al final de la guia
	*/
    typename map<string, string>::iterator end(){
      datos.end();
    }

  /**
	  @brief Inicializa un iterator constante al comienzo de la guia
	*/
    typename map<string, string>::const_iterator cbegin(){
      datos.begin();
    }

  /**
	  @brief Inicializa un iterator constante al final de la guia
	*/
    typename map<string, string>::const_iterator cend(){
      datos.end();
    }

  /**
    @brief Acceso a un elemento
    @param nombre: nombre del elemento  elemento acceder
    @return devuelve el valor asociado a un nombre, es decir el telÃ©fono
  */
    string & operator[](const string &nombre){
      return datos[nombre];
    }

  /**
    @brief Devuelve el numero de telefono de una persona de la guia
    @param nombre: nombre de la persona de la que se quiere obtener el telefono
    @return devuelve el numero de telefono asoiciado a la persona
  */
    string gettelefono(const string &nombre);

  /**
    @brief Insert un nuevo telefono 
    @param nombre: nombre clave del nuevo telefono
    @param tlf: numero de telefono
    @return : un pair donde first apunta al nuevo elemento insertado y bool es true si se ha insertado el nuevo tlf o false en caso contrario
  */  
    pair<map<string, string>::iterator, bool> insert(string nombre, string tlf);

  /**
    @brief Insert un nuevo telefono 
    @param p: pair con el nombre y el telefono asociado
    @return : un pair donde first apunta al nuevo elemento insertado y bool es true si se ha insertado el nuevo tlf o false en caso contrario
  */  
    pair<map<string, string>::iterator, bool> insert(pair<string, string> p);

  /**
    @brief Borrar un telefono
    @param nombre: nombre que se quiere borrar
    @note: en caso de que fuese un multimap borraria todos con ese nombre
  */  
    void borrar(const string &nombre);

  /**
    @brief Borrar un telefono
    @param nombre: nombre que se quiere borrar y telefono asociado
    @note: esta funcion nos permite borrar solamente aquel que coincida en nombre y tlf
  */  
    void borrar(const string &nombre, const string &tlf);

  /**
    @brief  Numero de telefonos 
    @return el numero de telefonos asociados
  */
    int size()const{
      return datos.size();
    }

  /**
    @brief Contabiliza cuantos telefonos tenemos asociados a un nombre
    @param nombre: nombre sobre el que queremos consultar
    @return numero de telefonos asociados a un nombre
  */
    unsigned int contabiliza(const string &nombre){
      return datos.count(nombre);
    }

  /**
    @brief Limpia la guia
  */
    void clear(){
      datos.clear();
    }

  /**
    @brief Union de guias de telefonos
    @param g: guia que se une
    @return: una nueva guia resultado de unir el objeto al que apunta this y g
  */
    Guia_Tlf operator+(const Guia_Tlf &g);

  /**
    @brief Diferencia de guias de telefonos
    @param g: guia que se une
    @return: una nueva guia resultado de la diferencia del objeto al que apunta this y g
  */  
    Guia_Tlf operator-(const Guia_Tlf &g);

  /**
    @brief Recopila todos los contactos cuyo nombre empieza la letra pasada como parametro
    @param letra: letra por la que empieza el nombre de los contactos buscados
    @return: retorna una guia con los contactos buscados.
  */  
    Guia_Tlf buscar_Por_Inicial(char letra);

  /**
    @brief combia el numero asociado a un cierto contacto de la guia
    @param nombre: nombre del contacto al que se le quiere cambiar el numero
    @param nuevo_numero: numero que se quiere asociar a dicho contacto
   */  
    bool cambia_Numero_Telefono(string nombre, string nuevo_numero);

  /**
    @brief busca constacto que coincide con un cierto numero de telefono
    @param n el telefono del contacto a buscar
    @return el contacto con su nombre y telefono 
   */   
    pair<string, string> buscar_Por_Numero(string n);

  /**
    @brief Escritura de la guia de telefonos
    @param os: flujo de salida. Es MODIFICADO
    @param g: guia de telefonos que se escribe
    @return el flujo de salida
  */   
    friend ostream & operator<<(ostream &os, Guia_Tlf &g);

  /**
    @brief Lectura de  la guia de telefonos
    @param is: flujo de entrada. ES MODIFICADO
    @param g: guia de telefonos. ES MODIFICADO
    @return el flujo de entrada
  */  
    friend istream & operator>>(istream &is, Guia_Tlf &g);

};

#endif