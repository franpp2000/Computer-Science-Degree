import numpy as np
import time
import random
import os
import re

random.seed(0)

# Guardamos el nombre de los ficheros ordenados gracias
# al uso de expresiones regulares
contenido = os.listdir('../datos_MDD/')
r = re.compile(r"(\d+)")
contenido.sort(key=lambda x: int(r.search(x).group(1)))


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


def suma_distancias(e, s, m_dist):
    """Funcion que calcula la suma de distancias de un elemento
    a los del conjunto solucion"""

    sum = 0.0
    # Para cada elemento del conjunto solucion
    # acumulamos la distancia de cada e_s a e
    for i in range(s.shape[0]):
        sum += m_dist[e, s[i]]

    return sum


def vector_suma_distancias(s, m_dist):
    result = np.array([])

    for i in range(s.shape[0]):
        suma_distacias_e = suma_distancias(s[i], s, m_dist)
        result = np.append(result, suma_distacias_e)

    return result


def actualizar_sum_dist_suma(s, v_sum_dist, e, m_dist):
    for i in range(s.shape[0]):
        v_sum_dist[i] += m_dist[s[i], e]

    return v_sum_dist


def actualizar_sum_dist_resta(s, v_sum_dist, e, m_dist):
    for i in range(s.shape[0]):
        v_sum_dist[i] -= m_dist[s[i], e]

    return v_sum_dist


def dispersion(v_sum_dist):
    min = np.amin(v_sum_dist)
    max = np.amax(v_sum_dist)

    return max - min


def generar_vecino(s, cl, v_sum_dist):
    # Elegimos aleatoriamente los dos elementos que vamos a intercambiar
    i_s = np.random.randint(0, s.shape[0] - 1)
    i_cl = np.random.randint(0, cl.shape[0] - 1)

    # Hacemos una copia del conjunto solución y
    # del vector de suma de distancias de s
    _v = v_sum_dist.copy()
    _s = s.copy()

    # Tomamos el elemento de cl y el elemento de s con los que vamos a
    # trabajar
    e_s = _s[i_s]
    e_cl = cl[i_cl]

    # Eliminamos el elemento y la suma de distancias del elemento
    # del conjunto solucion que estamos evaluando
    _v = np.delete(_v, i_s)
    _s = np.delete(_s, i_s)

    # Actualizamos _v al haber quitado el elemento i-ésimo de s
    _v = actualizar_sum_dist_resta(_s, _v, e_s, m_dist)

    # Calculamos suma de distancias del elemento de cl a los elementos
    # de s
    dist_sum = suma_distancias(e_cl, _s, m_dist)

    # Añadimos el elemento de cl a s y
    # la suma de distancias al vector de suma de distancias
    _v = np.append(_v, dist_sum)
    _s = np.append(_s, e_cl)

    # Actualizamos _v al haberle añadido el elemento i-ésimo de cl
    _v = actualizar_sum_dist_suma(_s, _v, e_cl, m_dist)

    return _s, _v


def enfriamiento_simulado(n, m, m_dist):
    elementos = np.arange(int(n))

    # Generamos una solución inicial aleatoria
    s = np.random.choice(n, m, replace=False)

    mejor = np.copy(s)

    # Eliminamos de cl los elementos que hemos añadido al conjunto solucion
    cl = np.setdiff1d(elementos, s)

    # Obtenemos el vector de sumas de distancias de la solucion
    v = vector_suma_distancias(s, m_dist)
    mejor_v = np.copy(v)

    # Generamos temperatura inicial
    T0 = (0.3 * dispersion(v))/(-np.log(0.3))

    # Fijamos la temperatura final
    Tf = 0.001

    T = T0
    max_vecinos = 10 * n
    max_exitos = int(0.1 * max_vecinos)
    max_it = 100000 / max_vecinos
    it = 0
    n_vecinos = 0
    n_exitos = 1

    while T > Tf and it < max_it and n_exitos > 0:
        n_vecinos = 0
        n_exitos = 0
        while n_vecinos < max_vecinos and n_exitos < max_exitos:
            _s, _v = generar_vecino(s, cl, v)

            n_vecinos += 1

            delta_f = dispersion(_v) - dispersion(v)

            if delta_f < 0 or np.random.rand() <= np.exp(-delta_f/T):
                n_exitos += 1

                s = np.copy(_s)
                v = np.copy(_v)
                cl = np.setdiff1d(elementos, s)

                #print(dispersion(v))

                if dispersion(v) < dispersion(mejor_v):
                    mejor = np.copy(s)
                    mejor_v = np.copy(v)

        beta = (T0 - Tf)/(max_it * T0 * Tf)
        T = T/(1 + beta * T)
        it += 1

    return mejor, mejor_v, dispersion(mejor_v)


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
    sol, v, d = enfriamiento_simulado(n, m, m_dist)
    end = time.time()

    print('Fichero: ', file)
    print('Solución: ', sol)
    #print('Vector de suma de distancias: ', v)
    print('Dispersion: ', d)
    print('Tiempo: ', end - start, '\n\n')
