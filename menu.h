#ifndef __MAIN_H__
#define __MAIN_H__


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "gimnasio.h"



// -------------------------- MENUES -------------------------- //

/*
 * Agrega un gimnasio al árbol de gimnasios
 * Devuelve EXITO o FALLA.
*/
int gimnasio_agregar(batallas_pokemon_t* partida);


/*
 * Agrega al protagonista del juego.
 * Devuelve EXITO o FALLA.
*/
int protagonista_agregar(batallas_pokemon_t* partida);


/*
 * Crea el menu principal con las opciones:
 * E - Ingresa archivo del entrenador principal 
 * A - Agrega un gimnasio al arbol de gimnasios 
 * I - Comienza la partida
 * S - Simula la partida
 * X para salir del juego
 * Reinicia el menú en caso de error.
*/
void menu_inicio(batallas_pokemon_t* partida);


/*
 * Comienza una partida simulada donde el usuario no debe poner input. 
 * La partida termina cuando el pokemon del equipo inicial pierde ante un gimnasio.
*/
void menu_simulacion(batallas_pokemon_t* partida);


/*
 * Crea el menu para un gimnasio con las opciones:
 * E - Ver informacion del protagonista
 * G - Ver informacion del gimnasio
 * C - Cambiar los pokemon de batalla
 * B - Realiza la proxima batalla planificada
 * X para salir del menu
 * Reinicia el menú en caso de error.
*/
void menu_gimnasio(batallas_pokemon_t* partida);


/*
 * Realiza la logica de la batalla.
*/
void menu_batalla(batallas_pokemon_t* partida,personaje_t* protagonista, gimnasio_t* gimnasio);


/*
 * Crea el menu principal con las opciones:
 * T - Pedir prestado Pokemon de lider
 * C - Cambiar Pokemon de batalla
 * N - Avanzar al proximo gimnasio
 * Reinicia el menú en caso de error.
*/
void menu_victoria(batallas_pokemon_t* partida, personaje_t* protagonista, gimnasio_t* gimnasio);


/*
 * Crea el menu principal con las opciones:
 * C - Cambiar Pokemon de batalla
 * R - Reintentar batalla
 * F - Finalizar partida
 * Reinicia el menú en caso de error.
*/
void menu_derrota(batallas_pokemon_t* partida, personaje_t* protagonista, gimnasio_t* gimnasio);


#endif /* __MAIN_H__ */

