#include "menu.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "lista.h"
#include "../extra/ansi.h"

struct menu {
	Lista *opciones;
};

menu_t *menu_crear()
{
	menu_t *menu = malloc(sizeof(menu_t));

	if (!menu)
		return NULL;

	menu->opciones = lista_crear();

	if (!menu->opciones) {
		free(menu);
		return NULL;
	}

	return menu;
}

void menu_destruir(menu_t *menu, void (*destructor)(void *))
{
	if (menu->opciones)
		lista_destruir_todo(menu->opciones, destructor);
	free(menu);
}

bool menu_agregar_opcion(menu_t *menu, char opcion, char *descripcion,
			 void (*accion)())
{
	if (!menu || !descripcion) {
		return false;
	}

	menuItem_t *item = malloc(sizeof(menuItem_t));
	if (!item) {
		return false;
	}

	item->opcion = (char)toupper(opcion);
	item->accion = accion;

	size_t descripcion_len = strlen(descripcion) + 1;
	item->descripcion = malloc(descripcion_len);
	if (!item->descripcion) {
		free(item);
		return false;
	}

	strncpy(item->descripcion, descripcion, descripcion_len);

	if (!lista_agregar_al_final(menu->opciones, item)) {
		free(item->descripcion);
		free(item);
		return false;
	}

	return true;
}

void menu_mostrar(menu_t *menu)
{
	size_t cantidad = lista_cantidad_elementos(menu->opciones);

	printf(ANSI_RESET_SCREEN);

	printf("Seleccione una opcion: \n");

	for (size_t i = 0; i < cantidad; i++) {
		menuItem_t *item = NULL;

		lista_obtener_elemento(menu->opciones, i, (void **)&item);

		printf("%s  (%c)%s %s\n", ANSI_COLOR_BOLD, item->opcion, ANSI_COLOR_RESET, item->descripcion);
	}
	printf("Ingrese una opcion: ");
}

int comparar_opciones(void *a, void *b)
{
	if (!a || !b)
		return 0;

	return *(char *)a - *(char *)b;
}

bool menu_ejecutar_opcion(menu_t *menu, char opcion)
{
    if (!menu)
        return false;

    menuItem_t *item = NULL;

    do {
        opcion = (char)toupper(opcion);

        item = lista_buscar_elemento(menu->opciones, &opcion, comparar_opciones);

        if (!item) {
			menu_mostrar(menu);


			if (scanf(" %c", &opcion) != 1)
			{
				printf("Error al leer la opción\n");
				return false;
			}
        }
    } while (!item);

	printf("\n");
    item->accion();
    return true;
}
