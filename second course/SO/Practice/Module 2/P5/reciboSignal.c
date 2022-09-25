#include <sys/types.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <signal.h>

static void sig_USR_hdlr(int sigNum){
  if(sigNum == SIGUSR1)
    printf("\nRecibida la señal SIGUSR1\n\n");
  else if(sigNum == SIGUSR2)
    printf("\nRecibida la señal SIGUSR2\n\n");  
}

int main(int argc, char *argv[]){
  struct sigaction sig_USR_nact;

  if(setvbuf(stdout, NULL, _IONBF, 0)){
    perror("\nError en setvbuf.");
    exit(-1);
  }

  sig_USR_nact.sa_handler = sig_USR_hdlr;

  sigempty(&sig_USR_nact.sa_mask);

  sig_USR_nact.sa_flags = 0;

  if(sigaction(SIGUSR1, &sig_USR_nact, NULL) < 0){
    perror("\nError al intentar establecer el manejador de señal para SIGUSR1");
    exit(-1);
  }

  if(sigaction(SIGUSR2, &sig_USR_nact, NULL) < 0){
    perror("\nError al intentar establecer el manejador de señal para SIGUSR2");
    exit(-1);
  }

  for(;;){}
}