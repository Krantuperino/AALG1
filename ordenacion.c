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

int MergeSort(int *tabla, int ip, int iu)
{
    int imedio, num;

    if(ip > iu)
        return ERR;

    if(ip == iu)
        return OK;

    if(ip < iu)
    {
        imedio = (ip + iu) / 2;
        MergeSort(tabla, ip, imedio);
        MergeSort(tabla, imedio+1, iu);
       num = Merge(tabla, ip, iu, imedio);
    }
    return num;
}

int Merge(int *tabla, int ip, int iu, int imedio)
{
    int t_aux[iu-ip+1];
    int num = 0;
    int k = 0;
    int i = ip;
    int j = imedio + 1;

    if(t_aux == NULL)
        return ERR;

    while(i <= imedio && j <= iu)
    {
        if(tabla[i] < tabla[j])
        {
            t_aux[k] = tabla[i];
            k++;
            i++;
            num++;
        }
        else
        {
            t_aux[k] = tabla[j];
            k++;
            j++;
        }
    }

    while(i <= imedio)
    {
        t_aux[k] = tabla[i];
        k++;
        i++;
    }

    while(j <= iu)
    {
        t_aux[k] = tabla[j];
        k++;
        j++;
    }

    for(i=iu; i >= ip; i--)
    {
        k--;
        tabla[i] = t_aux[k];
    }

    return num;
}