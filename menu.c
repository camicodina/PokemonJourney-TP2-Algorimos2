
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "gimnasio.h"
#include "menu.h"



/*
 * Agrega un gimnasio al árbol de gimnasios
*/
int gimnasio_agregar(batallas_pokemon_t* partida){
    char ruta[MAX_RUTA] = "";
    printf("Ingrese el path al archivo del gimnasio a agregar:\n");
    scanf("%s", ruta);

    if(heap_elementos(partida->gimnasios) < 8){
        gimnasio_t* gimnasio_a_agregar = gimnasio_crear(ruta);
        if(!gimnasio_a_agregar){
            return FALLA;
        }
        heap_insertar(partida->gimnasios, gimnasio_a_agregar);
    }else{
        printf("El heap está lleno! No se puede ingresar\n");
        return FALLA;
    }

    return EXITO;
}

int agregar_gimnasios_default(batallas_pokemon_t* partida){
    char ruta1[MAX_RUTA] = "gimnasios/gimnasio_1.txt";
    char ruta2[MAX_RUTA] = "gimnasios/gimnasio_2.txt";
    char ruta3[MAX_RUTA] = "gimnasios/gimnasio_3.txt";
    char ruta4[MAX_RUTA] = "gimnasios/gimnasio_4.txt";
    char ruta5[MAX_RUTA] = "gimnasios/gimnasio_5.txt";
    char ruta6[MAX_RUTA] = "gimnasios/gimnasio_6.txt";
    char ruta7[MAX_RUTA] = "gimnasios/gimnasio_7.txt";
    char ruta8[MAX_RUTA] = "gimnasios/gimnasio_8.txt";
    
    if(!heap_vacio(partida->gimnasios)){
        while (partida->gimnasios->tope > 0){
            heap_borrar_minimal(partida->gimnasios);
        }   
    }
        
    gimnasio_t* gimnasio_a_agregar_1 = gimnasio_crear(ruta1);
    if(!gimnasio_a_agregar_1) return FALLA;
    heap_insertar(partida->gimnasios, gimnasio_a_agregar_1);

    gimnasio_t* gimnasio_a_agregar_2 = gimnasio_crear(ruta2);
    if(!gimnasio_a_agregar_2) return FALLA;
    heap_insertar(partida->gimnasios, gimnasio_a_agregar_2);

    gimnasio_t* gimnasio_a_agregar_3 = gimnasio_crear(ruta3);
    if(!gimnasio_a_agregar_3) return FALLA;
    heap_insertar(partida->gimnasios, gimnasio_a_agregar_3);

    gimnasio_t* gimnasio_a_agregar_4 = gimnasio_crear(ruta4);
    if(!gimnasio_a_agregar_4) return FALLA;
    heap_insertar(partida->gimnasios, gimnasio_a_agregar_4);

    gimnasio_t* gimnasio_a_agregar_5 = gimnasio_crear(ruta5);
    if(!gimnasio_a_agregar_5) return FALLA;
    heap_insertar(partida->gimnasios, gimnasio_a_agregar_5);

    gimnasio_t* gimnasio_a_agregar_6 = gimnasio_crear(ruta6);
    if(!gimnasio_a_agregar_6) return FALLA;
    heap_insertar(partida->gimnasios, gimnasio_a_agregar_6);

    gimnasio_t* gimnasio_a_agregar_7 = gimnasio_crear(ruta7);
    if(!gimnasio_a_agregar_7) return FALLA;
    heap_insertar(partida->gimnasios, gimnasio_a_agregar_7);

    gimnasio_t* gimnasio_a_agregar_8 = gimnasio_crear(ruta8);
    if(!gimnasio_a_agregar_8) return FALLA;
    heap_insertar(partida->gimnasios, gimnasio_a_agregar_8);

    return EXITO;
}

