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
 * Función que dado un archivo carga un gimnasio reservando la memoria necesaria 
 * para el mismo o NULL en caso de error.
 */
gimnasio_t* gimnasio_crear(heap_t* heap_gimnasios, const char* ruta_archivo){

}

// -------------------------- FUNCIONES AGREGAR -------------------------- //

/*
 * Carga los gimnasios para la partida
 */
void agregar_gimnasios(heap_t* gimnasio);

/*
 * Carga un personaje para la partida
 */
void agregar_protagonista(personaje_t* protagonista);

/*
 * Agrega los tipos de batalla de batalla.h
 */
//void agregar_tipo_de_batalla(funcion_batalla id_batalla[MAX_BATALLAS]);


// -------------------------- FUNCIONES MOSTRAR -------------------------- //

/*
 * Muestra al entrenador con sus pokemon
 */
void protagonista_mostrar(personaje_t* personaje);

/*
 * Muestra información del gimnasio
 */
void gimnasio_mostrar(gimnasio_t* gimnasio);


// -------------------------- FUNCIONES BATALLA -------------------------- //

/*
 * Permite al jugador que pueda cambiar sus pokemon entre los obtenidos (caja) y 
 * los usados para el combate (party)
 */
void cambios_party_caja(personaje_t* personaje);

/*
*  Mejora cada una de las habilidades del pokemon mientras sean menores a 63.
*/
void recompensa_caracteristicas(pokemon_t* pokemon);


// -------------------------- FUNCIONES DESTRUIR -------------------------- //

/*
 * Destruye el pokemon liberando la memoria reservada por el mismo.
 */
void pokemon_destruir(pokemon_t* pokemon);

/*
 * Destruye el entrenador liberando la memoria reservada por el mismo.
 */
void entrenador_destruir(entrenador_t* entrenador);

/*
 * Destruye el gimnasio liberando la memoria reservada por el mismo.
 */
void gimnasio_destruir(gimnasio_t* gimnasio);

/*
 * Destruye el jugador liberando la memoria reservada por el mismo.
 */
void protagonista_destruir(personaje_t* personaje);




