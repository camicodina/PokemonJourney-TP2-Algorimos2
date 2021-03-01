#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>
#include "lista.h"

/*
 * Crea la lista reservando la memoria necesaria.
 * Devuelve un puntero a la lista creada o NULL en caso de error.
 */
lista_t* lista_crear(){
    lista_t* lista = malloc(sizeof(lista_t));
    if(!lista) return NULL;
    lista->nodo_inicio = NULL;
    lista->nodo_fin = NULL;
    lista->cantidad = 0;
    return lista;
}

/*
 * Inserta un elemento al final de la lista.
 * Devuelve 0 si pudo insertar o -1 si no pudo.
 */

nodo_t* aux_crear_nodos(void* elemento){
    nodo_t* nuevo_nodo = malloc(sizeof(nodo_t));
    if(!nuevo_nodo) return NULL;
    nuevo_nodo->elemento = elemento;
    nuevo_nodo->siguiente = NULL;
    return nuevo_nodo;
}

int lista_insertar(lista_t* lista, void* elemento){
    if(!lista) return -1;
    nodo_t* nodo_a_agregar = aux_crear_nodos(elemento);
    if(!nodo_a_agregar) return -1;
    if (lista->cantidad == 0){
        lista->nodo_inicio = nodo_a_agregar;
		lista->nodo_fin = nodo_a_agregar;
        lista->cantidad = 1;
        return 0;
    }else{
        lista->nodo_fin->siguiente = nodo_a_agregar;
        lista->nodo_fin = nodo_a_agregar;
        (lista->cantidad)++;
    }
    return 0;
}

/*
 * Inserta un elemento en la posicion indicada, donde 0 es insertar
 * como primer elemento y 1 es insertar luego del primer elemento.
 * En caso de no existir la posicion indicada, lo inserta al final.
 * Devuelve 0 si pudo insertar o -1 si no pudo.
 */

int lista_insertar_en_posicion(lista_t* lista, void* elemento, size_t posicion){
    if(!lista) return -1;
    int contador = 0;
    if(posicion>(lista->cantidad-1) || lista->cantidad==0){
        lista_insertar(lista, elemento);
    }else{
        nodo_t* nodo_a_insertar_en_posicion = aux_crear_nodos(elemento);
        if(!nodo_a_insertar_en_posicion) return -1;
        if(posicion == 0){
            nodo_a_insertar_en_posicion->siguiente = lista->nodo_inicio;
            lista->nodo_inicio = nodo_a_insertar_en_posicion;
        }else{
            nodo_t* aux_buscar_anterior = lista->nodo_inicio;
            while(contador<(posicion-1) && contador<(lista->cantidad)){
                if(aux_buscar_anterior!=NULL){
			        aux_buscar_anterior = aux_buscar_anterior->siguiente;
                }
                contador++;
		    }
            nodo_a_insertar_en_posicion->siguiente = aux_buscar_anterior->siguiente;
            aux_buscar_anterior->siguiente = nodo_a_insertar_en_posicion;
        }
        (lista->cantidad)++;
    };
    return 0;
}

/*
 * Quita de la lista el elemento que se encuentra en la ultima posición.
 * Devuelve 0 si pudo eliminar o -1 si no pudo.
 */

int lista_borrar(lista_t* lista){
    if(!lista) return -1;
    if(lista->cantidad == 0) return -1;

    if((lista->cantidad) == 1){
		free(lista->nodo_fin);
		lista->nodo_inicio = NULL;
		lista->nodo_fin = NULL;
        lista->cantidad--;
		return 0;
    }

    nodo_t* aux_buscar_penultimo = lista->nodo_inicio;
    size_t buscar = 0;
    size_t posicion_final = (lista->cantidad)-1;

    while(buscar < (posicion_final-1)){
		aux_buscar_penultimo = aux_buscar_penultimo->siguiente;
        buscar++;
	}

    if(aux_buscar_penultimo->siguiente != NULL){
        lista->nodo_fin = aux_buscar_penultimo;
        free(aux_buscar_penultimo->siguiente);
        lista->nodo_fin->siguiente = NULL;
    }

    (lista->cantidad)--;
    return 0;
}

