#include "main.h"

struct Proceso *setLista(FILE *archivo, struct Proceso *p){
  //Retorna una lista cde struct proceso y guarda el len de la lista en lenlista
	char buff[LONGBUFF];
	int filaux = 0, cont = 0,primera_vez = 0,contar_filas = 0,contar_columnas = 0;
	while(fscanf(archivo,"%s",buff) != EOF){
		if(filaux == 0){
			if(cont == 4){
				filaux++;
				cont = 1;
			}
			cont++;
		}else{

			if(primera_vez == 0){
				p = (struct Proceso *) malloc(1*sizeof(struct Proceso));
				primera_vez++;
				contar_filas++;
			}else{
				if(contar_columnas == 4){
					contar_columnas = 0;
					contar_filas++;
					p = realloc(p,contar_filas*sizeof(struct Proceso));

				}
			}
			if(buff != " " || buff != "\t" || buff != "\n"){
				if(contar_columnas == 0){
						p[contar_filas - 1].pid = atoi(buff);
				}else if(contar_columnas == 1){
						p[contar_filas - 1].llegada = atoi(buff);
				}else if(contar_columnas == 2){
						p[contar_filas - 1].duracion = atoi(buff);
				}else{
					 p[contar_filas - 1].prioridad = atoi(buff);
				}
				contar_columnas++;

		 	}
		}

	}
	lenlista = contar_filas;
	fclose(archivo);
	return p;
}

void ordenarLLegada(struct Proceso *p){
  //OrdenaLista por Llegada
  struct Proceso temp;
	for (int i = 0 ; i < lenlista - 1; i++){
    for (int j = 0; j < lenlista - 1; j++){
      if (p[j].llegada >= p[j + 1].llegada) {
				if (p[j].llegada == p[j + 1].llegada){
					if(p[j].pid > p[j + 1].pid){
						temp = p[j];
						p[j] = p[j + 1];
						p[j + 1] = temp;
					}
				}else{
					temp = p[j];
					p[j] = p[j + 1];
					p[j + 1] = temp;
				}

      }
    }
  }

}

void ordenarDuracion(struct Proceso *p){
  //OrdenaLista por duracion
	struct Proceso temp;
	for (int i = 0 ; i < lenlista - 1; i++){
    for (int j = 0; j < lenlista - 1; j++){
      if (p[j].duracion >= p[j + 1].duracion) {
				if (p[j].duracion == p[j + 1].duracion){
					if(p[j].pid > p[j + 1].pid){
						temp = p[j];
						p[j] = p[j + 1];
						p[j + 1] = temp;
					}
				}else{
					temp = p[j];
					p[j] = p[j + 1];
					p[j + 1] = temp;
				}

      }
    }
  }

}

void ordenarPrioridad(struct Proceso *p){
  //OrdenaLista por Llegada
  struct Proceso temp;
	for (int i = 0 ; i < lenlista - 1; i++){
    for (int j = 0; j < lenlista - 1; j++){
      if (p[j].prioridad >= p[j + 1].prioridad) {
				if (p[j].prioridad == p[j + 1].prioridad){
					if(p[j].pid > p[j + 1].pid){
						temp = p[j];
						p[j] = p[j + 1];
						p[j + 1] = temp;
					}
				}else{
					temp = p[j];
					p[j] = p[j + 1];
					p[j + 1] = temp;
				}

      }
    }
  }

}

struct Proceso *copiarLista(struct Proceso *p){
  //Copiar lista (para retornar una lista aux)
	 struct Proceso *tmp = (struct Proceso *) malloc(lenlista*sizeof(struct Proceso));
	 for (int i = 0; i < lenlista; i++) {
	 	tmp[i].pid = p[i].pid;
		tmp[i].llegada = p[i].llegada;
		tmp[i].duracion = p[i].duracion;
		tmp[i].prioridad = p[i].prioridad;
	 }
   return tmp;
}

