#include "pila.h"
#include "lista.h"

struct pila {
	Lista *lista;
};

Pila *pila_crear()
{
	return (Pila *)lista_crear();
}

void pila_destruir(Pila *pila)
{
	if (pila == NULL)
		return;

	lista_destruir((Lista *)pila);
}

void pila_destruir_todo(Pila *pila, void (*f)(void *))
{
	if (pila == NULL)
		return;

	lista_destruir_todo((Lista *)pila, f);
}

size_t pila_cantidad(Pila *pila)
{
	if (pila == NULL)
		return 0;

	return lista_cantidad_elementos((Lista *)pila);
}

void *pila_tope(Pila *pila)
{
	if (pila == NULL)
		return NULL;

	void *elemento;

	if (!lista_obtener_elemento((Lista *)pila, 0, &elemento))
		return NULL;

	return elemento;
}

bool pila_apilar(Pila *pila, void *dato)
{
	if (pila == NULL)
		return false;

	return lista_agregar_elemento((Lista *)pila, 0, dato);
}

void *pila_desapilar(Pila *pila)
{
	if (pila == NULL)
		return NULL;

	void *elemento;

	if (!lista_quitar_elemento((Lista *)pila, 0, &elemento))
		return NULL;

	return elemento;
}

bool pila_esta_vacía(Pila *pila)
{
	if (pila == NULL)
		return true;

	return lista_cantidad_elementos((Lista *)pila) == 0;
}