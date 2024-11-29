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

void destructor_pokemones_tablero(void *pokemon_void)
{
	if (!pokemon_void)
		return;

	pokemonTablero_t *pokemon = (pokemonTablero_t *)pokemon_void;

	if (pokemon->nombre) {
		free(pokemon->nombre);
		pokemon->nombre = NULL;
	}
	if (pokemon->color) {
		free(pokemon->color);
		pokemon->color = NULL;
	}
	if (pokemon->movimientos) {
		free(pokemon->movimientos);
		pokemon->movimientos = NULL;
	}

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
	if (cantidad_pokemones == 0) {
		lista_destruir(pokemones_seleccionados);
		return NULL;
	}

	for (size_t i = 0; i < 7; i++) {
		size_t indice = (size_t)rand() % cantidad_pokemones;

		pokemonTablero_t *pokemon = NULL;
		lista_obtener_elemento(pokemones, indice, (void **)&pokemon);
		if (!pokemon) {
			lista_destruir(pokemones_seleccionados);
			return NULL;
		}

		pokemonTablero_t *pokemon_seleccionado =
			malloc(sizeof(pokemonTablero_t));
		if (!pokemon_seleccionado) {
			lista_destruir(pokemones_seleccionados);
			return NULL;
		}

		pokemon_seleccionado->x = (size_t)rand() % ANCHO_TABLERO;
		pokemon_seleccionado->y = (size_t)rand() % ALTO_TABLERO;

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
			free(pokemon_seleccionado->color);
			free(pokemon_seleccionado->nombre);
			free(pokemon_seleccionado);
			lista_destruir(pokemones_seleccionados);
			return NULL;
		}
		strcpy(pokemon_seleccionado->movimientos, pokemon->movimientos);

		pokemon_seleccionado->indiceMovimiento =
			pokemon->indiceMovimiento;

		lista_agregar_al_final(pokemones_seleccionados,
				       pokemon_seleccionado);
	}

	return pokemones_seleccionados;
}

void mostrar_resultados(jugador_t *jugador)
{
	printf("🏆 Puntaje: %d\n", jugador->puntaje);

	if (pila_cantidad(jugador->rachaMayor) >
	    pila_cantidad(jugador->rachaActual)) {
		printf("El multiplicador maximo fue de: 🔥%ld\n",
		       pila_cantidad(jugador->rachaMayor));
		printf("La racha mas larga fue de: \n");
		while (!pila_esta_vacía(jugador->rachaMayor)) {
			pokemonTablero_t *pokemon =
				pila_desapilar(jugador->rachaMayor);
			printf("Pokemon: %s%s%s, puntaje %s%d%s\n",
			       pokemon->color, pokemon->nombre,
			       ANSI_COLOR_RESET, ANSI_COLOR_YELLOW,
			       pokemon->puntaje, ANSI_COLOR_RESET);
		}
	} else {
		printf("El multiplicador maximo fue de: %ld\n",
		       pila_cantidad(jugador->rachaActual));
		printf("La racha mas larga fue de: \n");
		while (!pila_esta_vacía(jugador->rachaActual)) {
			pokemonTablero_t *pokemon =
				pila_desapilar(jugador->rachaActual);
			printf("Pokemon: %s%s%s, puntaje %s%d%s\n",
			       pokemon->color, pokemon->nombre,
			       ANSI_COLOR_RESET, ANSI_COLOR_YELLOW,
			       pokemon->puntaje, ANSI_COLOR_RESET);
		}
	}

	printf("\n");
}

int comparar_pokemon_nombre(void *elemento1, void *elemento2)
{
	if (!elemento1 || !elemento2)
		return 0;

	pokemon_t *pokemon1 = (pokemon_t *)elemento1;
	pokemon_t *pokemon2 = (pokemon_t *)elemento2;

	return strcmp(pokemon1->nombre, pokemon2->nombre);
}

bool mostrar_pokemones(pokemon_t *pokemon, void *contexto)
{
	if (!pokemon)
		return false;

	printf("        %s%s•%s %s%s%s%s (%s) -> %s%s%d puntos%s\n",
	       ANSI_COLOR_BOLD, ANSI_COLOR_WHITE, ANSI_COLOR_RESET,
	       ANSI_COLOR_BOLD, pokemon->color, pokemon->nombre,
	       ANSI_COLOR_RESET, pokemon->movimientos, ANSI_COLOR_BOLD,
	       ANSI_COLOR_WHITE, pokemon->puntaje, ANSI_COLOR_RESET);

	return true;
}

bool mostrar_pokedex(void *contexto)
{
	Lista *pokedex = pokedex_crear();
	if (!pokedex) {
		return false;
	}

	if (!pokedex_agregar_pokemon(pokedex, "datos/pokedex.csv")) {
		pokedex_destruir_todo(pokedex, destructor_pokemones);
		return false;
	}

	pokedex_ordenar(pokedex, comparar_pokemon_nombre);

	printf("\nPokemones en la pokedex:\n");

	pokedex_iterar_pokemones(pokedex, mostrar_pokemones, NULL);

	pokedex_destruir_todo(pokedex, destructor_pokemones);

	*(bool *)contexto = true;

	return true;
}

