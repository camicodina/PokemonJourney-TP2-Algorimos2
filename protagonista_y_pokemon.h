#ifndef __PROTAGONISTA_Y_POKEMON_H__
#define __PROTAGONISTA_Y_POKEMON_H__

#define EXITO 0
#define FALLA -1
#define MAX_NOMBRE 30
#define MAX_RUTA 99


#define POKEMON 'P'
#define ENTRENADOR 'E'

#define FORMATO_LECTURA_ENTRENADOR "%30[^\n]\n"
#define FORMATO_LECTURA_POKEMON ";%30[^;];%i;%i;%i\n"

#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include "lista.h"

// -------------------------- ESTRUCTURAS -------------------------- //

typedef struct pokemon{
    char nombre[MAX_NOMBRE];
    int velocidad;
    int ataque;
    int defensa;
    int nivel;
    size_t id;
}pokemon_t;


typedef struct personaje{
    char nombre[MAX_NOMBRE];
    lista_t* party;
    lista_t* caja;
    int mis_medallas;
    size_t cantidad_pokemones;
} personaje_t;

// -------------------------- FUNCIONES -------------------------- //

/*
 * Función auxiliar para la lectura del nombre del entrenador/lider/protagonista.
 */
personaje_t* leo_nombre_personaje(personaje_t* personaje, pokemon_t* primer_pokemon, FILE* archivo_personaje);

/*
 * Función auxiliar para la lectura del primer pokemon que posee el 
 * entrenador/lider/protagonista.
 */
pokemon_t* leo_primer_pokemon(personaje_t* personaje, pokemon_t* primer_pokemon, FILE* archivo_personaje);


/*
 * Función auxiliar para crear el conjunto de pokemon para combarir inicial.
 */
void estado_inicial_party(personaje_t* personaje, pokemon_t* primer_pokemon);


/*
 * Función que, dado el archivo del protagonista o de un gimnasio, reserva la memoria 
 * necesaria para la creación de un entrenador.
 * Devuelve al entrenador o NULL en caso de error.
 */
personaje_t* protagonista_crear(char ruta_archivo[MAX_RUTA]);


/*
 * Función que opera sobre el archivo abierto para crear el personaje.
 */ 
personaje_t* personaje_cargar(personaje_t* personaje, pokemon_t* primer_pokemon, FILE* archivo_personaje);


/*
 * Muestra conjunto de pokemon para combatir de un entrenador
 */
void mostrar_pokemon_party(personaje_t* protagonista);

/*
 * Muestra conjunto de pokemon obtendos por un entrenador
 */
void mostrar_pokemon_caja(personaje_t* protagonista);

/*
 * Muestra al entrenador con sus pokemon
 */
void protagonista_mostrar(personaje_t* protagonista);


/*
 * Permite al jugador que pueda cambiar sus pokemon entre los obtenidos (caja) y 
 * los usados para el combate (party).
 * Devuelve EXITO O FALLA.
 */
int cambios_party_caja(personaje_t* protagonista);

/*
 * Elije Pokemon a usar en la batalla desde party
 */
pokemon_t* elegir_pokemon(personaje_t* protagonista);


/*
 * Destruye el pokemon liberando la memoria reservada por el mismo.
 */
void pokemon_destruir(pokemon_t* pokemon);


/*
 * Destruye el jugador liberando la memoria reservada por el mismo.
 */
void protagonista_destruir(personaje_t* protagonista);


#endif /* __PROTAGONISTA_Y_POKEMON_H__ */

