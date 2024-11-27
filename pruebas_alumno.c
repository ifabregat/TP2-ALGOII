#include "pa2m.h"
#include "extra/ansi.h"
#include "./src/menu.h"
#include "./src/pokedex.h"
#include "./src/juego.h"
#include <stdlib.h>

void crearMenu()
{
	menu_t *menu = menu_crear();

	pa2m_afirmar(menu != NULL, "Puedo crear un menu");

	menu_destruir(menu, NULL);
}

void destructor(void *elemento)
{
	menuItem_t *opcion = (menuItem_t *)elemento;
	free(opcion->descripcion);
	free(opcion);
}

void agregarOpciones()
{
	menu_t *menu = menu_crear();

	char *descripcion = "Opcion a";
	char *descripcion2 = "Opcion b";

	pa2m_afirmar(menu_agregar_opcion(menu, 'a', descripcion, NULL),
		     "Puedo agregar una opcion al menu");
	pa2m_afirmar(menu_agregar_opcion(menu, 'b', descripcion2, NULL),
		     "Puedo agregar una segunda opcion al menu");

	menu_destruir(menu, destructor);
}

bool imprimirA()
{
	printf("Opcion a\n");

	return true;
}

bool imprimirB()
{
	printf("Opcion b\n");

	return true;
}

void elegirOpcion()
{
	menu_t *menu = menu_crear();

	char *descripcion = "Opcion a";
	char *descripcion2 = "Opcion b";

	menu_agregar_opcion(menu, 'a', descripcion, imprimirA);
	menu_agregar_opcion(menu, 'b', descripcion2, imprimirB);

	pa2m_afirmar(menu_ejecutar_opcion(menu, 'a', NULL),
		     "Puedo elegir la opcion a");
	pa2m_afirmar(menu_ejecutar_opcion(menu, 'b', NULL),
		     "Puedo elegir la opcion b");

	menu_destruir(menu, destructor);
}

void mostrarMenu()
{
	menu_t *menu = menu_crear();

	char *descripcion = "Opcion a";
	char *descripcion2 = "Opcion b";

	menu_agregar_opcion(menu, 'a', descripcion, NULL);
	menu_agregar_opcion(menu, 'b', descripcion2, NULL);

	menu_mostrar(menu);

	printf("\n");

	menu_destruir(menu, destructor);
}

void seleccionarOpcion()
{
	menu_t *menu = menu_crear();

	char *descripcion = "Opcion a";
	char *descripcion2 = "Opcion b";

	menu_agregar_opcion(menu, 'a', descripcion, imprimirA);
	menu_agregar_opcion(menu, 'b', descripcion2, imprimirB);

	menu_mostrar(menu);

	char opcion = 0;

	if (scanf("%c", &opcion) != 1)
		printf("Error al leer la opcion\n");

	menu_ejecutar_opcion(menu, opcion, NULL);

	menu_destruir(menu, destructor);
}

void crearPokedex()
{
	Lista *pokedex = pokedex_crear();

	pa2m_afirmar(pokedex != NULL, "Puedo crear un pokedex");

	pokedex_destruir_todo(pokedex, NULL);
}

void destructor_pokemones(void *elemento)
{
	pokemon_t *pokemon = (pokemon_t *)elemento;
	free(pokemon->nombre);
	free(pokemon->color);
	free(pokemon->movimientos);
	free(pokemon);
}

void agregarPokemones()
{
	Lista *pokedex = pokedex_crear();

	pa2m_afirmar(pokedex_agregar_pokemon(pokedex, "datos/pokedex.csv"),
		     "Puedo agregar pokemones al pokedex");

	pa2m_afirmar(pokedex_cantidad(pokedex) == 10,
		     "La cantidad de pokemones es la correcta");

	pokedex_destruir_todo(pokedex, destructor_pokemones);
}

