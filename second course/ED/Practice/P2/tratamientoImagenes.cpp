#include "tratamientoImagenes.h"

using namespace std;


Imagen vectorAMatriz(const byte *v, const int fils, const int cols){
  
  Imagen I(fils, cols);
  
  int z = 0;
  
  for(int y = 0; y < fils; y++)
    for(int x = 0; x < cols; x++){
      I.asigna_pixel(y, x, v[z]);
      z++;
    }
  
  return I;
}


byte * matrizAVector(const Imagen & I){
  
  byte *v = new byte[I.num_columnas() * I.num_filas()];
  
  int z = 0;
  
  for(int y = 0; y < I.num_filas(); y++)
    for(int x = 0; x < I.num_columnas(); x++){
      v[z] = I.valor_pixel(y, x);
      z++;
    }  
  
  return v;
}


double calculaUmbral(const Imagen & I){
  double media1 = 0;
  
  for(int y = 0; y < I.num_filas(); y++)
    for(int x = 0; x < I.num_columnas(); x++)
      media1 += I.valor_pixel(y, x);
  
  media1 /= (I.num_filas() * I.num_columnas());
  
  bool fin = false;
 
  int cont1, cont2;
  double submedia1, submedia2;
  double media2;
  double diferencia;
  
  while(!fin){
    cont1 = cont2 = submedia1 = submedia2 = 0;
    
    for(int y = 0; y < I.num_filas(); y++)
      for(int x = 0; x < I.num_columnas(); x++){
        if(I.valor_pixel(y, x) > media1){
          submedia1 += I.valor_pixel(y,x);
          cont1++;
        }  
        else{
          submedia2 += I.valor_pixel(y,x);
          cont2++;
        }  
      }
    
    submedia1 /= cont1;
    submedia2 /= cont2;
    media2 = (submedia1 + submedia2) / 2;
    
    diferencia = media2 - media1;
    
    if(diferencia == 0)
      fin = true;
    else
      media1 = media2;
 
  }
  
  return media1;
  
}

void imagenUmbralizada(const char *f_entrada, const char *f_salida){
  byte *v;
  int nf, nc;
  
  v = LeerImagenPGM(f_entrada, nf, nc);
  
  if (!v){
    cerr << "Error: No pudo leerse la imagen." << endl;
    cerr << "Terminando la ejecucion del programa." << endl;
    exit (1);
  }
  
  // Mostrar los parametros calculados por LeerImagenPGM()
  cout << endl;
  cout << "Dimensiones de " << f_entrada << ":" << endl;
  cout << "   Imagen   = " << nf  << " filas x " << nc << " columnas " << endl;
  
  Imagen I;
  
  I = vectorAMatriz(v, nf, nc);
  
  delete [] v;
  v = 0;
  
  double umbral = calculaUmbral(I);
  
  for(int y = 0; y < I.num_filas(); y++)
    for(int x = 0; x < I.num_columnas(); x++){
      if(I.valor_pixel(y, x) > umbral)
        I.asigna_pixel(y, x, 255);
      else if(I.valor_pixel(y,x) <= umbral)
        I.asigna_pixel(y, x, 0);
    }
  
  v = matrizAVector(I);
  
  // Guardar la imagen resultado en el fichero
  if (EscribirImagenPGM (f_salida, v, nf, nc))
    cout  << "La imagen se guardo en " << f_salida << endl;
  else{
    cerr << "Error: No pudo guardarse la imagen." << endl;
    cerr << "Terminando la ejecucion del programa." << endl;
    exit (2);
  }
  // Liberar el vector
  delete [] v;
}


