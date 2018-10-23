/**
 *
 * Descripcion: Implementacion de funciones de generacion de permutaciones
 *
 * Fichero: permutaciones.c
 * Autor: Carlos Aguirre
 * Version: 1.0
 * Fecha: 16-09-2017
 *
 */


#include "permutaciones.h"

/***************************************************/
/* Funcion: aleat_num Fecha: 21/09/2018            */
/* Autores: Pablo Borrelli, Pablo Sánchez          */
/*                                                 */
/* Rutina que genera un numero aleatorio           */
/* entre dos numeros dados                         */
/*                                                 */
/* Entrada:                                        */
/* int inf: limite inferior                        */
/* int sup: limite superior                        */
/* Salida:                                         */
/* int: numero aleatorio                           */
/***************************************************/
int aleat_num(int inf, int sup)
{
  return (rand() % (sup - inf + 1)) + inf;
}

/***************************************************/
/* Funcion: genera_perm Fecha:                     */
/* Autores: Pablo Borrelli, Pablo Sánchez          */
/*                                                 */
/* Rutina que genera una permutacion               */
/* aleatoria                                       */
/*                                                 */
/* Entrada:                                        */
/* int n: Numero de elementos de la                */
/* permutacion                                     */
/* Salida:                                         */
/* int *: puntero a un array de enteros            */
/* que contiene a la permutacion                   */
/* o NULL en caso de error                         */
/***************************************************/
int* genera_perm(int N)
{
  int i, swap, random;
  int *perm;

  if(N < 1) {
    printf("N < 1\n");
    return NULL;
  }

  perm = malloc(N * sizeof(int));

  if(!perm){
    printf("Error in memory");
    return NULL;
  }

  for (i = 1; i <= N; i++){
    perm[i-1] = i;
  }

  for(i = 0; i < N; i++){
    random = aleat_num(i, N-1);
    swap = perm[i];
    perm[i] = perm[random];
    perm[random] = swap;
  }

  return perm;
}

/***************************************************/
/* Funcion: genera_permutaciones Fecha:            */
/* Autores: Pablo Borrelli, Pablo Sánchez          */
/*                                                 */
/* Funcion que genera n_perms permutaciones        */
/* aleatorias de tamanio elementos                 */
/*                                                 */
/* Entrada:                                        */
/* int n_perms: Numero de permutaciones            */
/* int N: Numero de elementos de cada              */
/* permutacion                                     */
/* Salida:                                         */
/* int**: Array de punteros a enteros              */
/* que apuntan a cada una de las                   */
/* permutaciones                                   */
/* NULL en caso de error                           */
/***************************************************/
int** genera_permutaciones(int n_perms, int N)
{
/* vuestro codigo */
  int **tabla;
  int i;

  tabla = malloc(sizeof(int)*N * n_perms);

  if(!tabla){
    printf("Memory error\n");
    return NULL;
  }

  if(n_perms < 1 || N < 1){
      printf("Wrong parameters\n");
      return NULL;
  }

  for(i=0; i < n_perms; i++){
    tabla[i] = genera_perm(N);
  }

  return tabla;
}
