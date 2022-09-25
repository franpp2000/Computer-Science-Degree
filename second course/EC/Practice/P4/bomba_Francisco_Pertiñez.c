 // gcc -Og bomba_Francisco_Pertiñez.c -o bomba_Francisco_Pertiñez -no-pie -fno-guess-branch-probability

#include <stdio.h>	// para printf(), fgets(), scanf()
#include <stdlib.h>	// para exit()
#include <string.h>	// para strncmp()
#include <sys/time.h>	// para gettimeofday(), struct timeval

#define SIZE 100
#define TLIM 30
                    
//char password[]="serresiete\n";	// contraseña  115 101 114 114 101 115 105 101 116 101//ASCII
//int  passcode  = 2020;			// pin

char detonador[] = {101, 116, 101, 105, 115, 101, 114, 114, 101, 115, 10, 0};//  eteiserres cifrada inversamente
int cable_morado = 1000;



void boom(void){
	printf(	"\n"
		"*****\n"
		"* BOOM!!! *\n"
		"*****\n"
		"\n");
	exit(-1);
}

void defused(void){
	printf(	"\n"
		"Â·Â·Â·Â·Â·Â·Â·Â·Â·Â·Â·Â·Â·Â·Â·Â·Â·Â·Â·Â·Â·Â·Â·Â·Â·\n"
		"Â·Â·Â· bomba desactivada Â·Â·Â·\n"
		"Â·Â·Â·Â·Â·Â·Â·Â·Â·Â·Â·Â·Â·Â·Â·Â·Â·Â·Â·Â·Â·Â·Â·Â·Â·\n"
		"\n");
	exit(0);
}

void alicates(char *ctrn){
  char aux[strlen(detonador)];

  if(strlen(detonador) != strlen(ctrn))
    boom();

  for(unsigned i = 0; i < strlen(detonador); i++){
    aux[i] = ctrn[(strlen(detonador) - 2) - i];
  }  

  int ok = 1;
  for(unsigned i = 0; i < strlen(aux) && ok == 1; i++){
    if(aux[i] != detonador[i])
      ok = 0;
  }

  if(ok == 0)
    boom();
   
}

void cuenta_atras(int pin){
	int aux = cable_morado;

	aux = cable_morado + 10;
	aux = aux * 2;

	if(aux != pin){ 
		boom();
	}
}

int main(){
	char pw[SIZE];
	int  pc, n;

	struct timeval tv1,tv2;	// gettimeofday() secs-usecs
	gettimeofday(&tv1,NULL);

	do	printf("\nIntroduce la contraseÃ±a: ");
	while (	fgets(pw, SIZE, stdin) == NULL );

	gettimeofday(&tv2,NULL);
	if    ( tv2.tv_sec - tv1.tv_sec > TLIM )
	    boom();

	alicates(pw);

	do  {	printf("\nIntroduce el pin: ");
	 if ((n=scanf("%i",&pc))==0)
		scanf("%*s")    ==1;         }
	while (	n!=1 );

	gettimeofday(&tv1,NULL);
	if    ( tv1.tv_sec - tv2.tv_sec > TLIM )
	    boom();

	cuenta_atras(pc);

	defused();
}
