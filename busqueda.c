/**
 *
 * Descripcion: Implementacion funciones para busqueda 
 *
 * Fichero: busqueda.c
 * Autor: Carlos Aguirre
 * Version: 1.0
 * Fecha: 11-11-2016
 *
 */

#include "busqueda.h"

#include <stdlib.h>
#include <math.h>
#include <time.h>

/**
 *  Funciones de geracion de claves
 *
 *  Descripcion: Recibe el numero de claves que hay que generar
 *               en el parametro n_claves. Las claves generadas
 *               iran de 1 a max. Las claves se devuelven en 
 *               el parametro claves que se debe reservar externamente
 *               a la funcion.
 */
  
/**
 *  Funcion: generador_claves_uniforme
 *               Esta fucnion genera todas las claves de 1 a max de forma 
 *               secuencial. Si n_claves==max entonces se generan cada clave
 *               una unica vez.
 */
void generador_claves_uniforme(int *claves, int n_claves, int max)
{
  int i;

  for(i = 0; i < n_claves; i++) claves[i] = 1 + (i % max);

  return;
}

/***************************************************/
/* Funcion: ini_diccionario    Fecha: 14/12/2018   */
/* Autores: Pablo Borrelli, Pablo Sánchez          */
/*                                                 */
/* Inicializa la estructura diccionario            */
/*                                                 */
/* Entrada:                                        */
/* int tamanio: Numero de elementos del diccionario*/
/* char orden: Define si esta ordenado o no        */
/* Salida:                                         */
/* PDICC Puntero a la nueva estructura             */
/*                                                 */
/***************************************************/
PDICC ini_diccionario (int tamanio, char orden)
{
	PDICC dic;
struct timespec start, finish;
	double tiempo=0, media=0, media_ob=0;
	if(tamanio<1)
		return NULL;

	dic = (PDICC) malloc(sizeof(DICC));
	if(!dic)
		return NULL;
	
	dic->tamanio = tamanio;
	dic->orden = orden;
	dic->n_datos = 0;

	dic->tabla = (int*) malloc(sizeof(int)*tamanio);
	if(!dic->tabla){
		free(dic);
		return NULL;
	}

	return dic;
}

/***************************************************/
/* Funcion: libera_diccionario  Fecha: 14/12/2018  */
/* Autores: Pablo Borrelli, Pablo Sánchez          */
/*                                                 */
/* Libera la estructura diccionario                */
/*                                                 */
/* Entrada:                                        */
/* PDICC pdicc: puntero a la estructura a liberar  */
/*                                                 */
/***************************************************/
void libera_diccionario(PDICC pdicc)
{
	if(!pdicc)
		return;
	free(pdicc->tabla);
	free(pdicc);
	return;
}

/***************************************************/
/* Funcion: inserta_diccionario  Fecha: 14/12/2018 */
/* Autores: Pablo Borrelli, Pablo Sánchez          */
/*                                                 */
/* Inserta un elemento en el diccionario           */
/*                                                 */
/* Entrada:                                        */
/* PDICC pdicc: Diccionario                        */
/* int clave: Dato a insertar                      */
/* Salida:                                         */
/* int OK o ERR en caso de fallo                   */
/*                                                 */
/***************************************************/
int inserta_diccionario(PDICC pdicc, int clave)
{
	int a, j;

	if(pdicc->tamanio == pdicc->n_datos)
		return ERR;
	
	pdicc->tabla[pdicc->n_datos] = clave;
	pdicc->n_datos++;

	if(pdicc->orden == ORDENADO){
		a = pdicc->tabla[pdicc->n_datos - 1];
		j = pdicc->n_datos - 2;

		while(j >= 0 && pdicc->tabla[j]>a){
			pdicc->tabla[j+1] = pdicc->tabla[j];
			j--;
		}
		pdicc->tabla[j+1] = a; 
	}

	return OK;
}

