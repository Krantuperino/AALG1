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

int * Create_AuxTable(int *tabla, int ip, int iu)
{
	int i, n = iu - ip;
	int * aux;

	aux = malloc(n * sizeof(int));

	if(ip > iu)
		return NULL;
	
	for(i=0; i<n; i++){
		aux[i]=tabla[ip+i];
	}

	return aux;
}

short Copy_IntoTable(int * taux, int * tabla, int ip, int iu){
	int i;

	if(tabla == NULL || taux == NULL || ip > iu)
		return ERR;

	for(i=0; i < iu - ip; i++){
		tabla[ip+i] = taux[i];
	}

	return OK;
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
	int imedio, OB=0, a;

	if(ip > iu)
		return ERR;
	
	if(ip == iu)
		return OK;
	else{
		imedio = (ip + iu)/2;
		a = MergeSort(tabla, ip, imedio);
		if(a == ERR)
			return ERR;
		else
			OB += a;
		a = MergeSort(tabla, imedio + 1, iu);
		if(a == ERR)
			return ERR;
		else
			OB += a;
		a = Merge(tabla, ip, iu, imedio);
		if(a == ERR)
			return ERR;
		else
			return OB + a;	
	}
}

int Merge(int *tabla, int ip, int iu, int imedio)
{
	int *t_aux = NULL;
	int i=ip, j=imedio+1, k=ip, num = 0;

	t_aux = Create_AuxTable(tabla, ip, iu);

	if(t_aux == NULL)
		return ERR;

	while(i<=imedio && j<=iu)
	{
		if(tabla[i] < tabla[j]){
			t_aux[k] = tabla[i];
			i++;
		}
		else{
			t_aux[k] = tabla[j];
			j++;
		}
		k++;
		num++;
	}

	if(i>imedio){
		while(j<=iu){
			t_aux[k]=tabla[j];
			j++;
			k++;
		}
	}
	else if(j>iu){
		while(i<=iu){
			t_aux[k]=tabla[i];
			i++;
			k++;
		}
	}

	if(Copy_IntoTable(t_aux, tabla, ip, iu) == ERR)
		return ERR;

	free(t_aux);

	return num;
}