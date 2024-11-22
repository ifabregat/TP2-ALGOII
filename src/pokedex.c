#include "pokedex.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "lista.h"
#include "csv.h"
#include "../extra/ansi.h"


struct pokedex
{
    Lista *pokemones;
};

pokedex_t *pokedex_crear()
{
    pokedex_t *pokedex = malloc(sizeof(pokedex_t));

    if (!pokedex)
        return NULL;

    pokedex->pokemones = lista_crear();

    if (!pokedex->pokemones)
    {
        free(pokedex);
        return NULL;
    }

    return pokedex;
}

void pokedex_destruir_todo(pokedex_t *pokedex, void (*destructor)(void *))
{
    lista_destruir_todo(pokedex->pokemones, destructor);

    free(pokedex);
}

char* obtener_color_ansi(const char* color)
{
    if (strcmp(color, "NEGRO") == 0)
        return ANSI_COLOR_BLACK;
    else if (strcmp(color, "ROJO") == 0)
        return ANSI_COLOR_RED;
    else if (strcmp(color, "VERDE") == 0)
        return ANSI_COLOR_GREEN;
    else if (strcmp(color, "AMARILLO") == 0)
        return ANSI_COLOR_YELLOW;
    else if (strcmp(color, "AZUL") == 0)
        return ANSI_COLOR_BLUE;
    else if (strcmp(color, "MAGENTA") == 0)
        return ANSI_COLOR_MAGENTA;
    else if (strcmp(color, "CIANO") == 0)
        return ANSI_COLOR_CYAN;
    else if (strcmp(color, "BLANCO") == 0)
        return ANSI_COLOR_WHITE;
    else
        return ANSI_COLOR_RESET;
}

pokemon_t *pokemon_crear(char *nombre, int puntaje, char *color, char *movimientos)
{
    pokemon_t *pokemon = malloc(sizeof(pokemon_t));

    if (!pokemon)
        return NULL;

    pokemon->nombre = malloc(strlen(nombre) + 1);

    if (!pokemon->nombre)
    {
        free(pokemon);
        return NULL;
    }

    pokemon->color = malloc(strlen(color) + 1);

    if (!pokemon->color)
    {
        free(pokemon->nombre);
        free(pokemon);
        return NULL;
    }

    pokemon->movimientos = malloc(strlen(movimientos) + 1);

    if (!pokemon->movimientos)
    {
        free(pokemon->nombre);
        free(pokemon->color);
        free(pokemon);
        return NULL;
    }

    strcpy(pokemon->nombre, nombre);
    strcpy(pokemon->color, color);
    strcpy(pokemon->movimientos, movimientos);

    pokemon->puntaje = puntaje;

    return pokemon;
}

bool parsear_string(const char *campo, void *ctx)
{
	if (campo == NULL || ctx == NULL) {
		return false;
	}

	char **nombre = (char **)ctx;

	if (*nombre != NULL) {
		free(*nombre);
		*nombre = NULL;
	}

	size_t longitud = strlen(campo);

	if (longitud == 0) {
		return false;
	}

	*nombre = malloc(longitud + 1);

	if (*nombre == NULL) {
		return false;
	}

	strcpy(*nombre, campo);

	return true;
}

bool parsear_entero(const char *campo, void *ctx)
{
	int *numero = ctx;

	if (campo == NULL || ctx == NULL) {
		return false;
	}

	return sscanf(campo, "%d", numero) == 1;
}

bool pokedex_agregar_pokemon(pokedex_t *pokedex, char *ruta)
{
    struct archivo_csv *archivo = abrir_archivo_csv(ruta, ',');

    if (!archivo)
        return false;

    bool (*parseadores[])(const char *, void *) = {parsear_string, parsear_entero, parsear_string, parsear_string};

    char *nombre = malloc(100);

    if (!nombre)
    {
        cerrar_archivo_csv(archivo);
        return false;
    }

    int puntaje;

    char *color = malloc(100);

    if (!color)
    {
        free(nombre);
        cerrar_archivo_csv(archivo);
        return false;
    }

    char *movimientos = malloc(100);

    if (!movimientos)
    {
        free(nombre);
        free(color);
        cerrar_archivo_csv(archivo);
        return false;
    }

    void *ctx[4] = {&nombre, &puntaje, &color, &movimientos};

    while (leer_linea_csv(archivo, 4, parseadores, ctx) == 4)
    {
        char *color_ansi = obtener_color_ansi(color);

        pokemon_t *pokemon = pokemon_crear(nombre, puntaje, color_ansi, movimientos);

        if (!pokemon)
        {
            free(nombre);
            free(color);
            free(movimientos);
            cerrar_archivo_csv(archivo);
            return false;
        }

        lista_agregar_al_final(pokedex->pokemones, pokemon);
    }

    free(nombre);
    free(color);
    free(movimientos);

    cerrar_archivo_csv(archivo);

    return true;
}

int comparador_nombre_ascendente(void *a, void *b) {
    pokemon_t *pokemon_a = (pokemon_t *)a;
    pokemon_t *pokemon_b = (pokemon_t *)b;

    return strcmp(pokemon_a->nombre, pokemon_b->nombre);
}

void pokedex_ordenar(pokedex_t *pokedex, int (*comparador)(void *, void *))
{
    if (pokedex->pokemones == NULL || comparador == NULL) {
        return;
    }

    size_t cantidad = lista_cantidad_elementos(pokedex->pokemones);
    if (cantidad < 2) {
        return;
    }

    for (size_t i = 0; i < cantidad - 1; i++) {
        for (size_t j = 0; j < cantidad - i - 1; j++) {
            void *elemento_j, *elemento_j1;
            if (!lista_obtener_elemento(pokedex->pokemones, j, &elemento_j) || 
                !lista_obtener_elemento(pokedex->pokemones, j + 1, &elemento_j1)) {
                return;
            }

            if (comparador(elemento_j, elemento_j1) > 0) {
                void *temp = elemento_j;
                lista_quitar_elemento(pokedex->pokemones, j, NULL);
                lista_agregar_elemento(pokedex->pokemones, j + 1, temp);
            }
        }
    }

    return;
}

size_t pokedex_cantidad(pokedex_t *pokedex)
{
    return lista_cantidad_elementos(pokedex->pokemones);
}

pokemon_t *pokedex_obtener_pokemon_random(pokedex_t *pokedex)
{
    size_t cantidad = pokedex_cantidad(pokedex);

    if (cantidad == 0)
        return NULL;

    size_t indice = (size_t)rand() % cantidad;

    void *elemento = NULL;
    
    lista_obtener_elemento(pokedex->pokemones, indice, &elemento);

    return elemento;
}

size_t pokedex_iterar_pokemones(pokedex_t *pokedex, bool (*funcion)(pokemon_t *, void *), void *ctx)
{
    pokedex_ordenar(pokedex, comparador_nombre_ascendente);

    return lista_iterar_elementos(pokedex->pokemones, (bool (*)(void *, void *))funcion, ctx);
}
