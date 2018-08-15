
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char tab = '\t';
char enter = '\n';
char  *lectura = "r";
char *escritura = "w";
int lenlista = 0;

struct Proceso{
	int pid;
	int llegada;
	int duracion;
	int prioridad;
};


#define LONGBUFF 100
