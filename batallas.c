#define GANO_PRIMERO 1
#define GANO_SEGUNDO -1

#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include "batallas.h"
#include "protagonista_y_pokemon.h"

/*
 * Se deberan implementar las 5 funciones de batalla.
 * Las reglas para decidir al ganador las inventan ustedes
 * 
 * Si el ganador es el primer pokemon, se devolvera 1
 * Si el ganador es el segundo pokemon, se devolvera -1
 * 
 * No habran empates.
 */

int funcion_batalla_1(void* pkm_1, void* pkm_2){
    // Gana el que tenga mayor ataque 
    if(((pokemon_t*)pkm_1)->ataque >= ((pokemon_t*)pkm_2)->ataque) return GANO_PRIMERO;
    return GANO_SEGUNDO;
}

int funcion_batalla_2(void* pkm_1, void* pkm_2){
    // Gana el que tenga mayor velocidad 
    if(((pokemon_t*)pkm_1)->velocidad >= ((pokemon_t*)pkm_2)->velocidad) return GANO_PRIMERO;
    return GANO_SEGUNDO;
}

int funcion_batalla_3(void* pkm_1, void* pkm_2){
    //Gana el que tenga mayor defensa
    if(((pokemon_t*)pkm_1)->defensa >= ((pokemon_t*)pkm_2)->defensa) return GANO_PRIMERO;
    return GANO_SEGUNDO;
}

int funcion_batalla_4(void* pkm_1, void* pkm_2){
    // Gana el que posea el nombre más corto 
    if(strlen(((pokemon_t*)pkm_1)->nombre) <= strlen(((pokemon_t*)pkm_2)->nombre)) return GANO_PRIMERO;
    return GANO_SEGUNDO;
}

int funcion_batalla_5(void* pkm_1, void* pkm_2){
    // Gana el que posea la mayor velocidad,ataque y defensa 
    if((((pokemon_t*)pkm_1)->ataque >= ((pokemon_t*)pkm_2)->ataque) && (((pokemon_t*)pkm_1)->velocidad >= ((pokemon_t*)pkm_2)->velocidad) && (((pokemon_t*)pkm_1)->defensa >= ((pokemon_t*)pkm_2)->defensa)) return GANO_PRIMERO;
    return GANO_SEGUNDO;
}