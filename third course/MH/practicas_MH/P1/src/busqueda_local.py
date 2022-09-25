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

#######################################
# Implementación Búsqueda Local #######
#######################################

"""
Función que genera el primer siguiente vecino que mejore la solución actual,
si lo hay.

Parámetros:
    - s: conjunto solucion.
    - dist_sum_v: vector suma de distancias.
    - cl: conjunto de elementos no pertenecientes al conjunto solución.
    - dist_m: matriz de distancias.
    - dispersión: dispersión de la solución actual.
"""


def generar_vecino(s, dist_sum_v, cl, dist_m, dispersion):
    iteraciones = 0
    # Recorremos el conjunto solución
    for i in range(s.shape[0]):
        # Recorremos el conjunto de elementos no pertenecientes al conjunto
        # solucion
        for j in range(cl.shape[0]):
            iteraciones += 1

            if(iteraciones == 100000):
                return s, dist_sum_v, dispersion

            # Hacemos una copia del conjunto solución y
            # del vector de suma de distancias de s
            _v = dist_sum_v.copy()
            _s = s.copy()

            # Tomamos el elemento de cl y el elemento de s con los que vamos a
            # trabajar en esta iteración
            e_s = _s[i]
            e_cl = cl[j]

            # Eliminamos el elemento y la suma de distancias del elemento
            # del conjunto solucion que estamos evaluando
            _v = np.delete(_v, i)
            _s = np.delete(_s, i)

            # Actualizamos _v al haber quitado el elemento i-ésimo de s
            _v = actualizar_sum_dist(_v, _s, e_s, m_dist, "-")

            # Calculamos suma de distancias del elemento de cl a los elementos
            # de s
            dist_sum = suma_distancias(e_cl, _s, m_dist)

            # Añadimos el elemento de cl a s y
            # la suma de distancias al vector de suma de distancias
            _v = np.append(_v, dist_sum)
            _s = np.append(_s, e_cl)

            # Actualizamos _v al haberle añadido el elemento i-ésimo de cl
            _v = actualizar_sum_dist(_v, _s, e_cl, m_dist, "+")

            # Adjuntamos elementos con su suma de distancias
            aux_s = list(zip(_s, _v))

            # Ordenamos por suma de distancias(de mayor contribución a menor)
            aux_s.sort(key=lambda x: x[1], reverse=True)

            _s, _v = unzip(aux_s)

            # Calculamos la dispersión de la solución que estamos evaluando
            _d = _v[0] - _v[-1]

            # Si la dispersión que acabamos de calcular es menor que la minima
            # hemos acabado
            if _d - dispersion < 0:
                s = _s.copy()
                dist_sum_v = _v.copy()
                dispersion = _d

                return s, dist_sum_v, dispersion

    # Necesitamos este return para cuando no haya mejora
    return s, dist_sum_v, dispersion


"""
Función que implementa la solución de búsqueda local al problema min-diff.

Parámetros:
    - m_dist: matriz de distancias.
    - n: número de elementos:
    - m: tamaño de la solución.

Return:
    - s: conjunto solución final.
    - dispersion: dispersion de la solucion.
"""


def busqueda_local(n, m, m_dist):
    elementos = np.arange(int(n))

    # Generamos una solución inicial aleatoria
    s = np.random.choice(n, m, replace=False)

    # Eliminamos de cl los elementos que hemos añadido al conjunto solucion
    cl = np.setdiff1d(elementos, s)

    # Desordenamos aleatoriamente cl
    np.random.shuffle(cl)

    # Obtenemos el vector de sumas de distancias de la solucion
    v = vector_suma_distancias(s, m_dist)

    # Adjuntamos elementos con su suma de distancias
    aux_s = list(zip(s, v))

    # Ordenamos por suma de distancias(de mayor contribución a menor)
    aux_s.sort(key=lambda x: x[1], reverse=True)

    s, v = unzip(aux_s)

    dispersion = v[0] - v[-1]

    fin = False

    while(not fin):
        # Generamos siguiente vecino que mejore la solucion actual
        neighbour_s, neighbour_v, neighbour_dispersion = generar_vecino(
            s, v, cl, m_dist, dispersion)

        # No ha habido mejora
        fin = (neighbour_dispersion == dispersion)

        # Si ha habido mejora actualizamos.
        if(not fin):
            s = neighbour_s
            v = neighbour_v
            dispersion = neighbour_dispersion
            cl = np.setdiff1d(elementos, s)
            np.random.shuffle(cl)

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
    s, dispersion = busqueda_local(int(n), int(
        m), m_dist)
    end = time.time()

    # Salida
    print('Fichero: ', file)
    print('Dispersión: ', dispersion)
    print('Tiempo: ', end - start, '\n\n')
