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

	if(ip > iu || !tabla)
		return ERR;

	if(ip == iu)
		return OK;

	if(ip < iu)
	{
		imedio = (ip + iu) / 2;
		num = MergeSort(tabla, ip, imedio);
		num += MergeSort(tabla, imedio+1, iu);
	   num += Merge(tabla, ip, iu, imedio);
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

int QuickSort(int *tabla, int ip, int iu)
{
	int num, pos;

	if(ip>iu || !tabla)
		return ERR;

	if(ip==iu)
		return 0;
	else
	{
		num = Split(tabla, ip, iu, &pos);
		if(num == -1)
			return ERR;
		if(ip < pos-1){
			num += QuickSort(tabla, ip, pos-1);
			if(num == -1)
				return ERR;
		}
		if(pos+1 < iu){
			num += QuickSort(tabla, pos+1, iu);
			if(num == -1)
				return ERR;
		}
	}

	return num;
}

int Split(int *tabla, int ip, int iu, int *pos)
{
	int k, m, i, num=0;

	if(!pos)
		return ERR;
	Middle(tabla, ip, iu, pos);

	k = tabla[*pos];

	m = *pos;

	swap(&tabla[ip], &tabla[m]);

	m = ip;

	for(i = ip+1; i<=iu; i++){
		if(tabla[i]<k){
			num++;
			m++;
			swap(&tabla[i], &tabla[m]);
		}
	}
	
	swap(&tabla[ip], &tabla[m]);

	*pos = m; 
	return num;
}

int Middle(int *tabla, int ip, int iu, int *pos){
	*pos = ip;
	return 0;
}