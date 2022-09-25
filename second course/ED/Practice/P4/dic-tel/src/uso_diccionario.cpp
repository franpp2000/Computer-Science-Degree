#include <cassert>
#include <fstream>
#include <iostream>
#include <string>
#include "diccionario.h"

using namespace std;
/*
istream& operator >>(istream& is, Diccionario<string,string>& D)
{
	  int np;
	  is >> np;
	  is.ignore(); //quitamos \n
	  
	  Diccionario<string,string> Daux;
	  for (int i = 0; i < np; ++i)
	  {
		    string clave;

		    getline(is,clave); 
		    
		    int ns;
		    is >> ns; 
		    is.ignore(); //quitamos \n
		    
		    list<string> laux;
		    for (int j = 0; j < ns; ++j)
		    {
			      string s;
			      getline(is, s);
			      
			      laux.insert(laux.end(), s);
		    }
		    
		    Daux.Insertar(clave,laux);		      
	  }
	  
	  D = Daux;
	  
	  return is;
}

ostream& operator <<(ostream& out, const Diccionario<string, string>& d)
{
	for (Diccionario<string, string>::const_iterator i = d.cbegin(); i != d.cend(); ++i)
	{
		out << (*i).clave << ":\n";
		
		for (list<string>::const_iterator j = (*i).info_asoci.begin(); j != (*i).info_asoci.end(); ++j)
			out << '\t' << *j << '\n';
		
		out << endl;
	}

	return out;
}
*/

int main()
{

	Diccionario<string, string> uno;

	//Comprobar iteradores para diccionario vacío
	assert(uno.begin() == uno.end());
	
	fstream input_data("datos/data.txt", fstream::in);
	input_data >> uno;

	Diccionario<string, string> dos(uno);

	Diccionario<string, string>::iterator it;
	
	uno.AddSignificado_Palabra("f. Dicho grave y sucinto que encierra doctrina o moralidad", "Sentencia");

	assert(uno.getInfo_Asoc("Sentencia").front() == "f. Frase o dicho que implica un juicio,una enseñanza.");
	assert(uno.getInfo_Asoc("Sentencia").back() == "f. Dicho grave y sucinto que encierra doctrina o moralidad");

	assert(uno.getInfo_Asoc("Sentencia").front() == dos.getInfo_Asoc("Sentencia").front());
	assert(uno.getInfo_Asoc("Sentencia").back() != dos.getInfo_Asoc("Sentencia").back());
	
	assert(uno.getInfo_Asoc("Sentencia").front() == "f. Frase o dicho que implica un juicio,una enseñanza.");
	
	Diccionario<string, string> tres;
	assert(tres.cbegin() == tres.cend());
	uno = tres;
	assert(uno.begin() == uno.end());
	assert(dos.begin() != dos.end());

	cout << "OK" << endl;
	

	cout << endl << "COMPROBACIONES DE METODOS PROPIOS:" << endl << endl;

	cout << endl << "Informacion en dos:" << endl << dos;

	dos.Elimina_Palabra("Sentencia");

	cout << endl << "Tras borrado de Sentencia:" << endl;
	cout << dos;

	uno.AddSignificado_Palabra("f. Animal que vuela", "Aguila");

	cout << endl << "Informacion en uno:" << endl << uno;

	dos = dos + uno;

	cout << endl << "dos tras union con uno:" << endl << dos;

	dos.Invierte_Diccionario();

	cout << endl << "dos tras invertir:" << endl << dos;

	dos.Ordena_Diccionario();

	cout << endl << "dos tras ordenar:" << endl << dos;

	return 0;
}