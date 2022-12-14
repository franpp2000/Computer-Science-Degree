
#include <cassert>
#include <fstream>
#include <iostream>
#include <string>
#include "guia.h"

using namespace std;

int main()
{
    Guia_Tlf uno;

    assert(uno.begin() == uno.end());

    fstream input_data("datos/telefonos.txt", fstream::in);
	input_data >> uno;

    Guia_Tlf dos(uno);
	assert(dos.begin() != dos.end());

	Guia_Tlf::iterator it;
	uno.insert("Manolo", "666666666");

    assert(uno["Pedro"] == dos["Pedro"]);
    uno["Pedro"][3] = '7';
    assert(uno["Pedro"] != dos["Pedro"]);

	uno = uno;
	assert(*uno.begin() == *dos.begin());

	Guia_Tlf tres;
    Guia_Tlf cuatro(tres);
	assert(tres.cbegin() == tres.cend());
	assert(cuatro.cbegin() == cuatro.cend());
	tres = uno;
    
    tres["Manolo"][0] = 0;
    assert(uno["Manolo"] != tres["Manolo"]);

    Guia_Tlf cinco = uno - dos;
    assert(cinco["Manolo"] == uno["Manolo"]);
    

    size_t c = 0;
    for (Guia_Tlf::iterator it = cinco.begin(); it != cinco.end(); ++it)
        //esto debe ejecutarse dos veces. Añadimos contador para que falle
        //si el diccionario contiene más elementos
        //Elementos esperados: Manolo y Pedro (porque a Pedro le hemos cambiado
        //un dígito)
        //usando (*it) en vez de it-> para evitar tener que sobrecargar -> en
        //caso de que el Guia_Tlf::iterator sea implementación propia
        assert(c++ < 2 && ((*it).first == "Manolo" || (*it).first == "Pedro"));
    
    //En la unión de diccionarios, cuando la clave existe en ambos, se puede
    //tomar el valor del primer diccionario o del segundo. Se aceptan ambos.
    Guia_Tlf seis = uno + dos;
    assert((seis["Pedro"] != uno["Pedro"] && seis["Pedro"] == dos["Pedro"])
        || (seis["Pedro"] == uno["Pedro"] && seis["Pedro"] != dos["Pedro"]));

    pair<std::map<string, string>::iterator, bool> p = seis.insert("Pedro", "123456789");
    assert(!p.second);
      
    cout << "OK" << endl;

    cout << endl << "COMPROBACIONES DE METODOS PROPIOS:" << endl << endl;

    cout << "Contactos que empiezan por 'N':" << endl;

    Guia_Tlf buscados = uno.buscar_Por_Inicial('N');

    cout << buscados;

    cout << endl << "Le cambiamos el numero a Nuria por 666:" << endl;

    buscados.cambia_Numero_Telefono("Nuria", "666");

    cout << buscados;

    cout << endl << "Buscamos un contacto con numero: 666666666" << endl;

    pair<string, string> contacto = uno.buscar_Por_Numero("666666666");

    cout << contacto.first << "   " << contacto.second << endl;

    return 0;
}   