<p align="center"><img width=60% src="https://upload.wikimedia.org/wikipedia/commons/thumb/9/98/International_Pok%C3%A9mon_logo.svg/800px-International_Pok%C3%A9mon_logo.svg.png"></p>


<h1 align="center">Journey</h1>
<h2 align="center">TP2 de Algoritmos y Programación II</h2><br>


_Trabajo práctico Nº1 de Algoritmos y Programación II, Cátedra Mendez, Facultad de Ingeniería de la Universidad de Buenos Aires._


## Introducción 🚀 

El objetivo de este trabajo es simular el camino que realiza un entrenador para convertirse en maestro Pokemon. Para eso, recorrerá distintos gimnasios y obtendrás las distintas medallas de la región (8) atravesando gimnasios más sencillos al principio y aumentando la dificultad paulatinamente.

## Modo de Uso 📝

Comandos de compilación y ejecución:

> $ gcc *.c -Wall -Werror -Wconversion -std=c99 -o aventura_pokemon                
> $ ./aventura_pokemon 

Durante la elaboración del trabajo también se utilizó valgrind para la depuración de problemas de memoria utilizando el siguiente comando: 

> $ valgrind --leak-check=full --track-origins=yes --show-reachable=yes ./aventura_pokemon 


## Contruido con... ⚙

TDAs principales_
- TDA Heap --> Usado para garantizar los niveles ascendentes en los gimnasios.
- TDA Lista --> Usado para almacenar los pokemones en los conjuntos party y caja. 
                También es usado para almacenar los entrenadores en un gimnasio.
- TDA Pila --> Usado para quitar y amontonar entrenadores en la lista del gimnasio.

Los archivos principales son:

- protagonista_y_pokemon donde se declaran las funciones para operar sobre los mismos.
- gimnasio que a partir del archivo anterior y batalla se encarga de crear el gimnasio y crear la logica del juego.
- main contiene los menues y llama a las funciones para ejecutar el juego.

---

_Camila Codina_

_Agradecimientos especiales:_
_Los personajes de Attack on Titan, The Promised Neverland, JoJo's Bizarre Adventure, Frozen y Harry Potter que accedieron a ser entrenadores y líderes Pokemon en el desarrollo de este juego.)_
