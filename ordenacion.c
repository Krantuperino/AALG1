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


/***************************************************/
/* Funcion: MergeSort        Fecha: 15/11/2018     */
/* Autores: Pablo Borrelli, Pablo Sánchez          */
/*                                                 */
/* Ordena la tabla dada desde ip hasta iu.         */
/*                                                 */
/* Entrada:                                        */
/* int *tabla: La tabla a ordenar                  */
/* int ip: indice desde donde ordenar la tabla     */
/* int iu: indice hasta donde ordenar la tabla     */
/* Salida:                                         */
/* int: Numero de OB o -1 en caso de error         */
/*                                                 */
/***************************************************/
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


/***************************************************/
/* Funcion: Merge            Fecha: 15/11/2018     */
/* Autores: Pablo Borrelli, Pablo Sánchez          */
/*                                                 */
/* Junta los trozos de la tabla separada en        */
/* MergeSort, ordenandolos en e proceso.           */
/*                                                 */
/* Entrada:                                        */
/* int *tabla: La tabla a ordenar                  */
/* int ip: indice desde donde ordenar la tabla     */
/* int iu: indice hasta donde ordenar la tabla     */
/* int imedio: punto medio de la tabla             */
/* Salida:                                         */
/* int: Numero de OB o -1 en caso de error         */
/*                                                 */
/***************************************************/
int Merge(int *tabla, int ip, int iu, int imedio)
{
	int *t_aux;
	int num = 0;
	int k = 0;
	int i = ip;
	int j = imedio + 1;

	t_aux= (int *) malloc(sizeof(int)*(iu-ip+1));
	if(t_aux==NULL)
		return ERR;

	while(i <= imedio && j <= iu)
	{
		if(tabla[i] < tabla[j])
		{
			t_aux[k] = tabla[i];
			i++;
		}
		else
		{
			t_aux[k] = tabla[j];
			j++;
		}
		k++;
		num++;
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

	free(t_aux);
	return num;
}

/***************************************************/
/* Funcion: QuickSort        Fecha: 28/09/2018     */
/* Autores: Pablo Borrelli, Pablo Sánchez          */
/*                                                 */
/* Ordena la tabla dada desde ip hasta iu.         */
/*                                                 */
/* Entrada:                                        */
/* int *tabla: La tabla a ordenar                  */
/* int ip: indice desde donde ordenar la tabla     */
/* int iu: indice hasta donde ordenar la tabla     */
/* Salida:                                         */
/* int: Numero de OB o -1 en caso de error         */
/*                                                 */
/***************************************************/
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
		if(num == ERR)
			return ERR;
		if(ip < pos-1){
			num += QuickSort(tabla, ip, pos-1);
			if(num == ERR)
				return ERR;
		}
		if(pos+1 < iu){
			num += QuickSort(tabla, pos+1, iu);
			if(num == ERR)
				return ERR;
		}
	}

	return num;
}

/***************************************************/
/* Funcion: QuickSort_src    Fecha: 28/09/2018     */
/* Autores: Pablo Borrelli, Pablo Sánchez          */
/*                                                 */
/* Ordena la tabla dada desde ip hasta iu.         */
/* Ahora sin recursion de cola.                    */
/*                                                 */
/* Entrada:                                        */
/* int *tabla: La tabla a ordenar                  */
/* int ip: indice desde donde ordenar la tabla     */
/* int iu: indice hasta donde ordenar la tabla     */
/* Salida:                                         */
/* int: Numero de OB o -1 en caso de error         */
/*                                                 */
/***************************************************/
int QuickSort_src(int *tabla, int ip, int iu)
{
	int num=0, pos=1, check;

	if(ip>iu || !tabla)
		return ERR;

	if(ip==iu)
		return 0;
	while(ip<iu)
	{
		check = Split(tabla, ip, iu, &pos);
		if(check == ERR)
			return ERR;
		else
			num += check;
		num += QuickSort_src(tabla, ip, pos-1);
		ip=pos+1;
	}

	return num;
}

/***************************************************/
/* Funcion: Split            Fecha: 15/11/2018     */
/* Autores: Pablo Borrelli, Pablo Sánchez          */
/*                                                 */
/* Separa la tabla ordenandola.                    */
/*                                                 */
/* Entrada:                                        */
/* int *tabla: La tabla a ordenar                  */
/* int ip: indice desde donde ordenar la tabla     */
/* int iu: indice hasta donde ordenar la tabla     */
/* int pos: posicion del pivote                    */
/* Salida:                                         */
/* int: Numero de OB o -1 en caso de error         */
/*                                                 */
/***************************************************/
int Split(int *tabla, int ip, int iu, int *pos)
{
	int k, m, i, num=0;

	if(Middle_Avg(tabla, ip, iu, pos) == ERR)
		return ERR;

	k = tabla[*pos];

	m = *pos;

	swap(&tabla[ip], &tabla[m]);

	m = ip;

	for(i = ip+1; i<=iu; i++){
		if(tabla[i]<k){
			m++;
			swap(&tabla[i], &tabla[m]);
		}
		num++;
	}
	
	swap(&tabla[ip], &tabla[m]);

	*pos = m; 
	return num;
}

/***************************************************/
/* Funcion: Split            Fecha: 15/11/2018     */
/* Autores: Pablo Borrelli, Pablo Sánchez          */
/*                                                 */
/* Coloca el pivote en ip.                         */
/*                                                 */
/* Entrada:                                        */
/* int *tabla: La tabla a ordenar                  */
/* int ip: indice desde donde ordenar la tabla     */
/* int iu: indice hasta donde ordenar la tabla     */
/* int pos: posicion del pivote                    */
/* Salida:                                         */
/* int: Numero de OB o -1 en caso de error         */
/*                                                 */
/***************************************************/
int Middle(int *tabla, int ip, int iu, int *pos){
	*pos = ip;
	return 0;
}

/***************************************************/
/* Funcion: Split            Fecha: 15/11/2018     */
/* Autores: Pablo Borrelli, Pablo Sánchez          */
/*                                                 */
/* Coloca el pivote en (ip+iu)/2.                  */
/*                                                 */
/* Entrada:                                        */
/* int *tabla: La tabla a ordenar                  */
/* int ip: indice desde donde ordenar la tabla     */
/* int iu: indice hasta donde ordenar la tabla     */
/* int pos: posicion del pivote                    */
/* Salida:                                         */
/* int: Numero de OB o -1 en caso de error         */
/*                                                 */
/***************************************************/
int Middle_Avg(int *tabla, int ip, int iu, int *pos){
	if(tabla==NULL || pos==NULL || ip>=iu)
		return ERR;
	*pos = (ip + iu)/2;

	return 0;
}