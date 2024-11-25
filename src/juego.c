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

	tablero->atrapados = lista_crear();

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

	lista_destruir_todo(tablero->atrapados, destructor);

	free(tablero);
}

pokemonTablero_t *encontrar_pokemon_en_posicion(Lista *pokemones, int x, int y)
{
	Lista_iterador *iterador = lista_iterador_crear(pokemones);
	if (!iterador)
		return NULL;

	pokemonTablero_t *pokemon = NULL;
	while (lista_iterador_hay_siguiente(iterador)) {
		pokemon = lista_iterador_obtener_elemento_actual(iterador);
		if (pokemon->x == x && pokemon->y == y) {
			lista_iterador_destruir(iterador);
			return pokemon;
		}
		lista_iterador_avanzar(iterador);
	}

	lista_iterador_destruir(iterador);
	return NULL;
}

void tablero_imprimir(juego_t *juego)
{
	printf("⏰%s%s%d%s  ", ANSI_COLOR_BOLD, ANSI_COLOR_WHITE,
	       20 - juego->iteraciones / 5, ANSI_COLOR_RESET);
	printf("👣%s%s%d%s  ", ANSI_COLOR_BOLD, ANSI_COLOR_WHITE,
	       juego->jugador->movimientos, ANSI_COLOR_RESET);
	printf("🐍%s%s%d%s  ", ANSI_COLOR_BOLD, ANSI_COLOR_WHITE,
	       juego->jugador->pokemonesAtrapados, ANSI_COLOR_RESET);
	printf("🏆%s%s%d%s ", ANSI_COLOR_BOLD, ANSI_COLOR_YELLOW,
	       juego->jugador->puntaje, ANSI_COLOR_RESET);
	printf("%s%s(x%d)%s", ANSI_COLOR_BOLD, ANSI_COLOR_WHITE,
	       juego->jugador->multiplicador, ANSI_COLOR_RESET);

	printf("\n");

	for (int i = -1; i <= juego->tablero->alto; i++) {
		for (int j = -1; j <= juego->tablero->ancho; j++) {
			if (i == -1) {
				if (j == -1)
					printf("╔");
				else if (j == juego->tablero->ancho)
					printf("╗");
				else
					printf("═");
			} else if (i == juego->tablero->alto) {
				if (j == -1)
					printf("╚");
				else if (j == juego->tablero->ancho)
					printf("╝");
				else
					printf("═");
			} else {
				if (j == -1 || j == juego->tablero->ancho) {
					printf("║");
				} else {
					if (i == juego->jugador->y &&
					    j == juego->jugador->x) {
						printf(ANSI_COLOR_WHITE ANSI_COLOR_BOLD
						       "@" ANSI_COLOR_RESET);
					} else {
						pokemonTablero_t *pokemon =
							encontrar_pokemon_en_posicion(
								juego->tablero
									->pokemones,
								j, i);
						if (pokemon) {
							printf("%s%c" ANSI_COLOR_RESET,
							       pokemon->color,
							       pokemon->letra);
						} else {
							printf("%c",
							       juego->tablero->celdas
								       [i][j]);
						}
					}
				}
			}
		}
		printf("\n");
	}

	printf("%s%s🌱 %d%s", ANSI_COLOR_BOLD, ANSI_COLOR_WHITE, juego->semilla,
	       ANSI_COLOR_RESET);
}

void tablero_eliminar_pokemon(Lista *pokemones, Lista *atrapados, pokemonTablero_t *pokemon)
{
	Lista_iterador *iterador = lista_iterador_crear(pokemones);
	if (!iterador)
		return;

	size_t indice = 0;

	while (lista_iterador_hay_siguiente(iterador)) {
		pokemonTablero_t *pokemon_actual =
			lista_iterador_obtener_elemento_actual(iterador);
		pokemonTablero_t *pokemon_atrapado = NULL;

		if (pokemon_actual == pokemon) {
			lista_agregar_al_final(atrapados,
					       pokemon_actual);
			lista_quitar_elemento(pokemones, indice,
					      (void **)&pokemon_atrapado);
			break;
		}

		lista_iterador_avanzar(iterador);
		indice++;
	}

	lista_iterador_destruir(iterador);
}