/*
 * Agrega un gimnasio al árbol de gimnasios
*/
int protagonista_agregar(batallas_pokemon_t* partida){
    char ruta[MAX_RUTA] = "";
    printf("Ingrese el path al archivo del protagonista:\n");
    scanf("%s", ruta);

    personaje_t* protagonista_a_agregar = protagonista_crear(ruta);
    if(!protagonista_a_agregar){
        return FALLA;
    }

    if(!partida->protagonista){
        partida->protagonista = protagonista_a_agregar;
    }else{
        protagonista_destruir(partida->protagonista);
        partida->protagonista = protagonista_a_agregar;
    }
    return EXITO;
}


//==================// MENU INICIO //==================// 

void menu_inicio(batallas_pokemon_t* partida){
    getchar();
    char eleccion;
    int agregar_protagonista;
    int agregar_gimnasio;
    int eleccion_gimnasios;
    bool error = false;

    printf("Elija una accion a realizar:\n");
    printf("E - Ingresa archivo del protagonista\n");
    printf("A - Agrega un gimnasio al arbol de gimnasios\n");
    printf("I - Comienza la partida\n");
    printf("S - Simula la partida\n");
    printf("X para salir del juego\n");
    scanf("%c", &eleccion);

    switch(eleccion){
    case 'E':
        agregar_protagonista = protagonista_agregar(partida);
        if(agregar_protagonista == EXITO){
            printf("\nSe cargó correctamente el protagonista\n");
            printf("ENTER para continuar\n\n");
            getchar();
            menu_inicio(partida);
        }else{
            error = true;
        }
        break;

    case 'A':
        printf("Elija una accion a realizar:\n");
        printf("1 - Ingrese la ruta para un archivo gimnasio\n");
        printf("2 - Agregar los 8 gimnasios predeterminados\n");
        scanf("%i", &eleccion_gimnasios);
        switch(eleccion_gimnasios){
        case 1:
            agregar_gimnasio = gimnasio_agregar(partida);
            if(agregar_gimnasio == EXITO){
                printf("\nSe cargó correctamente el gimnasio\n\n");
                getchar();
                menu_inicio(partida);
            }else{
                error = true;
            } 
            break;
        case 2: 
            agregar_gimnasio = agregar_gimnasios_default(partida); 
            if(agregar_gimnasio == EXITO){
                printf("\nSe cargaron correctamente todos los gimnasios\n");
                printf("ENTER para continuar\n\n");
                getchar();
                menu_inicio(partida);
            }else{
            error = true;
            } 
            break;
        default: 
            error = true;
        };
        break;
    case 'I':
        if(!partida->protagonista || heap_elementos(partida->gimnasios) != 8){
            printf("\nNo se cumplen los requisitos minimos. Por favor cargue los 8 gimnasios y al protagonista.\n\n");
            getchar();
            menu_inicio(partida);
        }else{
            printf("Comienza la aventura... ¿Estas listo?\n");
            getchar();
            system("clear");
            menu_gimnasio(partida);
        }
        break;

    case 'S':
        partida->es_simulacion = true;
        if(!partida->protagonista || heap_elementos(partida->gimnasios) != 8){
            printf("\nNo se cumplen los requisitos minimos. Por favor cargue los 8 gimnasios y al protagonista.\n\n");
            getchar();
            menu_inicio(partida);
        }else{
            printf("¡Mira como se desencadena una batalla legendaria!\n");
            getchar();
            system("clear");
            menu_simulacion(partida);
        }
        break;
    case 'X':
        liberar_todo(partida);
        exit(1);
        break;
    default:
        error = true;
    };

    if(error){
        printf("\nSe produjo un error... ENTER para volver\n\n");
        getchar();
        menu_inicio(partida);
    };

    
}

//==================// SIMULACION //==================//

void menu_simulacion(batallas_pokemon_t* partida){
    gimnasio_t* gimnasio_actual = heap_raiz(partida->gimnasios);
    personaje_t* jugador = partida->protagonista;
    if(jugador->mis_medallas < 8){
        printf("¡Bienvenido a Gimnasio %s !\n",gimnasio_actual->nombre);
        printf("Comienza la batalla...\n");
        menu_batalla(partida,jugador,gimnasio_actual);
    }
}


//==================// MENU GIMNASIO //==================//

