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


// -------------------------- FUNCION DE CREACION -------------------------- //


/*
 * Función que dado un archivo carga al personaje principal reservando la memoria necesaria 
 * para el mismo o NULL en caso de error.
 */
personaje_t* protagonista_crear(const char* ruta_archivo){

    //Reservo memoria para el personaje y el primer pokemon.
    personaje_t* protagonista = calloc(1,sizeof(personaje_t));
    if(!protagonista)return NULL;

    protagonista->mi_nivel=1;
    
    pokemon_t* mi_primer_pokemon = calloc(1,sizeof(pokemon_t));
    if(!mi_primer_pokemon){
        free(protagonista);
        return NULL;
    }

    //Abro archivo
    FILE* archivo_protagonista= fopen(ruta_archivo,"r");
    if(!archivo_protagonista){
        free(protagonista);
        free(mi_primer_pokemon);
        return NULL;
    }

    return personaje_cargar(protagonista, mi_primer_pokemon,archivo_protagonista,ENTRENADOR);
}


// -------------------------- FUNCIONES DE CARGADO -------------------------- //

/*
 * Función auxiliar para la lectura del nombre del entrenador/lider/protagonista.
 */
personaje_t* leo_nombre_personaje(personaje_t* personaje, pokemon_t* primer_pokemon, FILE* archivo_personaje,char tipo_de_personaje){
    char tipo = (char)fgetc(archivo_personaje);
    if(tipo != tipo_de_personaje){
        fclose(archivo_personaje);
        free(personaje);
        free(primer_pokemon);
        return NULL;
    }
    
    personaje_t* aux_personaje;
    int primera_linea_leida = fscanf(archivo_personaje, FORMATO_LECTURA_ENTRENADOR, aux_personaje->nombre);
    if(!primera_linea_leida || primera_linea_leida != 1){
        fclose(archivo_personaje);
        free(personaje);
        free(primer_pokemon);
        return NULL;
    }
   return aux_personaje;
}

/*
 * Función auxiliar para la lectura del primer pokemon que posee el 
 * entrenador/lider/protagonista.
 */
pokemon_t* leo_primer_pokemon(personaje_t* personaje, pokemon_t* primer_pokemon, FILE* archivo_personaje,char tipo_de_personaje){
char tipo = (char)fgetc(archivo_personaje);
    if(tipo!=POKEMON){
        fclose(archivo_personaje);
        free(personaje);
        free(primer_pokemon);
        return NULL;
    }

    pokemon_t* aux_pokemon;
    int pokemon_leido = fscanf(archivo_personaje, FORMATO_LECTURA_POKEMON,aux_pokemon->nombre, &(aux_pokemon->velocidad), &(aux_pokemon->ataque), &(aux_pokemon->defensa));
    if(!pokemon_leido || pokemon_leido != 4){
        fclose(archivo_personaje);
        free(primer_pokemon);
        free(personaje);
        return NULL;
    } 
    return aux_pokemon;
}

/*
 * Función auxiliar para crear el conjunto de pokemon para combarir inicial.
 */
void estado_inicial_party(personaje_t* personaje, pokemon_t* primer_pokemon){

    lista_iterador_t* iterador_caja = lista_iterador_crear(personaje->caja);
    while ((lista_iterador_tiene_siguiente(iterador_caja)) && (personaje->cantidad_pokemones < 6)){ 
        pokemon_t* pokemon_actual = lista_iterador_elemento_actual(iterador_caja);
        lista_insertar(personaje->party,pokemon_actual);
        lista_iterador_avanzar(iterador_caja);
    }
    lista_iterador_destruir(iterador_caja);
}


/*
 * Función que opera sobre el archivo abierto para crear el personaje.
 */ 
