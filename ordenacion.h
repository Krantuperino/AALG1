/**
 *
 * Descripcion: Funciones de cabecera para ordenacion
 *
 * Fichero: ordenacion.h
 * Autor: Carlos Aguirre
 * Version: 1.0
 * Fecha: 16-09-2016
 *
 */

#ifndef ORDENACION_H
#define ORDENACION_H

#include <stdio.h>
#include <stdlib.h>

/* constantes */

#ifndef ERR
  #define ERR -1
  #define OK (!(ERR))
#endif

/* definiciones de tipos */
typedef int (* pfunc_ordena)(int*, int, int);

/* Funciones */

void swap(int* a, int* b);
int SelectSort(int* tabla, int ip, int iu);
int SelectSortInv(int* tabla, int ip, int iu);
int MergeSort(int *tabla, int ip, int iu);
int Merge(int *tabla, int ip, int iu, int imedio);
int QuickSort(int *tabla, int ip, int iu);
int QuickSort_src(int *tabla, int ip, int iu);
int Split(int *tabla, int ip, int iu, int *pos);
int Middle(int *tabla, int ip, int iu, int *pos);
int Middle_Avg(int *tabla, int ip, int iu, int *pos);

#endif
