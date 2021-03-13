<p align="center"><img width=60% src="https://upload.wikimedia.org/wikipedia/commons/thumb/9/98/International_Pok%C3%A9mon_logo.svg/800px-International_Pok%C3%A9mon_logo.svg.png"></p>


<h1 align="center">Journey</h1>
<h2 align="center">TP2 de Algoritmos y Programación II</h2><br>


_Trabajo práctico Nº1 de Algoritmos y Programación II, Cátedra Mendez, Facultad de Ingeniería de la Universidad de Buenos Aires._


## Introducción 🚀 

El objetivo de este trabajo es simular el camino que realiza un entrenador para convertirse en maestro Pokemon. Para eso, recorrerá distintos gimnasios y obtendrás las distintas medallas de la región (8) atravesando gimnasios más sencillos al principio y aumentando la dificultad paulatinamente.

## Modo de Uso 📝

Comandos de compilación y ejecución:

> $ gcc *.c -g -Wall -Werror -O0 -Wconversion -std=c99 -o aventura_pokemon          
> $ ./aventura_pokemon 

Durante la elaboración del trabajo también se utilizó valgrind para la depuración de problemas de memoria utilizando el siguiente comando: 

> $ valgrind --leak-check=full --track-origins=yes --show-reachable=yes ./aventura_pokemon 


## Instrucciones 🦆

Una vez inicializado el programa se le presentará un menú inicial.
Para poder comenzar a jugar debe cargarse un archivo con los datos del juegador principal (de referencia, puede ver un ejemplo en la carpeta "protagonistas") y 8 gimnasios (puede encontrar los default en la carpeta gimnacios).

Hay dos formas de acceder al juego: mediante una simulación que recorre los gimnasios cargados sin pedir input del usuario o jugando!

Una vez vencidos los 8 gimnasios, finaliza el juego. 


## Contruido con... ⚙

_TDAs principales_

- TDA Heap --> Usado para garantizar los niveles ascendentes en los gimnasios.
- TDA Lista --> Usado para almacenar los pokemones en los conjuntos party y caja. 
                También es usado para almacenar los entrenadores en un gimnasio.
- TDA Pila --> Usado para quitar y amontonar entrenadores en la lista del gimnasio.

Los archivos principales son:

- batalla.c --> donde se declaran los criterios para ganar o perder ante los gimnasios.
- protagonista_y_pokemon.c --> donde se declaran las funciones para operar sobre los mismos.
- gimnasio.c --> donde a partir del archivo anterior y batalla.c se encarga de crear el gimnasio y gestionar la logica del juego.
- menu.c --> llama a los archivos con la lógica del juego y organiza los menúes.
- main.c --> llama a menu.c para ejecutar todas las funciones del juego.

---

_Camila Codina_

_Agradecimientos especiales:_
_Los personajes de Attack on Titan, The Promised Neverland, JoJo's Bizarre Adventure, Frozen y Harry Potter que accedieron a ser entrenadores y líderes Pokemon en el desarrollo de este juego.)_
