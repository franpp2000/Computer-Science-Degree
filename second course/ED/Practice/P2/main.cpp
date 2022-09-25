#include <iostream>
#include <cstring>
#include "Imagen.h"
#include "imagenES.h"
#include "tratamientoImagenes.h"

using namespace std;

int main (int argc, char *argv[]){

  int opcion = -1;
  string origen, destino; 
 
  cout << "\n\t\tAPLICACION DE TRATAMIENTO DE IMAGENES" << endl << endl << endl;
  
  cout << "Opciones: " << endl
          << "\tUMBRALIZAR IMAGEN (1)" << endl
          << "\tZOOM DE PORCION DE IMAGEN (2)" << endl
          << "\tCREAR ICONO DE LA IMAGEN (3)" << endl
          << "\tCONFIGURAR CONTRASTE DE LA IMAGEN (4)" << endl
          << "\tEFECTO MORPHING ENTRE DOS IMAGENES (5)" << endl << endl;
  
  cout << "Seleccione una opcion: ";
  cin >> opcion;
  cout << endl << endl;
  
  switch(opcion){
    
    case 1:
      
      cout << "Fichero de entrada: ";
      cin >> origen;
      cout << "Fichero de salida: ";
      cin >> destino;
      
      imagenUmbralizada(origen.c_str(), destino.c_str());
      
      break;
    
    case 2:
      
      int x0,y0,x1,y1;
      
      cout << "Fichero de entrada: ";
      cin >> origen;
      cout << "Fichero de salida: ";
      cin >> destino;
      cout << "Coordenada X esquina superior izquierda:";
      cin >> x0;
      cout << "Coordenada Y esquina superior izquierda:";
      cin >> y0;
      cout << "Coordenada X esquina inferior derecha:";
      cin >> x1;
      cout << "Coordenada X esquina inferior derecha:";
      cin >> y1;
     
      
      zoom(origen.c_str(), destino.c_str(), x0, y0, x1, y1);
      
      break;
      
    case 3:
      
      int f_ic, c_ic;
      
      cout << "Fichero de entrada: ";
      cin >> origen;
      cout << "Fichero de salida: ";
      cin >> destino;
      cout << "Filas del icono: ";
      cin >> f_ic;
      cout << "Columnas del icono: ";
      cin >> c_ic;
      
      creaIcono(origen.c_str(), destino.c_str(), f_ic, c_ic);
      
      break;
      
    case 4:
      
      int min, max;
      
      cout << "Fichero de entrada: ";
      cin >> origen;
      cout << "Fichero de salida: ";
      cin >> destino;
      cout << "Valor minimo de la escala de grises: ";
      cin >> min;
      cout << "Valor maximo de la escala de grises: ";
      cin >> max;
      
      aumentoContraste(origen.c_str(), destino.c_str(), min, max);
      
      break;
      
    case 5:
      
      int pasos;
      
      cout << "Imagen inicio: ";
      cin >> origen;
      cout << "Imagen fin: ";
      cin >> destino;
      cout << "Numero de pasos (max 255): ";
      cin >> pasos;
      
      morphing(origen.c_str(), destino.c_str(), pasos);
      
      
      break;
      
    default:
      cout << "OPCION INCORRECTA. EL RANGO ES ENTRE 1 Y 5" << endl;
  }
  
  
  return (0);
}
