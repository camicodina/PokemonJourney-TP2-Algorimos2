#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "gimnasio.h"

#define MAX_RUTA 99

// -------------------------- COSAS PARA EL HEAP -------------------------- //

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

//==================// SIMULACION //==================//

void menu_simulacion(batallas_pokemon_t* partida){
    gimnasio_t* gimnasio_ahora = heap_raiz(partida->gimnasios);
    printf("¡Bienvenido a Gimnasio %s !\n",gimnasio_ahora->nombre);
    
    printf("Comienza la batalla...\n");
    menu_batalla(partida,partida->protagonista,gimnasio_ahora);
}

//==================// MENU VICTORIA //==================//


void menu_victoria(batallas_pokemon_t* partida, personaje_t* protagonista, gimnasio_t* gimnasio){
    printf("Sos un capo, master!\n");
    protagonista->mis_medallas++;

    if(partida->es_simulacion){
        heap_quitar_raiz(partida->gimnasios);
        if(heap_vacio(partida->gimnasios) && protagonista->mis_medallas == 8){
             printf("No hay mas gimnasios... ¡TERMINA EL JUEGO!\n");
             menu_inicio(partida);
        }else{
            printf("Adelante!\n");
            menu_simulacion(partida);
        }
    }

    char eleccion;
    printf("¿Como festejamos la victoria?\n");
    printf("T - Pedir prestado Pokemon de lider\n");
    printf("C - Cambiar Pokemon de batalla\n");
    printf("N - Proximo gimnasio");
    scanf("%c", &eleccion);

    switch(eleccion){
    case 'T':
        pedir_prestado(protagonista, gimnasio->lider);
        break;
    case 'C':
        cambios_party_caja(protagonista);
        break;
    case 'N':
        heap_quitar_raiz(partida->gimnasios);
        if(heap_vacio(partida->gimnasios) && protagonista->mis_medallas == 8){
             printf("No hay mas gimnasios... ¡HA COMPLETADO EL JUEGO!\n");
             printf("¡Ahora si que eres un verdadero maestro pokemon!\n");
             printf("Esperamos que el juego te haya servido y quieras ser uno de verdad :D\n");
             menu_inicio(partida);
        }else{
            printf("Adelante!\n");
            menu_gimnasio(partida);
        }
        break;

    default:
        printf("Hubo un error, intente nuevamente:\n");
        menu_victoria(partida,protagonista,gimnasio);
    };
}

//==================// MENU DERROTA //==================//

void menu_derrota(batallas_pokemon_t* partida, personaje_t* protagonista, gimnasio_t* gimnasio){
    printf("Embeses la vida no es como keremos...\n");
    
    if(partida->es_simulacion){
        printf("Has perdido ante el gimnasio %s \n", gimnasio->nombre);
        menu_inicio(partida);
    }
    
    printf("No te rindas! A la cancha por la revancha\n");
    char eleccion;
    printf("¿Y ahora que hacemos?\n");
    printf("C - Cambiar Pokemon de batalla\n");
    printf("R - Reintentar batalla \n");
    printf("F - Finalizar");
    scanf("%c", &eleccion);

    switch(eleccion){
    case 'C':
        cambios_party_caja(protagonista);
        break;
    case 'R':
        menu_batalla(partida,protagonista,gimnasio);
        break;
    case 'F':
        printf("Embeses la vida no es como keremos...\n");
        printf("Has perdido ante el gimnasio %s \n", gimnasio->nombre);
        printf("A la proxima sera... \n");
        menu_inicio(partida);
        break;

    default:
        printf("Hubo un error, intente nuevamente:\n");
        menu_victoria(partida,protagonista,gimnasio);
    };
}

//==================// MENU BATALLA //==================//

void menu_batalla(batallas_pokemon_t* partida,personaje_t* protagonista, gimnasio_t* gimnasio){
    bool lider = lista_vacia(gimnasio->miembros);
    funcion_batalla batalla = partida->tipos[gimnasio->id_puntero_funcion];
    personaje_t* entrenador_oponente;
    if(!lider){
        entrenador_oponente = lista_tope(entrenador_oponente->party);
    }else{
        entrenador_oponente = gimnasio->lider;
    }
    
    lista_iterador_t* iterador_protagonista = lista_iterador_crear(partida->protagonista->party);
    lista_iterador_t* iterador_oponente = lista_iterador_crear(entrenador_oponente->party);
 
    
    while(lista_iterador_tiene_siguiente(iterador_protagonista) && lista_iterador_tiene_siguiente(iterador_oponente)){
        pokemon_t* pokemon_actual_protagonista = lista_iterador_elemento_actual(partida->protagonista->party);
        pokemon_t* pokemon_actual_oponente = lista_iterador_elemento_actual(entrenador_oponente->party);
        mostrar_combate_informacion(pokemon_actual_protagonista, pokemon_actual_oponente);

        if(batalla(pokemon_actual_protagonista,pokemon_actual_oponente)== GANO_PRIMERO){
            printf("GANASTE!\n");
            recompensa_caracteristicas(pokemon_actual_protagonista);
            lista_iterador_avanzar(pokemon_actual_oponente);
        }else{
            printf("Ha caido un grande...\n");
            lista_iterador_avanzar(pokemon_actual_protagonista);
        }
    }
    
    if(!lista_iterador_tiene_siguiente(iterador_oponente) && lista_iterador_tiene_siguiente(iterador_protagonista)){
        printf("VENCISTE AL ENTRENADOR!\n");
        lista_iterador_destruir(iterador_protagonista);
        lista_iterador_destruir(iterador_oponente);
        if(lider){
            menu_victoria(partida,protagonista,gimnasio);
        }
        protagonista_destruir(entrenador_oponente);
        lista_desapilar(gimnasio->miembros);
        printf("Y en el siguiente round...\n");
        menu_batalla(partida,protagonista,gimnasio);
    }

    menu_derrota(partida,protagonista,gimnasio);
}


