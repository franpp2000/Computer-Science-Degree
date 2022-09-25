#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>

#define tamano 1024
#define nom_archivo_bloqueo "Archivo_bloqueo"
#define longnombre 50

int main(int argc, char **argv){
  char buffer[tamano];
	int numBytes, fd_bloqueo;
	FILE *tmp; 
	char nomFifo[longnombre];
	
	struct flock cerrojo;

	if(setvbuf(stdout, NULL, _IONBF, 0)){
		perror("Error en setvbuf:");
		exit(EXIT_FAILURE);
	}

	// Creacion del archivo temporal
	umask(0);
	tmp = tmpfile();

	// Abrimos archivo de bloqueo
	fd_bloqueo = open(nom_archivo_bloqueo, O_WRONLY);

	// Lectura de los datos del fifo y escritura de estos en el archivo temporal
	while((numBytes = read(STDIN_FILENO, buffer, tamano)) > 0){
		fwrite(buffer, sizeof(char), numBytes, tmp);
	}

	//Coger cerrojo
	cerrojo.l_type = F_WRLCK;
	cerrojo.l_whence = SEEK_SET;
	cerrojo.l_start = 0;
	cerrojo.l_len = 0;
	if(fcntl(fd_bloqueo, F_SETLKW, &cerrojo) == -1){
		perror("Error en fcntl:");
		exit(EXIT_FAILURE);
	}

	//Coloco el puntero al inicio del archivo
	fseek(tmp, 0, SEEK_SET);

	//Lo escribo en pantalla
	while(!feof(tmp)){
    fread(buffer, sizeof(char), tamano, tmp);
    write(STDOUT_FILENO, buffer, strlen(buffer)+1);
  }

	// Soltar cerrojo
	cerrojo.l_type = F_UNLCK;
	cerrojo.l_whence = SEEK_SET;
	cerrojo.l_start = 0;
	cerrojo.l_len = 0;
	if(fcntl(fd_bloqueo, F_SETLKW, &cerrojo) == -1){
		perror("Error en fcntl:");
		exit(EXIT_FAILURE);
	}

	// Cerrar archivo temporal
  fclose(tmp);

  // Eliminar fifo
  sprintf(nomFifo, "fifo.%d", getpid());
  unlink(nomFifo);

  return 0;

}