void escribirInicioTex(FILE *archivo_tex){
	fprintf(archivo_tex,"\\documentclass{article}\n");
	fprintf(archivo_tex,"\\usepackage[utf8]{inputenc}\n");
	fprintf(archivo_tex,"\\usepackage{pgfgantt}\n");
	fprintf(archivo_tex,"\\usepackage{showexpl}\n");
	fprintf(archivo_tex,"\\usepackage{tikz}\n");
	fprintf(archivo_tex,"\\usepackage{graphicx}\n");
	fprintf(archivo_tex,"\\usepackage{amsmath}\n");
	fprintf(archivo_tex, "\\title{Tarea SO 1}\n");
	fprintf(archivo_tex, "\n");
	fprintf(archivo_tex, "\\author{Jeffrey Ricardo Alfaro Fonseca }\n");
	fprintf(archivo_tex, "\\date{August 2018}\n");
	fprintf(archivo_tex, "\n");
	fprintf(archivo_tex, "\\begin{document}\n");
	fprintf(archivo_tex, "\\maketitle\n");
}

void escribirCuerpo(FILE *archivo_tex,struct Proceso *p,int len,int wt[], char *nombre_p){
	int ganttfinal = 0 ,gantinicio = 1,aux = 0;
	for (int i = 0; i < len; i++) {
		ganttfinal += p[i].duracion;
	}

	fprintf(archivo_tex,"\\section{%s}\n",nombre_p);
	fprintf(archivo_tex,"\\begin{ganttchart}[\n");
	fprintf(archivo_tex,"\tx unit  = 0.5cm,\n");
	fprintf(archivo_tex,"\thgrid ,\n");
	fprintf(archivo_tex,"\tvgrid\n");
	fprintf(archivo_tex,"\t]{%d}{%d}\n",gantinicio,ganttfinal);
	fprintf(archivo_tex,"\n");
	fprintf(archivo_tex, "\t\\gantttitle{Diagrama %s}{%d} \\\\ \n",nombre_p,ganttfinal);
	fprintf(archivo_tex, "\t\\gantttitle{Tiempo Transcurrido}{%d}\\\\ \n",ganttfinal);
	fprintf(archivo_tex, "\t\\gantttitlelist{%d,...,%d}{%d} \\\\ \n",gantinicio,ganttfinal,gantinicio);

	for (int i = 0; i < len; i++) {
		if (i != 0) {
				fprintf(archivo_tex, "\t \\ganttlinkedbar{P%d}{%d}{%d} \\\\   \n",p[i].pid,gantinicio ,(gantinicio + p[i].duracion - 1));
		}else{
				fprintf(archivo_tex, "\t\\ganttbar{P%d}{%d}{%d} \\\\  \n",p[i].pid,gantinicio,p[i].duracion);
		}
		gantinicio += p[i].duracion;
		//aux += p[i].duracion;
	}

	fprintf(archivo_tex, "\\end{ganttchart}\n");
	fprintf(archivo_tex, "\\ \\ \\ \n");


		fprintf(archivo_tex, "\\begin{center}\n");
		fprintf(archivo_tex, "\\begin{tabular}{ c  c }\n");
		fprintf(archivo_tex, "\\multicolumn{2}{c}{Waiting Time } \\\\\n");
		fprintf(archivo_tex, "Process ID & Tiempo \\\\ [0.5ex]\n");
		int total = 0;
		for (int i = 0; i < len; i++) {
				fprintf(archivo_tex, "%d & %d\\\\\n",p[i].pid,wt[i]);
				total += wt[i];
		}
		fprintf(archivo_tex, "Total & %d/%d \\\\\n",total,lenlista);
		fprintf(archivo_tex, "\\end{tabular}\n");
		fprintf(archivo_tex, "\\end{center}\n");

}
/*
*
*
*
*		No expropiativos
*
*
*/

