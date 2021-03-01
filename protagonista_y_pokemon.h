#ifndef __PROTAGONISTA_Y_POKEMON_H__
#define __PROTAGONISTA_Y_POKEMON_H__

#define EXITO 0
#define FALLA -1
#define MAX_NOMBRE 30


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
}pokemon_t;


typedef struct personaje{
    char nombre[MAX_NOMBRE];
    lista_t* party;
    lista_t* caja;
    int mis_medallas;
    int mi_nivel;
    size_t cantidad_pokemones;
} personaje_t;

// -------------------------- FUNCIONES -------------------------- //

/*
 * Función que, dado el archivo del protagonista o de un gimnasio, reserva la memoria 
 * necesaria para la creación de un entrenador.
 * Devuelve al entrenador o NULL en caso de error.
 */
personaje_t* protagonista_crear(const char* ruta_archivo);


/*
 * Función que opera sobre el archivo abierto para crear el personaje.
 */ 
personaje_t* personaje_cargar(personaje_t* personaje, pokemon_t* primer_pokemon, FILE* archivo_personaje, char tipo_de_personaje);

/*
 * Muestra al entrenador con sus pokemon
 */
void protagonista_mostrar(personaje_t* protagonista);


/*
 * Permite al jugador que pueda cambiar sus pokemon entre los obtenidos (caja) y 
 * los usados para el combate (party)
 */
void cambios_party_caja(personaje_t* protagonista);


/*
 * Destruye el pokemon liberando la memoria reservada por el mismo.
 */
void pokemon_destruir(pokemon_t* pokemon);


/*
 * Destruye el jugador liberando la memoria reservada por el mismo.
 */
void protagonista_destruir(personaje_t* protagonista);


#endif /* __PROTAGONISTA_Y_POKEMON_H__ */

