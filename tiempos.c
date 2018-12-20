/**
 *
 * Descripcion: Implementacion de funciones de tiempo
 *
 * Fichero: tiempos.c
 * Autor: Carlos Aguirre Maeso
 * Version: 1.0
 * Fecha: 16-09-2017
 *
 */
#include <time.h>
#include <unistd.h>
#include "tiempos.h"
#include "ordenacion.h"
#include "permutaciones.h"
#include "busqueda.h"

/***************************************************/
/* Funcion: minTabla           Fecha: 29/10/2018   */
/* Autores: Pablo Borrelli, Pablo Sánchez          */
/*                                                 */
/* Escoje el menor elemento en una tabla           */
/*                                                 */
/* Entrada:                                        */
/* double *tabla: La tabla                         */
/* int N: El tamanio de la tabla                   */
/* Salida:                                         */
/* double El menor numero de la tabla              */
/*                                                 */
/***************************************************/
double minTabla(double *tabla, int N)
{
	int min=0, j;

	if(N==1)
		return tabla[min];

	for(j = 0; j < N; j++){
		if(tabla[j]<tabla[min])
			min = j;
	}

	return tabla[min];
}

/***************************************************/
/* Funcion: maxTabla           Fecha: 29/10/2018   */
/* Autores: Pablo Borrelli, Pablo Sánchez          */
/*                                                 */
/* Escoje el mayor elemento en una tabla           */
/*                                                 */
/* Entrada:                                        */
/* double *tabla: La tabla                         */
/* int N: El tamanio de la tabla                   */
/* Salida:                                         */
/* double El mayor numero de la tabla              */
/*                                                 */
/***************************************************/
double maxTabla(double *tabla, int N)
{
	int max=0, j;

	if(N==1)
		return tabla[max];

	for(j = 0; j < N; j++){
		if(tabla[j]>tabla[max])
			max = j;
	}

	return tabla[max];
}

/***************************************************/
/* Funcion:tiempo_medio_ordenacion Fecha:14/12/2018*/
/* Autores: Pablo Borrelli, Pablo Sánchez          */
/*                                                 */
/* Realiza medidas de rendimiento de los           */
/* algoritmos de ordenacion                        */
/*                                                 */
/* Entrada:                                        */
/* pfunc_ordena metodo: metodo de ordenacion       */
/* int n_perms: numero de permutaciones a ordenar  */
/* int N: numero de elementos de las permutaciones */
/* PTIEMPO ptiempo: guarda los datos de los tiempos*/
/* Salida:                                         */
/* short ERR en caso de error, OK en caso contrario*/
/*                                                 */
/***************************************************/
short tiempo_medio_ordenacion(pfunc_ordena metodo,
							  int n_perms,
							  int N,
							  PTIEMPO ptiempo)
{
	int i;
	double tabla_ob[n_perms];
	int** tabla = NULL;
	struct timespec start, finish;
	double tiempo=0, media=0, media_ob=0;

	//tabla_ob = calloc(N, sizeof(double));

	if(!metodo || n_perms < 1 || N < 1){
		return ERR;
	}

	tabla = genera_permutaciones(n_perms, N);

	ptiempo->n_elems = n_perms;
	ptiempo->N = N;

	for(i=0; i<n_perms; i++){

		clock_gettime(CLOCK_REALTIME, &start);

		tabla_ob[i] = metodo(tabla[i], 0, N-1);

		clock_gettime(CLOCK_REALTIME, &finish);

		tiempo = (double) (finish.tv_sec - start.tv_sec) + NANOSEC*(finish.tv_nsec - start.tv_nsec);

		media+= tiempo;
	}

	media = (double) media/(n_perms);
	for(i=0; i<n_perms; i++)
		media_ob += tabla_ob[i];
	media_ob = (double) media_ob/(n_perms);

	ptiempo->tiempo = media;
	ptiempo->medio_ob = media_ob;
	ptiempo->min_ob = (int) minTabla(tabla_ob, n_perms);
	ptiempo->max_ob = (int) maxTabla(tabla_ob, n_perms);

	for(i=0; i<n_perms; i++)
	  free(tabla[i]);
	free(tabla);
	return OK;
}