void zoom(const char *f_entrada, const char *f_salida, const int x1, const int y1, const int x2, const int y2){
  byte *v;
  int nf, nc;
  
  v = LeerImagenPGM(f_entrada, nf, nc);
  
  if (!v){
    cerr << "Error: No pudo leerse la imagen." << endl;
    cerr << "Terminando la ejecucion del programa." << endl;
    exit (1);
  }
  
  // Mostrar los parametros calculados por LeerImagenPGM()
  cout << endl;
  cout << "Dimensiones de " << f_entrada << ":" << endl;
  cout << "   Imagen   = " << nf  << " filas x " << nc << " columnas " << endl;
  
  Imagen I;
  
  I = vectorAMatriz(v, nf, nc);
  
  delete [] v;
  v = 0;
  
  int desplazamientoY = y2 - y1;
  int desplazamientoX = x2 - x1;
  
  Imagen imagenZoom(2 * desplazamientoY - 1, 2 * desplazamientoX - 1);
  
  for(int y = 0; y < desplazamientoY; y++)
    for(int x = 0; x < desplazamientoX; x++)
      imagenZoom.asigna_pixel(2 * y, 2 * x, I.valor_pixel(y1 + y, x1 + x));
  
  for(int y = 0; y < imagenZoom.num_filas(); y += 2)
    for(int x = 1; x < imagenZoom.num_columnas(); x += 2)
      imagenZoom.asigna_pixel(y, x, round((imagenZoom.valor_pixel(y, x - 1) + imagenZoom.valor_pixel(y, x + 1))/2.0));
    
  for(int y = 1; y < imagenZoom.num_filas(); y += 2)
    for(int x = 0; x < imagenZoom.num_columnas(); x++)
      imagenZoom.asigna_pixel(y, x, round((imagenZoom.valor_pixel(y - 1, x) + imagenZoom.valor_pixel(y + 1, x))/2.0));
  
  v = matrizAVector(imagenZoom);
  
  // Guardar la imagen resultado en el fichero
  if (EscribirImagenPGM (f_salida, v, imagenZoom.num_filas(), imagenZoom.num_columnas()))
    cout  << "La imagen se guardo en " << f_salida << endl;
  else{
    cerr << "Error: No pudo guardarse la imagen." << endl;
    cerr << "Terminando la ejecucion del programa." << endl;
    exit (2);
  }
  // Liberar el vector
  delete [] v;
  
}

void creaIcono(const char *f_entrada, const char *f_salida, int f_ic, int c_ic){
  byte *v;
  int nf, nc;
  
  v = LeerImagenPGM(f_entrada, nf, nc);
  
  if (!v){
    cerr << "Error: No pudo leerse la imagen." << endl;
    cerr << "Terminando la ejecucion del programa." << endl;
    exit (1);
  }
  
  // Mostrar los parametros calculados por LeerImagenPGM()
  cout << endl;
  cout << "Dimensiones de " << f_entrada << ":" << endl;
  cout << "   Imagen   = " << nf  << " filas x " << nc << " columnas " << endl;
  
  Imagen I;
  
  I = vectorAMatriz(v, nf, nc);
  
  delete [] v;
  v = 0;
  
  double reduccion_filas = ceil(nf/(double)f_ic);
  double reduccion_cols = ceil(nc/(double)c_ic);
  double media = 0;
   
  Imagen icono(f_ic, c_ic);
  
  for(int y = 0, i = 0; y < I.num_filas() && i < f_ic; y += reduccion_filas, i++){
    if(y != 0 && y + reduccion_filas * (f_ic - i) > nf)
      y--;
    for(int x = 0, j = 0; x < I.num_columnas() && j < c_ic; x += reduccion_cols, j++){
      if(x != 0 && x + reduccion_cols * (c_ic - j) > nc)
        x--;
      for(int z = y; z < y + reduccion_filas && z < I.num_filas(); z++)
        for(int k = x; k < x + reduccion_cols && k < I.num_columnas(); k++)
          media += (double)I.valor_pixel(z, k);
 
      media = ceil(media / ((double)reduccion_filas * reduccion_cols)*1.0);
      icono.asigna_pixel(i, j, (byte)media);
      media = 0;
    }
      
  }
    
  v = matrizAVector(icono);
  
  // Guardar la imagen resultado en el fichero
  if (EscribirImagenPGM (f_salida, v, icono.num_filas(), icono.num_columnas()))
    cout  << "La imagen se guardo en " << f_salida << endl;
  else{
    cerr << "Error: No pudo guardarse la imagen." << endl;
    cerr << "Terminando la ejecucion del programa." << endl;
    exit (2);
  }
  // Liberar el vector
  delete [] v;
}