/*************Fifo**********************/
void escribirFIFO(struct Proceso *fifo,FILE *archivo_tex){
	int duracion_total = fifo[0].llegada;
	int wt[lenlista];
	wt[0] = 0;

	/*printf("FIFO\n");
	printf("--------------------------\n");*/
	for (int i = 0; i < lenlista; i++) {
		duracion_total += fifo[i].duracion;
		if(i >= 1){
			wt[i] = duracion_total - fifo[i].duracion - fifo[i].llegada;
		}
		/*printf("Pid: P%d ", fifo[i].pid);
		printf("Llegada: %d ", fifo[i].llegada);
		printf("Duracion: %d ", fifo[i].duracion);
		printf("Prioridad: %d ", fifo[i].prioridad);
		printf("\n");*/
	}

	/*int total = 0;
	printf("WT => ");
	for (int i = 0; i < lenlista; i++) {
		printf("%d ",wt[i]);
		total += wt[i];
	}
	printf(" = %d/%d\n",total,lenlista);
	printf("--------------------------\n");*/
	escribirCuerpo(archivo_tex,fifo,lenlista,wt, "FIFO");
	free(fifo);
}

/************HPF**********************/
void escribirHPF(struct Proceso *hpf,FILE *archivo_tex){
	int p_actual = 1000, pos_actual = 0;
	int prioridad_actual = -1, duracion_total = 0;
  int wt[lenlista];
	struct Proceso aux;
	int iactual = 0, entro = 0;
	int tiempo_llegada_actual = 1000;
	int pos_menor_tiempo_llegada = 0;
	int primer_pro = 1;

	for (int z = 0; z < lenlista; z++) {
			if(hpf[z].llegada < tiempo_llegada_actual){
				tiempo_llegada_actual = hpf[z].llegada;

			}
	}
	duracion_total += tiempo_llegada_actual;
	for (int i = 0; i < lenlista - 1; i++) {
		prioridad_actual = -1;
		for (int j = i; j < lenlista; j++) {
			if(hpf[j].llegada <= tiempo_llegada_actual){
				//printf("duracion_total%d\n",tiempo_llegada_actual);
				if(hpf[j].prioridad < prioridad_actual || prioridad_actual ==  - 1){
					pos_actual = j;
					p_actual = hpf[j].pid;
					prioridad_actual = hpf[j].prioridad;

					entro = 1;
				}else if(hpf[j].prioridad == prioridad_actual || prioridad_actual == -1){
					if (hpf[j].pid < p_actual) {

						pos_actual = j;
						p_actual = hpf[j].pid;
						prioridad_actual = hpf[j].prioridad;
						entro = 1;
					}
				}
			}
		}
		aux = hpf[i];
		hpf[i] = hpf[pos_actual];
		hpf[pos_actual] = aux;
		duracion_total+= hpf[i].duracion;
		tiempo_llegada_actual = duracion_total;

		if(primer_pro == 0){
			wt[i] = duracion_total - hpf[i].llegada - hpf[i].duracion;
		}else{
			wt[i] = 0;
			primer_pro = 0;
		}
	}
	duracion_total+= hpf[lenlista - 1].duracion;
	wt[lenlista - 1] = duracion_total - hpf[lenlista - 1].llegada - hpf[lenlista - 1].duracion;
	/*printf("HPF\n");
	printf("--------------------------\n");
	for (int i = 0; i < lenlista; i++) {

		printf("Pid: P%d ", hpf[i].pid);
		printf("Llegada: %d ", hpf[i].llegada);
		printf("Duracion: %d ", hpf[i].duracion);
		printf("Prioridad: %d ", hpf[i].prioridad);
		printf("\n");
	}
	int total = 0;
	printf("WT => ");
	for (int i = 0; i < lenlista; i++) {
		printf("%d ",wt[i]);
		total += wt[i];
	}
	printf(" = %d/%d\n",total,lenlista);
	printf("--------------------------\n");*/
	escribirCuerpo(archivo_tex,hpf,lenlista,wt, "HPF");
	free(hpf);
}

