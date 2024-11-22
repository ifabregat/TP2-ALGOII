#include "pa2m.h"
#include "extra/ansi.h"
#include "./src/menu.h"
#include "./src/pokedex.h"
#include <stdlib.h>
#include <time.h>

void destructor(void *elemento)
{
	menuItem_t *opcion = (menuItem_t *)elemento;
	free(opcion->descripcion);
	free(opcion);
}

void imprimirA()
{
	printf("Opcion a\n");
}

void imprimirB()
{
	printf("Opcion b\n");
}

void crearMenu()
{
	menu_t *menu = menu_crear();

	pa2m_afirmar(menu != NULL, "Puedo crear un menu");

	menu_destruir(menu, NULL);
}

void agregarOpciones()
{
	menu_t *menu = menu_crear();

	char *descripcion = "Opcion a";
	char *descripcion2 = "Opcion b";

	pa2m_afirmar(menu_agregar_opcion(menu, 'a', descripcion, NULL), "Puedo agregar una opcion al menu");
	pa2m_afirmar(menu_agregar_opcion(menu, 'b', descripcion2, NULL), "Puedo agregar una segunda opcion al menu");


	menu_destruir(menu, destructor);
}

void elegirOpcion()
{
	menu_t *menu = menu_crear();

	char *descripcion = "Opcion a";
	char *descripcion2 = "Opcion b";

	menu_agregar_opcion(menu, 'a', descripcion, imprimirA);
	menu_agregar_opcion(menu, 'b', descripcion2, imprimirB);

	pa2m_afirmar(menu_ejecutar_opcion(menu, 'a'), "Puedo elegir la opcion a");
	pa2m_afirmar(menu_ejecutar_opcion(menu, 'b'), "Puedo elegir la opcion b");

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
	{
		printf("Error al leer la opcion\n");
	}

	menu_ejecutar_opcion(menu, opcion);

	menu_destruir(menu, destructor);
}

void crearPokedex()
{
	pokedex_t *pokedex = pokedex_crear();

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
	pokedex_t *pokedex = pokedex_crear();

	pa2m_afirmar(pokedex_agregar_pokemon(pokedex, "datos/pokedex.csv"), "Puedo agregar pokemones al pokedex");

	size_t cantidad = pokedex_cantidad(pokedex);

	printf("Cantidad de pokemones: %ld\n", cantidad);

	pa2m_afirmar(pokedex_cantidad(pokedex) == 10, "La cantidad de pokemones es la correcta");

	pokedex_destruir_todo(pokedex, destructor_pokemones);
}

void obtenerPokemonAleatorio()
{
	pokedex_t *pokedex = pokedex_crear();

	pokedex_agregar_pokemon(pokedex, "datos/pokedex.csv");

	pokemon_t *pokemon = pokedex_obtener_pokemon_random(pokedex);

	printf("Pokemon aleatorio: %s\n", pokemon->nombre);

	pa2m_afirmar(pokemon != NULL, "Puedo obtener un pokemon aleatorio");

	pokedex_destruir_todo(pokedex, destructor_pokemones);
}

void obtenerSietePokemonesAleatorios()
{
	srand((unsigned int)time(NULL));

	pokedex_t *pokedex = pokedex_crear();

	pokedex_agregar_pokemon(pokedex, "datos/pokedex.csv");

	for (int i = 0; i < 7; i++)
	{
		pokemon_t *pokemon = pokedex_obtener_pokemon_random(pokedex);

		printf("Pokemon aleatorio: %s\n", pokemon->nombre);
	}

	pokedex_destruir_todo(pokedex, destructor_pokemones);
}

bool imprimir_pokemon(pokemon_t *pokemon, void *ctx)
{
	printf("%s%s%s%s", ANSI_COLOR_BOLD, pokemon->color, pokemon->nombre, ANSI_COLOR_RESET);

	printf("%s (%s)", ANSI_COLOR_BOLD, pokemon->movimientos);

	printf(" ➡ %d puntos %s\n", pokemon->puntaje, ANSI_COLOR_RESET);

	return true;
}

void mostrarPokemones()
{
	pokedex_t *pokedex = pokedex_crear();

	pokedex_agregar_pokemon(pokedex, "datos/pokedex.csv");

	pokedex_iterar_pokemones(pokedex, imprimir_pokemon, NULL);

	pokedex_destruir_todo(pokedex, destructor_pokemones);
}

void menuMostrarPokedex()
{
	pokedex_t *pokedex = pokedex_crear();

	pokedex_agregar_pokemon(pokedex, "datos/pokedex.csv");

	menu_t *menu = menu_crear();

	menu_agregar_opcion(menu, 'P', "Mostrar pokedex", (void (*)(void))mostrarPokemones);
	
	menu_mostrar(menu);

	char opcion = 0;

	if (scanf("%c", &opcion) != 1)
	{
		printf("Error al leer la opcion\n");
	}

	menu_ejecutar_opcion(menu, opcion);

	menu_destruir(menu, destructor);
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
	menuMostrarPokedex();

	return pa2m_mostrar_reporte();
}
