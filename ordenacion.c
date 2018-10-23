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
/* Funcion: aleat_num Fecha: 28/09/2018            */
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
/*                                                 */
/*                                                 */
/***************************************************/
int SelectSort(int* tabla, int ip, int iu)
{
  int min, num = 0, j;

  if(!tabla || ip<0 || iu<ip + 1)
    return ERR;

  for(; ip < iu; ip++){
    min = ip;
    for(j = ip+1; j <= iu; j++){
      if(tabla[j]<tabla[min]){
        min = j;
      }
      num++;
    }
    swap(&tabla[ip], &tabla[min]);
  }

  return num;
}

int SelectSortInv(int* tabla, int ip, int iu)
{
  int min, num = 0, j;

  if(!tabla || ip<0 || iu<ip + 1)
    return ERR;

  for(; iu > ip; iu--){
    min = iu;
    for(j = iu-1; j >= ip; j--){
      if(tabla[j]<tabla[min]){
        min = j;
      }
      num++;
    }
    swap(&tabla[iu], &tabla[min]);
  }

  return num;
}
