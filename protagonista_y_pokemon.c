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
#include "protagonista_y_pokemon.h"


// -------------------------- FUNCION DE CREACION -------------------------- //


/*
 * Función que dado un archivo carga al personaje principal reservando la memoria necesaria 
 * para el mismo o NULL en caso de error.
 */
personaje_t* protagonista_crear(char ruta_archivo[MAX_RUTA]){
    //Abro archivo
    FILE* archivo_protagonista= fopen(ruta_archivo,"r");
    if(!archivo_protagonista){
        return NULL;
    }

    //Verifico tipo de la primera linea recibida
    char tipo = (char)fgetc(archivo_protagonista);
    if(tipo != ENTRENADOR){
        fclose(archivo_protagonista);
        return NULL;
    }

    //Reservo memoria para el personaje y el primer pokemon.
    personaje_t* protagonista = calloc(1,sizeof(personaje_t));
    if(!protagonista){
        fclose(archivo_protagonista);
        return NULL;
    }

    pokemon_t* mi_primer_pokemon = calloc(1,sizeof(pokemon_t));
    if(!mi_primer_pokemon){
        free(protagonista);
        fclose(archivo_protagonista);
        return NULL;
    }

    personaje_t* protagonista_cargado = personaje_cargar(protagonista,mi_primer_pokemon,archivo_protagonista);
    fclose(archivo_protagonista);
    return protagonista_cargado;
}


// -------------------------- FUNCIONES DE CARGADO -------------------------- //

/*
 * Función auxiliar para la lectura del nombre del entrenador/lider/protagonista.
 */
personaje_t* leo_nombre_personaje(personaje_t* personaje, pokemon_t* primer_pokemon, FILE* archivo_personaje){
    int primera_linea_leida = fscanf(archivo_personaje, FORMATO_LECTURA_ENTRENADOR, personaje->nombre);
    if(!primera_linea_leida || primera_linea_leida != 1){
        fclose(archivo_personaje);
        free(personaje);
        free(primer_pokemon);
        return NULL;
    }
   return personaje;
}

/*
 * Función auxiliar para la lectura del primer pokemon que posee el 
 * entrenador/lider/protagonista.
 */
