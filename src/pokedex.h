#ifndef POKEDEX_H
#define POKEDEX_H

#include <stddef.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "lista.h"
#include "csv.h"
#include "../extra/ansi.h"

typedef struct pokemon {
	char *nombre;
	int puntaje;
	char *color;
	char *movimientos;
} pokemon_t;

/*
* Crea un pokedex.
*/
Lista *pokedex_crear();

/*
* Destruye un pokedex.
* Si se recibe un destructor, se invoca con cada pokemon del pokedex.
*/
void pokedex_destruir_todo(Lista *pokedex, void (*destructor)(void *));

/*
* Agrega los pokemones del archivo a la pokedex.
* Devuelve true si se pudieron agregar los pokemones, false en caso contrario.
*/
bool pokedex_agregar_pokemon(Lista *pokedex, char *ruta);

/*
* Ordena los pokemones del pokedex por nombre.
* Devuelve true si se pudieron ordenar los pokemones, false en caso contrario.
*/
void pokedex_ordenar(Lista *pokedex, int (*comparador)(void *, void *));

/*
* Devuelve la cantidad de pokemones en el pokedex.
*/
size_t pokedex_cantidad(Lista *pokedex);

/*
* Devuelve el pokemon en la posición del pokedex.
*/
pokemon_t *pokedex_obtener_pokemon(Lista *pokedex, size_t pos);

/*
* Devuelve un pokemon aleatorio del pokedex.
*/
pokemon_t *pokedex_obtener_pokemon_random(Lista *pokedex);

/*
* Invoca la función funcion con cada pokemon del pokedex.
* La funcion se debe invocar a los pokemones ordenados por nombre de manera creciente.
* Devuelve la cantidad de pokemones que se pudieron recorrer.
*/
size_t pokedex_iterar_pokemones(Lista *pokedex,
				bool (*funcion)(pokemon_t *, void *),
				void *ctx);

#endif // POKEDEX_H