/***********SJF*********************/
void escribirSJF(struct Proceso *sjf,FILE *archivo_tex){
	int p_actual = 1000, pos_actual = 0;
	int duracion_actual = 0, duracion_total = 0;
  int wt[lenlista];
	struct Proceso aux;
	int iactual = 0, entro = 0;
	int tiempo_llegada_actual = 1000;
	int pos_menor_tiempo_llegada = 0;
	int primer_pro = 1;

	for (int z = 0; z < lenlista; z++) {
			if(sjf[z].llegada < tiempo_llegada_actual){
				tiempo_llegada_actual = sjf[z].llegada;

			}
	}
	duracion_total += tiempo_llegada_actual;
	for (int i = 0; i < lenlista - 1; i++) {
		duracion_actual = -1;
		for (int j = i; j < lenlista; j++) {
			if(sjf[j].llegada <= tiempo_llegada_actual){
				if(sjf[j].duracion < duracion_actual || duracion_actual == - 1){
					pos_actual = j;
					p_actual = sjf[j].pid;
					duracion_actual = sjf[j].duracion;

					entro = 1;
				}else if(sjf[j].duracion == duracion_actual || duracion_actual == -1){
					if (sjf[j].pid < p_actual) {

						pos_actual = j;
						p_actual = sjf[j].pid;
						duracion_actual = sjf[j].duracion;
						entro = 1;
					}
				}
			}
		}
		aux = sjf[i];
		sjf[i] = sjf[pos_actual];
		sjf[pos_actual] = aux;
		duracion_total+= sjf[i].duracion;
		tiempo_llegada_actual = duracion_total;

		if(primer_pro == 0){
			wt[i] = duracion_total - sjf[i].llegada - sjf[i].duracion;
		}else{
			wt[i] = 0;
			primer_pro = 0;
		}
	}
	duracion_total+= sjf[lenlista - 1].duracion;
	wt[lenlista - 1] = duracion_total - sjf[lenlista - 1].llegada - sjf[lenlista - 1].duracion;
	/*
	printf("SJF\n");
	printf("--------------------------\n");
	for (int i = 0; i < lenlista; i++) {

		printf("Pid: P%d ", sjf[i].pid);
		printf("Llegada: %d ", sjf[i].llegada);
		printf("Duracion: %d ", sjf[i].duracion);
		printf("Prioridad: %d ", sjf[i].prioridad);
		printf("\n");
	}

	int total = 0;
	printf("WT => ");
	for (int i = 0; i < lenlista; i++) {
		printf("%d ",wt[i]);
		total += wt[i];
	}
	printf(" = %d/%d\n",total,lenlista);

	printf("--------------------------\n");*/
	escribirCuerpo(archivo_tex,sjf,lenlista,wt, "SJF");
	free(sjf);
}

/*
*
*
*		Expropiativo
*
*
*/