void menu_gimnasio(batallas_pokemon_t* partida){
    gimnasio_t* gimnasio_actual = heap_raiz(partida->gimnasios);
    personaje_t* jugador = partida->protagonista;
    printf("Encaminandose al Gimnasio %s\n",gimnasio_actual->nombre);
    printf("...\n");
    printf("¡Bienvenido a Gimnasio %s!\n",gimnasio_actual->nombre);
    
    char eleccion;
    printf("¿Que hacemos ahora?\n");
    printf("E - Ver informacion tuya\n");
    printf("G - Ver informacion del gimnasio\n");
    printf("C - Cambiar los pokemon de batalla\n");
    printf("B - Realiza la proxima batalla planificada\n");
    scanf("%c", &eleccion);

    switch(eleccion){
    case 'E':
        protagonista_mostrar(jugador);
        getchar();
        menu_gimnasio(partida);
        break;
    case 'G':
        gimnasio_mostrar(gimnasio_actual);
        getchar();
        menu_gimnasio(partida);
        break;
    case 'C':
        cambios_party_caja(jugador);
        getchar();
        menu_gimnasio(partida);
        break;
    case 'B':
        printf("VAMOS QUE VOS PODES\n");
        getchar();
        menu_batalla(partida,jugador,gimnasio_actual);
        break;
    default:
        printf("Hubo un error, intente nuevamente:\n");
        getchar();
        menu_gimnasio(partida);
    };
}



//==================// MENU BATALLA //==================//

void menu_batalla(batallas_pokemon_t* partida,personaje_t* protagonista, gimnasio_t* gimnasio){
    bool es_lider = lista_vacia(gimnasio->miembros);
    funcion_batalla batalla = partida->tipos[gimnasio->id_puntero_funcion];
    personaje_t* entrenador_oponente;
    if(!es_lider){
        entrenador_oponente = lista_tope(gimnasio->miembros);
        printf("¡Comienza tu combate contra el entrenador %s!\n",entrenador_oponente->nombre);
    }else{
        entrenador_oponente = gimnasio->lider;
        printf("¡Comienza tu combate contra el lider de gimnasio %s!\n",entrenador_oponente->nombre);
    }
    
    lista_iterador_t* iterador_protagonista = lista_iterador_crear(partida->protagonista->party);
    lista_iterador_t* iterador_oponente = lista_iterador_crear(entrenador_oponente->party);
 
    
    while(lista_iterador_tiene_siguiente(iterador_protagonista) && lista_iterador_tiene_siguiente(iterador_oponente)){
        pokemon_t* pokemon_actual_protagonista = lista_iterador_elemento_actual(iterador_protagonista);
        pokemon_t* pokemon_actual_oponente = lista_iterador_elemento_actual(iterador_oponente);
        mostrar_combate_informacion(pokemon_actual_protagonista, pokemon_actual_oponente);

        if(batalla(pokemon_actual_protagonista,pokemon_actual_oponente)== GANO_PRIMERO){
            printf("GANASTE!\n");
            recompensa_caracteristicas(pokemon_actual_protagonista);
            lista_iterador_avanzar(iterador_oponente);
        }else{
            printf("Ha caido un grande...\n");
            lista_iterador_avanzar(iterador_protagonista);
        }
    }
    
    if(!lista_iterador_tiene_siguiente(iterador_oponente) && lista_iterador_tiene_siguiente(iterador_protagonista)){
        printf("VENCISTE AL ENTRENADOR!\n");
        lista_iterador_destruir(iterador_protagonista);
        lista_iterador_destruir(iterador_oponente);
        if(es_lider){
            protagonista->mis_medallas++;
            menu_victoria(partida,protagonista,gimnasio);
        }
        protagonista_destruir(entrenador_oponente);
        lista_desapilar(gimnasio->miembros);
        printf("Y en el siguiente round...\n");
        menu_batalla(partida,protagonista,gimnasio);
    }else{
        menu_derrota(partida,protagonista,gimnasio);
    }
    
}



//==================// MENU VICTORIA //==================//

