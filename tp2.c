#include "src/menu.h"
#include "src/pokedex.h"
#include "src/juego.h"
#include "extra/engine.h"
#include "extra/ansi.h"

void destructor_pokemones(void *elemento)
{
	if (!elemento)
		return;

	pokemon_t *pokemon = (pokemon_t *)elemento;
	free(pokemon->nombre);
	free(pokemon->color);
	free(pokemon->movimientos);
	free(pokemon);
}

void destructor_pokemones_tablero(void *elemento)
{
	if (!elemento)
		return;

	pokemonTablero_t *pokemon = elemento;

	free(pokemon->nombre);
	free(pokemon->color);
	free(pokemon->movimientos);

	free(pokemon);
}

Lista *pokemones_cargar()
{
	Lista *pokemones = lista_crear();
	if (!pokemones) {
		return NULL;
	}

	Lista *pokedex = pokedex_crear();
	if (!pokedex) {
		lista_destruir(pokemones);
		return NULL;
	}

	if (!pokedex_agregar_pokemon(pokedex, "datos/pokedex.csv")) {
		pokedex_destruir_todo(pokedex, destructor_pokemones);
		lista_destruir(pokemones);
		return NULL;
	}

	for (size_t i = 0; i < pokedex_cantidad(pokedex); i++) {
		pokemon_t *pokemon = pokedex_obtener_pokemon(pokedex, i);

		pokemonTablero_t *pokemon_lista =
			malloc(sizeof(pokemonTablero_t));
		if (!pokemon_lista) {
			pokedex_destruir_todo(pokedex, destructor_pokemones);
			lista_destruir(pokemones);
			return NULL;
		}

		pokemon_lista->x = (size_t)rand() % ANCHO_TABLERO;
		pokemon_lista->y = (size_t)rand() % ALTO_TABLERO;

		pokemon_lista->nombre = malloc(strlen(pokemon->nombre) + 1);
		if (!pokemon_lista->nombre) {
			free(pokemon_lista);
			pokedex_destruir_todo(pokedex, destructor_pokemones);
			lista_destruir(pokemones);
			return NULL;
		}
		strcpy(pokemon_lista->nombre, pokemon->nombre);

		pokemon_lista->letra = pokemon->nombre[0];
		pokemon_lista->puntaje = pokemon->puntaje;

		pokemon_lista->color = malloc(strlen(pokemon->color) + 1);
		if (!pokemon_lista->color) {
			free(pokemon_lista->nombre);
			free(pokemon_lista);
			pokedex_destruir_todo(pokedex, destructor_pokemones);
			lista_destruir(pokemones);
			return NULL;
		}
		strcpy(pokemon_lista->color, pokemon->color);

		pokemon_lista->movimientos =
			malloc(strlen(pokemon->movimientos) + 1);
		if (!pokemon_lista->movimientos) {
			free(pokemon_lista->nombre);
			free(pokemon_lista->color);
			free(pokemon_lista);
			pokedex_destruir_todo(pokedex, destructor_pokemones);
			lista_destruir(pokemones);
			return NULL;
		}
		strcpy(pokemon_lista->movimientos, pokemon->movimientos);

		pokemon_lista->indiceMovimiento = 0;

		lista_agregar_al_final(pokemones, pokemon_lista);
	}

	pokedex_destruir_todo(pokedex, destructor_pokemones);

	return pokemones;
}

Lista *pokemones_seleccionar(Lista *pokemones)
{
	Lista *pokemones_seleccionados = lista_crear();
	if (!pokemones_seleccionados) {
		return NULL;
	}

	size_t cantidad_pokemones = lista_cantidad_elementos(pokemones);
	if (cantidad_pokemones < 7) {
		lista_destruir(pokemones_seleccionados);
		return NULL; // No hay suficientes Pokémon para seleccionar 7
	}

	bool seleccionados[cantidad_pokemones];
	memset(seleccionados, 0, sizeof(seleccionados));

	size_t seleccionados_count = 0;
	while (seleccionados_count < 7) {
		size_t indice = (size_t)rand() % cantidad_pokemones;
		if (seleccionados[indice]) {
			continue; // Ya seleccionado, intenta con otro índice
		}

		seleccionados[indice] = true;
		seleccionados_count++;

		pokemonTablero_t *pokemon = NULL;
		lista_obtener_elemento(pokemones, indice, (void **)&pokemon);
		if (!pokemon) {
			lista_destruir(pokemones_seleccionados);
			return NULL;
		}

		// Crear una copia del Pokémon
		pokemonTablero_t *pokemon_seleccionado =
			malloc(sizeof(pokemonTablero_t));
		if (!pokemon_seleccionado) {
			lista_destruir(pokemones_seleccionados);
			return NULL;
		}

		pokemon_seleccionado->x = pokemon->x;
		pokemon_seleccionado->y = pokemon->y;

		pokemon_seleccionado->nombre =
			malloc(strlen(pokemon->nombre) + 1);
		if (!pokemon_seleccionado->nombre) {
			free(pokemon_seleccionado);
			lista_destruir(pokemones_seleccionados);
			return NULL;
		}
		strcpy(pokemon_seleccionado->nombre, pokemon->nombre);

		pokemon_seleccionado->letra = pokemon->letra;
		pokemon_seleccionado->puntaje = pokemon->puntaje;

		pokemon_seleccionado->color =
			malloc(strlen(pokemon->color) + 1);
		if (!pokemon_seleccionado->color) {
			free(pokemon_seleccionado->nombre);
			free(pokemon_seleccionado);
			lista_destruir(pokemones_seleccionados);
			return NULL;
		}
		strcpy(pokemon_seleccionado->color, pokemon->color);

		pokemon_seleccionado->movimientos =
			malloc(strlen(pokemon->movimientos) + 1);
		if (!pokemon_seleccionado->movimientos) {
			free(pokemon_seleccionado->nombre);
			free(pokemon_seleccionado->color);
			free(pokemon_seleccionado);
			lista_destruir(pokemones_seleccionados);
			return NULL;
		}
		strcpy(pokemon_seleccionado->movimientos, pokemon->movimientos);

        pokemon_seleccionado->indiceMovimiento = pokemon->indiceMovimiento;

		lista_agregar_al_final(pokemones_seleccionados,
				       pokemon_seleccionado);
	}

	return pokemones_seleccionados;
}

int main()
{
	srand((unsigned int)time(NULL));

	jugador_t *jugador = jugador_crear();
	if (!jugador) {
		return 1;
	}

	Lista *pokemones = pokemones_cargar();
	if (!pokemones) {
		jugador_destruir(jugador, NULL);
		return 1;
	}

	Lista *pokemones_tablero = pokemones_seleccionar(pokemones);
	if (!pokemones_tablero) {
		jugador_destruir(jugador, NULL);
		lista_destruir_todo(pokemones, destructor_pokemones);
		return 1;
	}

	tablero_t *tablero = tablero_crear(pokemones_tablero);
	if (!tablero) {
		jugador_destruir(jugador, NULL);
		lista_destruir_todo(pokemones, destructor_pokemones);
		lista_destruir_todo(pokemones_tablero,
				    destructor_pokemones_tablero);
		return 1;
	}

	juego_t juego = { .jugador = jugador,
			  .tablero = tablero,
			  .pokemones = pokemones,
			  .iteraciones = 0,
			  .semilla = 0,
			  .terminado = false };

	game_loop(logica, &juego);

	lista_destruir_todo(pokemones, destructor_pokemones_tablero);

	jugador_destruir(jugador, NULL);

	tablero_destruir(tablero, destructor_pokemones_tablero);

	return 0;
}