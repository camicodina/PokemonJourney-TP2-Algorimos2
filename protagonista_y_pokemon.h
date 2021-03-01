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
    int nivel;
}pokemon_t;


typedef struct personaje{
    char nombre[MAX_NOMBRE];
    lista_t* party;
    lista_t* caja;
    int mis_medallas;
    size_t cantidad_pokemones;
} personaje_t;

/*
 * Función que dado un archivo carga al personaje principal reservando la memoria necesaria 
 * para el mismo o NULL en caso de error.
 */
personaje_t* protagonista_crear(const char* ruta_archivo);


/*
 * Carga un personaje para la partida
 */
void agregar_protagonista(personaje_t* protagonista);


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

