#ifndef POKEDEX_H
#define POKEDEX_H

#include <stddef.h>
#include <stdbool.h>

typedef struct pokemon 
{
    char *nombre;
    int puntaje;
    char *color;
    char *movimientos;
} pokemon_t;

typedef struct pokedex pokedex_t;

/*
* Crea un pokedex.
*/
pokedex_t *pokedex_crear();

/*
* Destruye un pokedex.
* Si se recibe un destructor, se invoca con cada pokemon del pokedex.
*/
void pokedex_destruir_todo(pokedex_t *pokedex, void (*destructor)(void *));

/*
* Agrega los pokemones del archivo a la pokedex.
* Devuelve true si se pudieron agregar los pokemones, false en caso contrario.
*/
bool pokedex_agregar_pokemon(pokedex_t *pokedex, char *ruta);

/*
* Ordena los pokemones del pokedex por nombre.
* Devuelve true si se pudieron ordenar los pokemones, false en caso contrario.
*/
void pokedex_ordenar(pokedex_t *pokedex, int (*comparador)(void *, void *));

/*
* Devuelve la cantidad de pokemones en el pokedex.
*/
size_t pokedex_cantidad(pokedex_t *pokedex);

/*
* Devuelve el pokemon en la posición del pokedex.
*/
pokemon_t *pokedex_obtener_pokemon(pokedex_t *pokedex, size_t pos);

/*
* Devuelve un pokemon aleatorio del pokedex.
*/
pokemon_t *pokedex_obtener_pokemon_random(pokedex_t *pokedex);

/*
* Invoca la función funcion con cada pokemon del pokedex.
* La funcion se debe invocar a los pokemones ordenados por nombre de manera creciente.
* Devuelve la cantidad de pokemones que se pudieron recorrer.
*/
size_t pokedex_iterar_pokemones(pokedex_t *pokedex, bool (*funcion)(pokemon_t *, void *), void *ctx);

#endif // POKEDEX_H