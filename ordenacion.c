/**
 *
 * Descripcion: Implementacion de funciones de ordenacion
 *
 * Fichero: ordenacion.c
 * Autor: Carlos Aguirre
 * Version: 1.0
 * Fecha: 16-09-2017
 *
 */


#include "ordenacion.h"

/***************************************************/
/* Funcion: swap      Fecha: 28/09/2018            */
/* Autores: Pablo Borrelli, Pablo Sánchez          */
/*                                                 */
/* Cambia los valores de los int dados             */
/*                                                 */
/* Entrada:                                        */
/* int a                                           */
/* int b                                           */
/* Salida:                                         */
/* void                                            */
/***************************************************/
void swap(int * a, int * b){
  int temp;

  temp = *a;
  *a = *b;
  *b = temp;
}


/***************************************************/
/* Funcion: SelectSort    Fecha: 28/09/2018        */
/* Autores: Pablo Borrelli, Pablo Sánchez          */
/*                                                 */
/* Ordena la tabla dada desde ip hasta iu          */
/*                                                 */
/* Entrada:                                        */
/* int *tabla: La tabla a ordenar                  */
/* int ip: indice desde donde ordenar la tabla     */
/* int iu: indice hasta donde ordenar la tabla     */
/* Salida:                                         */
/* int: Numero de OB o -1 en caso de error         */
/*                                                 */
/***************************************************/
int SelectSort(int* tabla, int ip, int iu)
{
  int min, num = 0, j;
  int i=ip;

  if(!tabla || ip<0 || iu<ip)
	return ERR;

  for(; i < iu; i++){
	min = i;
	for(j = i+1; j <= iu; j++){
	  if(tabla[j]<tabla[min]){
		min = j;
	  }
	  num++;
	}
	swap(&tabla[i], &tabla[min]);
  }

  return num;
}

/***************************************************/
/* Funcion: SelectSortInv    Fecha: 28/09/2018     */
/* Autores: Pablo Borrelli, Pablo Sánchez          */
/*                                                 */
/* Ordena la tabla dada desde ip hasta iu. Pero    */
/* de mayor a menor                                */
/*                                                 */
/* Entrada:                                        */
/* int *tabla: La tabla a ordenar                  */
/* int ip: indice desde donde ordenar la tabla     */
/* int iu: indice hasta donde ordenar la tabla     */
/* Salida:                                         */
/* int: Numero de OB o -1 en caso de error         */
/*                                                 */
/***************************************************/
int SelectSortInv(int* tabla, int ip, int iu)
{
  int min, num = 0, j;
  int i=iu;

  if(!tabla || ip<0 || iu<ip)
	return ERR;

  for(; i > ip; i--){
	min = i;
	for(j = i-1; j >= ip; j--){
	  if(tabla[j]<tabla[min]){
		min = j;
	  }
	  num++;
	}
	swap(&tabla[i], &tabla[min]);
  }

  return num;
}
