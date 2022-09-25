/* Programa que recorre un sub-árbol con la función nftw */
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>
#include <ftw.h>

//Macro para verificar que un archivo cualquiera tiene permisos x para grupo y otros
#define permisos(mode) (((mode & ~S_IFMT) & 011) == 011)

int BYTES = 0;
int N_ARCH = 0;


int buscar(const char *path, const struct stat *atributos, int flags, struct FTW *ftw){

  if(strcmp(path, ".") != 0 && strcmp(path, "..") != 0){
    
    if(S_ISREG(atributos->st_mode) && permisos(atributos->st_mode)){
      printf("%s %li\n", path, atributos->st_ino);

      BYTES += atributos->st_size;
      N_ARCH++;
    }
  }

  return 0;
}

int main(int argc, char *argv[]){
  char nom_dir[1000];

  if(argc == 2){
    strcpy(nom_dir, argv[1]);
  }
  else if(argc == 1){
    strcpy(nom_dir, ".");
  }
  else{
    printf("Error en argumentos.\n El formato es: ./ejercicio3 <ruta> o ./buscar");
    exit(-1);
  }

  printf("Los i-nodos son:\n");

  if(nftw(nom_dir, buscar, 5, 0) != 0){
    printf("Error en nftw");
    exit(-2);
  }

  printf("\nExisten %i archivos regulares con permiso x para grupos y otros.\n", N_ARCH);
  printf("Size: %i bytes\n", BYTES);

  return(0);
}