void tablero_agregar_pokemon(Lista *pokedex, Lista *pokemones)
{
	size_t cantidad_pokemones = lista_cantidad_elementos(pokedex);
	if (cantidad_pokemones == 0) {
		return;
	}

	size_t indice = (size_t)rand() % cantidad_pokemones;

	pokemonTablero_t *pokemon = NULL;
	lista_obtener_elemento(pokemones, indice, (void **)&pokemon);
	if (!pokemon) {
		return;
	}

	pokemonTablero_t *pokemon_seleccionado =
		malloc(sizeof(pokemonTablero_t));
	if (!pokemon_seleccionado) {
		return;
	}

	pokemon_seleccionado->x = (size_t)rand() % ANCHO_TABLERO;
	pokemon_seleccionado->y = (size_t)rand() % ALTO_TABLERO;

	pokemon_seleccionado->nombre = malloc(strlen(pokemon->nombre) + 1);
	if (!pokemon_seleccionado->nombre) {
		return;
	}
	strcpy(pokemon_seleccionado->nombre, pokemon->nombre);

	pokemon_seleccionado->letra = pokemon->letra;
	pokemon_seleccionado->puntaje = pokemon->puntaje;

	pokemon_seleccionado->color = malloc(strlen(pokemon->color) + 1);
	if (!pokemon_seleccionado->color) {
		return;
	}
	strcpy(pokemon_seleccionado->color, pokemon->color);

	pokemon_seleccionado->movimientos =
		malloc(strlen(pokemon->movimientos) + 1);
	if (!pokemon_seleccionado->movimientos) {
		return;
	}
	strcpy(pokemon_seleccionado->movimientos, pokemon->movimientos);

	pokemon_seleccionado->indiceMovimiento = pokemon->indiceMovimiento;

	lista_agregar_al_final(pokemones, pokemon_seleccionado);
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
	jugador->rachaActual = pila_crear();
	jugador->rachaMayor = pila_crear();

	return jugador;
}

