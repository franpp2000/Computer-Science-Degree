import numpy as np
import numba


def lectura_datos(filepath):
    """Función que se encarga de la lectura de datos"""

    datos = []

    # Obtenemos todas las líneas del fichero
    with open(filepath) as fname:
        for lineas in fname:
            datos.append(lineas.split())

    # De las líneas que hemos obtenido, tomamos la primera que contiene el
    # valor de n y m
    first_line = datos.pop(0)

    datos = np.array(datos)

    return first_line[0], first_line[1], datos


@numba.jit(cache=True, parallel=True)
def suma_distancias(e, s, m_dist):
    """Funcion que calcula la suma de distancias de un elemento
    a los del conjunto solucion"""

    sum = 0.0
    # Para cada elemento del conjunto solucion
    # acumulamos la distancia de cada e_s a e
    for i in range(s.shape[0]):
        sum += m_dist[e, s[i]]

    return sum


@numba.jit(cache=True, parallel=True)
def actualizar_sum_dist_suma(s, v_sum_dist, e, m_dist):
    for i in range(s.shape[0]):
        v_sum_dist[i] += m_dist[s[i], e]

    return v_sum_dist


@numba.jit(cache=True, parallel=True)
def actualizar_sum_dist_resta(s, v_sum_dist, e, m_dist):
    for i in range(s.shape[0]):
        v_sum_dist[i] -= m_dist[s[i], e]

    return v_sum_dist


@numba.jit(cache=True)
def dispersion(v_sum_dist):
    min = np.amin(v_sum_dist)
    max = np.amax(v_sum_dist)

    return max - min
