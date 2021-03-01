#define EXITO 0
#define FALLA -1
#define MAX_NOMBRE 30
#define MAX_BATALLAS 5
#define MAX_NIVEL 63


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
#include "protagonista_y_pokemon.h"

/*
 * Función que dado un archivo carga al personaje principal reservando la memoria necesaria 
 * para el mismo o NULL en caso de error.
 */
personaje_t* protagonista_crear(const char* ruta_archivo){

    //Reservo memoria para protagonista y el primer pokemon.
    personaje_t* protagonista = calloc(1,sizeof(personaje_t));
    if(!protagonista)return NULL;

    pokemon_t* primer_pokemon = calloc(1,sizeof(pokemon_t));
    if(!primer_pokemon){
        free(protagonista);
        return NULL;
    }
    primer_pokemon->nivel=1;

    //Abro archivo
    FILE* archivo_protagonista = fopen(ruta_archivo,"r");
    if(!archivo_protagonista) return NULL;

    //Leo primera linea: nombre del protagonista.
    char tipo = (char)fgetc(archivo_protagonista);
    if(tipo != ENTRENADOR){
        fclose(archivo_protagonista);
        free(protagonista);
        free(primer_pokemon);
        return NULL;
    }
    int primera_linea_leida = fscanf(archivo_protagonista, FORMATO_LECTURA_ENTRENADOR, protagonista->nombre);
    if(!primera_linea_leida || primera_linea_leida != 1){
        fclose(archivo_protagonista);
        free(protagonista);
        free(primer_pokemon);
        return NULL;
    }

    //Leo segunda linea: primer pokemon del entrenador.
    tipo = (char)fgetc(archivo_protagonista);
    if(tipo!=POKEMON){
        fclose(archivo_protagonista);
        free(protagonista);
        free(primer_pokemon);
        return NULL;
    }
    int pokemon_leido = fscanf(archivo_protagonista, FORMATO_LECTURA_POKEMON,primer_pokemon->nombre, &(primer_pokemon->velocidad), &(primer_pokemon->ataque), &(primer_pokemon->defensa));
    if(!pokemon_leido || pokemon_leido != 4){
        fclose(archivo_protagonista);
        free(primer_pokemon);
        free(protagonista);
        return NULL;
    } 

    //Creo las listas party y caja. Agrego primer pokemon a caja (conjunto de poke obtenidos).
    
    protagonista->caja = lista_crear();
    if(!protagonista->caja){
        fclose(archivo_protagonista);
        free(primer_pokemon);
        free(protagonista);
        return NULL;
    }
    
    protagonista->party = lista_crear();
    if(!protagonista->party){
        fclose(archivo_protagonista);
        free(primer_pokemon);
        free(protagonista);
        lista_destruir(protagonista->caja);
        return NULL;
    }

    lista_insertar(protagonista->caja,primer_pokemon);
    (protagonista->cantidad_pokemones)++;

    //Leo y agrego el resto de pokemon en caso de haberlos

    pokemon_t* pokemon;
    tipo = (char)fgetc(archivo_protagonista);
    while(tipo==POKEMON){
        pokemon_leido = fscanf(archivo_protagonista, FORMATO_LECTURA_POKEMON,pokemon->nombre, &(pokemon->velocidad), &(opokemon->ataque), &(pokemon->defensa));
        if(pokemon_leido == 4){
            pokemon_t* otro_pokemon = calloc(1,sizeof(pokemon_t));
            if(!otro_pokemon){
                free(primer_pokemon); 
                lista_destruir(protagonista->caja);
                lista_destruir(protagonista->party);
                free(protagonista); 
                fclose(archivo_protagonista);
                return NULL;
            }
            *otro_pokemon = pokemon;
            otro_pokemon->nivel=1;
            lista_insertar(protagonista->caja, otro_pokemon);
            (protagonista->cantidad_pokemones)++;
        }else{
            free(primer_pokemon); 
            lista_destruir(protagonista->caja);
            lista_destruir(protagonista->party);
            free(protagonista); 
            fclose(archivo_protagonista);
            return NULL;
        } 
        tipo = (char)fgetc(archivo_protagonista);
    }
    
    //Agrego a party

    if(protagonista->cantidad_pokemones <= 6){
        for(size_t i=0; i<(protagonista->cantidad_pokemones); i++){
            pokemon_t* elemento = lista_elemento_en_posicion(protagonista->caja,i);
            lista_insertar(protagonista->party,elemento);
        }
    }else{
        for(size_t i=0; i<6; i++){
            pokemon_t* elemento = lista_elemento_en_posicion(protagonista->caja,i);
            lista_insertar(protagonista->party,elemento);
    }

    fclose(archivo_protagonista);
    return protagonista;

}


/*
 * Carga un personaje para la partida
 */
void agregar_protagonista(personaje_t* protagonista){

}


/*
 * Muestra al entrenador con sus pokemon
 */
void protagonista_mostrar(personaje_t* protagonista){

}


/*
 * Permite al jugador que pueda cambiar sus pokemon entre los obtenidos (caja) y 
 * los usados para el combate (party)
 */
void cambios_party_caja(personaje_t* protagonista){

}


/*
 * Destruye el pokemon liberando la memoria reservada por el mismo.
 */
void pokemon_destruir(pokemon_t* pokemon){
    if(!pokemon) return;
    free(pokemon);
}


/*
 * Destruye el jugador liberando la memoria reservada por el mismo.
 */
void protagonista_destruir(personaje_t* protagonista){
    if(!protagonista) return;
    while(!lista_vacia(protagonista->caja){
        pokemon_t pokemon_a_borrar = lista_primero(protagonista->caja);
        pokemon_destruir(pokemon_a_borrar);
        lista_borrar_de_posicion(protagonista->caja,0);
    }
    lista_destruir(personaje->pokemon_obtenidos);
    lista_destruir(personaje->pokemon_para_combatir);
    free(personaje);
}