int buscaMin(const byte *v, const int tam_v){
  int min;
  
  min = v[0];
  
  for(int y = 1; y < tam_v; y++)
    if(v[y] < min)
      min = v[y];
  
  return min;
}

int buscaMax(const byte *v, const int tam_v){
  int max;
  
  max = v[0];
  
  for(int y = 1; y < tam_v; y++)
    if(v[y] > max)
      max = v[y];
  
  return max;
}

void aumentoContraste(const char *f_entrada, const char *f_salida, const int min, const int max){
  byte *v;
  int nf, nc;
  
  v = LeerImagenPGM(f_entrada, nf, nc);
  
  if (!v){
    cerr << "Error: No pudo leerse la imagen." << endl;
    cerr << "Terminando la ejecucion del programa." << endl;
    exit (1);
  }
  
  // Mostrar los parametros calculados por LeerImagenPGM()
  cout << endl;
  cout << "Dimensiones de " << f_entrada << ":" << endl;
  cout << "   Imagen   = " << nf  << " filas x " << nc << " columnas" << endl;
  
  
  int a = buscaMin(v, nf * nc);
  int b = buscaMax(v, nf * nc);
  double cociente = 1.0*(max - min)/(b - a);
  
  Imagen I;
  
  I = vectorAMatriz(v, nf, nc);
  
  delete [] v;
  v = 0;
  
  byte operacion;
  
  for(int y = 0; y < nf; y++)
    for(int x = 0; x < nc; x++)
    {
      operacion = round(min + cociente * (I.valor_pixel(y, x) - a));
      I.asigna_pixel(y,x,operacion);
    }
  
  v = matrizAVector(I);
  
  // Guardar la imagen resultado en el fichero
  if (EscribirImagenPGM (f_salida, v, I.num_filas(), I.num_columnas()))
    cout  << "La imagen se guardo en " << f_salida << endl;
  else{
    cerr << "Error: No pudo guardarse la imagen." << endl;
    cerr << "Terminando la ejecucion del programa." << endl;
    exit (2);
  }
  // Liberar el vector
  delete [] v;
  
}

void morphing(const char *f_origen, const char *f_destino, int num_intermedios){
  byte *v;
   
  int nf, nc;
  
  v = LeerImagenPGM(f_origen, nf, nc);
  
  if (!v){
    cerr << "Error: No pudo leerse la imagen." << endl;
    cerr << "Terminando la ejecucion del programa." << endl;
    exit (1);
  }
  
  // Mostrar los parametros calculados por LeerImagenPGM()
  cout << endl;
  cout << "Dimensiones de " << f_origen << ":" << endl;
  cout << "   Imagen   = " << nf  << " filas x " << nc << " columnas" << endl;
  
  Imagen I_orig;
  
  I_orig = vectorAMatriz(v, nf, nc);
  
  delete [] v;
  v = 0;
  
  v = LeerImagenPGM(f_destino, nf, nc);
  
  if (!v){
    cerr << "Error: No pudo leerse la imagen." << endl;
    cerr << "Terminando la ejecucion del programa." << endl;
    exit (1);
  }
  
  // Mostrar los parametros calculados por LeerImagenPGM()
  cout << endl;
  cout << "Dimensiones de " << f_destino << ":" << endl;
  cout << "   Imagen   = " << nf  << " filas x " << nc << " columnas" << endl;
  
  Imagen I_dest;
  
  I_dest = vectorAMatriz(v, nf, nc);
  
  delete [] v;
  v = 0;
  
  Imagen intermedia(nf, nc);
  
  double porcentaje = 0;
  string fichero;
 
  for(int k = 0; k < num_intermedios; k++){
    for(int y = 0; y < I_orig.num_filas(); y++){
      for(int x = 0; x < I_orig.num_columnas(); x++){
        intermedia.asigna_pixel(y ,x , (1 - porcentaje) * I_orig.valor_pixel(y,x) + porcentaje * I_dest.valor_pixel(y,x));
      }
    }
    fichero = "frame" + to_string(k) + ".pgm";
    v = matrizAVector(intermedia);
    EscribirImagenPGM(fichero.c_str(), v, nf, nc);
    delete [] v;
    v = 0;
    porcentaje += 1/(double)num_intermedios;
  }
    
  
}