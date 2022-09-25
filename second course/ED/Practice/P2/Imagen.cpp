#include "Imagen.h"

using namespace std;

void Imagen::allocate(const int f, const int c){
  if(f > 0 && c > 0){
    cols = c;
    filas = f;
  
    img = new byte * [filas];
    for(int y = 0; y < filas; y++)
      img[y] = new byte [cols];
  }  
}

void Imagen::deallocate(){
  if(img != nullptr){
    for(int y = 0; y < filas; y++)
      delete [] img[y];
    delete [] img;  
    
    img = nullptr;
    filas = cols = 0;
  }
}

void Imagen::copy(const Imagen & imagen){
  for(int y = 0; y < imagen.num_filas(); y++)
    for(int x = 0; x < imagen.num_columnas(); x++)
      img[y][x] = imagen.valor_pixel(y, x);
}

Imagen::Imagen(){
  img = nullptr;
  filas = 0;
  cols = 0;
}

Imagen::Imagen(int f, int c) {
    allocate(f, c);
}

Imagen::~Imagen(){
  deallocate();
}

Imagen::Imagen(const Imagen& imagen){
  allocate(imagen.num_filas(), imagen.num_columnas());
  copy(imagen);
}

Imagen & Imagen::operator =(const Imagen & origen){
  if(this != &origen){
    deallocate();
    allocate(origen.num_filas(), origen.num_columnas());
    copy(origen);
  }
  
  return *this;
}

int Imagen::num_filas() const{
  return filas;
}

int Imagen::num_columnas() const{
  return cols;
}

byte Imagen::valor_pixel(const int f, const int c) const{
  if(f >= 0 && f < filas && c >= 0 && c < cols);
    return img[f][c];
}

void Imagen::asigna_pixel(const int f, const int c, byte valor){
  if(f >= 0 && f < filas && c >= 0 && c < cols && valor >= 0 && valor <= 255)
    img[f][c] = valor;
}