//==================// MENU GIMNASIO //==================//

void menu_gimnasio(batallas_pokemon_t* partida){
    gimnasio_t* gimnasio_ahora = heap_raiz(partida->gimnasios);
    printf("Encaminandose al Gimnasio %s\n",gimnasio_ahora->nombre);
    printf("...\n");
    printf("¡Bienvenido a Gimnasio %s !\n",gimnasio_ahora->nombre);
    
    char eleccion;
    printf("¿Que hacemos ahora?\n");
    printf("E - Ver informacion tuya\n");
    printf("G - Ver informacion del gimnasio\n");
    printf("C - Cambiar los pokemon de batalla");
    printf("B - Realiza la proxima batalla planificada\n");
    printf("X para salir del menu\n");
    scanf("%c", &eleccion);

    switch(eleccion){
    case 'E':
        protagonista_mostrar(partida->protagonista);
        break;
    case 'G':
        gimnasio_mostrar(gimnasio_ahora);
        break;
    case 'C':
        cambios_party_caja(partida->protagonista);
        break;
    case 'B':
        printf("VAMOS QUE VOS PODES\n");
        menu_batalla(partida,partida->protagonista,gimnasio_ahora);
        break;
    case 'X':
        break;
    default:
        printf("Hubo un error, intente nuevamente:\n");
        menu_gimnasio(partida);
    };

}

//==================// MENU INICIO //==================// 

void menu_inicio(batallas_pokemon_t* partida){
    char eleccion;

    printf("Elija una accion a realizar\n");
    printf("E - Ingresa archivo del entrenador principal customizado\n");
    printf("A - Agrega un gimnasio al arbol de gimnasios customizado\n");
    printf("I - Comienza la partida");
    printf("S - Simula la partida\n");
    printf("X para salir del juego\n");
    scanf("%c", &eleccion);

    switch(eleccion){
    case 'E':
        char ruta[MAX_RUTA];
        printf("Ingrese el path al archivo gimnasio\n");
        scanf("%s", &ruta);
        if(!partida->protagonista){
            personaje_t* protagonista = protagonista_crear(ruta);
            if(protagonista){
                printf("Se cargó correctamente el protagonista\n");
                partida->protagonista = protagonista;
        }else{
            protagonista_destruir(partida->protagonista);
            partida->protagonista == NULL;
            personaje_t* protagonista = protagonista_crear(ruta);
            if(protagonista){
                printf("Se cargó correctamente el protagonista\n");
                partida->protagonista = protagonista;
            }
        }
        break;

    case 'A':
        char ruta[MAX_RUTA];
        printf("Ingrese el path al archivo gimnasio\n");
        scanf("%s", &ruta);
        if(heap_elementos(partida->gimnasios)<=8){
            gimnasios_agregar(partida->gimnasios,ruta);
        }else{
            printf("El heap está lleno! No se puede ingresar\n");
        }
        break;
    case 'I':
        if(!partida->protagonista){
            printf("Se usa protagonista default, ¡Muchacho!\n");
            personaje_t* protagonista = protagonista_crear("protagonista.txt");
            if(protagonista){
                partida->protagonista = protagonista;
        }
        if(heap_elementos(partida->gimnasios) < 8){
            printf("Se usan gimnasios default\n");
            while (partida->gimnasios->tope > 0){
                heap_borrar_minimal(partida->gimnasios);
            }       
            todos_gimnasios_agregar(partida->gimnasios);
        }

        if((partida->protagonista) && (heap_elementos(partida->gimnasios) == 8)){
            printf("Comienza la aventura... ¿Estas listo?\n");
            menu_gimnasio(partida);
        }

        break;

    case 'S':
        partida->es_simulacion = true;
        if(!partida->protagonista){
                printf("Se usa protagonista default, ¡Muchacho!\n");
                personaje_t* protagonista = protagonista_crear("protagonista.txt");
                if(protagonista){
                    partida->protagonista = protagonista;
            }
        if(heap_elementos(partida->gimnasios) < 8){
            printf("Se usan gimnasios default\n");
            while (partida->gimnasios->tope > 0){
                heap_borrar_minimal(partida->gimnasios);
            }       
            todos_gimnasios_agregar(partida->gimnasios);
        }

        if((partida->protagonista) && (heap_elementos(partida->gimnasios) == 8)){
            printf("Comienza la aventura... ¿Estas listo?\n");
            menu_simulacion(partida);
        }
        break;
    case 'X':
        break;
    default:
        printf("Hubo un error, intente nuevamente:\n");
        menu_inicio(partida);
    };

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

