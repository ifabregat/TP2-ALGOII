#include "juego.h"

tablero_t *tablero_crear(Lista *pokemones)
{
	tablero_t *tablero = malloc(sizeof(tablero_t));
	if (!tablero)
		return NULL;

	tablero->ancho = ANCHO_TABLERO;
	tablero->alto = ALTO_TABLERO;

	tablero->celdas = malloc(sizeof(char *) * (size_t)tablero->alto);
	if (!tablero->celdas) {
		free(tablero);
		return NULL;
	}

	for (int i = 0; i < tablero->alto; i++) {
		tablero->celdas[i] =
			malloc(sizeof(char) * (size_t)tablero->ancho);
		if (!tablero->celdas[i]) {
			for (int j = 0; j < i; j++) {
				free(tablero->celdas[j]);
			}
			free(tablero->celdas);
			free(tablero);
			return NULL;
		}

		memset(tablero->celdas[i], ' ', (size_t)tablero->ancho);
	}

	tablero->pokemones = pokemones;

	return tablero;
}

void tablero_destruir(tablero_t *tablero, void (*destructor)(void *))
{
	if (!tablero)
		return;

	for (int i = 0; i < tablero->alto; i++) {
		free(tablero->celdas[i]);
	}

	free(tablero->celdas);

	lista_destruir_todo(tablero->pokemones, destructor);

	free(tablero);
}

pokemonTablero_t *posicion_pokemon(Lista *pokemones, int x, int y)
{
	if (!pokemones)
		return NULL;

	Lista_iterador *iterador = lista_iterador_crear(pokemones);
	if (!iterador)
		return NULL;

	while (lista_iterador_hay_siguiente(iterador)) {
		pokemonTablero_t *pokemon =
			lista_iterador_obtener_elemento_actual(iterador);
		if (pokemon->x == x && pokemon->y == y) {
			lista_iterador_destruir(iterador);
			return pokemon;
		}
	}

	lista_iterador_destruir(iterador);

	return NULL;
}

void tablero_imprimir(juego_t *juego, tablero_t *tablero, jugador_t *jugador)
{
	if (!tablero || !jugador)
		return;

	for (int i = -1; i <= tablero->alto; i++) {
		for (int j = -1; j <= tablero->ancho; j++) {
			if (i == -1) {
				if (j == -1)
					printf("╔");
				else if (j == tablero->ancho)
					printf("╗");
				else
					printf("═");
			} else if (i == tablero->alto) {
				if (j == -1)
					printf("╚");
				else if (j == tablero->ancho)
					printf("╝");
				else
					printf("═");
			} else {
				if (j == -1 || j == tablero->ancho) {
					printf("║");
				} else {
					if (i == jugador->y &&
					    j == jugador->x) {
						printf(ANSI_COLOR_WHITE ANSI_COLOR_BOLD
						       "@" ANSI_COLOR_RESET);
					} else {
						pokemonTablero_t *pokemon =
							posicion_pokemon(
								tablero->pokemones,
								j, i);
						if (pokemon) {
							printf("%s%c" ANSI_COLOR_RESET,
							       pokemon->color,
							       pokemon->letra);
						} else {
							printf("%c",
							       tablero->celdas
								       [i][j]);
						}
					}
				}
			}
		}
		printf("\n");
	}
}

jugador_t *jugador_crear()
{
	jugador_t *jugador = malloc(sizeof(jugador_t));
	if (!jugador)
		return NULL;

	jugador->x = 0;
	jugador->y = 0;
	jugador->puntaje = 0;
	jugador->multiplicador = 1;
	jugador->movimientos = 0;
	jugador->pokemonesAtrapados = 0;
	jugador->atrapados = NULL;

	return jugador;
}

void jugador_destruir(jugador_t *jugador, void (*destructor)(void *))
{
    if (!jugador)
        return;

    if (jugador->atrapados)
        pila_destruir_todo(jugador->atrapados, destructor);

    free(jugador);
}

int max(int a, int b)
{
    return a > b ? a : b;
}

int min(int a, int b)
{
    return a < b ? a : b;
}

void procesar_entrada(int entrada, tablero_t *tablero, jugador_t *jugador)
{
    if (entrada == TECLA_ARRIBA)
    {
        jugador->y--;
        jugador->movimientos++;
    }
    else if (entrada == TECLA_ABAJO)
    {
        jugador->y++;
        jugador->movimientos++;
    }
    else if (entrada == TECLA_IZQUIERDA)
    {
        jugador->x--;
        jugador->movimientos++;
    }
    else if (entrada == TECLA_DERECHA)
    {
        jugador->x++;
        jugador->movimientos++;
    }

    jugador->x = min(ANCHO_TABLERO - 1, max(0, jugador->x));
    jugador->y = min(ALTO_TABLERO - 1, max(0, jugador->y));
}