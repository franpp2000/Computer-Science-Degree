#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[]){
  int i0[2], i1[2], i2[2];

  pid_t h1, h2;

  int c1[2], c2[2];

  int mensaje = 0;
  char primo[4], arg1[4], arg2[4];

  if(argc < 3){
    perror("Error en argumentos.\n El formato es ./maestro limite_inferior limite_superior.\n");
    exit(-1);
  }

  i0[0] = atoi(argv[1]);
  i0[1] = atoi(argv[2]);

  if(i0[0] > i0[1]){
    i0[0] = i0[1];
    i0[1] = atoi(argv[1]);
  }

  i1[0] = i0[0];
  i1[1] = (i0[0] + i0[1]) / 2;

  i2[0] = i1[1] + 1;
  i2[1] = i0[1];

  //Cauce 1
  pipe(c1);

  if((h1 = fork()) < 0){
    perror("Error en la creacion del hijo 1.\n");
    exit(-2);
  }
  else if(h1 == 0){
    close(c1[0]);

    dup2(c1[1], STDOUT_FILENO);

    sprintf(arg1, "%i", i1[0]);
    sprintf(arg2, "%i", i1[1]);

    if(execl("./esclavo", "./esclavo", arg1, arg2, (char*)0) < 0){
      perror("Error al ejecutar esclavo\n");
      exit(-3);
    }
  }
  else{
    close(c1[1]);

    dup2(c1[0], STDIN_FILENO);

    printf("Hijo 1:\n");

    while(mensaje = read(c1[0], primo, sizeof(int)) > 0){
      printf("\t%s es primo\n", primo);
    }

    close(c1[0]);
  }

  //Cauce2
  pipe(c2);

  if((h2 = fork()) < 0){
    perror("Error en la creacion del hijo 2.\n");
    exit(-2);
  }
  else if(h2 == 0){
    close(c2[0]);

    dup2(c2[1], STDOUT_FILENO);

    sprintf(arg1, "%i", i2[0]);
    sprintf(arg2, "%i", i2[1]);

    if(execl("./esclavo", "./esclavo", arg1, arg2, (char*)0) < 0){
      perror("Error al ejecutar esclavo1\n");
      exit(-3);
    }
  }
  else{
    close(c2[1]);

    dup2(c2[2], STDIN_FILENO);

    printf("Hijo 2:\n");

    while(mensaje = read(c2[0], primo, sizeof(int)) > 0){
      printf("\t%s es primo\n", primo);
    }

    close(c2[0]);
  }

  return 0;
}