/***************************************************/
/* Funcion:tiempo_medio_busqueda Fecha:14/12/2018  */
/* Autores: Pablo Borrelli, Pablo Sánchez          */
/*                                                 */
/* Realiza medidas de rendimiento de los           */
/* algoritmos de busqueda                          */
/*                                                 */
/* Entrada:                                        */
/* pfunc_busqueda metodo: metodo de busqueda       */
/* pfunc_generador_claves generador: metodo de     */
/* generacion de claves                            */
/* int orden:define si tabla ordenada o no ordenada*/
/* int N: numero de elementos de las permutaciones */
/* int n_veces: veces que se busca cada clave      */
/* PTIEMPO ptiempo: guarda los datos de los tiempos*/
/* Salida:                                         */
/* short ERR en caso de error, OK en caso contrario*/
/*                                                 */
/***************************************************/
short tiempo_medio_busqueda(pfunc_busqueda metodo, pfunc_generador_claves generador,
                              int orden,
                              int N,
                              int n_veces,
                              PTIEMPO ptiempo)
{
	PDICC dicc = NULL;
	int * perm = NULL;
	int * claves = NULL;
	double tabla_ob[n_veces*N];
	int i, pos;
	struct timespec start, finish;
	double tiempo=0, media=0, media_ob=0;

	dicc = ini_diccionario(N, orden);
	if(!dicc){
		return ERR;
	}

	perm = genera_perm(N);
	if(!perm){
		goto err0;
	}

	if(insercion_masiva_diccionario(dicc, perm, N) == ERR){
		goto err1;
	}

	claves = (int *)malloc(sizeof(int)*n_veces*N);
	if(!claves){
		goto err1;
	}

	generador(claves, n_veces*N, N);

	ptiempo->n_elems = n_veces * N;
	ptiempo->N = N;

	for(i=0; i<ptiempo->n_elems; i++){

		clock_gettime(CLOCK_REALTIME, &start);

		tabla_ob[i] = busca_diccionario(dicc, claves[i], &pos, metodo);

		clock_gettime(CLOCK_REALTIME, &finish);

		tiempo = (double) (finish.tv_sec - start.tv_sec) + NANOSEC*(finish.tv_nsec - start.tv_nsec);

		media+= tiempo;
	}


	media = (double) media/(ptiempo->n_elems);
	for(i=0; i<ptiempo->n_elems; i++)
		media_ob += tabla_ob[i];
	media_ob = (double) media_ob/(ptiempo->n_elems);

	ptiempo->tiempo = media;
	ptiempo->medio_ob = media_ob;
	ptiempo->min_ob = (int) minTabla(tabla_ob, ptiempo->n_elems);
	ptiempo->max_ob = (int) maxTabla(tabla_ob, ptiempo->n_elems);

	free(perm);
	free(claves);
	libera_diccionario(dicc);
	return OK;

	err1:
		free(perm);
	err0:
		libera_diccionario(dicc);
		return ERR;

}

/***************************************************/
/*Funcion:genera_tiempos_ordenacion Fecha:14/12/2018*/
/* Autores: Pablo Borrelli, Pablo Sánchez          */
/*                                                 */
/* Automatiza la toma de tiempos                   */
/*                                                 */
/* Entrada:                                        */
/* pfunc_ordena metodo: metodo de ordenacion       */
/* char *fichero: nombre fichero guardar tiempos   */
/* int num_min: numero minimo de elementos tabla   */
/* int num_max: numero maximo elementos tabla      */
/* int incr: cantidad con la que incrementa        */
/* tamanio tabla                                   */
/* int n_perms: permutaciones que se ordenaran     */
/* Salida:                                         */
/* short ERR en caso de error, OK en caso contrario*/
/*                                                 */
/***************************************************/
short genera_tiempos_ordenacion(pfunc_ordena metodo, char* fichero,
								int num_min, int num_max,
								int incr, int n_perms)
{
	int i;
	int perms_imprimir;
	PTIEMPO ptiempo = NULL;

	perms_imprimir = ((num_max - num_min)/incr) + 1;
	ptiempo =(PTIEMPO) malloc (perms_imprimir*sizeof(TIEMPO));

	if(!metodo || !fichero || num_min >= num_max || incr<1 || n_perms<1|| !ptiempo){
		return ERR;
	}


	for(i=0; num_min <= num_max; num_min+=incr , i++){
		if(tiempo_medio_ordenacion(metodo, n_perms, num_min, &ptiempo[i]) == ERR)
			return ERR;
	}
	guarda_tabla_tiempos(fichero, ptiempo, perms_imprimir);

	free(ptiempo);
	return OK;
}

