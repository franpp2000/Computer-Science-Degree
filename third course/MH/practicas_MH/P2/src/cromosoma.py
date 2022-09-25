import numpy as np
import random
from funciones import *


class Cromosoma():
    """Clase que representa un cromosoma"""

    def __init__(self, n, m, elementos, m_dist, v_b=np.array([]), empty=False):
        """Constructor de la Clase"""

        if empty == True:
            self.v_binario = np.array([])
            self.conjunto_sol = np.array([], np.int32)
            self.conjunto_no_sol = np.array([], np.int32)
            self.v_sum_dist = np.array([])
        else:
            # representación binaria de una solución
            # 1 -> elemento seleccionado
            # 0 -> elemento no seleccionado
            if v_b.shape[0] == 0:
                self.v_binario = np.zeros(n, np.int32)

                indice = np.random.choice(n - 1, m, replace=False)

                for i in indice:
                    self.v_binario[indice] = 1
            else:
                self.v_binario = v_b.copy()

            # Conjunto solucion y conjunto no solucion
            self.conjunto_sol = np.array([], np.int32)
            self.conjunto_no_sol = np.array([], np.int32)

            for i in range(self.v_binario.shape[0]):
                if self.v_binario[i] == 1:
                    self.conjunto_sol = np.append(
                        self.conjunto_sol, elementos[i])
                elif self.v_binario[i] == 0:
                    self.conjunto_no_sol = np.append(
                        self.conjunto_no_sol, elementos[i])

            self.v_sum_dist = np.array([])
            # Recorremos el vector binario
            for i in range(self.conjunto_sol.shape[0]):
                self.v_sum_dist = np.append(
                    self.v_sum_dist, suma_distancias(self.conjunto_sol[i], self.conjunto_sol, m_dist))

    def eliminar(self, pos, m_dist):
        """Método para eliminar un elemento al conjunto solucion"""

        # Lo elimino del vector de suma de distancias
        self.v_sum_dist = np.delete(self.v_sum_dist, pos)

        # Lo elimino del conjunto solucion y y lo añado al conjunto no solucion
        e = self.conjunto_sol[pos]
        self.conjunto_sol = np.delete(self.conjunto_sol, pos)
        self.conjunto_no_sol = np.append(self.conjunto_no_sol, e)

        # Actualizo el las distancias al haber eliminado un elemento
        self.v_sum_dist = actualizar_sum_dist_resta(
            self.conjunto_sol, self.v_sum_dist, e, m_dist)

        # Lo marco a no seleccionado en la representación binaria
        self.v_binario[e] = 0

    def add(self, pos, m_dist):
        """Método para añadir un elemento al conjunto solucion"""

        e = self.conjunto_no_sol[pos]

        # Lo elimino del conjunto no solucion
        self.conjunto_no_sol = np.delete(self.conjunto_no_sol, pos)

        # Actualizo el vector de suma de distancias con la adición del elemento
        self.v_sum_dist = actualizar_sum_dist_suma(
            self.conjunto_sol, self.v_sum_dist, e, m_dist)
        self.v_sum_dist = np.append(
            self.v_sum_dist, suma_distancias(e, self.conjunto_sol, m_dist))

        # Lo añado al conjunto solucion
        self.conjunto_sol = np.append(self.conjunto_sol, e)

        # Lo marco como seleccionado en la representación binaria
        self.v_binario[e] = 1


######################################################
# Funciones Comunes de todos los algoritmos geneticos
######################################################

def calcular_v_binario(s, cl):
    v_b = np.full(s.shape[0] + cl.shape[0], -1)

    for e in s:
        v_b[e] = 1

    for e in cl:
        v_b[e] = 0

    return v_b


def mejor_cromosoma(p):
    """Funcion que busca el mejor cromosoma en la poblacion"""

    indice = -1
    mejor_dispersion = 999999

    # Recorremos la población buscando el cromosoma con mejor dispersion
    for i in range(p.shape[0]):
        d = dispersion(p[i].v_sum_dist)

        if d < mejor_dispersion:
            indice = i
            mejor_dispersion = d

    return indice


def peor_cromosoma(h):
    """Funcion que busca el peor cromosoma en la poblacion"""

    indice = -1
    peor_dispersion = -999999

    for i in range(h.shape[0]):
        d = dispersion(h[i].v_sum_dist)

        if d > peor_dispersion:
            indice = i
            peor_dispersion = d

    return indice


