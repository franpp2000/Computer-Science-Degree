#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <math.h>

int esPrimo(int n){
  int primo = 1;

  for(int i = 2; i < sqrt(n) && primo; i++){
    if(n % i == 0){
      primo = 0;
    }
  }

  return primo;
}

int main(int argc, char *argv[]){
  int lim_inf, lim_sup;
  char primo[4];

  if(argc < 3){
    perror("Error en argumentos.\n El formato es ./esclavo limite_inferior limite_superior.\n");
    exit(-1);
  }

  lim_inf = atoi(argv[1]);
  lim_sup = atoi(argv[2]);

  if(lim_inf > lim_sup){
    lim_inf = lim_sup;
    lim_sup = atoi(argv[1]);
  }

  for(int i = lim_inf; i <= lim_sup; i++){
    if(esPrimo(i)){
      sprintf(primo, "%i", i);
      write(STDOUT_FILENO, primo, sizeof(int));
    }
  }

  return 0;
}