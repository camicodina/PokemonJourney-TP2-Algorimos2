
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
gimnasio_t* leo_datos_gimnasio(gimnasio_t* gimnasio, FILE* archivo_gimnasio){
    char tipo = (char)fgetc(archivo_gimnasio);
    if(tipo != GIMNASIO){
        fclose(archivo_gimnasio);
        free(gimnasio);
        return NULL;
    }
    
    gimnasio_t* aux_gimnasio;
    int primera_linea_leida = fscanf(archivo_gimnasio, FORMATO_LECTURA_GIMNASIO, aux_gimnasio->nombre,&(aux_gimnasio->dificultad),&(aux_gimnasio->id_puntero_funcion));
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
        protagonista_destruir(lider_gimnasio);
        fclose(archivo_gimnasio);
        return NULL;
    }
    nuevo_gimnasio->lider=lider_gimnasio;

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

/*
 * Crea los gimnasios y los agrega al heap.
 * Devuelve EXITO o FALLA.
*/
int todos_gimnasios_agregar(heap_t* heap_gimnasios){
    if(!heap_gimnasios) return FALLA;

    gimnasio_t* gimnasio_1 =gimnasio_crear("Gimnasios/gimnasio_1");
    gimnasio_t* gimnasio_2 =gimnasio_crear("Gimnasios/gimnasio_2");
    gimnasio_t* gimnasio_3 =gimnasio_crear("Gimnasios/gimnasio_3");
    gimnasio_t* gimnasio_4 =gimnasio_crear("Gimnasios/gimnasio_4");
    gimnasio_t* gimnasio_5 =gimnasio_crear("Gimnasios/gimnasio_5");
    gimnasio_t* gimnasio_6 =gimnasio_crear("Gimnasios/gimnasio_6");
    gimnasio_t* gimnasio_7 =gimnasio_crear("Gimnasios/gimnasio_7");
    gimnasio_t* gimnasio_8 =gimnasio_crear("Gimnasios/gimnasio_8");

    if(!gimnasio_1 || !gimnasio_2 || !gimnasio_3 || !gimnasio_4 || !gimnasio_5 || !gimnasio_6 || !gimnasio_7 || !gimnasio_8){
        heap_destruir(heap_gimnasios);
        gimnasio_destruir(gimnasio_1);
        gimnasio_destruir(gimnasio_2);
        gimnasio_destruir(gimnasio_3);
        gimnasio_destruir(gimnasio_4);
        gimnasio_destruir(gimnasio_5);
        gimnasio_destruir(gimnasio_6);
        gimnasio_destruir(gimnasio_7);
        gimnasio_destruir(gimnasio_8);
        return FALLA;
    }

    heap_insertar(heap_gimnasios, gimnasio_1);
    heap_insertar(heap_gimnasios, gimnasio_2);
    heap_insertar(heap_gimnasios, gimnasio_3);
    heap_insertar(heap_gimnasios, gimnasio_4);
    heap_insertar(heap_gimnasios, gimnasio_5);
    heap_insertar(heap_gimnasios, gimnasio_6);
    heap_insertar(heap_gimnasios, gimnasio_7);
    heap_insertar(heap_gimnasios, gimnasio_8);

    return EXITO;

}


/*
 * Agrega un gimnasio al árbol de gimnasios
*/
int gimnasios_agregar(heap_t* heap_gimnasios,const char* ruta){
    if(!heap_gimnasios) return FALLA;
    if(!ruta) return FALLA;

    gimnasio_t* gimnasio_a_agregar =gimnasio_crear(ruta);
    if(!gimnasio_a_agregar){
        return FALLA;
    }
    heap_insertar(heap_gimnasios, gimnasio_a_agregar);
    return EXITO;

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
    free(gimnasio);    
}

/*
 * Libera todo
 */
void liberar_todo(batallas_pokemon_t* batallas_pokemon){
    if(!batallas_pokemon) return;
    entrenador_destruir(batallas_pokemon->protagonista);
    heap_destruir(batallas_pokemon->gimnasios);
}