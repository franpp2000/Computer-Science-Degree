#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<errno.h>

int main(int argc, char *argv[]){
  int fdin;
  int fdout;
  char buffer[80];
  int numbytes;
  int i = 1;

  if(argc < 2)
    fdin = STDIN_FILENO;
  else
    if((fdin = open(argv[1], O_RDONLY)) < 0){
      printf("\nError %d en open", errno);
      perror("\nError en open");
      exit(-1);
    }

   if((fdout = open("salida.txt", O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR)) < 0){
      printf("\nError %d en open", errno);
      perror("\nError en open");
      exit(-1);
   }

   write(fdout, &buffer, 27);
   write(fdout, "\n", 1);

   while((numbytes = read(fdin, &buffer, 80)) > 0){

     char cabecera[10];
     sprintf(cabecera, "Bloque %i", i);

     write(fdout, &cabecera, sizeof(cabecera));

     write(fdout, "\n", 1);

     write(fdout, &buffer, numbytes);

     write(fdout, "\n", 1);

     i++;
   }

   if(lseek(fdout, 0, SEEK_SET) < 0){
     perror("\nError en lseek");
     exit(-1);
   }

   char totalbloques[27];
   sprintf(totalbloques, "El numero de bloques es %i", i - 1);

   write(fdout, &totalbloques, sizeof(totalbloques));

   close(fdout);
   close(fdin);

  return 0;
}