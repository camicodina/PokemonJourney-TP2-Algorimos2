
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


// -------------------------- FUNCIONES DE BATALLA -------------------------- //

void batallas_cargar(funcion_batalla* batallas){
    batallas[0] = &funcion_batalla_1;
    batallas[1] = &funcion_batalla_2;
    batallas[2] = &funcion_batalla_3;
    batallas[3] = &funcion_batalla_4;
    batallas[4] = &funcion_batalla_5;
}

// -------------------------- FUNCIONES CREACION -------------------------- //

/*
 * Función auxiliar para la lectura de los datos del gimnasio.
 */
gimnasio_t* creo_gimnasio_y_leo_datos(FILE* archivo_gimnasio){
    gimnasio_t* nuevo_gimnasio = calloc(1,sizeof(gimnasio_t));
    if(!nuevo_gimnasio){
        return NULL;
    }

    int primera_linea_leida = fscanf(archivo_gimnasio, FORMATO_LECTURA_GIMNASIO,nuevo_gimnasio->nombre,&(nuevo_gimnasio->dificultad),&(nuevo_gimnasio->id_puntero_funcion));
    if(!primera_linea_leida || primera_linea_leida != 3){
        free(nuevo_gimnasio);
        return NULL;
    }
    return nuevo_gimnasio;
}

personaje_t* leer_nombre_y_primer_pokemon(FILE* archivo_gimnasio, gimnasio_t* nuevo_gimnasio, personaje_t* personaje_gimnasio, pokemon_t* primer_pokemon){

    //Leo primera linea: nombre
    leo_nombre_personaje(personaje_gimnasio,primer_pokemon,archivo_gimnasio);

    //Leo segunda linea: primer pokemon
    leo_primer_pokemon(personaje_gimnasio,primer_pokemon,archivo_gimnasio);

    //Creo las listas party y caja. Agrego primer pokemon a caja del lider (conjunto de poke obtenidos).
    personaje_gimnasio->caja = lista_crear();
    if(!personaje_gimnasio->caja){
        free(primer_pokemon);
        free(personaje_gimnasio);
        gimnasio_destruir(nuevo_gimnasio);
        fclose(archivo_gimnasio);
        return NULL;
    }
    
    personaje_gimnasio->party = lista_crear();
    if(!personaje_gimnasio->party){
        free(primer_pokemon);
        free(personaje_gimnasio);
        lista_destruir(personaje_gimnasio->caja);
        gimnasio_destruir(nuevo_gimnasio);
        fclose(archivo_gimnasio);
        return NULL;
    }

    lista_insertar(personaje_gimnasio->caja,primer_pokemon);
    (personaje_gimnasio->cantidad_pokemones)++;

    return personaje_gimnasio;
}


/*
 * Función que dado un archivo carga un gimnasio reservando la memoria necesaria 
 * para el mismo o NULL en caso de error.
 */
