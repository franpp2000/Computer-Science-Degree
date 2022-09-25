import numpy as np
import random
import time
import os
import re
from funciones import *
from cromosoma import *

random.seed(0)

# Guardamos el nombre de los ficheros ordenados gracias
# al uso de expresiones regulares
contenido = os.listdir('../datos_MDD/')
r = re.compile(r"(\d+)")
contenido.sort(key=lambda x: int(r.search(x).group(1)))


def am_10_mejores(tam_poblacion, n, m, elementos, m_dist):
    t = 0
    g = 0
    # Genero la población inicial
    poblacion = np.array([])
    for i in range(tam_poblacion):
        cr = Cromosoma(n, m, elementos, m_dist)
        poblacion = np.append(poblacion, cr)

    g += 1
    mejor = mejor_cromosoma(poblacion)
    t += 10

    # Calculamos el número de cruces y de mutaciones
    n_cruces = int(0.7 * tam_poblacion / 2)
    n_mutaciones = int(0.1 * n)
    n_mejores_bl = int(0.1 * tam_poblacion)

    # Mientras no evaluemos la función objetivo 100000
    while t < 100000:
        # Cada 10 generaciones
        if g % 10 == 0:
            #+start = time.time()
            poblacion, eval = aplicar_BL_mejor(
                n_mejores_bl, poblacion, n, m, elementos, m_dist)
            #end = time.time()
            #print('Tiempo en BL: ', end - start, '\n\n')
            t += eval

        # Selecciono la poblacion de padres
        #start = time.time()
        padres = seleccion_padres_agg(poblacion)
        #end = time.time()
        #print('Tiempo Seleccionando Padres: ', end - start, '\n\n')

        # Genero la población intermedia
        #start = time.time()
        intermedia = cruces_agg_un(padres, n_cruces, n, m, elementos, m_dist)
        #end = time.time()
        #print('Tiempo Cruzando padres: ', end - start, '\n\n')

        # Muto la poblacion
        #start = time.time()
        hijos = mutacion(intermedia, n_mutaciones, m_dist)
        #end = time.time()
        #print('Tiempo Mutanciones: ', end - start, '\n\n')

        # Reemplazo la poblacion
        #start = time.time()
        poblacion = reemplazo_agg(hijos, poblacion[mejor])
        #end = time.time()
        #print('Tiempo Reeplazando poblacion: ', end - start, '\n\n')

        #start = time.time()
        mejor = mejor_cromosoma(poblacion)
        #end = time.time()
        #print('Tiempo Buscando mejor de la poblacion: ', end - start, '\n\n')
        g += 1
        t += 10

    return poblacion[mejor]


# Ejecución
for file in contenido:
    n, m, datos = lectura_datos('../datos_MDD/' + file)

    n = int(n)
    m = int(m)

    # Formato datos
    elementos_dos_a_dos = np.array(datos[:, 0:2], np.int64)
    distancias = np.array(datos[:, 2], np.float64)

    # Montamos la matriz de distancias que es con lo que trabajaremos realmente
    m_dist = np.zeros((n, n))
    for i in range(elementos_dos_a_dos.shape[0]):
        m_dist[elementos_dos_a_dos[i, 0],
               elementos_dos_a_dos[i, 1]] = distancias[i]
        m_dist[elementos_dos_a_dos[i, 1],
               elementos_dos_a_dos[i, 0]] = distancias[i]

    start = time.time()
    sol = am_10_mejores(10, n, m, np.arange(
        0, int(n), 1, dtype=np.int32), m_dist)
    end = time.time()

    print('Fichero: ', file)
    print('Vector de suma de distancias: ', sol.v_sum_dist)
    print(sol.conjunto_sol)
    print('Dispersion: ', dispersion(sol.v_sum_dist))
    print('Tiempo: ', end - start, '\n\n')
