#define EXITO 0
#define FALLA -1

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "heap.h"

// -------------------------- FUNCIONES CREACION -------------------------- //

/*
 * Crea el heap y reserva la memoria necesaria de la estructura.
 * Comparador se utiliza para comparar dos elementos.
 * Destructor es invocado sobre cada elemento que sale del heap,
 * puede ser NULL indicando que no se debe utilizar un destructor.
 *
 * Devuelve un puntero al heap creado o NULL en caso de error.
 */
heap_t* heap_crear(heap_comparador comparador, heap_liberar_elemento destructor){
    if(!comparador) return NULL;
    heap_t* heap = calloc(1,sizeof(heap_t));
	if(!heap) return NULL;
	heap->comparador= comparador;
    heap->destructor= destructor;
    return heap;
}

// -------------------------- FUNCIONES INSERCIÓN -------------------------- //


/*
 * Intercambia un nodo que es demasiado chico (a partir del comparador recibido)
 * con su padre (por lo tanto, lo mueve hacia arriba) hasta que no es más chico 
 * que el nodo que está encima.
 */
void sift_up(heap_t* heap, size_t pos_nuevo){
    if(pos_nuevo == 0) return;
    size_t pos_padre = (pos_nuevo-1)/2;
    int comparacion = heap->comparador(heap->vector[pos_nuevo],heap->vector[pos_padre]);
    if(comparacion == -1){ // Si 1er elemento es menor al segundo
        void* pos_aux = heap->vector[pos_nuevo];
        heap->vector[pos_nuevo] = heap->vector[pos_padre];
        heap->vector[pos_padre] = pos_aux;
        sift_up(heap,pos_padre);
    }
}


/*
 * Inserta un elemento en el heap.
 * Devuelve 0 si pudo insertar o -1 si no pudo.
 * El arbol admite elementos con valores repetidos.
 */
int heap_insertar(heap_t* heap, void* elemento){
    if(!heap) return FALLA;
    if(!heap->comparador) return FALLA;
    void** vector = realloc(heap->vector,sizeof(void**)*((size_t)heap->tope+1));
    if(!vector) return FALLA;
    heap->vector = vector;
    heap->vector[heap->tope] = elemento;
    (heap->tope)++;
    sift_up(heap, heap->tope-1);
    return EXITO;
}

// -------------------------- FUNCIONES BORRAR -------------------------- //

/*
 * Intercambia un nodo que es demasiado grande con su hijo más pequeño 
 * (por lo tanto, lo mueve hacia abajo) hasta que sea al menos tan chico como 
 * los dos nodos debajo de él.
 */
void sift_down(heap_t* heap, size_t pos_elemento){
	size_t pos_izquierda = (pos_elemento*2)+1;
	size_t pos_derecha = (pos_elemento*2)+2;
	if(pos_izquierda >= heap->tope) return;
	size_t pos_del_menor = pos_izquierda;

	if(pos_derecha < heap->tope){
        if(heap->comparador(heap->vector[pos_izquierda], heap->vector[pos_derecha]) == 1){
            pos_del_menor = pos_derecha;
        }
    }
	if(heap->comparador(heap->vector[pos_elemento], heap->vector[pos_del_menor]) == 1){
        void* pos_aux = heap->vector[pos_elemento];
        heap->vector[pos_elemento] = heap->vector[pos_del_menor];
        heap->vector[pos_del_menor] = pos_aux;
		sift_down(heap, pos_del_menor);
	}
}

/*
 * Quita del heap la raiz (minimal). Adicionalmente, si encuentra el elemento, 
 * invoca el destructor con dicho elemento.
 * Devuelve 0 si pudo eliminar el elemento o -1 en caso contrario.
 */
int heap_borrar_minimal(heap_t* heap){
    if(!heap) return FALLA;
    if(heap_vacio(heap)) return FALLA;
    void* raiz = heap_raiz(heap);
    void* ultimo = heap->vector[heap->tope-1];

    if(heap->tope == 1){
        if(heap->destructor){
            heap->destructor(raiz);
        }
        free(heap->vector); 
        heap->vector = NULL;
        heap->tope = 0;
        return EXITO;
    }

    void** vector = realloc(heap->vector, sizeof(void**)*((size_t)heap->tope-1));
    if(!vector) return -1;
    heap->vector = vector;
    if(heap->destructor){
        heap->destructor(raiz);
    }
    raiz=ultimo;
	(heap->tope)--;
	if(heap->tope > 0){
        sift_down(heap, 0);
    }
	return EXITO;
}


// -------------------------- OTRAS FUNCIONES -------------------------- //

/*
 * Devuelve la cantidad de elementos que hay en el arbol (heap).
*/
size_t heap_elementos(heap_t* heap){
    if (!heap) return 0;
    return heap->tope;
}

/*
 * Devuelve el elemento almacenado como raiz o NULL si el árbol está
 * vacío o no existe.
 */
void* heap_raiz(heap_t* heap){
    if(!heap) return NULL;
    if(!heap->vector) return NULL;
    return heap->vector[0];
}

/*
 * Determina si el heap está vacío.
 * Devuelve true si está vacío o el heap es NULL, false si el heap tiene elementos.
 */
bool heap_vacio(heap_t* heap){
    if(!heap) return true;
    if(heap->tope == 0) return true;
    return false;
}


// -------------------------- FUNCIONES DESTRUIR -------------------------- //

/*
 * Destruye el heap liberando la memoria reservada por el mismo.
 * Adicionalmente invoca el destructor con cada elemento presente en
 * el heap.
 */
void heap_destruir(heap_t* heap) {
    if(!heap) return;
    while (heap->tope > 0){
            heap_borrar_minimal(heap);
        }        
    free(heap);
}