void jugador_destruir(jugador_t *jugador, void (*destructor)(void *))
{
	if (!jugador)
		return;

	if (jugador->rachaActual)
		pila_destruir_todo(jugador->rachaActual, destructor);

	if (jugador->rachaMayor)
		pila_destruir_todo(jugador->rachaMayor, destructor);

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

void procesar_movimiento_pokemones(Lista *pokemones, int entrada)
{
	Lista_iterador *iterador = lista_iterador_crear(pokemones);
	if (!iterador)
		return;

	while (lista_iterador_hay_siguiente(iterador)) {
		pokemonTablero_t *pokemon =
			lista_iterador_obtener_elemento_actual(iterador);
		if (!pokemon) {
			lista_iterador_avanzar(iterador);
			continue;
		}

		if (pokemon->movimientos[pokemon->indiceMovimiento] == '\0') {
			pokemon->indiceMovimiento = 0;
		}
		char movimiento =
			pokemon->movimientos[pokemon->indiceMovimiento];

		switch (movimiento) {
		case 'N':
			pokemon->y = max(0, pokemon->y - 1);
			break;

		case 'S':
			pokemon->y = min(ALTO_TABLERO - 1, pokemon->y + 1);
			break;

		case 'E':
			pokemon->x = min(ANCHO_TABLERO - 1, pokemon->x + 1);
			break;

		case 'O':
			pokemon->x = max(0, pokemon->x - 1);
			break;

		case 'J':
			switch (entrada) {
			case TECLA_ARRIBA:
				pokemon->y = max(0, pokemon->y - 1);
				break;
			case TECLA_ABAJO:
				pokemon->y =
					min(ALTO_TABLERO - 1, pokemon->y + 1);
				break;
			case TECLA_IZQUIERDA:
				pokemon->x = max(0, pokemon->x - 1);
				break;
			case TECLA_DERECHA:
				pokemon->x =
					min(ANCHO_TABLERO - 1, pokemon->x + 1);
				break;
			}
			break;

		case 'I':
			switch (entrada) {
			case TECLA_ARRIBA:
				pokemon->y =
					min(ALTO_TABLERO - 1, pokemon->y + 1);
				break;
			case TECLA_ABAJO:
				pokemon->y = max(0, pokemon->y - 1);
				break;
			case TECLA_IZQUIERDA:
				pokemon->x =
					min(ANCHO_TABLERO - 1, pokemon->x + 1);
				break;
			case TECLA_DERECHA:
				pokemon->x = max(0, pokemon->x - 1);
				break;
			}
			break;

		case 'R':
			switch (rand() % 4) {
			case 0:
				pokemon->y = max(0, pokemon->y - 1);
				break;
			case 1:
				pokemon->y =
					min(ALTO_TABLERO - 1, pokemon->y + 1);
				break;
			case 2:
				pokemon->x =
					min(ANCHO_TABLERO - 1, pokemon->x + 1);
				break;
			case 3:
				pokemon->x = max(0, pokemon->x - 1);
				break;
			}
			break;

		default:
			break;
		}

		pokemon->indiceMovimiento++;

		lista_iterador_avanzar(iterador);
	}

	lista_iterador_destruir(iterador);
}

void procesar_entrada(int entrada, jugador_t *jugador, Lista *pokemones)
{
	if (entrada == TECLA_ARRIBA) {
		jugador->y--;
		// procesar_movimiento_pokemones(pokemones, entrada);
		jugador->movimientos++;
	} else if (entrada == TECLA_ABAJO) {
		jugador->y++;
		// procesar_movimiento_pokemones(pokemones, entrada);
		jugador->movimientos++;
	} else if (entrada == TECLA_IZQUIERDA) {
		jugador->x--;
		// procesar_movimiento_pokemones(pokemones, entrada);
		jugador->movimientos++;
	} else if (entrada == TECLA_DERECHA) {
		jugador->x++;
		// procesar_movimiento_pokemones(pokemones, entrada);
		jugador->movimientos++;
	}

	jugador->x = min(ANCHO_TABLERO - 1, max(0, jugador->x));
	jugador->y = min(ALTO_TABLERO - 1, max(0, jugador->y));
}

size_t comparar_rachas(size_t rachaActual, size_t rachaMayor)
{
	return rachaActual > rachaMayor ? rachaActual : rachaMayor;
}

void administrar_puntaje(jugador_t *jugador, pokemonTablero_t *pokemon)
{
	if (pila_esta_vacía(jugador->rachaActual)) {
		pila_apilar(jugador->rachaActual, pokemon);
		jugador->puntaje += pokemon->puntaje;
		return;
	}

	pokemonTablero_t *ultimo_pokemon = pila_tope(jugador->rachaActual);

	if (ultimo_pokemon->letra == pokemon->letra ||
	    strcmp(ultimo_pokemon->color, pokemon->color) == 0) {
		pila_apilar(jugador->rachaActual, pokemon);
		jugador->multiplicador++;
	} else {
		size_t comparacion =
			comparar_rachas(pila_cantidad(jugador->rachaActual),
					pila_cantidad(jugador->rachaMayor));

		if (comparacion == pila_cantidad(jugador->rachaActual)) {
			pila_destruir_todo(jugador->rachaMayor,
					   destructor_pokemones_tablero);
			jugador->rachaMayor = pila_crear();

			while (!pila_esta_vacía(jugador->rachaActual)) {
				pokemonTablero_t *pokemon =
					pila_desapilar(jugador->rachaActual);
				pila_apilar(jugador->rachaMayor, pokemon);
			}
		}

		pila_apilar(jugador->rachaActual, pokemon);

		jugador->multiplicador = 1;
	}

	jugador->puntaje += pokemon->puntaje * jugador->multiplicador;
}

int logica(int entrada, void *datos)
{
	juego_t *juego = datos;

	borrar_pantalla();

	procesar_entrada(entrada, juego->jugador, juego->tablero->pokemones);

	pokemonTablero_t *atrapado = encontrar_pokemon_en_posicion(
		juego->tablero->pokemones, juego->jugador->x,
		juego->jugador->y);
	if (atrapado) {
		administrar_puntaje(juego->jugador, atrapado);
		tablero_eliminar_pokemon(juego->tablero->pokemones, juego->tablero->atrapados, atrapado);
		// tablero_agregar_pokemon(juego->pokemones, juego->tablero->pokemones);
		juego->jugador->pokemonesAtrapados++;
	}

	if (20 - juego->iteraciones / 5 == 0 || entrada == 'q' ||
	    entrada == 'Q')
		juego->terminado = true;

	juego->iteraciones++;

	tablero_imprimir(juego);

	esconder_cursor();

	printf("\n");

	return juego->terminado;
}