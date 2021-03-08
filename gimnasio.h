#ifndef __GIMNASIO_H__
#define __GIMNASIO_H__

#define MAX_BATALLAS 5
#define MAX_NIVEL 63

#define GIMNASIO 'G'
#define LIDER 'L'

#define FORMATO_LECTURA_GIMNASIO ";%49[^;];%i;%i\n"

#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include "batallas.h"
#include "lista.h"
#include "heap.h"
#include "protagonista_y_pokemon.h"

// -------------------------- ESTRUCTURAS -------------------------- //

typedef int (*funcion_batalla)(void*, void*);
void batallas_cargar(funcion_batalla* batallas);

typedef struct gimnasio{
    char nombre[MAX_NOMBRE];
    int dificultad;
    int id_puntero_funcion;
    personaje_t* lider;
    lista_t* miembros;
}gimnasio_t;

typedef struct batallas_pokemon{
    funcion_batalla tipos[MAX_BATALLAS];
    personaje_t* protagonista;
    heap_t* gimnasios;
    bool es_simulacion;
}batallas_pokemon_t;


// -------------------------- FUNCIONES -------------------------- //

/*
 * Función que dado un archivo carga un gimnasio reservando la memoria necesaria 
 * para el mismo o NULL en caso de error.
 */
gimnasio_t* gimnasio_crear(const char* ruta_archivo);



/*
 * Crea los gimnasios y los agrega al heap.
 * Devuelve EXITO o FALLA.
*/
int todos_gimnasios_agregar(heap_t* heap_gimnasios){


/*
 * Agrega un gimnasio al árbol de gimnasios
 * Devuelve EXITO o FALLA.
*/
int gimnasios_agregar(heap_t* heap_gimnasios,const char* ruta);

/*
 * Muestra información del gimnasio
 */
void gimnasio_mostrar(gimnasio_t* gimnasio);


/*
 * Muestra los dos pokemon que se enfrentan en el combate del siglo.
 */
void mostrar_combate_informacion(pokemon_t* pokemon_protagonista, pokemon_t* pokemon_oponente);


/*
*  Mejora cada una de las habilidades del pokemon mientras sean menores a 63.
*/
void recompensa_caracteristicas(pokemon_t* pokemon);


/*
 * Revisa la caja del protagonista y la del oponente. El protagonista pide 
 * prestado un pokemon del oponente a elección.
 * Devuelve EXITO o FALLA.
 */
int pedir_prestado(personaje_t* protagonista, personaje_t* oponente);


/*
 * Destruye el gimnasio liberando la memoria reservada por el mismo.
 */
void gimnasio_destruir(gimnasio_t* gimnasio);


/*
 * Libera todo
 */
void liberar_todo(batallas_pokemon_t* batallas_pokemon);


#endif /* __GIMNASIO_H__ */