personaje_t* personaje_cargar(personaje_t* personaje, pokemon_t* primer_pokemon, FILE* archivo_personaje, char tipo_de_personaje){
    if(!personaje || !primer_pokemon || !archivo_personaje || !tipo_de_personaje){
        fclose(archivo_personaje);
        free(personaje);
        free(primer_pokemon);
        return NULL;
    }

    //Leo primera linea: nombre del personaje.
    personaje_t* datos_personaje = leo_nombre_personaje(personaje,primer_pokemon,archivo_personaje,tipo_de_personaje);
    personaje = datos_personaje;

    //Leo segunda linea: primer pokemon del entrenador.
    pokemon_t* datos_pokemon = leo_primer_pokemon(personaje,primer_pokemon,archivo_personaje,tipo_de_personaje);
    primer_pokemon = datos_pokemon;

    //Creo las listas party y caja. Agrego primer pokemon a caja (conjunto de poke obtenidos).
    personaje->caja = lista_crear();
    if(!personaje->caja){
        fclose(archivo_personaje);
        free(primer_pokemon);
        free(personaje);
        return NULL;
    }
    
    personaje->party = lista_crear();
    if(!personaje->party){
        fclose(archivo_personaje);
        free(primer_pokemon);
        free(personaje);
        lista_destruir(personaje->caja);
        return NULL;
    }

    lista_insertar(personaje->caja,primer_pokemon);
    (personaje->cantidad_pokemones)++;

    //Leo y agrego el resto de pokemon en caso de haberlos

    pokemon_t* aux_otro_pokemon;
    char tipo = (char)fgetc(archivo_personaje);
    while(tipo==POKEMON){
        int pokemon_leido = fscanf(archivo_personaje, FORMATO_LECTURA_POKEMON,aux_otro_pokemon->nombre, &(aux_otro_pokemon->velocidad), &(aux_otro_pokemon->ataque), &(aux_otro_pokemon->defensa));
        if(pokemon_leido == 4){
            pokemon_t* otro_pokemon = calloc(1,sizeof(pokemon_t));
            if(!otro_pokemon){
                free(primer_pokemon); 
                lista_destruir(personaje->caja);
                lista_destruir(personaje->party);
                free(personaje); 
                fclose(archivo_personaje);
                return NULL;
            }
            otro_pokemon = aux_otro_pokemon;
            lista_insertar(personaje->caja, otro_pokemon);
            (personaje->cantidad_pokemones)++;
        }else{
            free(primer_pokemon); 
            lista_destruir(personaje->caja);
            lista_destruir(personaje->party);
            free(personaje); 
            fclose(archivo_personaje);
            return NULL;
        } 
        tipo = (char)fgetc(archivo_personaje);
    }

    fclose(archivo_personaje);
    
    //Agrego a party
    estado_inicial_party(personaje, primer_pokemon);
    
    return personaje;

}

// -------------------------- OTRAS FUNCIONES -------------------------- //


void mostrar_pokemon(pokemon_t* pokemon){
    printf("%s        %i               %i          %i       \n",pokemon->nombre,pokemon->velocidad,pokemon->ataque,pokemon->defensa);
    printf("-----------------------------------------------------------------\n");
    printf("\n");
}

void mostrar_pokemon_party(personaje_t* protagonista){
    lista_iterador_t* iterador_party = lista_iterador_crear(protagonista->party);
    printf("POKEMON EN PARTY:\n");
    printf("-----------------------------------------------------------------\n");
    printf("NOMBRE        VELOCIDAD        ATAQUE        DEFENSA        \n");
    while(lista_iterador_tiene_siguiente(iterador_party)){
        pokemon_t* pokemon_actual_p = lista_iterador_elemento_actual(iterador_party);
        mostrar_pokemon(pokemon_actual_p);
        lista_iterador_avanzar(iterador_party);
    }
    lista_iterador_destruir(iterador_party);
}

void mostrar_pokemon_caja(personaje_t* protagonista){
    lista_iterador_t* iterador_caja = lista_iterador_crear(protagonista->caja);
    printf("POKEMON EN CAJA:\n");
    printf("-----------------------------------------------------------------\n");
    printf("NOMBRE        VELOCIDAD        ATAQUE        DEFENSA        \n");
    while(lista_iterador_tiene_siguiente(iterador_caja)){
        pokemon_t* pokemon_actual_c = lista_iterador_elemento_actual(iterador_caja);
        mostrar_pokemon(pokemon_actual_c);
        lista_iterador_avanzar(iterador_caja);
    }
    lista_iterador_destruir(iterador_caja);
}

/*
 * Muestra al entrenador con sus pokemon
 */
void protagonista_mostrar(personaje_t* protagonista){
    if(!protagonista) return;
    printf("✩✩✩✩✩✩✩✩✩✩✩✩✩✩✩✩✩✩✩✩✩✩✩✩\n");
    printf("NOMBRE: %s\n",protagonista->nombre);
    printf("NIVEL: %i\n",protagonista->mi_nivel);
    printf("CANTIDAD DE MEDALLAS OBTENIDAS: %i\n",protagonista->mis_medallas);
    printf("\n");
    mostrar_pokemon_party(protagonista);
    mostrar_pokemon_caja(protagonista);
    printf("✩✩✩✩✩✩✩✩✩✩✩✩✩✩✩✩✩✩✩✩✩✩✩✩\n");
}


/*
 * Permite al jugador que pueda cambiar sus pokemon entre los obtenidos (caja) y 
 * los usados para el combate (party)
 */
void cambios_party_caja(personaje_t* protagonista){

}

// -------------------------- FUNCIONES DE DESTRUCCION -------------------------- //


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
    while(!lista_vacia(protagonista->caja)){
        pokemon_t* pokemon_a_borrar = lista_primero(protagonista->caja);
        pokemon_destruir(pokemon_a_borrar);
        lista_borrar_de_posicion(protagonista->caja,0);
    }
    lista_destruir(protagonista->caja);
    lista_destruir(protagonista->party);
    free(protagonista);
}