/******************HPF EXP********************/
void escribirHPF_EXP(struct Proceso *hpf_exp,FILE *archivo_tex){
	int p_actual = 1000, pos_actual = 0;
	int prioridad_actual = -1, duracion_total = 0,duracion_aux = 0, duracion_aux2 = 1000, nuevo_tiempo_llegada = 0;
  int wt[lenlista];
	struct Proceso aux;
	struct Proceso aux2;
	int iactual = 0, entro = 0, duracion_tmp = 0;
	int tiempo_llegada_actual = 1000;
	int pos_menor_tiempo_llegada = 0;
	int primer_pro = 1;
	int len_aux = lenlista, duracionmenoracero = 0;
	int tiempototal = 0;
	for (int z = 0; z < lenlista; z++) {
			if(hpf_exp[z].llegada < tiempo_llegada_actual){
				tiempo_llegada_actual = hpf_exp[z].llegada;

			}
	}
	duracion_total += tiempo_llegada_actual;
	duracion_aux += tiempo_llegada_actual;
	for (int i = 0; i < len_aux ; i++) {
		prioridad_actual = -1;
		for (int j = i; j < len_aux; j++) {
			if(hpf_exp[j].llegada <= duracion_aux){
			if(hpf_exp[j].prioridad < prioridad_actual || prioridad_actual ==  - 1){
					pos_actual = j;
					p_actual = hpf_exp[j].pid;
					prioridad_actual = hpf_exp[j].prioridad;
				}else if(hpf_exp[j].prioridad == prioridad_actual || prioridad_actual == -1){
					if (hpf_exp[j].pid < p_actual) {
						pos_actual = j;
						p_actual = hpf_exp[j].pid;
						prioridad_actual = hpf_exp[j].prioridad;
					}
				}
			}
		}
		aux = hpf_exp[i];
		hpf_exp[i] = hpf_exp[pos_actual];
		hpf_exp[pos_actual] = aux;
		duracion_total+= hpf_exp[i].duracion;
		tiempo_llegada_actual = duracion_total;
		duracion_aux++;
		duracion_aux2 = 1000;
		for (int z = i; z < len_aux; z++) {
				if(hpf_exp[z].llegada < duracion_aux2){
					duracion_aux2 = hpf_exp[z].llegada;

				}
		}
		duracion_aux += duracion_aux2;
		if (primer_pro == 0) {
			if(hpf_exp[i].prioridad  < hpf_exp[i - 1].prioridad){
					len_aux = len_aux + 1;
					hpf_exp = realloc(hpf_exp,len_aux*sizeof(struct Proceso));
					duracion_tmp =  hpf_exp[i - 1].duracion;
					hpf_exp[i - 1].duracion = 1;

					aux2.pid =  hpf_exp[i - 1].pid;
					aux2.duracion = duracion_tmp - 1;
					aux2.llegada = hpf_exp[i - 1].llegada;
					aux2.prioridad = hpf_exp[i - 1].prioridad;
					hpf_exp[len_aux - 1] = aux2;
				}
		}
		primer_pro = 0;

	}

	int lleg = 0,llegaux;
	for (int i = 0; i < len_aux; i++) {
		lleg += hpf_exp[i].duracion;
		llegaux = 0;
		for (int j = i; j < len_aux; j++) {
			if(i != j){
				llegaux += hpf_exp[i].duracion;
				if(hpf_exp[j].pid == hpf_exp[i].pid){
					hpf_exp[j].llegada = llegaux - lleg;
				}

			}
		}
	}
	wt[len_aux];
	wt[0] = 0;
	//printf("HPF-Expropiativo\n");
	//printf("--------------------------\n");
	nuevo_tiempo_llegada += hpf_exp[0].duracion;
	for (int i = 0; i < len_aux; i++) {
		if(i > 0){
			wt[i] = nuevo_tiempo_llegada - hpf_exp[i].llegada;
			nuevo_tiempo_llegada += hpf_exp[i].duracion;

		}
		//printf("Pid: P%d ", hpf_exp[i].pid);
		//printf("Llegada: %d ", hpf_exp[i].llegada);
	//	printf("Duracion: %d ", hpf_exp[i].duracion);
		//printf("Prioridad: %d ", hpf_exp[i].prioridad);
		//printf("\n");
	}

	/*int total = 0;
	printf("WT => ");
	for (int i = 0; i < len_aux; i++) {
		printf("%d ",wt[i]);
		total += wt[i];
	}
	printf(" = %d/%d\n",total,lenlista);
	printf("--------------------------\n");*/
	escribirCuerpo(archivo_tex,hpf_exp,len_aux,wt, "HPF-Expropiativo");
	free(hpf_exp);
}

/******************RR*************************/
void escribirRR(struct Proceso *rr,int tiempo,FILE *archivo_tex){
	int len_aux = lenlista;
	struct Proceso aux;
	int duracion_total = 0, duracion_aux = 0, duracion_total_aux = 0;
	duracion_total += rr[0].llegada;
	for (int i = 0; i < len_aux; i++) {

			duracion_aux = rr[i].duracion - tiempo;

			if(duracion_aux > 0){
				duracion_total += tiempo;
				len_aux = len_aux + 1;
				rr = realloc(rr,len_aux*sizeof(struct Proceso));
				rr[i].duracion = tiempo;
				aux.pid =  rr[i].pid;
				aux.duracion = duracion_aux;
				aux.llegada = duracion_total;
				aux.prioridad = rr[i].prioridad;
				rr[len_aux - 1] = aux;
			}else{
				duracion_total += rr[i].duracion;
			}
	}

	int wt[len_aux];
	int total_tiempo = rr[0].llegada;
	wt[0] = 0;

	//printf("RR-%d\n",tiempo);
	//printf("--------------------------\n");
	for (int i = 0; i < len_aux; i++) {
		total_tiempo += rr[i].duracion;
		if (i > 0) {
			wt[i] =  total_tiempo - rr[i].llegada - rr[i].duracion;
		}
		/*printf("Pid: P%d ", rr[i].pid);
		printf("Llegada: %d ", rr[i].llegada);
		printf("Duracion: %d ", rr[i].duracion);
		printf("Prioridad: %d ", rr[i].prioridad);
		printf("\n");*/
	}
	/*int total = 0;
	printf("WT => ");
	for (int i = 0; i < len_aux; i++) {
		printf("%d ",wt[i]);
		total += wt[i];
	}
	printf(" = %d/%d\n",total,lenlista);
	printf("--------------------------\n");*/
	if(tiempo == 2){
			escribirCuerpo(archivo_tex,rr,len_aux,wt, "RR-2");
	}else{
			escribirCuerpo(archivo_tex,rr,len_aux,wt, "RR-3");
	}

	free(rr);
}

