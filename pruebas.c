#include "heap.h"
#include "gimnasio.h"
#include "pa2mm.h"

int comparador(gimnasio_t* gimnasio_1, gimnasio_t* gimnasio_2){
    if(gimnasio_1->dificultad > gimnasio_2->dificultad){
        return 1;
    }else if(gimnasio_1->dificultad < gimnasio_2->dificultad){
        return -1;
    }else{
        return 0;
    }
}

void destructor(gimnasio_t* gimnasio){
    gimnasio_destruir(gimnasio);
}

// -------------------------- PRUEBAS HEAP -------------------------- //

void probar_crear_heap_vacio(){
    heap_t* heap_inicial = NULL;

    pa2m_afirmar((heap_inicial=heap_crear(comparador,destructor)) != NULL, "Puedo crear un heap");
    pa2m_afirmar(heap_vacio(heap_inicial) == true, "Esta vacio");
    pa2m_afirmar(heap_raiz(heap_inicial) == NULL, "Su inicio es NULL");
    pa2m_afirmar(heap_borrar_minimal(heap_inicial) == -1, "No se puede borrar minimal");

    heap_destruir(heap_inicial);
}


void probar_insertar_en_heap(){
    heap_t* heap_inicial;
    gimnasio_t* gimnasio_1 =gimnasio_crear("Gimnasios/gimnasio_1");
    gimnasio_t* gimnasio_2 =gimnasio_crear("Gimnasios/gimnasio_2");
    gimnasio_t* gimnasio_3 =gimnasio_crear("Gimnasios/gimnasio_3");
    if(!gimnasio_1 || !gimnasio_2 || !gimnasio_3){
        gimnasio_destruir(gimnasio_1);
        gimnasio_destruir(gimnasio_2);
        gimnasio_destruir(gimnasio_3);
    }
    

    pa2m_afirmar(heap_insertar(heap_inicial, gimnasio_1) == 0, "Se inserta primer elemento");
    pa2m_afirmar(heap_vacio(heap_inicial) == false, "Ya no esta vacio");
    pa2m_afirmar(heap_insertar(heap_inicial, gimnasio_2) == 0, "Se inserta segundo elemento");
    pa2m_afirmar(heap_elementos(heap_inicial) == 2, "Hay dos elementos");
    pa2m_afirmar(heap_raiz(heap_inicial) == gimnasio_1, "La raiz es el menor elemento");
    
    heap_destruir(heap_inicial);

}

int main(){
    

    pa2m_nuevo_grupo("PRUEBAS DE HEAP");
    probar_crear_heap_vacio();
    probar_insertar_en_heap();
    
    pa2m_mostrar_reporte();
}