/*
 * Quita de la lista el elemento que se encuentra en la posición
 * indicada, donde 0 es el primer elemento.
 * En caso de no existir esa posición se intentará borrar el último
 * elemento.
 * Devuelve 0 si pudo eliminar o -1 si no pudo.
 *
 */


int lista_borrar_de_posicion(lista_t* lista, size_t posicion){
    if(!lista) return -1;
    if(lista_vacia(lista)) return -1;
    size_t contador = 0;
    nodo_t* aux_buscar = lista->nodo_inicio;

    if(posicion>=(lista->cantidad-1)){
        lista_borrar(lista);
    }else{
        if(posicion == 0){
            lista->nodo_inicio = aux_buscar->siguiente;
		    free(aux_buscar);
        }else{
            while(contador< (posicion-1)){
                if(aux_buscar != NULL){
                    aux_buscar = aux_buscar->siguiente;
                }
                contador++;
            }
            nodo_t* aux_siguiente = aux_buscar->siguiente->siguiente;
            free(aux_buscar->siguiente);
            aux_buscar->siguiente = aux_siguiente;
        }
        (lista->cantidad)--;
    }
    return 0;
}

/*
 * Devuelve el elemento en la posicion indicada, donde 0 es el primer
 * elemento.
 *
 * Si no existe dicha posicion devuelve NULL.
 */

void* lista_elemento_en_posicion(lista_t* lista, size_t posicion){
    if(!lista) return NULL;
    if(posicion >= lista->cantidad) return NULL;
    if(posicion == 0) return lista->nodo_inicio->elemento;
    if(posicion == ((lista->cantidad)-1)) return lista->nodo_fin->elemento;

    nodo_t* aux_buscar = lista->nodo_inicio;

    for(size_t i=0; i<posicion && aux_buscar!=NULL; i++){
        aux_buscar = aux_buscar->siguiente;
    }
    if(aux_buscar != NULL) return aux_buscar->elemento;
    return NULL;
}


/*
 * Devuelve el último elemento de la lista o NULL si la lista se
 * encuentra vacía.
 */
void* lista_ultimo(lista_t* lista){
    if(!lista) return NULL;
    if(lista->cantidad == 0) return NULL;
    return (lista->nodo_fin->elemento);
}

/*
 * Devuelve true si la lista está vacía o false en caso contrario.
 */
bool lista_vacia(lista_t* lista){
    if(!lista || lista->cantidad == 0)
		return true;
	return false;
}

/*
 * Devuelve la cantidad de elementos almacenados en la lista.
 */
size_t lista_elementos(lista_t* lista){
    if(!lista || lista_vacia(lista)){
        return 0;
    }else{
        return (lista->cantidad);
    }
}

/*
 * Apila un elemento.
 * Devuelve 0 si pudo o -1 en caso contrario.
 */

int lista_apilar(lista_t* lista, void* elemento){
    if(!lista) return -1;
    return lista_insertar(lista,elemento);
}

/*
 * Desapila un elemento.
 * Devuelve 0 si pudo desapilar o -1 si no pudo.
 */


int lista_desapilar(lista_t* lista){
    if(!lista) return -1;
    if(lista_vacia(lista)) return -1;
    return lista_borrar(lista);
}


/*
 * Devuelve el elemento en el tope de la pila o NULL
 * en caso de estar vacía.
 */
void* lista_tope(lista_t* lista){
    if(!lista) return NULL;
    if(lista_vacia(lista)) return NULL;
    return lista_ultimo(lista);
}

/*
 * Encola un elemento.
 * Devuelve 0 si pudo encolar o -1 si no pudo.
 */
int lista_encolar(lista_t* lista, void* elemento){
    if(!lista) return -1;
    if(!elemento) return -1;
    return lista_insertar(lista,elemento);
}

