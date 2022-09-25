#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <dirent.h>

//Macro para verificar que un archivo cualquiera tiene permisos x para grupo y otros
#define permisos(mode) (((mode & ~S_IFMT) & 011) == 011)

struct salida{
  int bytes, n_arch;
};

struct salida buscar(char nom_dir[1000]){
  DIR *directorio; //directorio de nombre nom_dir
  struct dirent *arch; //cada entrada del directorio
  char pathname[1000]; //nombre de cada entrada del directorio
  struct stat atributos; //struct para acceder los atributos de un archivo
  struct salida s;
  s.bytes = 0;
  s.n_arch = 0;

  directorio = opendir(nom_dir);

  if(directorio == NULL){
    printf("Error en la apertura del directorio %s", nom_dir);
    exit(-2);
  }

  while((arch = readdir(directorio)) != NULL){
    if(strcmp(arch->d_name, ".") != 0 && strcmp(arch->d_name, "..") != 0){
      sprintf(pathname, "%s/%s", nom_dir, arch->d_name);

      if(stat(pathname, &atributos) < 0){
        printf("Error en la obtencion de los atributos %s - %s\n", pathname, strerror(errno));
      }
      else if(S_ISDIR(atributos.st_mode)){
        s = buscar(pathname);
      }
      else if(S_ISREG(atributos.st_mode) && permisos(atributos.st_mode)){
        printf("%s %li\n", pathname, atributos.st_ino);
        s.bytes += atributos.st_size;
        s.n_arch++;
      }
    }
  }

  return s;
}

int main(int argc, char *argv[]){
  char nom_dir[1000];
  struct salida s;

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

  s = buscar(nom_dir);

  printf("\nExisten %i archivos regulares con permiso x para grupos y otros.\n", s.n_arch);
  printf("Size: %i bytes\n", s.bytes);

  return(0);
}
