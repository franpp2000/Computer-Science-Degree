#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

#define tamano 1024
#define longnombre 50

static void mimanejador(int senal){ 
  int estado;
  pid_t pid = wait(&estado);
}

int main(int argc, char *argv[]){

  setbuf(stdout, NULL);

  int dfifoE, dfifoS, fd_bloqueo, dfifoProxy;
  int pid, pid_cliente;
  int num;
  char nombrefifoE[longnombre], nombrefifoS[longnombre], nombrefifoProxy[longnombre];

  signal(SIGCHLD, mimanejador);

  if(argc != 2){
    printf("Uso: %s <nombre_fifo>\n", argv[0]);
    exit(-1);
  }

  //Creamos los nombres de los FIFOs conocidos, uno de entrada y otro de salida.
  sprintf(nombrefifoE,"%se",argv[1]);
	sprintf(nombrefifoS,"%ss",argv[1]);

  unlink(nombrefifoE);
  unlink(nombrefifoS);
  unlink("Archivo_bloqueo");

  umask(0);
  //Creamos un cauce con nombre para entrada y salida
  if((mkfifo(nombrefifoE, 0666)) < 0){
    perror("Error en mkfifo\n");
    exit(EXIT_FAILURE);
  }

  if((mkfifo(nombrefifoS, 0666)) < 0){
    perror("Error en mkfifo\n");
    exit(EXIT_FAILURE);
  }

  //Creamos y abrimos el archivo de bloqueo
  umask(0);
  fd_bloqueo = open("Archivo_bloqueo", O_CREAT, 0666);

  //Abrimos los cauces de entrada y salida
  if((dfifoE = open(nombrefifoE, O_RDWR)) < 0){
    perror("Error abriendo cauce FIFO de entrada.\n");
    exit(EXIT_FAILURE);
  }

  if((dfifoS = open(nombrefifoS, O_RDWR)) < 0){
    perror("Error abriendo cauce FIFO de salida.\n");
    exit(EXIT_FAILURE);
  }

  while((num = read(dfifoE, &pid_cliente, sizeof(int))) > 0){

    //Creamos el hijo proxy
    pid = fork();
    if(pid == -1){
      perror("Error al crear el proceso hijo:");
      exit(EXIT_FAILURE);
    }

    if(pid == 0){ //Proceso hijo

      //Creamos el FIFO del proxy
      umask(0);
      sprintf(nombrefifoProxy, "fifo.%d", getpid());
      
      if(mkfifo(nombrefifoProxy, 0666) < 0){
        perror("Error en mkfifo\n");
        exit(EXIT_FAILURE);
      }

      // Escribir en el fifo de salida el pid del hijo
      pid = getpid();

      if((num = write(dfifoS, &pid, sizeof(int))) < 0){
        perror("Error al escribir el pid del hijo:");
        exit(EXIT_FAILURE);
      }

      //Abrimos el FIFO del proxy
      if((dfifoProxy = open(nombrefifoProxy, O_RDONLY)) < 0){
        perror("Error al abrir el fifo del hijo:");
        exit(EXIT_FAILURE);
      }

      //Ponemos el FIFO como entrada estandar
      dup2(dfifoProxy, STDIN_FILENO);

      //Ejecutamos el proxy
      execlp("./proxy", "proxy", NULL);
    }
  }
  
  return 0;
}
