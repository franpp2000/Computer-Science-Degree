#!/bin/bash

#Creamos un par de grupos
groupadd grupo1
groupadd grupo2

#Asignamos distintos usuarios a dichos grupos
gpasswd -a usuario1 grupo1
gpasswd -a usuario2 grupo2

#Desde root ejecutando la orden id nos muestra por salida el UID, GID y los demas grupos a los que pertenece
#dicho usuario, que en este caso solo es al de root, todos estos IDs tienen el numero 0 asignado.
