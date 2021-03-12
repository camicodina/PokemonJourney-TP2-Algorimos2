
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
    gimnasio_t* gimnasio = calloc(1,sizeof(gimnasio_t));
    if(!gimnasio){
        fclose(archivo_gimnasio);
        return NULL;
    }

    int primera_linea_leida = fscanf(archivo_gimnasio, FORMATO_LECTURA_GIMNASIO,gimnasio->nombre,&(gimnasio->dificultad),&(gimnasio->id_puntero_funcion));
    if(!primera_linea_leida || primera_linea_leida != 3){
        fclose(archivo_gimnasio);
        free(gimnasio);
        return NULL;
    }
    return gimnasio;
}


/*
 * Función auxiliar para la lectura de los datos del lider.
 */
personaje_t* creo_lider_y_leo_datos(FILE* archivo_gimnasio, gimnasio_t* gimnasio){
    personaje_t* lider_gimnasio = calloc(1,sizeof(personaje_t));
    if(!lider_gimnasio){
        gimnasio_destruir(gimnasio);
        fclose(archivo_gimnasio);
        return NULL;
    }
    pokemon_t* primer_pokemon_lider = calloc(1,sizeof(pokemon_t));
    if(!primer_pokemon_lider){
        gimnasio_destruir(gimnasio);
        free(lider_gimnasio);
        fclose(archivo_gimnasio);
        return NULL;
    }

    lider_gimnasio = personaje_cargar(lider_gimnasio, primer_pokemon_lider, archivo_gimnasio);
    if(!lider_gimnasio){
        free(lider_gimnasio);
        free(primer_pokemon_lider);
        gimnasio_destruir(gimnasio);
        fclose(archivo_gimnasio);
        return NULL;
        }

    protagonista_mostrar(lider_gimnasio);
    return lider_gimnasio;
}

/*
 * Función auxiliar para la lectura de los datos de un entrenador.
 */
personaje_t* creo_entrenador_y_leo_datos(FILE* archivo_gimnasio, gimnasio_t* gimnasio){
    personaje_t* entrenador_gimnasio = calloc(1,sizeof(personaje_t));
    if(!entrenador_gimnasio){
        gimnasio_destruir(gimnasio);
        fclose(archivo_gimnasio);
        return NULL;
    }
    pokemon_t* su_primer_pokemon= calloc(1,sizeof(pokemon_t));
    if(!su_primer_pokemon){
        free(entrenador_gimnasio);
        gimnasio_destruir(gimnasio);
        fclose(archivo_gimnasio);
        return NULL;
    }

    entrenador_gimnasio = personaje_cargar(entrenador_gimnasio, su_primer_pokemon, archivo_gimnasio);
    if(!entrenador_gimnasio){
        free(entrenador_gimnasio);
        free(su_primer_pokemon);
        fclose(archivo_gimnasio);
        return NULL;
    }
   
    return entrenador_gimnasio;
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
    gimnasio_t* nuevo_gimnasio = creo_gimnasio_y_leo_datos(archivo_gimnasio);
    if(!nuevo_gimnasio){
        fclose(archivo_gimnasio);
        return NULL;
    }

    //Reservo memoria para el lider y leo sus datos
    letra_leida = (char)fgetc(archivo_gimnasio);
    if(letra_leida != LIDER){
        fclose(archivo_gimnasio);
        gimnasio_destruir(nuevo_gimnasio);
        return NULL;
    }

    personaje_t* nuevo_lider = creo_lider_y_leo_datos(archivo_gimnasio,nuevo_gimnasio);
    if(!nuevo_lider){
        fclose(archivo_gimnasio);
        gimnasio_destruir(nuevo_gimnasio);
        return NULL;
    }
    nuevo_gimnasio->lider = nuevo_lider;


    //Creo pila (lista) de entrenadores y apilo al lider.
    nuevo_gimnasio->miembros = lista_crear();
    if (!nuevo_gimnasio->miembros){
        fclose(archivo_gimnasio);
        gimnasio_destruir(nuevo_gimnasio);
        return NULL;
    }


    //Leo a los entrenadores y a sus pokemon
    
    printf("%c",letra_leida);
    while(letra_leida == ENTRENADOR){
        printf("hola");
        personaje_t* nuevo_entrenador =  creo_entrenador_y_leo_datos(archivo_gimnasio,nuevo_gimnasio);
        if(!nuevo_entrenador){
            return nuevo_gimnasio;
        }
        lista_apilar(nuevo_gimnasio->miembros, nuevo_entrenador);
        
        letra_leida = (char)fgetc(archivo_gimnasio);
    }

    return nuevo_gimnasio;
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
    printf("%s        %i               %i          %i       \n",pokemon_protagonista->nombre,pokemon_protagonista->velocidad,pokemon_protagonista->ataque,pokemon_protagonista->defensa);
    printf("Se enfrenta al temerario...");
    printf("%s        %i               %i          %i       \n",pokemon_oponente->nombre,pokemon_oponente->velocidad,pokemon_oponente->ataque,pokemon_oponente->defensa);
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
