#include <stdio.h>
#include <stdlib.h>

extern int lista[];
extern int longlista, resultado;
extern char formato[];

void suma(){

	int i, res = 0;

	for(i = 0; i < longlista; i++)
		res += lista[i];

	resultado = res;

	printf(formato, res, res);

	exit(0);
}