def mutacion(interm, n_m, m_dist):
    """Funcion que implementa el operador de mutación por intercambio"""

    i = 0

    # Mientras no hayamos hecho el número de mutaciones correspondiente
    while i < n_m:
        # Elegimos el cromosoma que va a mutar
        c = random.randint(0, interm.shape[0] - 1)

        # Elegimos si el primer gen será de los seleccionados o
        # no seleccionados
        eleccion = random.randint(0, 1)

        if eleccion == 1:
            g1 = random.choice(
                np.arange(0, interm[c].conjunto_sol.shape[0] - 1, 1))
            g2 = random.choice(
                np.arange(0, interm[c].conjunto_no_sol.shape[0] - 1, 1))
            interm[c].eliminar(g1, m_dist)
            interm[c].add(g2, m_dist)
        else:
            g1 = random.choice(
                np.arange(0, interm[c].conjunto_no_sol.shape[0] - 1, 1, np.int32))
            g2 = random.choice(
                np.arange(0, interm[c].conjunto_sol.shape[0] - 1, 1, np.int32))
            interm[c].add(g1, m_dist)
            interm[c].eliminar(g2, m_dist)

        i += 1

    return interm

##########################################################################
# Funciones comunes de los AGG
##########################################################################


def seleccion_padres_agg(p):
    """Funcion que se encarga de la selección de los padres de una poblacion
    según un modelo generacional"""

    padres = np.array([])

    # Realizamos tantos torneos binarios como cromosomas tenemos en la
    # poblacion
    for i in range(p.shape[0]):
        # Elijo el primer contrincante aleatoriamente
        c1 = random.randint(0, p.shape[0] - 1)
        # Elijo el segundo contrincante aleatoriamente que no sea otra vez
        # el primero
        c2 = random.randint(0, p.shape[0] - 1)
        while c2 == c1:
            c2 = random.randint(0, p.shape[0] - 1)
        # Me quedo con el ganador
        if dispersion(p[c1].v_sum_dist) < dispersion(p[c2].v_sum_dist):
            padres = np.append(padres, p[c1])
        else:
            padres = np.append(padres, p[c2])

    return padres


def reemplazo_agg(h, m):
    """Funcion que realiza el reemplazo de la poblacion
    según el modelo generacional"""

    # Compruebo si ha sobrevivido la mejor solucion de la generación anterior
    i = 0
    sobrevive = False
    while i < h.shape[0] and sobrevive == False:
        if np.array_equal(h[i].v_binario, m.v_binario):
            sobrevive = True
        i += 1

    # Si ha sobrevivido se reemplaza toda la poblacion
    if sobrevive:
        return h
    else:
        # Buscamos el peor de los hijos
        peor = peor_cromosoma(h)
        # Lo eliminamos
        h = np.delete(h, peor)
        # Añadimos el mejor de la poblacion
        h = np.append(h, m)

        return h


###############################################################################
# Funciones comunes al los algoritmos geneticos que utilizan el cruce uniforme
###############################################################################

def operador_reparacion(h, m, m_dist):
    """Funcion que implementa el operador de reparación que se usa en
    el operador de cruce uniforme"""

    # Calculamos la media de las sumas de distancias de cada elemento
    media = np.mean(h.v_sum_dist)

    # Calculamos el número de 1 que tiene el vector binario
    n_unos = np.count_nonzero(h.v_binario == 1)

    # Calculamos la violación del hijo
    violacion = m - n_unos

    # Si el número de 1s es m no hace falta hacer ningún ajuste
    if violacion == 0:
        return h
    # Si tenemos mas 1s de los necesarios
    elif violacion < 0:

        max_diferencia = -999999
        indice = -1

        # Mientras queden elementos por quitar
        while violacion < 0:
            # Dentro del conjuntos solucion, buscamos el elemento mas
            # distante a la media
            for i in range(h.v_sum_dist.shape[0]):
                diferencia = np.abs(h.v_sum_dist[i] - media)

                if diferencia > max_diferencia:
                    max_diferencia = diferencia
                    indice = i

            # Lo quitamos del conjunto solucion y lo añadimos al conjunto de
            # no solucion
            h.eliminar(indice, m_dist)

            media = np.mean(h.v_sum_dist)
            max_diferencia = -999999
            indice = -1
            violacion += 1

    # Mientras queden elementos por añadir
    elif violacion > 0:

        min_diferencia = 999999
        indice = -1

        # Mientras queden elementos por añadir
        while violacion > 0:
            # Dentro del conjunto no solucion, buscamos el elemento mas proximo
            # a la media
            for i in range(h.conjunto_no_sol.shape[0]):
                # Calculamos la suma de distancias de el elemento i-esimo
                # a los del conjunto solución
                sum_dist = suma_distancias(
                    h.conjunto_no_sol[i], h.conjunto_sol, m_dist)

                diferencia = np.abs(sum_dist - media)

                if diferencia < min_diferencia:
                    min_diferencia = diferencia
                    indice = i

            # Lo añadimos del conjunto solucion y lo eliminamos del conjunto de
            # no solucion
            h.add(indice, m_dist)

            media = np.mean(h.v_sum_dist)
            min_diferencia = 999999
            indice = -1
            violacion -= 1

    return h


