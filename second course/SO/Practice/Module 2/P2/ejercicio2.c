#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <dirent.h>

int main(int argc, char *argv[]){
  char *nom_dir;         //argumento 1, nombre del directorio
  int permisos;          //argumento 2, permisos
  DIR *directorio;       //directorio de nombre nom_dir
  struct dirent *arch;   //cada entrada del directorio
  char pathname[1000];   //nombre de cada entrada del directorio
  struct stat atributos; //estructura para acceder a los atributos del archivo
  mode_t perm_arch;      //permisos antiguos de cada entrada del directorio 


  if(argc != 3){
    printf("Error en argumentos.\n El formato es ./ejercicio2 <nombre_directorio> <permisos>");
    exit(-1);
  }
  else{
    nom_dir = argv[1];
    permisos = strtol(argv[2], NULL, 8);
    
    directorio = opendir(nom_dir);
    if(directorio == NULL){
      printf("Error en la apertura del directorio %s", nom_dir);
      exit(-2);
    }
  }

  arch = readdir(directorio);
  while((arch = readdir(directorio)) != NULL){

    if(strcmp(arch->d_name, ".") != 0 && strcmp(arch->d_name, "..") != 0){
      sprintf(pathname, "%s/%s", nom_dir, arch->d_name);

      if(stat(pathname, &atributos) < 0){
        printf("Error en la obtencion de los atributos de %s - %s\n", pathname, strerror(errno));
      }
      else{
        perm_arch = atributos.st_mode;

        if(chmod(pathname, permisos) < 0){
          printf("%s: %o %s\n", arch->d_name, perm_arch, strerror(errno));
        }
        else{
          if(stat(pathname, &atributos)){
            printf("Error en la obtencion de los atributos de %s - %s\n", pathname, strerror(errno));
          }
          else{
            printf("%s: %o %o\n", arch->d_name, perm_arch, atributos.st_mode);
          }
        }
      }
    }
  }
  
}