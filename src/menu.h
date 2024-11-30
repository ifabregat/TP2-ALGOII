#ifndef MENU_H
#define MENU_H

#include <stddef.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "lista.h"
#include "../extra/ansi.h"

typedef struct menuItem {
	char opcion;
	char *descripcion;
	bool (*accion)(void *);
} menuItem_t;

typedef struct menu {
	Lista *opciones;
} menu_t;

/*
* Crea un nuevo menu.
* Devuelve un puntero al menu creado o NULL en caso de error.
*/
menu_t *menu_crear();

/*
* Destruye un menu.
*/
void menu_destruir(menu_t *menu, void (*destructor)(void *));

/*
* Agrega una opcion al menu.
* Devuelve true si la opcion fue agregada correctamente, false en caso contrario.
*/
bool menu_agregar_opcion(menu_t *menu, char opcion, char *descripcion,
			 bool (*accion)(void *));

/*
* Muestra el menu por pantalla.
*/
void menu_mostrar(menu_t *menu);

/*
* Ejecuta la opcion seleccionada.
* Devuelve true si la opcion fue ejecutada correctamente, false en caso contrario.
*/
bool menu_ejecutar_opcion(menu_t *menu, char opcion, void *contexto);

#endif // MENU_H