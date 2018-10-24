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

/***************************************************/
/* Funcion: tiempo_medio_ordenacion Fecha:         */
/*                                                 */
/* Vuestra documentacion (formato igual            */
/* que en el primer apartado):                     */
/***************************************************/
double minTabla(double tabla[], int N)
{
    int min=0, j;

    for(j = 1; j < N; j++){
        if(tabla[j]<tabla[min])
            min = j;
    }

    return tabla[min];
}

/***************************************************/
/* Funcion: tiempo_medio_ordenacion Fecha:         */
/*                                                 */
/* Vuestra documentacion (formato igual            */
/* que en el primer apartado):                     */
/***************************************************/
double maxTabla(double tabla[], int N)
{
    int max=0, j;

    for(j = 1; j < N; j++){
        if(tabla[j]>tabla[max])
            max = j;
    }

    return tabla[max];
}

/***************************************************/
/* Funcion: tiempo_medio_ordenacion Fecha:         */
/*                                                 */
/* Vuestra documentacion (formato igual            */
/* que en el primer apartado):                     */
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

    if(!metodo || n_perms < 1 || N < 2){
        return ERR;
    }

    tabla = genera_permutaciones(n_perms, N);

    ptiempo->n_elems = n_perms;
    ptiempo->N = N;

    for(i=0; i<n_perms; i++){

        clock_gettime(CLOCK_REALTIME, &start);

        tabla_ob[i] = metodo(tabla[i], 0, N);

        clock_gettime(CLOCK_REALTIME, &finish);

        tiempo = (double) (finish.tv_sec - start.tv_sec) + NANOSEC*(finish.tv_nsec - start.tv_nsec);

        media+= tiempo;
    }

    media = (double) media/n_perms;
    for(i=0; i<n_perms; i++)
        media_ob += tabla_ob[i];
    media_ob = (double) media_ob/n_perms;

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
/* Funcion: genera_tiempos_ordenacion Fecha:       */
/*                                                 */
/* Vuestra documentacion                           */
/***************************************************/
short genera_tiempos_ordenacion(pfunc_ordena metodo, char* fichero,
                                int num_min, int num_max,
                                int incr, int n_perms)
{
    int i;
    int perms_imprimir;
    PTIEMPO  ptiempo = NULL;

    perms_imprimir = ((num_max - num_min)/incr);

    ptiempo =(PTIEMPO) calloc (perms_imprimir, sizeof(PTIEMPO));

    if(!metodo || !fichero || num_min >= num_max || incr<1 || n_perms<1|| !ptiempo){
        return ERR;
    }


    for(i=0; num_min <= num_max; num_min+=incr , i++){
        tiempo_medio_ordenacion(metodo, n_perms, num_min, &ptiempo[i]);
    }
    guarda_tabla_tiempos(fichero, ptiempo, perms_imprimir);

    free(ptiempo);
    return OK;
}

/***************************************************/
/* Funcion: guarda_tabla_tiempos Fecha:            */
/*                                                 */
/* Vuestra documentacion (formato igual            */
/* que en el primer apartado):                     */
/***************************************************/
short guarda_tabla_tiempos(char* fichero, PTIEMPO tiempo, int n_tiempos)
{
    int i;
    FILE * file = NULL;

    file = fopen(fichero, "w");
    if(!file)
        return ERR;

    for(i=0; i<=n_tiempos; i++)
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