gimnasio_t* gimnasio_crear(char ruta_archivo[MAX_RUTA]){
    //Abro archivo
    FILE* archivo_gimnasio= fopen(ruta_archivo,"r");
    if(!archivo_gimnasio){
        return NULL;
    }

    //Reservo memoria para el gimnasio y leo sus datos
    char letra_leida = (char)fgetc(archivo_gimnasio);
    if(letra_leida != GIMNASIO){
        fclose(archivo_gimnasio);
        return NULL;
    }
    gimnasio_t* gimnasio = creo_gimnasio_y_leo_datos(archivo_gimnasio);


    //Reservo memoria para el lider y leo sus datos
    letra_leida = (char)fgetc(archivo_gimnasio);
    if(letra_leida != LIDER){
        gimnasio_destruir(gimnasio);
        fclose(archivo_gimnasio);
        return NULL;
    }
    personaje_t* lider_gimnasio = calloc(1,sizeof(personaje_t));
    if(!lider_gimnasio){
        gimnasio_destruir(gimnasio);
        fclose(archivo_gimnasio);
        return NULL;
    }
    pokemon_t* primer_pokemon_lider = calloc(1,sizeof(pokemon_t));
    if(!primer_pokemon_lider){
        free(lider_gimnasio);
        gimnasio_destruir(gimnasio);
        fclose(archivo_gimnasio);
        return NULL;
    }

    //Agrego el nombre y el primer pokemon del lider
    lider_gimnasio = leer_nombre_y_primer_pokemon(archivo_gimnasio,gimnasio,lider_gimnasio,primer_pokemon_lider);

    //Leo y agrego el resto de pokemon del lider en caso de haberlos
    pokemon_t aux_otro_pokemon;
    letra_leida = (char)fgetc(archivo_gimnasio);
    while(letra_leida == POKEMON){
        int pokemon_leido = fscanf(archivo_gimnasio, FORMATO_LECTURA_POKEMON,aux_otro_pokemon.nombre, &(aux_otro_pokemon.velocidad), &(aux_otro_pokemon.ataque), &(aux_otro_pokemon.defensa));
        if(pokemon_leido == 4){
            pokemon_t* otro_pokemon = calloc(1,sizeof(pokemon_t));
            if(!otro_pokemon){
                protagonista_destruir(lider_gimnasio);
                gimnasio_destruir(gimnasio);
                fclose(archivo_gimnasio);
                return NULL;
            }
            *otro_pokemon = aux_otro_pokemon;
            lista_insertar(lider_gimnasio->caja, otro_pokemon);
            otro_pokemon = NULL;
            (lider_gimnasio->cantidad_pokemones)++;
        }else{
            protagonista_destruir(lider_gimnasio);                
            gimnasio_destruir(gimnasio);
            fclose(archivo_gimnasio);
            return NULL;
        } 
        letra_leida = (char)fgetc(archivo_gimnasio);
    }
    
    //Agrego a party
    estado_inicial_party(lider_gimnasio, primer_pokemon_lider);
    
    //Asigno al gimnasio el lider creado
    gimnasio->lider = lider_gimnasio;


    //Creo pila (lista) de entrenadores y apilo al lider.
    gimnasio->miembros = lista_crear();
    if (!gimnasio->miembros){
        fclose(archivo_gimnasio);
        gimnasio_destruir(gimnasio);
        return NULL;
    }


    //Leo a los entrenadores y a sus pokemon
    if(letra_leida != ENTRENADOR){ //Caso: gimnasio sin entrenadores
        fclose(archivo_gimnasio);
        return gimnasio;
    }
    
    while(letra_leida == ENTRENADOR){
        personaje_t* entrenador_gimnasio = calloc(1,sizeof(personaje_t));
        if(!entrenador_gimnasio){
            fclose(archivo_gimnasio);
            return gimnasio;
        }
        pokemon_t* su_primer_pokemon= calloc(1,sizeof(pokemon_t));
        if(!su_primer_pokemon){
            free(entrenador_gimnasio);
            fclose(archivo_gimnasio);
            return gimnasio;
        }

        entrenador_gimnasio = leer_nombre_y_primer_pokemon(archivo_gimnasio,gimnasio,entrenador_gimnasio,su_primer_pokemon);

        //Leo y agrego el resto de pokemon en caso de haberlos
        pokemon_t aux_otro_pokemon;
        letra_leida = (char)fgetc(archivo_gimnasio);
        while(letra_leida == POKEMON){
            int pokemon_leido = fscanf(archivo_gimnasio, FORMATO_LECTURA_POKEMON,aux_otro_pokemon.nombre, &(aux_otro_pokemon.velocidad), &(aux_otro_pokemon.ataque), &(aux_otro_pokemon.defensa));
            if(pokemon_leido == 4){
                pokemon_t* otro_pokemon = calloc(1,sizeof(pokemon_t));
                if(!otro_pokemon){
                    protagonista_destruir(entrenador_gimnasio);
                    fclose(archivo_gimnasio);
                    return gimnasio;
                }
                *otro_pokemon = aux_otro_pokemon;
                lista_insertar(entrenador_gimnasio->caja, otro_pokemon);
                otro_pokemon = NULL;
                (entrenador_gimnasio->cantidad_pokemones)++;
            }else{
                protagonista_destruir(entrenador_gimnasio);
                fclose(archivo_gimnasio);
                return gimnasio;;
            } 
            letra_leida = (char)fgetc(archivo_gimnasio);
        }
        
        //Agrego a party
        estado_inicial_party(entrenador_gimnasio, su_primer_pokemon);

        //Apilo entrenador en lista de entrenadores
        lista_apilar(gimnasio->miembros, entrenador_gimnasio);
    }

    fclose(archivo_gimnasio);
    return gimnasio;
}



// -------------------------- FUNCIONES MOSTRAR -------------------------- //

void mostrar_miembros(lista_t* miembros){
    lista_iterador_t* iterador_miembros = lista_iterador_crear(miembros);
    printf("MIEMBROS OFICIALES:\n");
    printf("------------------------\n");
    while(lista_iterador_tiene_siguiente(iterador_miembros)){
        personaje_t* personaje_actual = lista_iterador_elemento_actual(iterador_miembros);
        
        printf("%s \n",personaje_actual->nombre);
    
        lista_iterador_avanzar(iterador_miembros);
    }
    lista_iterador_destruir(iterador_miembros);
}

