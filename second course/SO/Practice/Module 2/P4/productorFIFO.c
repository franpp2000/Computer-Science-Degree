#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define ARCHIVO_FIFO "ComunicacionFIFO"

int main(int argc, char *argv[]){
  int fd;

  if(argc != 2){
    printf("\nproductorFIFO: faltan argumentos (mensaje)");
    printf("\nPruebe: productorFIFO <mensaje>, donde <mensaje> es una cadena de caracteres.\n");
    exit(-1);
  }

  if((fd = open(ARCHIVO_FIFO, O_WRONLY)) < 0){
    perror("\nError en open");
    exit(-1);
  }

  if(write(fd, argv[1], strlen(argv[1]) + 1) != strlen(argv[1]) + 1){
    perror("\nError al escribir en el FIFO");
    exit(-1);
  }

  close(fd);

  return 0; 
}