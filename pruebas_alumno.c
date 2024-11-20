#include "pa2m.h"
#include "extra/ansi.h"
#include "./src/menu.h"
#include "./src/pokedex.h"
#include <stdlib.h>

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


	return pa2m_mostrar_reporte();
}
