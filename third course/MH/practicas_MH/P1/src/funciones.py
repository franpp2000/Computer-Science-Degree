import numpy as np

"""
Función para la lectura de datos

Parámetros:
    - filepath: ruta del fichero de donde se leerán los datos

Return:
    - n: número de elementos
    - m: tamaño de la solucion
    - datos: matriz en la que cada fila  es de la forma: [i, j, dist(i,j)]
"""


def lectura_datos(filepath):
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


"""
Función para eliminar de un vector un elemento

Parámetros:
    - e: valor del elemento a eliminar
    - v: vector que contiene al elemento

Return: retorna el vector con el elemento eliminado
"""


def eliminar(e, v):
    eliminado = False
    i = 0
    tam = v.shape[0]

    # Mientras no lo hayamos eliminado y no hayamos recorrido
    # el vector totalmente
    while not eliminado and i < tam:
        if v[i] == e:
            v = np.delete(v, i)
            eliminado = True
        else:
            i += 1

    return v


"""
Función que hace lo contrario a la función zip de Python

Parámetros:
    - tuple_list: lista de tuplas en la que cada tupla es de la forma:
      (elemento del conjunto solución, suma de distancias de dicho elemento)

return:
    - s: conjunto solución.
    - v: vector de suma de distancias
"""


def unzip(tuple_list):
    s = []
    dist_sum_v = []

    for tupla in tuple_list:
        s.append(tupla[0])
        dist_sum_v.append(tupla[1])

    return np.array(s), np.array(dist_sum_v)


"""
Función que calcula la suma de distancias de un elemento
a los del conjunto solucion

Parámetros:
    - e: elemento del que vamos a calcular la suma de distacias
    - s: conjunto solución

Return: retorna la suma de distancias.
"""


def suma_distancias(e, s, dist_m):
    sum = 0.000  # Variable donde acumularemos la suma de distacias

    # Para cada elemento del conjunto solucion
    # acumulamos la distancia de cada e_s a e
    for e_s in s:
        sum += dist_m[np.amin(np.array([e, e_s])), np.amax(np.array([e, e_s]))]

    return sum


"""
Función que actualiza la suma de distancias de cada elemento al añadir/eliminar
un determinado elemento del conjunto solución

Parámetros:
    - dist_sum_v: vector de sumas de distancias de los elementos de un conjunto
    solución.
    - s: conjunto solución.
    - e: elemento que se añade/elimina al/del conjunto solución.
    - dist_m: matriz de distancias.
    - operación: parámetro que determina si el elemento se añade (+) o
    se elimina (-)

Return: retorna el vector de suma de distancias actualizado.
"""


def actualizar_sum_dist(dist_sum_v, s, e, dist_m, operacion):
    # Recorremos el conjunto solución y para cada suma de distacias
    # de cada elemento del conjunto solución actualizamos sumando/restando
    # la distancia de cada elemento al que estamos añadiendo/eliminando
    for i in range(s.shape[0]):
        if operacion == '+':
            dist_sum_v[i] += dist_m[np.amin(np.array([s[i], e])),
                                    np.amax(np.array([s[i], e]))]
        elif operacion == '-':
            dist_sum_v[i] -= dist_m[np.amin(np.array([s[i], e])),
                                    np.amax(np.array([s[i], e]))]
    return dist_sum_v


"""
Función que calcula el vector de suma de distacias asociado a los elementos de
un determinado conjunto solución

Parámetros:
    - s: conjunto solución.
    - m_dist: matriz de distancias.

"""


def vector_suma_distancias(s, m_dist):
    result = np.array([])

    for e_s in s:
        suma_distacias_e = suma_distancias(e_s, s, m_dist)
        result = np.append(result, suma_distacias_e)

    return result