def generar_hijo_un(p1, p2, n, m, elementos, m_dist):
    """Función que genera un hijo de un par de cromosomas
    usando cruce uniforme"""

    v_b = np.array([])
    # Recorremos ambos padres a la vez
    for i in range(p1.v_binario.shape[0]):
        # Si el gen i-esimo que estamos observando tiene el mismo valor en
        # ambos padres conservo dicho valor en el hijo
        if p1.v_binario[i] == p2.v_binario[i]:
            v_b = np.append(v_b, p1.v_binario[i])

        # Si no es así elijo el valor del gen de uno de los dos aleatoriamente
        else:
            v_b = np.append(v_b, random.randint(0, 1))

    hijo = Cromosoma(n, m, elementos, m_dist, v_b)

    # Aplicamos al hijo el operador de reparación para que sea factible
    hijo = operador_reparacion(hijo, m, m_dist)

    return hijo

#############################################################
# Funciones propias del AGG_uniforme
#############################################################


def cruces_agg_un(p, n_c, n, m, elementos, m_dist):
    """Función que implementa el operador de cruce uniforme"""

    hijos = np.array([])
    i = 0
    j = 0
    # Mientras no se den el total de cruces
    while i < n_c:
        # Selecciono los dos padres consecutivos
        p1 = p[j]
        j += 1
        p2 = p[j]
        j += 1

        # Generamos dos hijos de los mismo padres
        h1 = generar_hijo_un(p1, p2, n, m, elementos, m_dist)
        h2 = generar_hijo_un(p1, p2, n, m, elementos, m_dist)
        # Añadimos ambos hijos a la población de hijos
        hijos = np.append(hijos, h1)
        hijos = np.append(hijos, h2)

        i += 1

    # Añado los demas cromosomas que no han cruzado
    hijos = np.append(hijos, p[j:])

    return hijos

##########################################################################
# Funciones propias de los algorimos que usan cruce por posicion
##########################################################################


def generar_hijo_pos(p1, p2, n, m, elementos, m_dist):
    """Función que genera un hijo de un par de cromosomas
    usando cruce por posicion"""

    v_resto = np.array([])
    v_b = np.full(p1.v_binario.shape[0], -1)

    # Recorremos ambos padres a la vez
    for i in range(p1.v_binario.shape[0]):
        if p1.v_binario[i] == p2.v_binario[i]:
            v_b[i] = p1.v_binario[i]
        else:
            v_resto = np.append(v_resto, p1.v_binario[i])

    # Desordeno los valores de v_resto
    np.random.shuffle(v_resto)

    i = 0
    for j in range(v_b.shape[0]):
        if v_b[j] == -1:
            v_b[j] = v_resto[i]
            i += 1

    hijo = Cromosoma(n, m, elementos, m_dist, v_b)

    return hijo

#############################################################
# Funciones propias del AGG_posicion
#############################################################


