#Ejemplo de sistema de archivos
#
#UUID=319a9218-3c9b-499f-a97b-b84ea67edafb /            ext4    errors=remount-ro 0       1
#
#Informacion:
#
#UUID: ID del disco montado
#/: Punto de montaje del dispositivo
#ext4: Tipo de sistema de ficheros. Es el algoritmo que se utilizara para interpretarlo
#errors=remount-ro: Lugar donde se especifica los parametro que mount usara para montar el dispositivo. En este ejemplo en caso de error ejecutar dicha orden
#0: Comando que utiliza dump para hacer para hacer respaldo del sistema de archivos, si es 0 no se toma en cuenta, si es 1 si
#1: Indica el orden en que la aplicacion fsck revisara la particion en busca de errosres tras el inicio. Va desde 0 a 2 (cuanto mayor sea el numero, mayor prioridad)
#
#