/*
 * Desencola un elemento.
 * Devuelve 0 si pudo desencolar o -1 si no pudo.
 */
int lista_desencolar(lista_t* lista){
    if(!lista) return -1;
    return lista_borrar_de_posicion(lista, 0);
}


/*
 * Devuelve el primer elemento de la cola o NULL en caso de estar
 * vacía.
 */
void* lista_primero(lista_t* lista){
    if(!lista) return NULL;
    return lista_elemento_en_posicion(lista, 0);;
}

/*
 * Libera la memoria reservada por la lista.
 */

void lista_destruir(lista_t* lista){
    if(lista){
        while(lista->cantidad>0){
		lista_borrar(lista);
        }
        free(lista);
    }
}

// -------------------------- ITERADOR -------------------------- //

/*
 * Crea un iterador para una lista. El iterador creado es válido desde
 * el momento de su creación hasta que no haya mas elementos por
 * recorrer o se modifique la lista iterada (agregando o quitando
 * elementos de la lista).
 *
 * Al momento de la creación, el iterador queda listo para devolver el
 * primer elemento utilizando lista_iterador_elemento_actual.
 *
 * Devuelve el puntero al iterador creado o NULL en caso de error.
 */

lista_iterador_t* lista_iterador_crear(lista_t* lista){
    if(!lista) return NULL;
    lista_iterador_t* iterador = malloc(sizeof(lista_iterador_t));
    if(!iterador) return NULL;
    iterador->lista = lista;
    iterador->corriente = lista->nodo_inicio;
    return iterador;
}

/*
 * Devuelve true si hay mas elementos sobre los cuales iterar o false
 * si no hay mas.
 */

bool lista_iterador_tiene_siguiente(lista_iterador_t* iterador){
    if(!iterador) return false;
    return iterador->corriente;
}

/*
 * Avanza el iterador al siguiente elemento.
 * Devuelve true si pudo avanzar el iterador o false en caso de
 * que no queden elementos o en caso de error.
 *
 * Una vez llegado al último elemento, si se invoca a
 * lista_iterador_elemento_actual, el resultado siempre será NULL.
 */

bool lista_iterador_avanzar(lista_iterador_t* iterador){
    if(!iterador) return false;
    if(!(iterador->corriente)) return false; 
    iterador->corriente = iterador->corriente->siguiente;
    return iterador->corriente;
}

/*
 * Devuelve el elemento actual del iterador o NULL en caso de que no
 * exista dicho elemento o en caso de error.
 */
void* lista_iterador_elemento_actual(lista_iterador_t* iterador){
    if(!iterador) return NULL;
    if(!(iterador->lista)) return NULL;
    if(!(iterador->corriente)) return NULL;
    return iterador->corriente->elemento;
}

/*
 * Libera la memoria reservada por el iterador.
 */
void lista_iterador_destruir(lista_iterador_t* iterador){
    if(iterador){
        free(iterador);
    }
}

/*
 * Iterador interno. Recorre la lista e invoca la funcion con cada elemento de
 * la misma. Dicha función puede devolver true si se deben seguir recorriendo
 * elementos o false si se debe dejar de iterar elementos.
 *
 * La función retorna la cantidad de elementos iterados o 0 en caso de error.
 */
size_t lista_con_cada_elemento(lista_t* lista, bool (*funcion)(void*, void*), void *contexto){
    if(!lista) return 0;
    if(!funcion) return 0;
    if(!contexto) return 0;
    size_t cantidad_de_elementos_iterados = 0;
    nodo_t* aux_buscar = lista->nodo_inicio;
    bool sigo_recorriendo = true;

    while(cantidad_de_elementos_iterados < (lista->cantidad) && sigo_recorriendo){
        sigo_recorriendo = funcion(aux_buscar->elemento, contexto);
        aux_buscar = aux_buscar->siguiente;
        (cantidad_de_elementos_iterados)++;
    }
    return cantidad_de_elementos_iterados;
}