def cruces_agg_pos(p, n_c, n, m, elementos, m_dist):
    """Función que implementa el operador de cruce por posicion"""

    hijos = np.array([])
    i = 0
    j = 0
    # Mientras no se den el total de cruces
    while i < n_c:
        # Selecciono los dos padres consecutivos
        p1 = p[j]
        j += 1
        p2 = p[j]
        j += 1

        # Generamos dos hijos de los mismo padres
        h1 = generar_hijo_pos(p1, p2, n, m, elementos, m_dist)
        h2 = generar_hijo_pos(p1, p2, n, m, elementos, m_dist)
        # Añadimos ambos hijos a la población de hijos
        hijos = np.append(hijos, h1)
        hijos = np.append(hijos, h2)

        i += 1

    # Añado los demas cromosomas que no han cruzado
    hijos = np.append(hijos, p[j:])

    return hijos

#####################################################
# Funciones comunes de AGE
######################################################


def seleccion_padres_age(p):
    padres = np.array([])

    # Realizamos 2 torneos binarios para elegir los dos padres
    i = 0
    while i < 2:
        # Elijo el primer contrincante aleatoriamente
        c1 = random.randint(0, p.shape[0] - 1)
        # Elijo el segundo contrincante aleatoriamente que no sea otra vez
        # el primero
        c2 = random.randint(0, p.shape[0] - 1)
        while c2 == c1:
            c2 = random.randint(0, p.shape[0] - 1)
        # Me quedo con el ganador
        if dispersion(p[c1].v_sum_dist) < dispersion(p[c2].v_sum_dist):
            padres = np.append(padres, p[c1])
        else:
            padres = np.append(padres, p[c2])

        i += 1

    return padres


def reemplazo_age(h, p):
    # Buscamos los dos peores cromosomas de la poblacion y si los sustituimos
    # por los dos hijos que hemos generado si procede
    peor_p = peor_cromosoma(p)

    peor_h = peor_cromosoma(h)
    mejor_h = mejor_cromosoma(h)

    # Si el peor de la poblacion es peor que el peor de los hijos añado el
    # mejor de los hijos
    if dispersion(p[peor_p].v_sum_dist) > dispersion(h[peor_h].v_sum_dist):
        p = np.delete(p, peor_p)

        segundo_peor_p = peor_cromosoma(p)

        p = np.append(p, p[mejor_h])

        # Si el segundo peor de la poblacion es peor que el peor de los hijos
        # añado el peor de los hijos
        if dispersion(p[segundo_peor_p].v_sum_dist) > dispersion(h[peor_h].v_sum_dist):
            p = np.delete(p, segundo_peor_p)
            p = np.append(p, p[peor_h])

    elif dispersion(p[peor_p].v_sum_dist) > dispersion(h[mejor_h].v_sum_dist):
        p = np.delete(p, peor_p)
        p = np.append(p, p[mejor_h])

    return p

#####################################################################
# Funciones propias de AGE_uniforme
#####################################################################


def cruce_age_un(p, n_c, n, m, elementos, m_dist):
    hijos = np.array([])

    # Generamos dos hijos
    h1 = generar_hijo_un(p[0], p[1], n, m, elementos, m_dist)
    h2 = generar_hijo_un(p[0], p[1], n, m, elementos, m_dist)
    # Añadimos ambos hijos a la población de hijos
    hijos = np.append(hijos, h1)
    hijos = np.append(hijos, h2)

    return hijos


###############################################################
# Funciones Propias de AGE_posicion
###############################################################

def cruce_age_pos(p, n_c, n, m, elementos, m_dist):
    hijos = np.array([])

    # Generamos dos hijos
    h1 = generar_hijo_pos(p[0], p[1], n, m, elementos, m_dist)
    h2 = generar_hijo_pos(p[0], p[1], n, m, elementos, m_dist)
    # Añadimos ambos hijos a la población de hijos
    hijos = np.append(hijos, h1)
    hijos = np.append(hijos, h2)

    return hijos


######################################################
# Funciones comunes de los algorimos meméticos
######################################################

def generar_vecino(evaluaciones_d, s, dist_sum_v, cl, m_dist, d):
    iteraciones = 0
    # Recorremos el conjunto solución
    for i in range(s.shape[0]):
        # Recorremos el conjunto de elementos no pertenecientes al conjunto
        # solucion
        for j in range(cl.shape[0]):
            iteraciones += 1

            if(iteraciones == 400 - evaluaciones_d):
                return s, dist_sum_v, d, iteraciones

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

            # Calculamos la dispersión de la solución que estamos evaluando
            _d = dispersion(_v)

            # Si la dispersión que acabamos de calcular es menor que la minima
            # hemos acabado
            if _d - d < 0:
                s = _s.copy()
                dist_sum_v = _v.copy()
                d = _d

                return s, dist_sum_v, d, iteraciones

    # Necesitamos este return para cuando no haya mejora
    return s, dist_sum_v, d, iteraciones