void juego(int semilla)
{
	jugador_t *jugador = jugador_crear();
	if (!jugador) {
		return;
	}

	Lista *pokedex = pokedex_crear();
	if (!pokedex) {
		jugador_destruir(jugador, NULL);
		return;
	}

	if (!pokedex_agregar_pokemon(pokedex, "datos/pokedex.csv")) {
		pokedex_destruir_todo(pokedex, destructor_pokemones);
		jugador_destruir(jugador, NULL);
		return;
	}

	Lista *pokemones = pokemones_cargar();
	if (!pokemones) {
		jugador_destruir(jugador, NULL);
		return;
	}

	Lista *pokemones_tablero = pokemones_seleccionar(pokemones);
	if (!pokemones_tablero) {
		jugador_destruir(jugador, NULL);
		lista_destruir_todo(pokemones, destructor_pokemones);
		return;
	}

	tablero_t *tablero = tablero_crear(pokemones_tablero);
	if (!tablero) {
		jugador_destruir(jugador, NULL);
		lista_destruir_todo(pokemones, destructor_pokemones);
		lista_destruir_todo(pokemones_tablero,
				    destructor_pokemones_tablero);
		return;
	}

	juego_t juego = { .jugador = jugador,
			  .tablero = tablero,
			  .pokedex = pokedex,
			  .iteraciones = 0,
			  .semilla = semilla,
			  .terminado = false };

	game_loop(logica, &juego);

	mostrar_resultados(jugador);

	pokedex_destruir_todo(pokedex, destructor_pokemones);
	lista_destruir_todo(pokemones, destructor_pokemones_tablero);
	jugador_destruir(jugador, destructor_pokemones_tablero);
	tablero_destruir(tablero, destructor_pokemones_tablero);
}

bool sin_semilla(void *contexto)
{
	int semilla = (int)time(NULL);
	srand((unsigned int)semilla);

	semilla = rand();
	srand((unsigned int)semilla);
	juego(semilla);

	*(bool *)contexto = false;

	return true;
}

bool con_semilla(void *contexto)
{
	int semilla = 0;

	printf("Ingrese la semilla: ");
	if (scanf("%d", &semilla) != 1) {
		printf("Error al leer la semilla\n");
		return false;
	}

	srand((unsigned int)semilla);

	juego(semilla);

	*(bool *)contexto = false;

	return true;
}

bool salir(void *contexto)
{
	*(bool *)contexto = false;

	return true;
}

menu_t *menu_juego()
{
	menu_t *menu = menu_crear();
	if (!menu) {
		return NULL;
	}

	menu_agregar_opcion(menu, 'P', "Pokedex", mostrar_pokedex);
	menu_agregar_opcion(menu, 'J', "Jugar", sin_semilla);
	menu_agregar_opcion(menu, 'S', "Semilla", con_semilla);
	menu_agregar_opcion(menu, 'Q', "Salir", salir);

	return menu;
}

void menu_destructor(void *dato)
{
	menuItem_t *item = (menuItem_t *)dato;
	if (!item) {
		return;
	}

	free(item->descripcion);
	free(item);
}

void mostrar_logo()
{
	printf("%s%s", ANSI_COLOR_BOLD, ANSI_COLOR_YELLOW);

	printf("                                  ,'\\\n");
	printf("    _.----.        ____         ,'  _\\   ___    ___     ____\n");
	printf("_,-'       `.     |    |  /`.   \\,-'    |   \\  /   |   |    \\  |`.\n");
	printf("\\      __    \\    '-.  | /   `.  ___    |    \\/    |   '-.   \\ |  |\n");
	printf(" \\.    \\ \\   |  __  |  |/    ,','_  `.  |          | __  |    \\|  |\n");
	printf("   \\    \\/   /,' _`.|      ,' / / / /   |          ,' _`.|     |  |\n");
	printf("    \\     ,-'/  /   \\    ,'   | \\/ / ,`.|         /  /   \\  |     |\n");
	printf("     \\    \\ |   \\_/  |   `-.  \\    `'  /|  |    ||   \\_/  | |\\    |\n");
	printf("      \\    \\ \\      /       `-.`.___,-' |  |\\  /| \\      /  | |   |\n");
	printf("       \\    \\ `.__,'|  |`-._    `|      |__| \\/ |  `.__,'|  | |   |\n");
	printf("        \\_.-'       |__|    `-._ |              '-.|     '-.| |   |\n");
	printf("                                `'                            '-._|\n");

	printf("%s", ANSI_COLOR_RESET);
}

int main()
{
	borrar_pantalla();

	menu_t *menu = menu_juego();
	if (!menu) {
		printf("Error: no se pudo crear el menú.\n");
		return 1;
	}

	mostrar_logo();
	menu_mostrar(menu);

	char opcion = 0;
	bool interfaz = true;
	bool continuar = true;

	while (interfaz) {
		if (scanf(" %c", &opcion) != 1) {
			printf("Error al leer la opción\n");
		}

		opcion = (char)toupper(opcion);

		if (menu_ejecutar_opcion(menu, opcion, &continuar) == false) {
			borrar_pantalla();
			mostrar_logo();
		}

		if (!continuar)
			interfaz = false;
		else
			menu_mostrar(menu);
	}

	menu_destruir(menu, menu_destructor);
	return 0;
}