/*
 * Muestra información del gimnasio
 */
void gimnasio_mostrar(gimnasio_t* gimnasio){
    if(!gimnasio) return;
    printf("✩✩✩✩✩✩✩✩✩✩✩✩✩✩✩✩✩✩✩✩✩✩✩✩\n");
    printf("GIMNASIO: %s\n",gimnasio->nombre);
    printf("DIFICULTAD: %i\n",gimnasio->dificultad);
    printf("LIDER: %s\n",gimnasio->lider->nombre);
    printf("\n");
    mostrar_miembros(gimnasio->miembros);
    printf("✩✩✩✩✩✩✩✩✩✩✩✩✩✩✩✩✩✩✩✩✩✩✩✩\n");
}


/*
 * Muestra los dos pokemon que se enfrentan en el combate del siglo.
 */
void mostrar_combate_informacion(pokemon_t* pokemon_protagonista, pokemon_t* pokemon_oponente){
    printf("\n---------------------------------------------------------\n");
    printf("NOMBRE        VELOCIDAD        ATAQUE        DEFENSA      \n");
    printf("%-10s        %i             %i            %i            \n",pokemon_protagonista->nombre,pokemon_protagonista->velocidad,pokemon_protagonista->ataque,pokemon_protagonista->defensa);
    printf("---------------------------------------------------------\n");
    printf("\nSe enfrenta al temerario...\n");
    printf("\n---------------------------------------------------------\n");
    printf("%-10s        %i             %i            %i            \n",pokemon_oponente->nombre,pokemon_oponente->velocidad,pokemon_oponente->ataque,pokemon_oponente->defensa);
    printf("\n---------------------------------------------------------\n");
    printf("\n");
}


// -------------------------- FUNCIONES POST-BATALLA -------------------------- //

/*
*  Mejora cada una de las habilidades del pokemon mientras sean menores a 63.
*/
void recompensa_caracteristicas(pokemon_t* pokemon){
    if(!pokemon) return;
    if(pokemon->nivel < 63){
        printf("%s SUBIO DE NIVEL!\n", pokemon->nombre);
        printf("Todas la caracteristicas aumentan +1\n");
        pokemon->ataque++;
        pokemon->velocidad++;
        pokemon->defensa++;
        pokemon->nivel++; 
    }
}

/*
 * Revisa la caja del protagonista y la del oponente. El protagonista pide 
 * prestado un pokemon del oponente a elección.
 * Devuelve EXITO o FALLA.
 */
int pedir_prestado(personaje_t* protagonista, personaje_t* oponente){
    size_t id_prestado;
    if(!protagonista) return FALLA;
    if(!oponente) return FALLA;
    printf("Elija el Pokemon a tomar prestado por un ratito :)\n");
    mostrar_pokemon_caja(oponente);
    printf("Ingrese el id del pokemon que quiera pedir o '0' para cancelar:\n");
    scanf("%lu", &id_prestado);
    if(id_prestado <= (oponente->cantidad_pokemones)){
        if(id_prestado == 0) return FALLA;
        size_t posicion_prestado = id_prestado-1;
        pokemon_t* aux_pokemon_prestado = (pokemon_t*)(lista_elemento_en_posicion(oponente->caja,posicion_prestado));
        pokemon_t* pokemon_prestado = calloc(1,sizeof(pokemon_t));
        if(!pokemon_prestado) return -1;
        pokemon_prestado = aux_pokemon_prestado;

        lista_insertar(protagonista->caja, pokemon_prestado);
        printf("Completado!\n");
        return 0;
    }else{
        printf("Hubo un error\n");
        return -1;
    }
}

// -------------------------- FUNCIONES DESTRUIR -------------------------- //

/*
 * Destruye la lista de miembros de un gimnasio.
 */
void miembros_destruir(lista_t* lista_miembros){
    if(!lista_miembros) return;
    while(!lista_vacia(lista_miembros)){
        personaje_t* personaje_a_borrar = lista_ultimo(lista_miembros);
        protagonista_destruir(personaje_a_borrar);
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
    protagonista_destruir(gimnasio->lider);
    free(gimnasio);    
}

/*
 * Libera todo
 */
void liberar_todo(batallas_pokemon_t* batallas_pokemon){
    if(!batallas_pokemon) return;
    protagonista_destruir(batallas_pokemon->protagonista);
    heap_destruir(batallas_pokemon->gimnasios);
    free(batallas_pokemon);
}
