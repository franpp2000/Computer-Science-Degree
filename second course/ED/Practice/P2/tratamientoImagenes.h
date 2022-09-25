/**
  * @file tratamientoImagenes.h
  * @brief Fichero cabecera con las fuanciones encargadas del tratamiento de imagenes
  *
  * Permite aplicar sobre imagenes operaciones de zoom, reduccion, etc
  */

#ifndef TRATAMIENTOIMAGENES_H
#define TRATAMIENTOIMAGENES_H

#include <math.h>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include "Imagen.h"
#include "imagenES.h"

/**
  * @brief Funcion encargada de pasar los datos de un vector a una Imagen(matriz)
  * 
  * @param v vector cargado con los datos
  * @param fils filas de la matriz
  * @param cols columnas de la matriz
  * 
  * @return devuelve la imagen cargada con los datos 
  */
Imagen vectorAMatriz(const byte *v, const int fils, const int cols);

/**
 * @brief Funcion encargada de pasar los datos de una Imagen(matriz) a un vector
 * 
 * @param Imagen imagen cargada con los datos
 *    * @return devuelve el vector cargado con los datos
 * 
 * @return puntero a zona de memoria dinamica donde es alojado el vector
 * 
 * @post En caso de éxito, el puntero apunta a una zona de memoria reservada en
 * memoria dinámica. Será el usuario el responsable de liberarla. 
 *
 */
byte * matrizAVector(const Imagen & I);

/**
 * @brief Funcion que se calcula de calcular el umbral de una imagen
 *  
 * @param Imagen imagen de la que se va a calcular el umbral 
 * 
 * @return devuelve el umbral de la imagen pasada como parametro
 * 
 */
double calculaUmbral(const Imagen & I);

/**
 * @brief Funcion encargada de umbralizar una imagen
 * 
 * @param f_entrada nombre de fichero de donde se lee la imagen a tratar
 * @param f_salida nombre de fichero donde se va a escribir la imagen ya umbralizada
 * 
 * @return void
 */
void imagenUmbralizada(const char *f_entrada, const char *f_salida);

/**
 * @brief Funcion encargada de hacer zoom a una porcion de una imagen
 * 
 * Dicho zoom se lleva a cabo mediante una interpolacion poniendo entre cada 2 filas (resp columnas) de la imagen
 * original otra fila (resp. columna) cuyos valores de gris son la media de los que tiene a
 * laizquierda y a la derecha (resp. arriba y abajo).
 * 
 * @param f_entrada nombre del fichero de donde se lee la imagen a tratar
 * @param f_salida nombre del fichero donde se va escribir la imagen con zoom
 * @param x1 coordenada x de la esquina superior izquierda de la porcion de la imagen
 * @param y1 coordenada y de la esquina superior izquierda de la porcion de la imagen
 * @param x2 coordenada x de la esquina inferior derecha de la porcion de la imagen
 * @param y2 coordenada y de la esquina inferior derecha de la porcion de la imagen
 * 
 * @pre la porcion de imagen debe tener unas proporciones de N x N
 * 
 * @pre las coordenadas pasadas como parametros deben deben estar comprendidas entre 0 y el
 * tamaño de la imagen original
 * 
 * @return void
 * 
 * @pos en caso de exito, la imagen resultante en el fichero f_salida sera de unas 
 * proporciones de (2*N - 1) x (2*N - 1) 
 */
void zoom(const char *f_entrada, const char *f_salida, const int x1, const int y1, const int x2, const int y2);

/**
 * @brief Funcion que crea un icono a partir de una imagen
 *  
 * @param f_entrada nombre del fichero de donde se lee la imagen a tratar
 * @param f_salida nombre del fichero donde se va a escribir el icono
 * @param f_ic filas que tendra el icono
 * @param c_ic columnas que tendra el icono
 * 
 * @pre filas/columnas del icono no pueden ser mayor que filas/columnas de imagen original
 * ni valores negativos
 * 
 * @return void
 * 
 * @pos en caso de exito, la imagen resultante en el fichero f_salida sera de unas
 * proporciones de c_ic x f_ic
 */
void creaIcono(const char *f_entrada, const char *f_salida, int f_ic, int c_ic);

/**
 * @brief Funcion que devuelve el dato de menos valor (numerico) de un vector
 * 
 * @param v vector con datos
 * @param tam_v tamaño del vector
 * 
 * @return devuelve el valor mas bajo del vector 
 */
int buscaMin(const byte *v, const int tam_v);

/**
 * @brief Funcion que devuelve el dato de mas valor (numerico) de un vector
 * 
 * @param v vector con datos
 * @param tam_v tamaño del vector
 * 
 * @return devuelve el valor mas alto del vector 
 */
int buscaMax(const byte *v, const int tam_v);

/**
 * @brief Funcion encargada de variar el nivel de contraste de una imagen
 * 
 * @param f_entrada nombre del fichero de donde se va a leer la imagen a tratar
 * @param f_salida nombre del fichero de salida donde se va escribir la imagen con el contraste configurado
 * @param min valor minimo del rango de valores de grises tras modificacion de contraste
 * @param max valor maximo del rango de valores de grises tras modificacion de contraste
 * 
 * @pre min y max deben ser valores comprendidos entre 0-255
 * 
 * @return void
 */
void aumentoContraste(const char *f_entrada, const char *f_salida, const int min, const int max);

/**
 * @brief Funcion encargada de llevar el efecto de Morphing entre dos imagenes
 *
 * En un principio, la imagen se parecera un 100% a la original y por tanto un 0% a la final,
 * de manera que por cada fichero intermedio creado este se parecera un (1/num_ficheros)% mas la final
 * hasta que el ultimo fichero se parecera un 0% al original y un 100% al final.
 * 
 * @param f_origen nombre del fichero que alberga la imagen inicial
 * @param f_destino nombre del fichero que alberga la imagen en la que se quiere transformar la imagen inicial
 * @param f_intermedio numero de fichero intermedios que tiene que crearse
 * 
 * @return void
 * 
 * @pos en caso de exito, se escribe en los distintos ficheros intermedios la transicion
 * de una imagen a otra
 */
void morphing(const char *f_origen, const char *f_destino, int fich_intermedios);
#endif /* TRATAMIENTOIMAGENES_H */