/***************************************************/
/* Funcion:genera_tiempos_busqueda Fecha:14/12/2018*/
/* Autores: Pablo Borrelli, Pablo Sánchez          */
/*                                                 */
/* Automatiza la toma de tiempos                   */
/*                                                 */
/* Entrada:                                        */
/* pfunc_busqueda metodo: metodo de busqueda       */
/* pfunc_generador_claves generador: metodo de     */
/* generacion de claves                            */
/* int orden:define si tabla ordenada o no ordenada*/
/* char *fichero: nombre fichero guardar tiempos   */
/* int num_min: numero minimo de elementos tabla   */
/* int num_max: numero maximo elementos tabla      */
/* int incr: cantidad con la que incrementa        */
/* tamanio tabla                                   */
/* int n_veces: veces que se busca cada clave      */
/* Salida:                                         */
/* short ERR en caso de error, OK en caso contrario*/
/*                                                 */
/***************************************************/
short genera_tiempos_busqueda(	pfunc_busqueda metodo, pfunc_generador_claves generador,
								int orden, char * fichero,
								int num_min, int num_max,
								int incr, int n_veces)
{
	int i;
	int perms_imprimir;
	PTIEMPO ptiempo = NULL;

	perms_imprimir = ((num_max - num_min)/incr) + 1;

	ptiempo =(PTIEMPO) malloc (perms_imprimir*sizeof(TIEMPO));

	if(!metodo || !fichero || num_min >= num_max || incr<1 || n_veces<1|| !ptiempo){
		return ERR;
	}


	for(i=0; num_min <= num_max; num_min+=incr , i++){
		if(tiempo_medio_busqueda(metodo, generador, orden, num_min, n_veces, &ptiempo[i]) == ERR)
			return ERR;
	}
	guarda_tabla_tiempos(fichero, ptiempo, perms_imprimir);

	free(ptiempo);
	return OK;
}


/***************************************************/
/* Funcion: guarda_tabla_tiempos Fecha: 14/12/2018 */
/*                                                 */
/* Guarda un fichero con los datos de los tiempos  */
/* y las cantidades de operaciones basicas         */
/*                                                 */
/* Entrada:                                        */
/* char *fichero: nombre fichero guardar tiempos   */
/*PTIEMPO ptiempo:contiene los datos de los tiempos*/
/* int n_tiempos:numero de tiempos que se guardaran*/
/* Salida:                                         */
/* short ERR en caso de error, OK en caso contrario*/
/*                                                 */
/***************************************************/
short guarda_tabla_tiempos(char* fichero, PTIEMPO tiempo, int n_tiempos)
{
	int i;
	FILE * file = NULL;

	file = fopen(fichero, "w");
	if(!file)
		return ERR;


	fprintf(file, "Num ej\tTamaño\tTiempo(sec)\t\tMedia OB\t\tMin OB\tMax OB\n");

	for(i=0; i<=n_tiempos-1; i++)
	{
		fprintf(file, "%d)\t", i+1);
		fprintf(file, "%d\t", tiempo[i].N);
		fprintf(file, "%.10e\t", tiempo[i].tiempo);
		fprintf(file, "%.10e\t", tiempo[i].medio_ob);
		fprintf(file, "%d\t", tiempo[i].min_ob);
		fprintf(file, "%d\t", tiempo[i].max_ob);
		fprintf(file, "\n");
	}

	fclose(file);

	return OK;
}
