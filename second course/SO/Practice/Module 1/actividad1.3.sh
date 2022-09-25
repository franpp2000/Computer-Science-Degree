#!/bin/bash

#Creamos las cuentas de usuario con diferentes parametros:
useradd usuario1 -b /home -d /home/usuario1
useradd usuario2 -b /home -d /home/usuario2 -e 2010-09-07
useradd usuario3 -b /home -d /home/usuario3 -c "Usuario3" -g 1003

# Eliminamos alguno de estos usuarios:
userdel usuario1

# Tras eliminarlo nos damos cuenta que habiendo ejecutado la orden userdel como se ha hecho
# el directorio personal del usuario aun permanece.

#Entramos en el sistema con una de las cuentas creadas y mostramos que archivos guarda en su directorio home
sudo su usuario1 #Si no se es root previamente
ls -l /home/usuario1

#Vemos como dentro del directorio home se encuentra la misma estructura de directorios que habia cuando hicimos 
# nuestra primera cuenta, es decir, los directorios Escritorio, Descargas, Imagenes...
