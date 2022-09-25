#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void){
  pid_t pid;
  int estado; 
  const int HIJOS = 5;

  for(int i = 0; i < HIJOS; i++){
    if((pid = fork()) < 0){
      perror("Error al crear hijo\n");
      exit(-1);
    }
    else if(pid == 0){
      printf("\nSoy el hijo %i\n", getpid());
      exit(0);
    }
  }

  for(int i = 0; i < HIJOS; i++){
    pid = wait(&estado);

    printf("\nAcaba de finalizar mi hijo %i\n", pid);
    printf("Me quedan %i hijos vivos\n", HIJOS - i - 1);
  }

  return 0;
}