/***************************************************/
/* Funcion: insercion_masiva_diccionario           */
/*                               Fecha: 14/12/2018 */
/* Autores: Pablo Borrelli, Pablo Sánchez          */
/*                                                 */
/* Inserta una serie de elementos en el diccionario*/
/*                                                 */
/* Entrada:                                        */
/* PDICC pdicc: Diccionario                        */
/* int *claves: Datos a insertar                   */
/* int nclaves: Numero de datos a insertar         */
/* Salida:                                         */
/* int OK o ERR en caso de fallo                   */
/*                                                 */
/***************************************************/
int insercion_masiva_diccionario (PDICC pdicc,int *claves, int n_claves)
{
	int i;
	
	if(pdicc->n_datos + n_claves > pdicc->tamanio || !pdicc)
		return ERR;

	for(i=0; i <n_claves; i++){
		if(inserta_diccionario(pdicc, claves[i]) == ERR)
			return ERR;
	}

	return OK;
}

/***************************************************/
/* Funcion: busca_diccionario                      */
/*                               Fecha: 14/12/2018 */
/* Autores: Pablo Borrelli, Pablo Sánchez          */
/*                                                 */
/* Inserta una serie de elementos en el diccionario*/
/*                                                 */
/* Entrada:                                        */
/* PDICC pdicc: Diccionario                        */
/* int claves: Dato a buscar                       */
/* int *ppos: Puntero que indica la posicion de    */
/*            la clave                             */
/* pfunc_busqueda metodo: Metodo a utilizar para   */
/*                        encontrar la clave       */
/* Salida:                                         */
/* int Numero de OBs usado para encontrar la clave */
/*                                                 */
/***************************************************/
int busca_diccionario(PDICC pdicc, int clave, int *ppos, pfunc_busqueda metodo)
{
	int check;

	if(!pdicc || !ppos || !metodo)
		return ERR;
	
	check = metodo(pdicc->tabla, 0, pdicc->n_datos - 1, clave, ppos);

	if(*ppos == NO_ENCONTRADO)
		return NO_ENCONTRADO;
	
	return check;
}


/* Funciones de busqueda del TAD Diccionario */

/***************************************************/
/* Funcion: bbin                                   */
/*                               Fecha: 14/12/2018 */
/* Autores: Pablo Borrelli, Pablo Sánchez          */
/*                                                 */
/* Busca la clave [clave] en una tabla e indica su */
/* posicion en ppos                                */
/*                                                 */
/* Entrada:                                        */
/* int *tabla                                      */
/* int P: posicion minima de la tabla              */
/* int U: posicion maxima de la tabla              */
/* int clave: Clave a buscar en la tabla           */
/* int *ppos: Puntero donde guardar la posicion de */
/*            la clave                             */
/* Salida:                                         */
/* int numero de OBs o ERR en caso de fallo        */
/*                                                 */
/***************************************************/
int bbin(int *tabla,int P,int U,int clave,int *ppos)
{
	int n=0, imedio, iu = U, ip = P;

	if(!tabla || !ppos || P>U)
		return ERR;

	while(ip<=iu){
		imedio = (ip + iu)/2;
		n++;
		if(tabla[imedio] == clave){			
			*ppos = imedio;
			return n;
		}
		else if(tabla[imedio]<clave){
			ip = imedio + 1;  
		}
		else{
			iu = imedio - 1;
		}
	}

	*ppos = NO_ENCONTRADO;
	return n;
}

/***************************************************/
/* Funcion: blin                                   */
/*                               Fecha: 14/12/2018 */
/* Autores: Pablo Borrelli, Pablo Sánchez          */
/*                                                 */
/* Busca la clave [clave] en una tabla e indica su */
/* posicion en ppos                                */
/*                                                 */
/* Entrada:                                        */
/* int *tabla                                      */
/* int P: posicion minima de la tabla              */
/* int U: posicion maxima de la tabla              */
/* int clave: Clave a buscar en la tabla           */
/* int *ppos: Puntero donde guardar la posicion de */
/*            la clave                             */
/* Salida:                                         */
/* int numero de OBs o ERR en caso de fallo        */
/*                                                 */
/***************************************************/
int blin(int *tabla,int P,int U,int clave,int *ppos)
{
	int i;
	int n=0;

	if(!tabla || !ppos || P>U)
		return ERR;
	
	for(i=P; i<=U; i++){
		n++;
		if(tabla[i]==clave){
			*ppos = i;
			return n;
		}
	}

	*ppos = NO_ENCONTRADO;
	return n;
}



