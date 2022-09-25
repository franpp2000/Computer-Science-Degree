import numpy as np
import random
import os
import time
import re
from funciones import *

random.seed(0)

# Guardamos el nombre de los ficheros ordenados gracias
# al uso de expresiones regulares
contenido = os.listdir('../datos_MDD/')
r = re.compile(r"(\d+)")
contenido.sort(key=lambda x: int(r.search(x).group(1)))


#########################################
# Implementeación greedy ################
#########################################


"""
Función para elegir el siguiente mejor elemento para incorporar a la solución

Parámetros:
    - rcl: conjunto de elementos no pertenecientes al conjunto solucion.
    - s: conjunto solución.
    - dist_sum_v: vector de suma de distancias.
    - m_dist: matriz de distancias.

Return:
    - best: siguiente mejor elemento para incorporar a la solución
    - best_v: vector de suma de distacias tras haber añadido el siguiente mejor
    - best_dispersion: dispersión del conjunto solución tras añadir el
    siguiente mejor
"""


def elegir_mejor(rcl, s, dist_sum_v, m_dist):
    best_dispersion = 9999999
    best = -1

    # Para cada elemento no perteneciente al conjunto solución
    for e in rcl:
        # Creamos una copia del vector de suma de distancias que tenemos hasta el momento
        _v = dist_sum_v.copy()

        # Actualizamos la suma de distancias de cada elemento del conjunto
        # solución añadiendo la distancia de estos a e
        _v = actualizar_sum_dist(_v, s, e, m_dist, "+")

        # Calculamos la suma de distancias de e a los elementos
        # del conjunto solucion
        dist_sum = suma_distancias(e, s, m_dist)

        # Añadimos la suma de distancias al vector de suma de distancias
        _v = np.append(_v, dist_sum)

        # Calculamos el mínimo y el máximo de dichas sumas de distancias
        min = np.amin(_v)
        max = np.amax(_v)

        # Calculamos la dispersión de la solución que estamos evaluando
        _d = max - min

        # Si la dispersión que acabamos de calcular es menor que la minima
        # hasta el momento actualizamos
        if _d < best_dispersion:
            best_dispersion = _d
            best = e
            best_v = _v

    return best, best_v, best_dispersion


"""
Función que implementa la solución greedy al problema min-diff.

Parámetros:
    - m_dist: matriz de distancias.
    - n: número de elementos:
    - m: tamaño de la solución.

Return:
    - s: conjunto solución final.
    - dispersion: dispersion de la solucion.
"""


def greedy(m_dist, n, m):
    s = []  # Conjunto solución, inicialmente vacío
    cl = np.arange(1, int(n), 1)  # Conjunto de elementos
    dispersion = -1

    # Elegimos un elemento aleatorio como solución inicial
    v0 = random.randint(0, n - 1)

    # Lo añadimos al conjunto solución
    s.append(v0)

    # Lo eliminamos del conjunto de elementos no elegidos
    cl = eliminar(v0, cl)

    v_dist_sum = [0.0]

    # mientras no tengamos una solución del tamaño que queremos
    while len(s) < m:
        # Hacemos una copia de cl
        rcl = cl.copy()

        # Desordemos los elementos para no beneficiar a ninguno
        np.random.shuffle(rcl)

        # Elegimos el siguiente mejor elemento para añadir al conjunto solucion
        mejor, v_dist_sum, dispersion = elegir_mejor(
            rcl, np.array(s), v_dist_sum, m_dist)

        # Lo añadimos al conjunto solucion
        s.append(mejor)

        # Lo eliminamos de cl
        cl = eliminar(mejor, cl)

    return s, dispersion


# Ejecución
for file in contenido:
    n, m, datos = lectura_datos('../datos_MDD/' + file)

    # Formato datos
    elementos_dos_a_dos = np.array(datos[:, 0:2], np.int64)
    distancias = np.array(datos[:, 2], np.float64)

    # Montamos la matriz de distancias que es con lo que trabajaremos realmente
    m_dist = np.zeros((int(n), int(n)))
    for i in range(elementos_dos_a_dos.shape[0]):
        m_dist[elementos_dos_a_dos[i, 0],
               elementos_dos_a_dos[i, 1]] = distancias[i]

    # Calculamos tiempos
    start = time.time()
    s, dispersion = greedy(m_dist, int(n), int(m))
    end = time.time()

    # Salida
    print('Fichero: ', file)
    print('Dispersión: ', dispersion)
    print('Tiempo: ', end - start, '\n\n')