void menu_victoria_modificado(batallas_pokemon_t* partida, personaje_t* protagonista, gimnasio_t* gimnasio){
    printf("Sos un capo, master!\n");

    char eleccion;
    printf("¿Como festejamos la victoria?\n");
    printf("C - Cambiar Pokemon de batalla\n");
    printf("N - Proximo gimnasio\n");
    scanf("%c", &eleccion);

    switch(eleccion){
    case 'C':
        cambios_party_caja(protagonista);
        getchar();
        menu_victoria(partida,protagonista,gimnasio);
        break;
    case 'N':
        heap_borrar_minimal(partida->gimnasios);
        if(heap_vacio(partida->gimnasios) && protagonista->mis_medallas == 8){
             printf("No hay mas gimnasios... ¡HA COMPLETADO EL JUEGO!\n");
             printf("¡Ahora si que eres un verdadero maestro pokemon!\n");
             printf("Esperamos que el juego te haya servido y quieras ser uno de verdad :D\n");
             getchar();
             menu_inicio(partida);
        }else{
            printf("Adelante!\n");
            getchar();
            system("clear");
            menu_gimnasio(partida);
        }
        break;

    default:
        printf("Hubo un error, intente nuevamente:\n");
        getchar();
        menu_victoria_modificado(partida,protagonista,gimnasio);
    };
}



void menu_victoria(batallas_pokemon_t* partida, personaje_t* protagonista, gimnasio_t* gimnasio){
    printf("Sos un capo, master!\n");

    if(partida->es_simulacion){
        heap_borrar_minimal(partida->gimnasios);
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
    printf("N - Proximo gimnasio\n");
    scanf("%c", &eleccion);

    switch(eleccion){
    case 'T':
        pedir_prestado(protagonista, gimnasio->lider);
        getchar();
        menu_victoria_modificado(partida,protagonista,gimnasio);
        break;
    case 'C':
        cambios_party_caja(protagonista);
        getchar();
        menu_victoria(partida,protagonista,gimnasio);
        break;
    case 'N':
        heap_borrar_minimal(partida->gimnasios);
        if(heap_vacio(partida->gimnasios) && protagonista->mis_medallas == 8){
             printf("No hay mas gimnasios... ¡HA COMPLETADO EL JUEGO!\n");
             printf("¡Ahora si que eres un verdadero maestro pokemon!\n");
             printf("Esperamos que el juego te haya servido y quieras ser uno de verdad :D\n");
             liberar_todo(partida);
             exit(1);
        }else{
            printf("Adelante!\n");
            getchar();
            system("clear");
            menu_gimnasio(partida);
        }
        break;

    default:
        printf("Hubo un error, intente nuevamente:\n");
        getchar();
        menu_victoria(partida,protagonista,gimnasio);
    };
}


//==================// MENU DERROTA //==================//

void menu_derrota(batallas_pokemon_t* partida, personaje_t* protagonista, gimnasio_t* gimnasio){
    printf("Embeses la vida no es como keremos...\n");
    
    if(partida->es_simulacion){
        printf("Has perdido ante el gran gimnasio de %s \n", gimnasio->lider->nombre);
        printf("Terminando el juego... \n");
        liberar_todo(partida);
        exit(1);
    }
    
    printf("¡%s!¡No te rindas!\n", protagonista->nombre);
    char eleccion;
    printf("¿Y ahora que hacemos?\n");
    printf("C - Cambiar Pokemon de batalla\n");
    printf("R - Reintentar batalla \n");
    printf("F - Finalizar\n");
    scanf("%c", &eleccion);

    switch(eleccion){
    case 'C':
        cambios_party_caja(protagonista);
        getchar();
        menu_derrota(partida,protagonista,gimnasio);
        break;
    case 'R':
        printf("Vamos por la revancha!\n");
        getchar();
        system("clear");
        menu_gimnasio(partida);
        break;
    case 'F':
        printf("Has perdido ante el gimnasio %s \n", gimnasio->nombre);
        printf("A la proxima sera... ENTER para volver al menu principal \n");
        getchar();
        menu_inicio(partida);
        break;
    default:
        printf("Hubo un error, intente nuevamente:\n");
        getchar();
        menu_derrota(partida,protagonista,gimnasio);
    };

}