void obtenerPokemonAleatorio()
{
	srand((unsigned int)time(NULL));

	Lista *pokedex = pokedex_crear();

	pokedex_agregar_pokemon(pokedex, "datos/pokedex.csv");

	pokemon_t *pokemon = pokedex_obtener_pokemon_random(pokedex);

	pa2m_afirmar(pokemon != NULL, "Puedo obtener un pokemon aleatorio");

	printf("Pokemon aleatorio: %s\n", pokemon->nombre);

	pokedex_destruir_todo(pokedex, destructor_pokemones);
}

void obtenerSietePokemonesAleatorios()
{
	srand((unsigned int)time(NULL));

	Lista *pokedex = pokedex_crear();

	pokedex_agregar_pokemon(pokedex, "datos/pokedex.csv");

	for (int i = 0; i < 7; i++) {
		pokemon_t *pokemon = pokedex_obtener_pokemon_random(pokedex);

		printf("Pokemon aleatorio obtenido: %s\n", pokemon->nombre);
	}

	pokedex_destruir_todo(pokedex, destructor_pokemones);
}

bool imprimir_pokemon(pokemon_t *pokemon, void *ctx)
{
	printf("%s%s%s%s", ANSI_COLOR_BOLD, pokemon->color, pokemon->nombre,
	       ANSI_COLOR_RESET);

	printf("%s (%s)", ANSI_COLOR_BOLD, pokemon->movimientos);

	printf(" ➡ %d puntos %s\n", pokemon->puntaje, ANSI_COLOR_RESET);

	return true;
}

bool mostrarPokemones()
{
	Lista *pokedex = pokedex_crear();

	pokedex_agregar_pokemon(pokedex, "datos/pokedex.csv");

	pokedex_iterar_pokemones(pokedex, imprimir_pokemon, NULL);

	pokedex_destruir_todo(pokedex, destructor_pokemones);

	return true;
}

void menuMostrarPokedex()
{
	menu_t *menu = menu_crear();

	char *descripcion = "Pokedex";

	menu_agregar_opcion(menu, 'P', descripcion, mostrarPokemones);

	menu_mostrar(menu);

	char opcion = 0;

	if (scanf(" %c", &opcion) != 1)
		printf("Error al leer la opcion\n");

	printf("\n");

	menu_ejecutar_opcion(menu, opcion, NULL);

	menu_destruir(menu, destructor);
}

void crearTableroConListaNula()
{
	Lista *pokemones = NULL;

	tablero_t *tablero = tablero_crear(pokemones);

	pa2m_afirmar(tablero != NULL,
		     "Puedo crear un tablero con una lista nula");

	tablero_destruir(tablero, NULL);
}

void crearTableroConListaVacia()
{
	Lista *pokemones = lista_crear();

	tablero_t *tablero = tablero_crear(pokemones);

	pa2m_afirmar(tablero != NULL,
		     "Puedo crear un tablero con una lista no nula");

	pa2m_afirmar(tablero->pokemones != NULL,
		     "El tablero tiene una lista de pokemones");

	pa2m_afirmar(lista_cantidad_elementos(tablero->pokemones) == 0,
		     "La lista de pokemones esta vacia");

	tablero_destruir(tablero, NULL);
}

void crearTableroConLista()
{
	Lista *pokemones = lista_crear();

	Lista *pokedex = pokedex_crear();

	pokedex_agregar_pokemon(pokedex, "datos/pokedex.csv");

	for (size_t i = 0; i < pokedex_cantidad(pokedex); i++) {
		pokemon_t *pokemon = pokedex_obtener_pokemon(pokedex, i);
		pokemon_t *pokemon_copia = malloc(sizeof(pokemon_t));

		pokemon_copia->nombre = malloc(strlen(pokemon->nombre) + 1);

		strcpy(pokemon_copia->nombre, pokemon->nombre);

		pokemon_copia->color = malloc(strlen(pokemon->color) + 1);

		strcpy(pokemon_copia->color, pokemon->color);

		pokemon_copia->puntaje = pokemon->puntaje;

		pokemon_copia->movimientos =
			malloc(strlen(pokemon->movimientos) + 1);

		strcpy(pokemon_copia->movimientos, pokemon->movimientos);

		lista_agregar_al_final(pokemones, pokemon_copia);
	}

	tablero_t *tablero = tablero_crear(pokemones);

	pa2m_afirmar(tablero != NULL,
		     "Puedo crear un tablero con una lista no nula");

	pa2m_afirmar(tablero->pokemones != NULL,
		     "El tablero tiene una lista de pokemones");

	pa2m_afirmar(lista_cantidad_elementos(tablero->pokemones) == 10,
		     "La lista de pokemones tiene 10 elementos");

	pokedex_destruir_todo(pokedex, destructor_pokemones);
	tablero_destruir(tablero, destructor_pokemones);
}