def busqueda_local(c_sol, c_no_sol, v_sum_dist, m_dist):
    elementos = np.arange(c_sol.shape[0] + c_no_sol.shape[0])

    evaluaciones_d = 0

    # Generamos una solución inicial
    s = c_sol.copy()

    # Eliminamos de cl los elementos que hemos añadido al conjunto solucion
    cl = c_no_sol.copy()

    # Desordenamos aleatoriamente cl
    np.random.shuffle(cl)

    # Obtenemos el vector de sumas de distancias de la solucion
    v = v_sum_dist.copy()

    d = dispersion(v)

    fin = False

    while(not fin and evaluaciones_d < 400):
        # Generamos siguiente vecino que mejore la solucion actual
        neighbour_s, neighbour_v, neighbour_d, eval = generar_vecino(
            evaluaciones_d, s, v, cl, m_dist, d)

        evaluaciones_d += eval

        # No ha habido mejora
        fin = (neighbour_d == d)

        # Si ha habido mejora actualizamos.
        if(not fin):
            s = neighbour_s
            v = neighbour_v
            d = neighbour_d
            cl = np.setdiff1d(elementos, s)
            np.random.shuffle(cl)

    return s, v, cl, evaluaciones_d


#######################################################
# Funciones propias de AM-10-1
#######################################################

def aplicar_BL(p, n, m, elementos, m_dist):
    eval = 0
    for i in range(p.shape[0]):
        s, v, cl, evaluaciones_d = busqueda_local(
            p[i].conjunto_sol, p[i].conjunto_no_sol, p[i].v_sum_dist, m_dist)
        v_b = calcular_v_binario(s, cl)
        cr_bl = Cromosoma(n, m, elementos, m_dist, empty=True)
        cr_bl.v_binario = v_b
        cr_bl.conjunto_sol = s
        cr_bl.conjunto_no_sol = cl
        cr_bl.v_sum_dist = v
        eval += evaluaciones_d

        p[i] = cr_bl

    return p, eval


##########################################################
# Funciones propias de AM-10-0.1
##########################################################

def aplicar_BL_random(n_aplicar_bl, p, n, m, elementos, m_dist):
    indices = np.random.choice(
        np.arange(0, p.shape[0], 1), n_aplicar_bl, replace=False)

    eval = 0

    for i in indices:
        s, v, cl, evaluaciones_d = busqueda_local(
            p[i].conjunto_sol, p[i].conjunto_no_sol, p[i].v_sum_dist, m_dist)
        v_b = calcular_v_binario(s, cl)
        cr_bl = Cromosoma(n, m, elementos, m_dist, empty=True)
        cr_bl.v_binario = v_b
        cr_bl.conjunto_sol = s
        cr_bl.conjunto_no_sol = cl
        cr_bl.v_sum_dist = v
        eval += evaluaciones_d

        p[i] = cr_bl

    return p, eval


############################################################
# Funciones propias de AM-10-0.1mej
############################################################

def busca_n_mejores(n, p):
    _p = p.copy()
    i = 0
    mejores = np.array([], np.int32)
    while i < n:
        mejor = mejor_cromosoma(_p)
        _p = np.delete(_p, mejor)
        mejores = np.append(mejores, mejor)
        i += 1

    return mejores


def aplicar_BL_mejor(n_mejores_bl, p, n, m, elementos, m_dist):
    mejores = busca_n_mejores(n_mejores_bl, p)

    eval = 0

    for i in mejores:
        s, v, cl, evaluaciones_d = busqueda_local(
            p[i].conjunto_sol, p[i].conjunto_no_sol, p[i].v_sum_dist, m_dist)
        v_b = calcular_v_binario(s, cl)
        cr_bl = Cromosoma(n, m, elementos, m_dist, empty=True)
        cr_bl.v_binario = v_b
        cr_bl.conjunto_sol = s
        cr_bl.conjunto_no_sol = cl
        cr_bl.v_sum_dist = v
        eval += evaluaciones_d

        p[i] = cr_bl

    return p, eval