pokemon_t* leo_primer_pokemon(personaje_t* personaje, pokemon_t* primer_pokemon, FILE* archivo_personaje){
char tipo = (char)fgetc(archivo_personaje);
    if(tipo!=POKEMON){
        fclose(archivo_personaje);
        free(personaje);
        free(primer_pokemon);
        return NULL;
    }

    int pokemon_leido = fscanf(archivo_personaje, FORMATO_LECTURA_POKEMON,primer_pokemon->nombre, &(primer_pokemon->velocidad), &(primer_pokemon->ataque), &(primer_pokemon->defensa));
    if(!pokemon_leido || pokemon_leido != 4){
        fclose(archivo_personaje);
        free(primer_pokemon);
        free(personaje);
        return NULL;
    } 
    return primer_pokemon;
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
personaje_t* personaje_cargar(personaje_t* personaje, pokemon_t* primer_pokemon, FILE* archivo_personaje){
    if(!personaje || !primer_pokemon || !archivo_personaje){
        fclose(archivo_personaje);
        free(personaje);
        free(primer_pokemon);
        return NULL;
    }

    //Leo primera linea: nombre del personaje.
    leo_nombre_personaje(personaje,primer_pokemon,archivo_personaje);

    //Leo segunda linea: primer pokemon del entrenador.
    leo_primer_pokemon(personaje,primer_pokemon,archivo_personaje);

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
    pokemon_t aux_otro_pokemon;
    char tipo = (char)fgetc(archivo_personaje);
    while(tipo == POKEMON){
        int pokemon_leido = fscanf(archivo_personaje, FORMATO_LECTURA_POKEMON,aux_otro_pokemon.nombre, &(aux_otro_pokemon.velocidad), &(aux_otro_pokemon.ataque), &(aux_otro_pokemon.defensa));
        if(pokemon_leido == 4){
            pokemon_t* otro_pokemon = calloc(1,sizeof(pokemon_t));
            if(!otro_pokemon){
                protagonista_destruir(personaje);
                fclose(archivo_personaje);
                return NULL;
            }
            *otro_pokemon = aux_otro_pokemon;
            lista_insertar(personaje->caja, otro_pokemon);
            otro_pokemon = NULL;
            (personaje->cantidad_pokemones)++;
        }else{
            protagonista_destruir(personaje);
            fclose(archivo_personaje);
            return NULL;
        } 
        tipo = (char)fgetc(archivo_personaje);
    }
    
    //Agrego a party
    estado_inicial_party(personaje, primer_pokemon);
    
    return personaje;

}

// -------------------------- OTRAS FUNCIONES -------------------------- //

/*
 * Imprime el pokemon recibido por parámetro con sus características 
 */
void mostrar_pokemon(pokemon_t* pokemon){
    printf("%-10s        %i             %i            %i           %lu   \n",pokemon->nombre,pokemon->velocidad,pokemon->ataque,pokemon->defensa,pokemon->id);
    printf("-----------------------------------------------------------------\n");
    printf("\n");
}


/*
 * Muestra conjunto de pokemon para combatir de un entrenador
 */
void mostrar_pokemon_party(personaje_t* protagonista){
    size_t i=1;
    lista_iterador_t* iterador_party = lista_iterador_crear(protagonista->party);
    printf("POKEMON EN PARTY:\n");
    printf("-----------------------------------------------------------------\n");
    printf("NOMBRE        VELOCIDAD        ATAQUE        DEFENSA        ID    \n");
    while(lista_iterador_tiene_siguiente(iterador_party)){
        pokemon_t* pokemon_actual_p = lista_iterador_elemento_actual(iterador_party);
        pokemon_actual_p->id = i;
        mostrar_pokemon(pokemon_actual_p);
        i++;
        lista_iterador_avanzar(iterador_party);
    }
    lista_iterador_destruir(iterador_party);
}

/*
 * Muestra conjunto de pokemon obtendos por un entrenador
 */
void mostrar_pokemon_caja(personaje_t* protagonista){
    size_t i = 1;
    lista_iterador_t* iterador_caja = lista_iterador_crear(protagonista->caja);
    printf("POKEMON EN CAJA:\n");
    printf("-----------------------------------------------------------------\n");
    printf("NOMBRE        VELOCIDAD        ATAQUE        DEFENSA        ID   \n");
    while(lista_iterador_tiene_siguiente(iterador_caja)){
        pokemon_t* pokemon_actual_c = lista_iterador_elemento_actual(iterador_caja);
        pokemon_actual_c->id=i;
        mostrar_pokemon(pokemon_actual_c);
        i++;
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
    printf("CANTIDAD DE MEDALLAS OBTENIDAS: %i\n",protagonista->mis_medallas);
    printf("\n");
    mostrar_pokemon_party(protagonista);
    printf("\n");
    mostrar_pokemon_caja(protagonista);
    printf("✩✩✩✩✩✩✩✩✩✩✩✩✩✩✩✩✩✩✩✩✩✩✩✩\n");
}

int recorrer_party(personaje_t* protagonista, pokemon_t* buscado){
    if(!protagonista || !protagonista->party || !buscado) return FALLA;
    lista_iterador_t* iterador_party = lista_iterador_crear(protagonista->party);
    while(lista_iterador_tiene_siguiente(iterador_party)){
        pokemon_t* pokemon_actual = lista_iterador_elemento_actual(iterador_party);
        if(pokemon_actual->nombre == buscado->nombre){
            return FALLA;
        }
        lista_iterador_avanzar(iterador_party);
    }
    lista_iterador_destruir(iterador_party);
    return EXITO;
}


/*
 * Elije Pokemon a usar en la batalla desde party
 */
pokemon_t* elegir_pokemon(personaje_t* protagonista){
    pokemon_t* pokemon_elegido;
    size_t elegido;
    
    printf("Seleccione el Pokemon a utilizar en la partida:\n");
    mostrar_pokemon_party(protagonista);
    scanf("%lu", &elegido);
    if((elegido <= (protagonista->cantidad_pokemones)) && (elegido != 0)){
        size_t posicion_elegido = elegido-1;
        pokemon_elegido = (pokemon_t*)(lista_elemento_en_posicion(protagonista->party,posicion_elegido));
    }
    return pokemon_elegido;
}

/*
 * Permite al jugador que pueda cambiar sus pokemon entre los obtenidos (caja) y 
 * los usados para el combate (party).
 * Devuelve EXITO O FALLA.
 */
int cambios_party_caja(personaje_t* protagonista){
    if(!protagonista) return FALLA;
    size_t id_sacar;
    size_t id_agregar;

    int valorOp;
    printf("Elija la operación que desea realizar:\n");
    printf("1 - Devolver a caja\n");
    printf("2 - Agregar a party\n");
    printf("0 - Cancelar\n");
    scanf("%i", &valorOp);

    switch(valorOp){
    case 1: 
        printf("Elija el Pokemon que desee devolver a caja:\n");
        mostrar_pokemon_party(protagonista);
        printf("Ingrese el ID del pokemon que eligido o '0' para cancelar:\n");
        scanf("%lu", &id_sacar);
        if(id_sacar <= lista_elementos(protagonista->party)){
            if(id_sacar == 0){
                printf("La operacion fue cancelada\n");
                return FALLA;
            }
            size_t posicion_a_sacar = id_sacar-1;
            lista_borrar_de_posicion(protagonista->party,posicion_a_sacar);
        }else{
            printf("Hubo un error\n");
            return FALLA;
        }
        printf("Completado!\n");
        break;
    case 2:
        printf("Elija el Pokemon que desee agregar a party:\n");
        mostrar_pokemon_caja(protagonista);
        printf("Ingrese el ID del pokemon que quiera o '0' para cancelar:\n");
        scanf("%lu", &id_agregar);
        if(id_agregar <= lista_elementos(protagonista->caja)){
            if(id_agregar == 0){
                printf("La operacion fue cancelada\n");
                return FALLA;
            }
            size_t posicion_a_agregar = id_agregar-1;
            pokemon_t* aux_pokemon_a_agregar = (pokemon_t*)(lista_elemento_en_posicion(protagonista->caja,posicion_a_agregar));
            int ya_estaba = recorrer_party(protagonista,aux_pokemon_a_agregar);
            if((ya_estaba==EXITO) && (lista_elementos(protagonista->party) < 6)){
                 lista_insertar(protagonista->party, aux_pokemon_a_agregar);
            }else{
                printf("Hubo un error\n");
                return FALLA;
            }
        }else{
            printf("Hubo un error\n");
            return FALLA;
        } 
        printf("Completado!\n");
        break; 
    case 0:
        printf("Operación cancelada.\n");
        return FALLA;
        break;
    default:
        printf("Hubo un error, intente nuevamente:\n");
        getchar();
        cambios_party_caja(protagonista);
    };

    
    return 0;

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

