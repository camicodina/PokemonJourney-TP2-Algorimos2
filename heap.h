#ifndef __HEAP_H__
#define __HEAP_H__

#define EXITO 0
#define FALLA -1

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>


/*
 * Comparador de elementos. Recibe dos elementos del arbol y devuelve
 * 0 en caso de ser iguales, 1 si el primer elemento es menor al
 * segundo o -1 si el primer elemento es mayor al segundo.
 */
typedef int (*heap_comparador)(void*, void*);

/*
 * Destructor de elementos. Cada vez que un elemento deja el heap
 * (arbol_borrar o arbol_destruir) se invoca al destructor pasandole
 * el elemento.
 */
typedef void (*heap_liberar_elemento)(void*);


typedef struct heap{
    void** vector;
    size_t tope;
    heap_comparador comparador;
    heap_liberar_elemento destructor;
}heap_t;


/*
 * Crea el heap y reserva la memoria necesaria de la estructura.
 * Comparador se utiliza para comparar dos elementos.
 * Destructor es invocado sobre cada elemento que sale del heap,
 * puede ser NULL indicando que no se debe utilizar un destructor.
 *
 * Devuelve un puntero al heap creado o NULL en caso de error.
 */
heap_t* heap_crear(heap_comparador comparador, heap_liberar_elemento destructor);


/*
 * Inserta un elemento en el heap.
 * Devuelve 0 si pudo insertar o -1 si no pudo.
 * El arbol admite elementos con valores repetidos.
 */
int heap_insertar(heap_t* heap, void* elemento);


/*
 * Quita del heap la raiz (minimal). Adicionalmente, si encuentra el elemento, 
 * invoca el destructor con dicho elemento.
 * Devuelve 0 si pudo eliminar el elemento o -1 en caso contrario.
 */
int heap_borrar_minimal(heap_t* heap);

/*
 * Devuelve la cantidad de elementos que hay en el arbol (heap).
*/
size_t heap_elementos(heap_t* heap);

/*
 * Devuelve el elemento almacenado como raiz o NULL si el árbol está
 * vacío o no existe.
 */
void* heap_raiz(heap_t* heap);


/*
 * Determina si el heap está vacío.
 * Devuelve true si está vacío o el heap es NULL, false si el heap tiene elementos.
 */
bool heap_vacio(heap_t* heap);


/*
 * Destruye el heap liberando la memoria reservada por el mismo.
 * Adicionalmente invoca el destructor con cada elemento presente en
 * el heap.
 */
void heap_destruir(heap_t* heap);



#endif /* __HEAP_H__ */