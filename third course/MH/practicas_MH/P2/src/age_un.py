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


def age_un(tam_poblacion, n, m, elementos, m_dist):
    t = 0
    # Genero la población inicial
    poblacion = np.array([])
    for i in range(tam_poblacion):
        cr = Cromosoma(n, m, elementos, m_dist)
        poblacion = np.append(poblacion, cr)

    mejor = mejor_cromosoma(poblacion)
    t += 50

    # Calculamos el número de cruces y de mutaciones
    n_cruces = 1
    n_mutaciones = int(0.1 * n)

    # Mientras no evaluemos la función objetivo 100000
    while t < 100000:
        # Selecciono la poblacion de padres
        #start = time.time()
        padres = seleccion_padres_age(poblacion)
        #end = time.time()
        #print('Tiempo Seleccionando Padres: ', end - start, '\n\n')

        # Genero la población intermedia
        #start = time.time()
        intermedia = cruce_age_un(padres, n_cruces, n, m, elementos, m_dist)
        #end = time.time()
        #print('Tiempo Cruzando padres: ', end - start, '\n\n')

        # Muto la poblacion
        #start = time.time()
        hijos = mutacion(intermedia, n_mutaciones, m_dist)
        #end = time.time()
        #print('Tiempo Mutanciones: ', end - start, '\n\n')

        # Reemplazo la poblacion
        #start = time.time()
        poblacion = reemplazo_age(hijos, poblacion)
        #end = time.time()
        #print('Tiempo Reeplazando poblacion: ', end - start, '\n\n')

        #start = time.time()
        mejor = mejor_cromosoma(poblacion)
        #end = time.time()
        #print('Tiempo Buscando mejor de la poblacion: ', end - start, '\n\n')

        t += 50

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
    sol = age_un(50, n, m, np.arange(0, int(n), 1, dtype=np.int32), m_dist)
    end = time.time()

    print('Fichero: ', file)
    print(sol.conjunto_sol)
    print('Vector de suma de distancias: ', sol.v_sum_dist)
    print('Dispersion: ', dispersion(sol.v_sum_dist))
    print('Tiempo: ', end - start, '\n\n')
