#!/bin/bash

# Visualizamos el contenido de los archivos useradd y login.defs:
cat /etc/default/useradd
cat /etc/login.defs

#Creamos una cuenta de usuario:
adduser usuario1

#Visualizamos los archivos passwd y group:
cat /etc/passwd
cat /etc/group

#Vemos como al final de los dos archivos ha quedado constancia de la creacion de dicho usuario.
