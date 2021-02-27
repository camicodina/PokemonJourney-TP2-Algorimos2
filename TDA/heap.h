#ifndef __HEAP_H__
#define __HEAP_H__

#define ABB_RECORRER_INORDEN   0
#define ABB_RECORRER_PREORDEN  1
#define ABB_RECORRER_POSTORDEN 2

#define EXITO 0
#define FALLA -1

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>


/*
 * Comparador de elementos. Recibe dos elementos del arbol y devuelve
 * 0 en caso de ser iguales, 1 si el primer elemento es mayor al
 * segundo o -1 si el primer elemento es menor al segundo.
 */
typedef int (*heap_comparador)(void*, void*);

/*
 * Destructor de elementos. Cada vez que un elemento deja el heap
 * (arbol_borrar o arbol_destruir) se invoca al destructor pasandole
 * el elemento.
 */
typedef void (*heap_liberar_elemento)(void*);


typedef struct heap {
    void** vector;
    size_t tope;
    heap_comparador comparador;
    heap_liberar_elemento destructor;
}heap_t;

/*
 * Se encanrga de reservar memoria para el heap, designando el comparador de elementos a 
 * utilizar y su destructor (la forma de eliminar dichos elementos).
 * Devuelve un puntero al heap creado o NULL en caso de error.
 */
heap_t* heap_crear(heap_comparador comparador, heap_liberar_elemento destructor);

/*
 * Recibe el puntero al (heap) y el elemento a insertar en este.
 * Inserta el elemento en su correspondiente posicion.
 * Devuelve 0 si el elemento se inserta correctamente o -1 en caso de error.
 */
int heap_insertar_elemento(heap_t* heap, void* elemento);

/*
 * Devuelve el elemento que se encuentra en la raiz. En caso de un arbol maximal el elemento mayor,
 * y en caso de un arbol minimal, el elemento menor. (El elemento mayor o menor es definido por el comparador).
 */
void* heap_obtener_raiz(heap_t* heap);

/*
 * Elimina el elemento que se encuentra en la raiz, devulve 0 en caso de exito y -1 en caso de error.
 */
int heap_eliminar_raiz(heap_t* heap);

/*
 * Devuelve la cantidad de elementos que hay en el arbol (heap).
*/
size_t heap_elementos(heap_t* heap);

/*
 * Determina si el árbol está vacío.
 * Devuelve true si está vacío o el arbol es NULL, false si el árbol tiene elementos.
 */
bool heap_vacio(heap_t* heap);


/*
 * LIbera la memoria reservada para el heap.
 */
void heap_destruir(heap_t* heap);

#endif /* __HEAP_H__ */