/***************SRT*******************/
void escribirSRT(struct Proceso *srt,FILE *archivo_tex){
	int p_actual = 1000, pos_actual = 0 , len_aux = lenlista;
	int duracion_actual = 0, duracion_total = 0,nuevo_tiempo_llegada = 0;
  int wt[lenlista];
	struct Proceso aux, aux2;
	int iactual = 0, entro = 0;
	int tiempo_llegada_actual = 1000;
	int pos_menor_tiempo_llegada = 0;
	int primer_pro = 1;
	int crono = 0 , crono_aux = 0, duracion_tmp = 0;
	for (int z = 0; z < lenlista; z++) {
			if(srt[z].llegada < tiempo_llegada_actual){
				tiempo_llegada_actual = srt[z].llegada;

			}
	}
	duracion_total += tiempo_llegada_actual;
	crono = tiempo_llegada_actual;
	for (int i = 0; i < len_aux; i++) {
		duracion_actual = -1;
		for (int j = i; j < len_aux; j++) {
			if(srt[j].llegada <= tiempo_llegada_actual){
				if(srt[j].duracion < duracion_actual || duracion_actual == - 1){
					pos_actual = j;
					p_actual = srt[j].pid;
					duracion_actual = srt[j].duracion;

					entro = 1;
				}else if(srt[j].duracion == duracion_actual || duracion_actual == -1){
					if (srt[j].pid < p_actual) {

						pos_actual = j;
						p_actual = srt[j].pid;
						duracion_actual = srt[j].duracion;
						entro = 1;
					}
				}
			}
		}
		aux = srt[i];
		srt[i] = srt[pos_actual];
		srt[pos_actual] = aux;
		crono++;
		crono_aux = 1000;
		for (int z = i; z < len_aux; z++) {
				if(srt[z].llegada < crono_aux){
					crono_aux = srt[z].llegada;
				}
		}
		crono += crono_aux;
		duracion_total+= srt[i].duracion;
		tiempo_llegada_actual = duracion_total;
		if (primer_pro == 0) {
			if(srt[i].duracion  < srt[i - 1].duracion){
				if(srt[i - 1].duracion - srt[i].duracion > srt[i].duracion){
					len_aux = len_aux + 1;
					srt = realloc(srt,len_aux*sizeof(struct Proceso));
					duracion_tmp =  srt[i - 1].duracion;
					srt[i - 1].duracion = crono - srt[i].llegada - srt[i - 1].llegada - srt[i - 1].duracion;
					aux2.pid =  srt[i - 1].pid;
					aux2.duracion = duracion_tmp - srt[i].llegada;
					if(aux2.duracion < 0){
						aux2.duracion *= -1;
					}
					aux2.llegada = srt[i - 1].llegada;
					aux2.prioridad = srt[i - 1].prioridad;

					srt[len_aux - 1] = aux2;
				}
			}
		}
		primer_pro = 0;


	}

	int lleg = 0,llegaux;
	for (int i = 0; i < len_aux; i++) {
		lleg += srt[i].duracion;
		llegaux = 0;
		for (int j = i; j < len_aux; j++) {
			if(i != j){
				llegaux += srt[i].duracion;
				if(srt[j].pid == srt[i].pid){
					srt[j].llegada = llegaux - lleg;
				}

			}
		}
	}
	wt[len_aux];
	wt[0] = 0;
	//printf("SRT\n");
	//printf("--------------------------\n");
	nuevo_tiempo_llegada += srt[0].duracion;
	for (int i = 0; i < len_aux; i++) {
		if(i > 0){
			wt[i] = nuevo_tiempo_llegada - srt[i].llegada;
			nuevo_tiempo_llegada += srt[i].duracion;

		}
		/*printf("Pid: P%d ", srt[i].pid);
		printf("Llegada: %d ", srt[i].llegada);
		printf("Duracion: %d ", srt[i].duracion);
		printf("Prioridad: %d ", srt[i].prioridad);
		printf("\n");*/
	}

/*	int total = 0;
	printf("WT => ");
	for (int i = 0; i < len_aux; i++) {
		printf("%d ",wt[i]);
		total += wt[i];
	}
	printf(" = %d/%d\n",total,lenlista);
	printf("--------------------------\n");*/
	escribirCuerpo(archivo_tex,srt,len_aux,wt, "SRT");
	free(srt);
}

