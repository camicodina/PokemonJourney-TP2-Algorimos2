const char* ARCHIVO_ARRECIFE;
const char* ARCHIVO_ACUARIO;
const int MAX_POKEMON = 100;
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "batallas.h"


//==================// FUNCIONES DE (...) //==================// 



//==================// FUNCION PRINCIPAL //==================// 

int main (int argc, char **argv){
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
//     ARCHIVO_ARRECIFE = argv[1];
//     ARCHIVO_ACUARIO = argv[2];
//     arrecife_t* arrecife_de_pokemones = crear_arrecife(ARCHIVO_ARRECIFE);
//     if(!arrecife_de_pokemones){
//         printf("No se pudo generar el arrecife de pokemones. Saliendo del programa...\n");
//         return -1;
//     }
//     acuario_t* acuario_de_pokemones = crear_acuario();
//     if(!acuario_de_pokemones){
//         printf("No se pudo generar el arrecife de pokemones. Saliendo del programa...\n");
//         liberar_arrecife(arrecife_de_pokemones);
//         return -1;
//     }
//     introduccion(arrecife_de_pokemones, acuario_de_pokemones, ARCHIVO_ACUARIO);
//     liberar_acuario(acuario_de_pokemones);
//     liberar_arrecife(arrecife_de_pokemones);
    return 0;
}