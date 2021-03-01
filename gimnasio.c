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
#include "gimnasio.h"


// -------------------------- FUNCIONES CREACION -------------------------- //

/*
 * Función que dado un archivo de gimnasio carga un entrenador reservando la memoria 
 * necesaria para el mismo o NULL en caso de error.
 */
entrenador_t* entrenador_crear(const char* ruta_archivo){
    
}


/*
 * Función que dado un archivo carga un gimnasio reservando la memoria necesaria 
 * para el mismo o NULL en caso de error.
 */
gimnasio_t* gimnasio_crear(heap_t* heap_gimnasios, const char* ruta_archivo){

}


// -------------------------- FUNCIONES MOSTRAR -------------------------- //

/*
 * Muestra información del gimnasio
 */
void gimnasio_mostrar(gimnasio_t* gimnasio);


// -------------------------- FUNCIONES BATALLA -------------------------- //


/*
*  Mejora cada una de las habilidades del pokemon mientras sean menores a 63.
*/
void recompensa_caracteristicas(pokemon_t* pokemon);


// -------------------------- FUNCIONES DESTRUIR -------------------------- //

/*
 * Destruye el entrenador liberando la memoria reservada por el mismo.
 */
void entrenador_destruir(entrenador_t* entrenador);

/*
 * Destruye el gimnasio liberando la memoria reservada por el mismo.
 */
void gimnasio_destruir(gimnasio_t* gimnasio);
