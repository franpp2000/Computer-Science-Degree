#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(){
  const int HIJOS = 5;
  pid_t pid, hijos[HIJOS];
  int estado, h = 4;

  for(int i = 0; i < HIJOS; i++){
    if((pid = fork()) < 0){
      perror("Error al crear hijo\n");
      exit(-1);
    }
    else if(pid == 0){
      printf("\nSoy el hijo %i\n", getpid());
      exit(0);
    }
    else{
      hijos[i] = pid;
    }
  }

  for(int i = 0; i < HIJOS; i += 2){
    pid = waitpid(hijos[i], &estado, 0);

    printf("\nAcaba de finalizar mi hijo %i\n", pid);
    printf("Me quedan %i hijos vivos\n", h--);
  }

  for(int i = 1; i < HIJOS; i += 2){
    pid = waitpid(hijos[i], &estado, 0);

    printf("\nAcaba de finalizar mi hijo %i\n", pid);
    printf("Me quedan %i hijos vivos\n", h--);
  }

  return 0;
}