void imprimirTablero()
{
	tablero_t tablero = {
		.ancho = 5, .alto = 7, .celdas = NULL, .pokemones = NULL
	};

	tablero.celdas = malloc((size_t)tablero.alto * (size_t)sizeof(char *));
	if (!tablero.celdas)
		return;

	for (int i = 0; i < tablero.alto; i++) {
		tablero.celdas[i] =
			malloc((size_t)tablero.ancho * (size_t)sizeof(char));

		memset(tablero.celdas[i], ' ', (size_t)tablero.ancho);
	}

	jugador_t *jugador = jugador_crear();

	jugador->x = 2;
	jugador->y = 3;

	juego_t juego = { .jugador = jugador, .tablero = &tablero };

	tablero_imprimir(&juego);

	pa2m_afirmar(true, "Puedo imprimir el tablero");

	for (int i = 0; i < tablero.alto; i++)
		free(tablero.celdas[i]);

	free(tablero.celdas);

	jugador_destruir(jugador, destructor_pokemones_tablero);
}

void crearJugador()
{
	jugador_t *jugador = jugador_crear();

	pa2m_afirmar(jugador != NULL, "Puedo crear un jugador");

	jugador_destruir(jugador, NULL);
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

void crearJugadorConUltimoPokemonCazado()
{
	jugador_t *jugador = jugador_crear();

	Lista *pokedex = pokedex_crear();

	pokedex_agregar_pokemon(pokedex, "datos/pokedex.csv");

	pokemon_t *pokemon = pokedex_obtener_pokemon(pokedex, 0);
	pokemonTablero_t *pokemon_atrapado = malloc(sizeof(pokemonTablero_t));

	pokemon_atrapado->x = (size_t)rand() % ANCHO_TABLERO;
	pokemon_atrapado->y = (size_t)rand() % ALTO_TABLERO;

	pokemon_atrapado->nombre = malloc(strlen(pokemon->nombre) + 1);
	strcpy(pokemon_atrapado->nombre, pokemon->nombre);

	pokemon_atrapado->color = malloc(strlen(pokemon->color) + 1);
	strcpy(pokemon_atrapado->color, pokemon->color);

	pokemon_atrapado->puntaje = pokemon->puntaje;

	pokemon_atrapado->movimientos =
		malloc(strlen(pokemon->movimientos) + 1);
	strcpy(pokemon_atrapado->movimientos, pokemon->movimientos);

	pila_apilar(jugador->rachaActual, pokemon_atrapado);

	pa2m_afirmar(jugador->rachaActual != NULL,
		     "El jugador tiene pokemones atrapados");

	pa2m_afirmar(pila_cantidad(jugador->rachaActual) == 1,
		     "El jugador tiene 1 pokemon atrapado");

	destructor_pokemones_tablero(pokemon_atrapado);

	pokedex_destruir_todo(pokedex, destructor_pokemones);

	jugador_destruir(jugador, NULL);
}

void crearJugadorConMuchosPokemones()
{
	jugador_t *jugador = jugador_crear();

	Lista *pokedex = pokedex_crear();

	pokedex_agregar_pokemon(pokedex, "datos/pokedex.csv");

	for (size_t i = 0; i < pokedex_cantidad(pokedex); i++) {
		pokemon_t *pokemon = pokedex_obtener_pokemon(pokedex, i);
		pokemonTablero_t *pokemon_atrapado =
			malloc(sizeof(pokemonTablero_t));

		pokemon_atrapado->x = (size_t)rand() % ANCHO_TABLERO;
		pokemon_atrapado->y = (size_t)rand() % ALTO_TABLERO;

		pokemon_atrapado->nombre = malloc(strlen(pokemon->nombre) + 1);
		strcpy(pokemon_atrapado->nombre, pokemon->nombre);

		pokemon_atrapado->color = malloc(strlen(pokemon->color) + 1);
		strcpy(pokemon_atrapado->color, pokemon->color);

		pokemon_atrapado->puntaje = pokemon->puntaje;

		pokemon_atrapado->movimientos =
			malloc(strlen(pokemon->movimientos) + 1);
		strcpy(pokemon_atrapado->movimientos, pokemon->movimientos);

		pila_apilar(jugador->rachaActual, pokemon_atrapado);
	}

	pa2m_afirmar(jugador->rachaActual != NULL,
		     "El jugador tiene pokemones atrapados");

	pa2m_afirmar(pila_cantidad(jugador->rachaActual) == 10,
		     "El jugador tiene 10 pokemones atrapados");

	pokemonTablero_t *atrapado = pila_desapilar(jugador->rachaActual);

	pa2m_afirmar(strcmp(atrapado->nombre, "Galvantula") == 0,
		     "El pokemon atrapado es Galvantula");

	while (pila_cantidad(jugador->rachaActual) > 0) {
		pokemonTablero_t *pokemon =
			pila_desapilar(jugador->rachaActual);
		destructor_pokemones_tablero(pokemon);
	}

	destructor_pokemones_tablero(atrapado);

	pokedex_destruir_todo(pokedex, destructor_pokemones);
	jugador_destruir(jugador, destructor_pokemones_tablero);
}

void jugadorMueveArriba()
{
	tablero_t *tablero = tablero_crear(NULL);

	jugador_t *jugador = jugador_crear();

	jugador->x = 3;

	pa2m_afirmar(jugador->x == 3, "El jugador esta en la posicion x = 3");

	procesar_entrada(TECLA_ARRIBA, jugador, tablero->pokemones);

	pa2m_afirmar(jugador->x = 2,
		     "El jugador se movio para arriba, esta en x = 2");

	jugador_destruir(jugador, NULL);

	tablero_destruir(tablero, NULL);
}

void jugadorMueveAbajo()
{
	tablero_t *tablero = tablero_crear(NULL);

	jugador_t *jugador = jugador_crear();

	jugador->x = 3;

	pa2m_afirmar(jugador->x == 3, "El jugador esta en la posicion x = 3");

	procesar_entrada(TECLA_ABAJO, jugador, tablero->pokemones);

	pa2m_afirmar(jugador->x = 4,
		     "El jugador se movio para arriba, esta en x = 4");

	jugador_destruir(jugador, NULL);

	tablero_destruir(tablero, NULL);
}

void jugadorMueveDerecha()
{
	tablero_t *tablero = tablero_crear(NULL);

	jugador_t *jugador = jugador_crear();

	jugador->y = 3;

	pa2m_afirmar(jugador->y == 3, "El jugador esta en la posicion y = 3");

	procesar_entrada(TECLA_DERECHA, jugador, tablero->pokemones);

	pa2m_afirmar(jugador->y = 4,
		     "El jugador se movio para arriba, esta en y = 4");

	jugador_destruir(jugador, NULL);

	tablero_destruir(tablero, NULL);
}

void jugadorMueveIzquierda()
{
	tablero_t *tablero = tablero_crear(NULL);

	jugador_t *jugador = jugador_crear();

	jugador->y = 3;

	pa2m_afirmar(jugador->y == 3, "El jugador esta en la posicion y = 3");

	procesar_entrada(TECLA_DERECHA, jugador, tablero->pokemones);

	pa2m_afirmar(jugador->y = 2,
		     "El jugador se movio para arriba, esta en y = 2");

	jugador_destruir(jugador, NULL);

	tablero_destruir(tablero, NULL);
}

void primerPokemonCazado()
{
	jugador_t *jugador = jugador_crear();

	pokemonTablero_t pokemon = { .nombre = "Bulbasaur",
				     .color = ANSI_COLOR_BLUE,
				     .letra = 'B',
				     .puntaje = 10,
				     .movimientos = "IRJI",
				     .indiceMovimiento = 0 };

	administrar_puntaje(jugador, &pokemon);

	pa2m_afirmar(pila_tope(jugador->rachaActual) == &pokemon,
		     "El primer pokemon atrapado es Bulbasaur");

	pa2m_afirmar(jugador->puntaje == 10, "El puntaje del jugador es 10");

	pa2m_afirmar(pila_cantidad(jugador->rachaActual) == 1,
		     "La racha actual tiene 1 pokemones");

	pa2m_afirmar(jugador->multiplicador == 1,
		     "El multiplicador del jugador es 1");

	pa2m_afirmar(pila_cantidad(jugador->rachaMayor) == 0,
		     "La racha mayor tiene 0 pokemones");

	jugador_destruir(jugador, NULL);
}

void variosPokemonesCazados()
{
	jugador_t *jugador = jugador_crear();

	pokemonTablero_t pokemon = { .nombre = "Bulbasaur",
				     .color = ANSI_COLOR_BLUE,
				     .letra = 'B',
				     .puntaje = 10,
				     .movimientos = "IRJI",
				     .indiceMovimiento = 0 };

	administrar_puntaje(jugador, &pokemon);

	pa2m_afirmar(pila_tope(jugador->rachaActual) == &pokemon,
		     "El primer pokemon atrapado es Bulbasaur");

	pa2m_afirmar(jugador->puntaje == 10, "El puntaje del jugador es 10");

	pa2m_afirmar(pila_cantidad(jugador->rachaActual) == 1,
		     "La racha actual tiene 1 pokemones");

	pa2m_afirmar(jugador->multiplicador == 1,
		     "El multiplicador del jugador es 1");

	pa2m_afirmar(pila_cantidad(jugador->rachaMayor) == 0,
		     "La racha mayor tiene 0 pokemones");

	printf("\n");

	pokemonTablero_t pokemon2 = { .nombre = "Charmander",
				      .color = ANSI_COLOR_RED,
				      .letra = 'C',
				      .puntaje = 10,
				      .movimientos = "IRJI",
				      .indiceMovimiento = 0 };

	administrar_puntaje(jugador, &pokemon2);

	pa2m_afirmar(pila_tope(jugador->rachaMayor) == &pokemon,
		     "El segundo pokemon atrapado es Charmander");

	pa2m_afirmar(jugador->puntaje == 20, "El puntaje del jugador es 20");

	pa2m_afirmar(jugador->multiplicador == 1,
		     "El multiplicador del jugador es 1");

	pa2m_afirmar(pila_cantidad(jugador->rachaActual) == 1,
		     "La racha actual tiene 1 pokemones");

	pa2m_afirmar(pila_cantidad(jugador->rachaMayor) == 1,
		     "La racha mayor tiene 1 pokemones");

	printf("\n");

	administrar_puntaje(jugador, &pokemon2);

	pa2m_afirmar(pila_tope(jugador->rachaActual) == &pokemon2,
		     "El tercer pokemon atrapado es Charmander");

	pa2m_afirmar(jugador->puntaje == 40, "El puntaje del jugador es 40");

	pa2m_afirmar(jugador->multiplicador == 2,
		     "El multiplicador del jugador es 2");

	pa2m_afirmar(pila_cantidad(jugador->rachaActual) == 2,
		     "La racha actual tiene 2 pokemones");

	pa2m_afirmar(pila_cantidad(jugador->rachaMayor) == 1,
		     "La racha mayor tiene 1 pokemones");

	administrar_puntaje(jugador, &pokemon2);

	printf("\n");

	pa2m_afirmar(pila_tope(jugador->rachaActual) == &pokemon2,
		     "El cuarto pokemon atrapado es Charmander");

	pa2m_afirmar(jugador->puntaje == 70, "El puntaje del jugador es 70");

	pa2m_afirmar(jugador->multiplicador == 3,
		     "El multiplicador del jugador es 3");

	pa2m_afirmar(pila_cantidad(jugador->rachaActual) == 3,
		     "La racha actual tiene 3 pokemones");

	pa2m_afirmar(pila_cantidad(jugador->rachaMayor) == 1,
		     "La racha mayor tiene 1 pokemones");

	jugador_destruir(jugador, NULL);
}

void eliminarPokemon()
{
	jugador_t *jugador = jugador_crear();

	Lista *pokemones = lista_crear();

	Lista *atrapados = lista_crear();

	pokemonTablero_t pokemon = { .nombre = "Bulbasaur",
				     .color = ANSI_COLOR_BLUE,
				     .letra = 'B',
				     .puntaje = 10,
				     .movimientos = "IRJI",
				     .indiceMovimiento = 0 };

	lista_agregar_al_final(pokemones, &pokemon);

	pa2m_afirmar(lista_cantidad_elementos(pokemones) == 1,
		     "La lista tiene 1 pokemon");

	void *elemento = NULL;

	lista_obtener_elemento(pokemones, 0, &elemento);

	pa2m_afirmar(elemento == &pokemon, "El pokemon es Bulbasaur");

	printf("\n");

	tablero_eliminar_pokemon(pokemones, atrapados, &pokemon);

	pa2m_afirmar(lista_cantidad_elementos(pokemones) == 0,
		     "Se pudo eliminar el pokemon");

	lista_destruir(pokemones);

	lista_destruir(atrapados);

	jugador_destruir(jugador, NULL);
}

void eliminarVariosPokemones()
{
	jugador_t *jugador = jugador_crear();

	Lista *pokemones = lista_crear();

	Lista *atrapados = lista_crear();

	pokemonTablero_t pokemon = { .nombre = "Bulbasaur",
				     .color = ANSI_COLOR_BLUE,
				     .letra = 'B',
				     .puntaje = 10,
				     .movimientos = "IRJI",
				     .indiceMovimiento = 0 };

	lista_agregar_al_final(pokemones, &pokemon);

	pa2m_afirmar(lista_cantidad_elementos(pokemones) == 1,
		     "La lista tiene 1 pokemon");

	void *elemento = NULL;
	lista_obtener_elemento(pokemones, 0, &elemento);

	pa2m_afirmar(elemento == &pokemon, "El pokemon es Bulbasaur\n");

	pokemonTablero_t pokemon2 = { .nombre = "Charmander",
				      .color = ANSI_COLOR_RED,
				      .letra = 'C',
				      .puntaje = 10,
				      .movimientos = "IRJI",
				      .indiceMovimiento = 0 };

	lista_agregar_al_final(pokemones, &pokemon2);

	pa2m_afirmar(lista_cantidad_elementos(pokemones) == 2,
		     "La lista tiene 2 pokemones");

	lista_obtener_elemento(pokemones, 1, &elemento);

	pa2m_afirmar(elemento == &pokemon2,
		     "El segundo pokemon es Charmander\n");

	lista_agregar_al_final(pokemones, &pokemon2);

	pa2m_afirmar(lista_cantidad_elementos(pokemones) == 3,
		     "La lista tiene 3 pokemones");

	lista_obtener_elemento(pokemones, 2, &elemento);

	pa2m_afirmar(elemento == &pokemon2, "El tercer pokemon es Charmander");

	printf("\n");

	tablero_eliminar_pokemon(pokemones, atrapados, &pokemon2);

	pa2m_afirmar(lista_cantidad_elementos(pokemones) == 2,
		     "Se pudo eliminar el pokemon, la lista tiene 2 pokemones");

	lista_obtener_elemento(pokemones, 0, &elemento);

	pa2m_afirmar(elemento == &pokemon, "El primer pokemon es Bulbasaur");

	lista_obtener_elemento(pokemones, 1, &elemento);

	pa2m_afirmar(elemento == &pokemon2, "El segundo pokemon es Charmander");

	tablero_eliminar_pokemon(pokemones, atrapados, &pokemon);

	lista_destruir(pokemones);

	lista_destruir(atrapados);

	jugador_destruir(jugador, NULL);
}

void agregarUnPokemon()
{
	Lista *pokedex = pokedex_crear();

	pokedex_agregar_pokemon(pokedex, "datos/pokedex.csv");

	Lista *pokemones = lista_crear();

	tablero_agregar_pokemon(pokedex, pokemones);

	pa2m_afirmar(lista_cantidad_elementos(pokemones) == 1,
		     "Se pudo agregar un pokemon al tablero");

	void *elemento = NULL;
	lista_obtener_elemento(pokemones, 0, &elemento);

	printf("Nombre: %s\n", ((pokemonTablero_t *)elemento)->nombre);

	destructor_pokemones_tablero(elemento);
	lista_destruir(pokemones);
	pokedex_destruir_todo(pokedex, destructor_pokemones);
}

void agregarVariosPokemones()
{
	Lista *pokedex = pokedex_crear();

	pokedex_agregar_pokemon(pokedex, "datos/pokedex.csv");

	Lista *pokemones = lista_crear();

	tablero_agregar_pokemon(pokedex, pokemones);

	pa2m_afirmar(lista_cantidad_elementos(pokemones) == 1,
		     "Se pudo agregar un pokemon al tablero");

	void *elemento = NULL;
	lista_obtener_elemento(pokemones, 0, &elemento);

	printf("Nombre: %s\n", ((pokemonTablero_t *)elemento)->nombre);

	destructor_pokemones_tablero(elemento);

	printf("\n");

	tablero_agregar_pokemon(pokedex, pokemones);

	pa2m_afirmar(lista_cantidad_elementos(pokemones) == 2,
		     "Se pudo agregar un segundo pokemon al tablero");

	lista_obtener_elemento(pokemones, 1, &elemento);

	printf("Nombre: %s\n", ((pokemonTablero_t *)elemento)->nombre);

	destructor_pokemones_tablero(elemento);
	lista_destruir(pokemones);
	pokedex_destruir_todo(pokedex, destructor_pokemones);
}

int main()
{
	pa2m_nuevo_grupo("Pruebas de menu");
	crearMenu();
	printf("\n");
	agregarOpciones();
	printf("\n");
	elegirOpcion();
	printf("\n");
	mostrarMenu();
	printf("\n");
	seleccionarOpcion();
	pa2m_nuevo_grupo("Pruebas de pokedex");
	crearPokedex();
	printf("\n");
	agregarPokemones();
	printf("\n");
	mostrarPokemones();
	printf("\n");
	obtenerPokemonAleatorio();
	printf("\n");
	obtenerSietePokemonesAleatorios();
	printf("\n");
	menuMostrarPokedex();
	pa2m_nuevo_grupo("Pruebas de juego");
	crearTableroConListaNula();
	printf("\n");
	crearTableroConListaVacia();
	printf("\n");
	crearTableroConLista();
	printf("\n");
	imprimirTablero();
	printf("\n");
	crearJugador();
	printf("\n");
	crearJugadorConUltimoPokemonCazado();
	printf("\n");
	crearJugadorConMuchosPokemones();
	printf("\n");
	jugadorMueveArriba();
	printf("\n");
	jugadorMueveAbajo();
	printf("\n");
	jugadorMueveDerecha();
	printf("\n");
	jugadorMueveIzquierda();
	printf("\n");
	primerPokemonCazado();
	printf("\n");
	variosPokemonesCazados();
	printf("\n");
	eliminarPokemon();
	printf("\n");
	eliminarVariosPokemones();
	printf("\n");
	agregarUnPokemon();
	printf("\n");
	agregarVariosPokemones();

	return pa2m_mostrar_reporte();
}
