#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]){
  pid_t pid;
  int num;

  if(argc != 2){
    perror("Error en argumentos.\n El formato es: ./ejercicio1 <numero>\n");
    exit(-1);
  }

  num = atoi(argv[1]);

  if((pid = fork()) < 0){
    perror("Error en el fork\n");
    exit(-2);
  }
  
  if(pid == 0){
    if(num % 2 == 0)
      printf("H: El numero %i es par.\n", num);
    else
      printf("H: El numero %i es impar.\n", num);
  }
  else{
    if(num % 4 == 0)
      printf("P: El numero %i es divisible por 4.\n", num);
    else
      printf("P: El numero %i no es divisible por 4.\n", num);
  }

  return 0;
}