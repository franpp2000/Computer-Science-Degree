#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

int main(){

  int i;
  int nprocs = 20;
  pid_t childpid;

  for(i = 1; i < nprocs; i++){
    if((childpid = fork()) == -1){
      fprintf(stderr, "Could not create child %d: %d\n", i, strerror(errno));
      exit(-1);
    }
    if(!childpid){ //childpid == 0 (hijo)
      printf("\nPID Hijo: %d \n    PID Padre: %d \n", getpid(), getppid());
      break;
    }
  } 
}