/*
*
*
*		Llamada a los metodos
*
*
*/

void FIFO(struct Proceso *p,FILE *archivo_tex){
	  struct Proceso *fifo = copiarLista(p);
		ordenarLLegada(fifo);
		escribirFIFO(fifo,archivo_tex);

}

void HPF(struct Proceso *p,FILE *archivo_tex){
	struct Proceso *hpf = copiarLista(p);
	ordenarPrioridad(hpf);
	escribirHPF(hpf,archivo_tex);
}

void SJF(struct Proceso *p,FILE *archivo_tex){
	struct Proceso *sjf = copiarLista(p);
	ordenarDuracion(sjf);
	escribirSJF(sjf,archivo_tex);

}

void SRT(struct Proceso *p,FILE *archivo_tex){
	struct Proceso *srt = copiarLista(p);
	ordenarDuracion(srt);
	escribirSRT(srt,archivo_tex);

}

void RR(struct Proceso *p,int tiempo,FILE *archivo_tex){
	struct Proceso *rr = copiarLista(p);
	ordenarLLegada(rr);
	escribirRR(rr,tiempo,archivo_tex);
}

void HPF_EXP(struct Proceso *p,FILE *archivo_tex){
	struct Proceso *hpf_exp = copiarLista(p);
	ordenarPrioridad(hpf_exp);
	escribirHPF_EXP(hpf_exp,archivo_tex);
}

int main(int argc, char* argv[]){
	//Nombre Archivo

	const char *nombre_archivo = argv[1];
	const char *nombre_tex = argv[2];

	if (nombre_archivo == NULL || nombre_tex == NULL) {
		printf("Introdusca los parametros correctos\n");
		return -1;
	}
	// Lista de procesos
	struct Proceso *p;
	// Abrimos Archhivo modo lectura
	FILE *archivo  = fopen(nombre_archivo,lectura);
	if(archivo == NULL){
		printf("No existe el archivo\n");
		return -1;
	}
	printf("Escribiendo archivo .");
	// Llenamos la lista
	p = setLista(archivo, p);
	//Archivo modo escritura
	printf(".");
	FILE *archivo_tex = fopen(nombre_tex,escritura);
	//Escribimos el inicio del tex
	printf(".");
	escribirInicioTex(archivo_tex);
	printf(".");
	//FIFO
	FIFO(p,archivo_tex);
	printf(".");
	//SJF
	SJF(p,archivo_tex);
	printf(".");
	//HPF
	HPF(p,archivo_tex);
	printf(".");
	//RR-2
	RR(p,2,archivo_tex);
	printf(".");
	//RR-3
	RR(p,3,archivo_tex);
	printf(".");
	//HPF - Expropiativo
	HPF_EXP(p,archivo_tex);
	printf(".");
	//SRT
	SRT(p,archivo_tex);

	fprintf(archivo_tex, "\\end{document}");
	fclose(archivo_tex);
	free(p);
	printf("\nArchivo Escrito\n");
	return 0;

}
