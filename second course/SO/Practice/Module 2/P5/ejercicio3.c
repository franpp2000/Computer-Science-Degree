#include <stdio.h>
#include <signal.h>

void manejador(int i){
  printf("Acaba de desbloquearse el proceso.\n");
}

int main(){
  sigset_t mascara;
  struct sigaction tarea;

  //inicializamos la mascara
  sigemptyset(&tarea.sa_mask);

  //le asignamos nuestro manejador;
  tarea.sa_handler = manejador;

  //le asignamos manejador a SIGUSR1
  sigaction(SIGUSR1, &tarea, NULL);
  tarea.sa_flags = 0;

  //vaciamos y añadimos todas las señales a mascara
  sigdelset(&mascara, SIGUSR1);
  sigfillset(&mascara);

  //suspende el proceso hasta que se envia alguna de las señales que NO estan bloqueadas
  sigsuspend(&mascara);

  return 0;
}