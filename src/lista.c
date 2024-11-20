#include "lista.h"

typedef struct Nodo {
	void *dato;
	struct Nodo *siguiente;
} Nodo_t;

struct lista {
	Nodo_t *primero;
	Nodo_t *ultimo;
	size_t cantidad;
};

struct lista_iterador {
	Nodo_t *nodo_actual;
};

Nodo_t *lista_obtener_nodo(Lista *lista, size_t posicion)
{
	if (lista == NULL || posicion >= lista->cantidad)
		return NULL;

	Nodo_t *actual = lista->primero;

	for (size_t i = 0; i < posicion; i++) {
		if (actual == NULL)
			return NULL;
		actual = actual->siguiente;
	}

	return actual;
}

Lista *lista_crear()
{
	Lista *lista = calloc(1, sizeof(Lista));

	if (lista == NULL)
		return NULL;

	return lista;
}

void lista_destruir(Lista *lista)
{
	lista_destruir_todo(lista, NULL);
}

void lista_destruir_todo(Lista *lista, void (*destructor)(void *))
{
	if (lista == NULL)
		return;

	Nodo_t *actual = lista->primero;
	Nodo_t *siguiente = NULL;

	while (actual != NULL) {
		siguiente = actual->siguiente;

		if (destructor != NULL) {
			destructor(actual->dato);
		}

		free(actual);
		actual = siguiente;
	}

	free(lista);
}

size_t lista_cantidad_elementos(Lista *lista)
{
	if (lista == NULL)
		return 0;

	return lista->cantidad;
}

bool lista_agregar_elemento(Lista *lista, size_t posicion, void *cosa)
{
	if (lista == NULL || posicion > lista->cantidad)
		return false;

	Nodo_t *nuevo_nodo = malloc(sizeof(Nodo_t));

	if (nuevo_nodo == NULL)
		return false;

	nuevo_nodo->dato = cosa;
	nuevo_nodo->siguiente = NULL;

	if (posicion == 0) {
		nuevo_nodo->siguiente = lista->primero;
		lista->primero = nuevo_nodo;

		if (lista->ultimo == NULL)
			lista->ultimo = nuevo_nodo;

	} else if (posicion == lista->cantidad) {
		lista->ultimo->siguiente = nuevo_nodo;
		lista->ultimo = nuevo_nodo;

	} else {
		Nodo_t *anterior = lista_obtener_nodo(lista, posicion - 1);
		if (anterior == NULL) {
			free(nuevo_nodo);
			return false;
		}

		nuevo_nodo->siguiente = anterior->siguiente;
		anterior->siguiente = nuevo_nodo;
	}

	lista->cantidad++;
	return true;
}

bool lista_agregar_al_final(Lista *lista, void *cosa)
{
	if (lista == NULL)
		return false;

	return lista_agregar_elemento(lista, lista->cantidad, cosa);
}

bool lista_quitar_elemento(Lista *lista, size_t posicion,
			   void **elemento_quitado)
{
	if (lista == NULL || posicion >= lista->cantidad)
		return false;

	Nodo_t *nodo_eliminado = NULL;
	Nodo_t *anterior = NULL;

	if (posicion == 0) {
		nodo_eliminado = lista->primero;
		lista->primero = nodo_eliminado->siguiente;
	} else {
		anterior = lista_obtener_nodo(lista, posicion - 1);

		if (anterior == NULL)
			return false;

		nodo_eliminado = anterior->siguiente;
		anterior->siguiente = nodo_eliminado->siguiente;
	}

	if (elemento_quitado != NULL)
		*elemento_quitado = nodo_eliminado->dato;

	free(nodo_eliminado);
	lista->cantidad--;

	if (lista->cantidad == 0) {
		lista->primero = NULL;
		lista->ultimo = NULL;
	} else if (nodo_eliminado == lista->ultimo) {
		lista->ultimo = anterior;
	}

	return true;
}

void *lista_buscar_elemento(Lista *lista, void *buscado,
			    int (*comparador)(void *, void *))
{
	if (lista == NULL || comparador == NULL)
		return NULL;

	Nodo_t *actual = lista->primero;

	while (actual != NULL) {
		if (comparador(actual->dato, buscado) == 0)
			return actual->dato;

		actual = actual->siguiente;
	}

	return NULL;
}

bool lista_obtener_elemento(Lista *lista, size_t posicion,
			    void **elemento_encontrado)
{
	Nodo_t *nodo = lista_obtener_nodo(lista, posicion);

	if (nodo == NULL)
		return false;

	if (elemento_encontrado != NULL)
		*elemento_encontrado = nodo->dato;

	return true;
}

size_t lista_iterar_elementos(Lista *lista, bool (*f)(void *, void *),
			      void *ctx)
{
	if (lista == NULL || f == NULL)
		return 0;

	size_t elementos_iterados = 0;
	Nodo_t *actual = lista->primero;

	while (actual != NULL) {
		if (f(actual->dato, ctx) == false)
			return elementos_iterados + 1;

		actual = actual->siguiente;
		elementos_iterados++;
	}

	return elementos_iterados;
}

Lista_iterador *lista_iterador_crear(Lista *lista)
{
	if (lista == NULL)
		return NULL;

	Lista_iterador *iterador = malloc(sizeof(Lista_iterador));

	if (iterador == NULL)
		return NULL;

	iterador->nodo_actual = lista->primero;

	return iterador;
}

bool lista_iterador_hay_siguiente(Lista_iterador *iterador)
{
	if (iterador == NULL || iterador->nodo_actual == NULL)
		return false;

	return iterador->nodo_actual != NULL;
}

void lista_iterador_avanzar(Lista_iterador *iterador)
{
	if (iterador == NULL || iterador->nodo_actual == NULL)
		return;

	iterador->nodo_actual = iterador->nodo_actual->siguiente;
}

void *lista_iterador_obtener_elemento_actual(Lista_iterador *iterador)
{
	if (iterador == NULL || iterador->nodo_actual == NULL)
		return NULL;

	return iterador->nodo_actual->dato;
}

void lista_iterador_destruir(Lista_iterador *iterador)
{
	free(iterador);
}