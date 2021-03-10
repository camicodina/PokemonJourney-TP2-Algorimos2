#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "lista.h"
#include "heap.h"
#include "batallas.h"
#include "protagonista_y_pokemon.h"
#include "gimnasio.h"

#include "menu.h"


// -------------------------- COSAS PARA EL HEAP -------------------------- //

int comparador(void* gim_1, void* gim_2){
    gimnasio_t* gimnasio_1 = (gimnasio_t*)gim_1;
    gimnasio_t* gimnasio_2 = (gimnasio_t*)gim_2;
    if(gimnasio_1->dificultad > gimnasio_2->dificultad){
        return 1;
    }else if(gimnasio_1->dificultad < gimnasio_2->dificultad){
        return -1;
    }else{
        return 0;
    }
}

void destructor(void* gim){
    gimnasio_t* gimnasio = (gimnasio_t*)gim;
    gimnasio_destruir(gimnasio);
}

//==================// FUNCION PRINCIPAL //==================// 

int main(){
    printf("\033[01;33m");
    printf("                                       ,'|                           \n"); 
    printf("     _.----.        ____         ,'  _|   ___    ___     ____        \n");    
    printf(" _,-'       `.     |    |  /`.   |,-'    |   |  /   |   |    |  |`.  \n");   
    printf(" |      __    |    '-.  | /   `.  ___    |    |/    |   '-.   | |  | \n");  
    printf("  |.    | |   |  __  |  |/    ,','_  `.  |          | __  |    ||  | \n");   
    printf("    |    |/   /,' _`.|      ,' / / / /   |          ,' _`.|     |  | \n");  
    printf("     |     ,-'/  /   |    ,'   | |/ / ,`.|         /  /   |  |     | \n");  
    printf("      |    | |   |_/  |   `-.  |    `'  /|  |    ||   |_/  | ||    | \n");   
    printf("       |    | |      /       `-.`.___,-' |  ||  /| |      /  | |   | \n");   
    printf("        |    | `.__,'|  |`-._    `|      |__| |/ |  `.__,'|  | |   | \n");    
    printf("         |_.-'       |__|    `-._ |              '-.|     '-.| |   | \n");   
    printf("                                 `'                            '-._| \n");    
    printf("\033[0m");

    printf("¡Bienvenidx a Aventura Pokemon!\n");
    printf("Iniciando el juego...\n");

    batallas_pokemon_t* nueva_partida = calloc(1,sizeof(batallas_pokemon_t));
    if(!nueva_partida) return FALLA;

    nueva_partida->es_simulacion = false;
    nueva_partida->gimnasios = heap_crear(comparador, destructor);
    if(!nueva_partida->gimnasios){
        printf("Error al inicializar el juego.");
        free(nueva_partida);
        return FALLA;
    }
    
    batallas_cargar(nueva_partida->tipos);
    menu_inicio(nueva_partida);


    liberar_todo(nueva_partida);

    return EXITO;
}
