#include "menu.h"

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

int comparar_opciones(void *a, void *b)
{
	if (!a || !b)
		return 0;

	char opcion_a = (char)toupper(*(char *)a);
	char opcion_b = (char)toupper(*(char *)b);

	return opcion_a - opcion_b;
}

bool menu_agregar_opcion(menu_t *menu, char opcion, char *descripcion,
			 bool (*accion)(void *, void *))
{
	if (!menu || !descripcion) {
		return false;
	}

	opcion = (char)toupper(opcion);

	if (lista_buscar_elemento(menu->opciones, &opcion, comparar_opciones)) {
		printf("La opción '%c' ya existe en el menú.\n", opcion);
		return false;
	}

	menuItem_t *item = malloc(sizeof(menuItem_t));
	if (!item) {
		return false;
	}

	item->opcion = opcion;
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

	for (size_t i = 0; i < cantidad; i++) {
		menuItem_t *item = NULL;

		lista_obtener_elemento(menu->opciones, i, (void **)&item);

		printf("\n%s                            (%c)%s %s",
		       ANSI_COLOR_BOLD, item->opcion, ANSI_COLOR_RESET,
		       item->descripcion);
	}
	printf("\nSeleccione una opcion: ");
}

bool menu_ejecutar_opcion(menu_t *menu, char opcion, void *contexto,
			  void *contexto2)
{
	if (!menu || !menu->opciones)
		return false;

	opcion = (char)toupper(opcion);

	menuItem_t *item = lista_buscar_elemento(menu->opciones, &opcion,
						 comparar_opciones);

	if (!item) {
		printf("Opción inválida. Intente de nuevo.\n");
		return false;
	}

	if (item->accion) {
		return item->accion(contexto, contexto2);
	}

	return false;
}
