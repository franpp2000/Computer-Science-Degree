#!/bin/bash

#Intentando visualizar el archivo /etc/shadow nos reporta la terminal: Permiso denegado.
#La razon de esto es que si listamos dicho archivo con la orden
ls -l /etc/shadow
#vemos que los permisos que tiene establecido son 640, lo que quiere decir que solo puede leer en él el 
# propietario, el cual sabemos que es el root pues la orden anterior tambien nos informa de ello.
