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
 * Función auxiliar para la lectura de los datos del gimnasio.
 */
gimnasio_t* leo_datos_gimnasio(gimnasio_t* gimnasio, FILE* archivo_gimnasio){
    char tipo = (char)fgetc(archivo_gimnasio);
    if(tipo != GIMNASIO){
        fclose(archivo_gimnasio);
        free(gimnasio);
        return NULL;
    }
    
    gimnasio_t* aux_gimnasio;
    int primera_linea_leida = fscanf(archivo_gimnasio, FORMATO_LECTURA_GIMNASIO, aux_gimnasio->nombre,aux_gimnasio->dificultad,aux_gimnasio->id_puntero_funcion);
    if(!primera_linea_leida || primera_linea_leida != 3){
        fclose(archivo_gimnasio);
        free(gimnasio);
        return NULL;
    }
   return aux_gimnasio;
}

/*
 * Función que dado un archivo carga un gimnasio reservando la memoria necesaria 
 * para el mismo o NULL en caso de error.
 */
gimnasio_t* gimnasio_crear(const char* ruta_archivo){
    
    //Reservo memoria para el gimnasio.
    gimnasio_t* nuevo_gimnasio = calloc(1,sizeof(gimnasio_t));
    if(!nuevo_gimnasio)return NULL;

    //Abro archivo
    FILE* archivo_gimnasio= fopen(ruta_archivo,"r");
    if(!archivo_gimnasio){
        free(nuevo_gimnasio);
        return NULL;
    }
    nuevo_gimnasio = leo_datos_gimnasio(nuevo_gimnasio, archivo_gimnasio);

    //Reservo memoria para el lider y su primer pokemon.
    personaje_t* lider_gimnasio = calloc(1,sizeof(personaje_t));
    if(!lider_gimnasio){
        free(nuevo_gimnasio);
        fclose(archivo_gimnasio);
        return NULL;
    }
    pokemon_t* primer_pokemon_lider = calloc(1,sizeof(pokemon_t));
    if(!primer_pokemon_lider){
        free(nuevo_gimnasio);
        free(lider_gimnasio);
        fclose(archivo_gimnasio);
        return NULL;
    }
    
    //Cargo al lider
    lider_gimnasio = personaje_cargar(lider_gimnasio, primer_pokemon_lider, archivo_gimnasio, LIDER);
    if(!lider_gimnasio){
        free(lider_gimnasio);
        free(primer_pokemon_lider);
        free(nuevo_gimnasio);
        fclose(archivo_gimnasio);
        return NULL;
    }

    //Creo pila (lista) de entrenadores y apilo al lider.
    nuevo_gimnasio->miembros = lista_crear();
    if (!nuevo_gimnasio->miembros){
        free(nuevo_gimnasio);
        entrenador_destruir(lider_gimnasio);
        fclose(archivo_gimnasio);
        return NULL;
    }
    nuevo_gimnasio->lider=lider_gimnasio->nombre;
    lista_apilar(nuevo_gimnasio->miembros, lider_gimnasio);

    while(archivo_gimnasio != EOF){
        personaje_t* entrenador_gimnasio = calloc(1,sizeof(personaje_t));
        if(!entrenador_gimnasio){
            gimnasio_destruir(nuevo_gimnasio);
            fclose(archivo_gimnasio);
            return NULL;
        }
        pokemon_t* su_primer_pokemon= calloc(1,sizeof(pokemon_t));
        if(!primer_pokemon_lider){
            free(entrenador_gimnasio);
            gimnasio_destruir(nuevo_gimnasio);
            fclose(archivo_gimnasio);
            return NULL;
        }
        entrenador_gimnasio = personaje_cargar(entrenador_gimnasio, su_primer_pokemon, archivo_gimnasio, ENTRENADOR);
        if (!entrenador_gimnasio){
            free(entrenador_gimnasio);
            free(su_primer_pokemon);
            gimnasio_destruir(nuevo_gimnasio);
            fclose(archivo_gimnasio);
            return NULL;
        }
        lista_apilar(nuevo_gimnasio->miembros, entrenador_gimnasio);
    }

    return nuevo_gimnasio;
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
 * Destruye la lista de miembros de un gimnasio.
 */
void miembros_destruir(lista_t* lista_miembros){
    if(!lista_miembros) return;
    while(!lista_vacia(lista_miembros)){
        personaje_t* personaje_a_borrar = lista_ultimo(lista_miembros);
        entrenador_destruir(personaje_a_borrar);
        lista_desapilar(lista_miembros);
    }
    lista_destruir(lista_miembros);
}

/*
 * Destruye el gimnasio liberando la memoria reservada por el mismo.
 */
void gimnasio_destruir(gimnasio_t* gimnasio){
    if (!gimnasio) return;
    miembros_destruir(gimnasio->miembros);
    free(gimnasio);    
}