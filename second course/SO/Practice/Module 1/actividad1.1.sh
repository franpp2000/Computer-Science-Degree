#!/bin/bash

cp /home/francisco/Descargas/*.gz /tmp  #copiamos los archivos con extension .gzSX en el directorio tmp
# cp /fenix/depar/lsi/UML/*.gz /tmp version para el laboratorio

cd /tmp

gunzip -d *.gz

./kernel32-3.0.4 ubda=./Fedora13-x86-root_fs mem=1024m
