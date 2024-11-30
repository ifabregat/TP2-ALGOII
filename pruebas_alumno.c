#include "pa2m.h"
#include "extra/ansi.h"
#include "./src/menu.h"
#include "./src/pokedex.h"
#include "./src/juego.h"
#include <stdlib.h>

int comparar_cadenas(void *elemento1, void *elemento2)
{
	char *cadena1 = (char *)elemento1;
	char *cadena2 = (char *)elemento2;

	if (cadena1 == NULL && cadena2 == NULL) {
		return 0;
	} else if (cadena1 == NULL) {
		return -1;
	} else if (cadena2 == NULL) {
		return 1;
	}

	return strcmp(cadena1, cadena2);
}

void crearPila()
{
	Pila *pila = pila_crear();
	pa2m_afirmar(pila != NULL, "Puedo crear una pila");
	pila_destruir(pila);
}

void agregarALaPila()
{
	Pila *pila = pila_crear();
	int valor = 5;
	pa2m_afirmar(pila_apilar(pila, &valor),
		     "Puedo agregar un valor a la pila");
	pa2m_afirmar(pila_cantidad(pila) == 1,
		     "La cantidad de elementos en la pila es 1");
	pila_destruir(pila);
}

void agregarUnElementoALaPilaDevuelveElTope()
{
	Pila *pila = pila_crear();
	int *valor = malloc(sizeof(int));
	*valor = 5;
	pila_apilar(pila, valor);
	printf("%d\n", *(int *)pila_tope(pila));
	pa2m_afirmar(pila_tope(pila) != NULL, "El tope de la pila no es NULL");
	pa2m_afirmar(pila_tope(pila) == valor,
		     "El tope de la pila es el valor que agregué");
	pila_destruir_todo(pila, free);
}

void agregarDosElementosALaPilaDevuelveElTopeCorrecto()
{
	Pila *pila = pila_crear();
	int *valor1 = malloc(sizeof(int));
	int *valor2 = malloc(sizeof(int));
	*valor1 = 5;
	*valor2 = 10;
	pila_apilar(pila, valor1);
	pila_apilar(pila, valor2);
	printf("%d\n", *(int *)pila_tope(pila));
	pa2m_afirmar(pila_tope(pila) != NULL, "El tope de la pila no es NULL");
	pa2m_afirmar(pila_tope(pila) == valor2,
		     "El tope de la pila es el último valor que agregué");
	pa2m_afirmar(pila_cantidad(pila) == 2,
		     "La cantidad de elementos en la pila es 2");
	pila_destruir_todo(pila, free);
}

void agregarUnElementoALaPilaNulo()
{
	Pila *pila = pila_crear();
	pa2m_afirmar(pila_apilar(pila, NULL),
		     "No puedo agregar un valor nulo a la pila");
	pa2m_afirmar(pila_cantidad(pila) == 1,
		     "La cantidad de elementos en la pila es 0");
	pa2m_afirmar(pila_tope(pila) == NULL, "El tope de la pila es NULL");
	pila_destruir_todo(pila, free);
}

void desapilarUnElementoDeLaPila()
{
	Pila *pila = pila_crear();
	int valor = 5;
	pila_apilar(pila, &valor);
	printf("Apilado: %d\n", *(int *)pila_tope(pila));
	pa2m_afirmar(*(int *)pila_tope(pila) == 5,
		     "El tope de la pila es el valor que agregué");
	int *desapilado = pila_desapilar(pila);
	printf("Desapilado: %d\n", *desapilado);
	pa2m_afirmar(*desapilado == 5, "Puedo desapilar un valor de la pila");
	pa2m_afirmar(pila_cantidad(pila) == 0,
		     "La cantidad de elementos en la pila es 0");
	pila_destruir(pila);
}

void desapilarUnElementoDeLaPilaDeDos()
{
	Pila *pila = pila_crear();
	int valor1 = 10;
	int valor2 = 20;
	pila_apilar(pila, &valor1);
	pila_apilar(pila, &valor2);
	pa2m_afirmar(*(int *)pila_tope(pila) == 20,
		     "El tope de la pila es el último valor que agregué");
	pa2m_afirmar(pila_cantidad(pila) == 2,
		     "La cantidad de elementos en la pila es 2");
	int *desapilado = pila_desapilar(pila);
	printf("Desapilado: %d\n", *desapilado);
	pa2m_afirmar(*desapilado == 20, "Puedo desapilar un valor de la pila");
	pa2m_afirmar(*(int *)pila_tope(pila) == 10,
		     "El tope de la pila es el valor que quedó");
	pa2m_afirmar(pila_cantidad(pila) == 1,
		     "La cantidad de elementos en la pila es 1");
	pila_destruir(pila);
}

void pilaVacia()
{
	Pila *pila = pila_crear();
	pa2m_afirmar(pila_esta_vacía(pila), "La pila está vacía");
	pila_destruir(pila);
}

void pilaVaciaConElementos()
{
	Pila *pila = pila_crear();
	int valor = 5;
	pila_apilar(pila, &valor);
	pa2m_afirmar(!pila_esta_vacía(pila), "La pila no está vacía");
	pila_destruir(pila);
}

void crearLista()
{
	Lista *lista = lista_crear();
	pa2m_afirmar(lista != NULL, "Puedo crear una lista");
	lista_destruir(lista);
}

void agregarALaLista()
{
	Lista *lista = lista_crear();
	int valor = 5;
	pa2m_afirmar(lista_agregar_al_final(lista, &valor),
		     "Puedo agregar un valor a la lista");
	pa2m_afirmar(lista_cantidad_elementos(lista) == 1,
		     "La cantidad de elementos en la lista es 1");
	lista_destruir(lista);
}

void agregarDosElementoALaListaEnPosicion()
{
	Lista *lista = lista_crear();
	int valor = 5;
	int valor2 = 10;
	pa2m_afirmar(lista_agregar_elemento(lista, 0, &valor),
		     "Puedo agregar un valor a la lista en la posición 0");
	pa2m_afirmar(lista_agregar_elemento(lista, 1, &valor2),
		     "Puedo agregar un valor a la lista en la posición 1");
	pa2m_afirmar(lista_cantidad_elementos(lista) == 2,
		     "La cantidad de elementos en la lista es 2");
	lista_destruir(lista);
}

void agregarUnElementoALaListaNulo()
{
	Lista *lista = lista_crear();
	pa2m_afirmar(lista_agregar_elemento(lista, 0, NULL),
		     "Si puedo agregar un valor nulo a la lista");
	pa2m_afirmar(lista_cantidad_elementos(lista) == 1,
		     "La cantidad de elementos en la lista es 1");
	int valor = 5;
	pa2m_afirmar(lista_agregar_elemento(lista, 1, &valor),
		     "Puedo agregar un valor a la lista en la posición 1");
	pa2m_afirmar(lista_cantidad_elementos(lista) == 2,
		     "La cantidad de elementos en la lista es 2");
	lista_destruir(lista);
}

void eliminarUnElementoDeLaLista()
{
	Lista *lista = lista_crear();
	int valor = 5;
	pa2m_afirmar(lista_agregar_al_final(lista, &valor),
		     "Puedo agregar un valor a la lista");
	void *elemento = NULL;
	pa2m_afirmar(lista_quitar_elemento(lista, 0, &elemento),
		     "Puedo eliminar un valor de la lista");
	pa2m_afirmar(elemento != NULL, "El elemento eliminado no es NULL");
	pa2m_afirmar(*(int *)elemento == 5,
		     "El elemento eliminado es el valor que agregué");
	pa2m_afirmar(lista_cantidad_elementos(lista) == 0,
		     "La cantidad de elementos en la lista es 0");
	lista_destruir(lista);
}

void eliminarUnElementoNuloDeLaLista()
{
	Lista *lista = lista_crear();
	int valor = 5;
	pa2m_afirmar(lista_agregar_al_final(lista, &valor),
		     "Puedo agregar un valor a la lista");
	pa2m_afirmar(lista_agregar_al_final(lista, NULL),
		     "Puedo agregar un valor nulo a la lista");
	void *elemento = NULL;
	pa2m_afirmar(lista_quitar_elemento(lista, 1, &elemento),
		     "Si puedo eliminar un valor nulo de la lista");
	pa2m_afirmar(elemento == NULL, "El elemento eliminado es NULL");
	pa2m_afirmar(lista_cantidad_elementos(lista) == 1,
		     "La cantidad de elementos en la lista es 1");
	lista_destruir(lista);
}

void buscarUnElementoDeLaLista()
{
	Lista *lista = lista_crear();
	char *valor1 = "Hola";
	char *valor2 = "Mundo";
	char *valor3 = "!";
	lista_agregar_al_final(lista, valor1);
	lista_agregar_al_final(lista, valor2);
	lista_agregar_al_final(lista, valor3);

	char *buscado = "Mundo";
	void *encontrado =
		lista_buscar_elemento(lista, buscado, comparar_cadenas);
	pa2m_afirmar(encontrado != NULL, "Puedo buscar un valor en la lista");
	pa2m_afirmar(encontrado == valor2,
		     "El valor encontrado es el valor que busqué");
	lista_destruir(lista);
}

void buscarUnElementoNuloDeLaLista()
{
	Lista *lista = lista_crear();
	char *valor1 = "Hola";
	char *valor2 = "Mundo";
	char *valor3 = "!";
	lista_agregar_al_final(lista, valor1);
	lista_agregar_al_final(lista, valor2);
	lista_agregar_al_final(lista, valor3);

	void *encontrado = lista_buscar_elemento(lista, NULL, comparar_cadenas);
	pa2m_afirmar(encontrado == NULL,
		     "No puedo buscar un valor nulo en la lista");
	lista_destruir(lista);
}

void obtenerElementoDeLaLista()
{
	Lista *lista = lista_crear();
	char *valor1 = "Hola";
	char *valor2 = "Mundo";
	char *valor3 = "!";
	lista_agregar_al_final(lista, valor1);
	lista_agregar_al_final(lista, valor2);
	lista_agregar_al_final(lista, valor3);

	void *elemento = NULL;
	pa2m_afirmar(lista_obtener_elemento(lista, 1, &elemento),
		     "Puedo obtener un valor de la lista");
	pa2m_afirmar(elemento != NULL, "El elemento obtenido no es NULL");
	pa2m_afirmar(strcmp((char *)elemento, "Mundo") == 0,
		     "El elemento obtenido es el valor que busqué");
	lista_destruir(lista);
}

void obtenerUnElementoNoexistente()
{
	Lista *lista = lista_crear();
	char *valor1 = "Hola";
	char *valor2 = "Mundo";
	char *valor3 = "!";
	lista_agregar_al_final(lista, valor1);
	lista_agregar_al_final(lista, valor2);
	lista_agregar_al_final(lista, valor3);

	void *elemento = NULL;
	pa2m_afirmar(
		!lista_obtener_elemento(lista, 3, &elemento),
		"No puedo obtener un valor de la lista en una posición no existente");
	pa2m_afirmar(elemento == NULL, "El elemento obtenido es NULL");
	lista_destruir(lista);
}

void crearIteradorLista()
{
	Lista *lista = lista_crear();
	int valor1 = 5;
	int valor2 = 10;
	int valor3 = 15;

	lista_agregar_al_final(lista, &valor1);
	lista_agregar_al_final(lista, &valor2);
	lista_agregar_al_final(lista, &valor3);

	Lista_iterador *iterador = lista_iterador_crear(lista);
	pa2m_afirmar(iterador != NULL, "Puedo crear un iterador de la lista");

	lista_iterador_destruir(iterador);
	lista_destruir(lista);
}

void crearIteradorListaNull()
{
	Lista_iterador *iterador = lista_iterador_crear(NULL);
	pa2m_afirmar(iterador == NULL,
		     "Puedo crear un iterador de una lista nula");
	lista_iterador_destruir(iterador);
}

void obtenerElementoDeLaListaIterada()
{
	Lista *lista = lista_crear();
	int valor1 = 5;
	int valor2 = 10;
	int valor3 = 15;

	lista_agregar_al_final(lista, &valor1);
	lista_agregar_al_final(lista, &valor2);
	lista_agregar_al_final(lista, &valor3);

	Lista_iterador *iterador = lista_iterador_crear(lista);
	pa2m_afirmar(iterador != NULL, "Puedo crear un iterador de la lista");

	pa2m_afirmar(lista_iterador_hay_siguiente(iterador),
		     "Hay un siguiente elemento en la lista");
	pa2m_afirmar(lista_iterador_obtener_elemento_actual(iterador) ==
			     &valor1,
		     "El elemento actual es el primero de la lista");
	lista_iterador_avanzar(iterador);
	pa2m_afirmar(lista_iterador_hay_siguiente(iterador),
		     "Hay un siguiente elemento en la lista");
	pa2m_afirmar(lista_iterador_obtener_elemento_actual(iterador) ==
			     &valor2,
		     "El elemento actual es el segundo de la lista");
	lista_iterador_avanzar(iterador);
	pa2m_afirmar(lista_iterador_hay_siguiente(iterador),
		     "Hay un siguiente elemento en la lista");
	pa2m_afirmar(lista_iterador_obtener_elemento_actual(iterador) ==
			     &valor3,
		     "El elemento actual es el tercero de la lista");
	lista_iterador_avanzar(iterador);
	pa2m_afirmar(!lista_iterador_hay_siguiente(iterador),
		     "No hay un siguiente elemento en la lista");

	lista_iterador_destruir(iterador);
	lista_destruir(lista);
}

bool imprimir_elemento(void *elemento, void *contexto)
{
	if (!elemento)
		return false;

	int valor = *(int *)elemento;
	printf("%d\n", valor);

	return true;
}

void mostrarListaIteradorInterno()
{
	Lista *lista = lista_crear();
	int valor1 = 5;
	int valor2 = 10;
	int valor3 = 15;

	lista_agregar_al_final(lista, &valor1);
	lista_agregar_al_final(lista, &valor2);
	lista_agregar_al_final(lista, &valor3);

	printf("Imprimiendo los elementos de la lista:\n");
	size_t elementos_iterados =
		lista_iterar_elementos(lista, imprimir_elemento, NULL);

	pa2m_afirmar(elementos_iterados == 3,
		     "Se iteraron los 3 elementos de la lista");

	lista_destruir(lista);
}

bool imprimir_y_detener_si_mayor_que_diez(void *elemento, void *contexto)
{
	if (!elemento)
		return false;

	int *valor = (int *)elemento;

	printf("%d\n", *valor);

	return *valor <= 10;
}

void detenerIteradorInterno()
{
	Lista *lista = lista_crear();

	int *valor1 = malloc(sizeof(int));
	int *valor2 = malloc(sizeof(int));
	int *valor3 = malloc(sizeof(int));
	int *valor4 = malloc(sizeof(int));

	*valor1 = 5;
	*valor2 = 10;
	*valor3 = 15;
	*valor4 = 20;

	lista_agregar_al_final(lista, valor1);
	lista_agregar_al_final(lista, valor2);
	lista_agregar_al_final(lista, valor3);
	lista_agregar_al_final(lista, valor4);

	printf("Iterando y deteniéndose si el valor es mayor que 10:\n");
	size_t elementos_iterados = lista_iterar_elementos(
		lista, imprimir_y_detener_si_mayor_que_diez, NULL);

	printf("Elementos iterados: %zu\n", elementos_iterados);

	pa2m_afirmar(
		elementos_iterados == 3,
		"Se iteraron solo los primeros 3 elementos antes de detenerse");

	free(valor1);
	free(valor2);
	free(valor3);
	free(valor4);

	lista_destruir(lista);
}

bool sumar_elementos(void *elemento, void *contexto)
{
	if (!elemento || !contexto)
		return false;

	int *acumulador = (int *)contexto;
	int valor = *(int *)elemento;

	*acumulador += valor;

	return true;
}

void sumarElementosConIteradorInterno()
{
	Lista *lista = lista_crear();
	int valor1 = 5;
	int valor2 = 10;
	int valor3 = 15;

	lista_agregar_al_final(lista, &valor1);
	lista_agregar_al_final(lista, &valor2);
	lista_agregar_al_final(lista, &valor3);

	int acumulador = 0;
	lista_iterar_elementos(lista, sumar_elementos, &acumulador);

	pa2m_afirmar(acumulador == 30, "La suma de los elementos es 30");

	lista_destruir(lista);
}

void iteradorInternoConListaNula()
{
	printf("Probando iterador con lista nula:\n");
	size_t elementos_iterados =
		lista_iterar_elementos(NULL, imprimir_elemento, NULL);

	pa2m_afirmar(elementos_iterados == 0,
		     "No se iteran elementos en una lista nula");
}

void iterarConInternoConUnaFuncionNula()
{
	Lista *lista = lista_crear();
	int valor1 = 5;
	lista_agregar_al_final(lista, &valor1);

	printf("Probando iterador con función de callback nula:\n");
	size_t elementos_iterados = lista_iterar_elementos(lista, NULL, NULL);

	printf("Elementos iterados: %zu\n", elementos_iterados);

	pa2m_afirmar(elementos_iterados == 0,
		     "No se iteran elementos cuando el callback es nulo");

	lista_destruir(lista);
}

void destructor(void *elemento)
{
	free(elemento);
}

void crearUnaListaYAgregarUnElementoAumentaLaCantidadDeElementos()
{
	Lista *lista = lista_crear();
	pa2m_afirmar(lista != NULL, "Puedo crear una lista");
	pa2m_afirmar(lista_cantidad_elementos(lista) == 0,
		     "La cantidad de elementos de la lista es 0 al inicio");

	int *elemento = malloc(sizeof(int));
	*elemento = 10;
	pa2m_afirmar(lista_agregar_elemento(lista, 0, elemento),
		     "Puedo agregar un elemento a la lista");

	pa2m_afirmar(lista_agregar_elemento(lista, 1, NULL),
		     "Puedo agregar un elemento nulo a la lista");

	int *elemento_obtenido = NULL;
	pa2m_afirmar(lista_obtener_elemento(lista, 0,
					    (void **)&elemento_obtenido),
		     "Puedo obtener el primer elemento de la lista");
	pa2m_afirmar(elemento_obtenido != NULL,
		     "El primer elemento no es nulo");
	pa2m_afirmar(*elemento_obtenido == 10,
		     "El primer elemento de la lista es el correcto");

	pa2m_afirmar(lista_obtener_elemento(lista, 1,
					    (void **)&elemento_obtenido),
		     "Puedo obtener el segundo elemento de la lista");
	pa2m_afirmar(elemento_obtenido == NULL,
		     "El segundo elemento de la lista es nulo");

	pa2m_afirmar(lista_cantidad_elementos(lista) == 2,
		     "La cantidad de elementos de la lista es 2");

	lista_destruir_todo(lista, destructor);
}

bool contar_elementos(void *elemento, void *ctx)
{
	int *limite = (int *)ctx;

	*limite = *limite - 1;

	if (*limite == 0)
		return false;

	return true;
}

void recorrerLaListaConElIteradorInternoLimitadoADosInvocacionesDevuelveTres()
{
	Lista *lista = lista_crear();
	pa2m_afirmar(lista != NULL, "Puedo crear una lista");

	int *elemento1 = malloc(sizeof(int));
	*elemento1 = 1;
	lista_agregar_elemento(lista, 0, elemento1);

	int *elemento2 = malloc(sizeof(int));
	*elemento2 = 2;
	lista_agregar_elemento(lista, 1, elemento2);

	int *elemento3 = malloc(sizeof(int));
	*elemento3 = 3;
	lista_agregar_elemento(lista, 2, elemento3);

	int *elemento4 = malloc(sizeof(int));
	*elemento4 = 4;
	lista_agregar_elemento(lista, 3, elemento4);

	size_t limite = 2;
	size_t elementos_iterados =
		lista_iterar_elementos(lista, contar_elementos, &limite);

	printf("Elementos iterados: %zu\n", elementos_iterados);

	pa2m_afirmar(elementos_iterados == 2,
		     "Recorrer la lista devuelve 3 elementos");

	lista_destruir(lista);
	free(elemento1);
	free(elemento2);
	free(elemento3);
	free(elemento4);
}

void iteradorInternoLimitadoEn3()
{
	Lista *lista = lista_crear();
	pa2m_afirmar(lista != NULL, "Puedo crear una lista");

	for (int i = 0; i < 5; i++) {
		int elemento = i;
		pa2m_afirmar(lista_agregar_al_final(lista, &elemento),
			     "Agrego elemento a la lista");
	}

	size_t limite = 3;
	size_t elementos_iterados =
		lista_iterar_elementos(lista, contar_elementos, &limite);

	printf("Elementos iterados: %zu\n", elementos_iterados);

	pa2m_afirmar(
		elementos_iterados == 3,
		"Recorrer la lista con el iterador interno limitado a 3 invocaciones devuelve 3");

	lista_destruir(lista);
}

void destruirTodoAplicaLaFuncionDadaACadaElemento()
{
	Lista *lista = lista_crear();

	if (lista == NULL) {
		fprintf(stderr, "Error al crear la lista.\n");
		return;
	}

	int *elemento1 = malloc(sizeof(int));
	int *elemento2 = malloc(sizeof(int));
	int *elemento3 = malloc(sizeof(int));
	*elemento1 = 10;
	*elemento2 = 20;
	*elemento3 = 30;

	lista_agregar_al_final(lista, elemento1);
	lista_agregar_al_final(lista, elemento2);
	lista_agregar_al_final(lista, elemento3);

	pa2m_afirmar(lista_cantidad_elementos(lista) == 3,
		     "La cantidad de elementos es 3 antes de destruir");

	lista_destruir_todo(lista, destructor);

	pa2m_afirmar(true, "La lista ha sido destruida correctamente.");
}

void crearMenu()
{
	menu_t *menu = menu_crear();

	pa2m_afirmar(menu != NULL, "Puedo crear un menu");

	menu_destruir(menu, NULL);
}

void destructo_menu(void *elemento)
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

	menu_destruir(menu, destructo_menu);
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

	menu_destruir(menu, destructo_menu);
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

	menu_destruir(menu, destructo_menu);
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

	menu_destruir(menu, destructo_menu);
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

	menu_destruir(menu, destructo_menu);
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
	pa2m_nuevo_grupo("Pruebas de pila");
	crearPila();
	printf("\n");
	agregarALaPila();
	printf("\n");
	agregarUnElementoALaPilaDevuelveElTope();
	printf("\n");
	agregarDosElementosALaPilaDevuelveElTopeCorrecto();
	printf("\n");
	agregarUnElementoALaPilaNulo();
	printf("\n");
	desapilarUnElementoDeLaPila();
	printf("\n");
	desapilarUnElementoDeLaPilaDeDos();
	printf("\n");
	pilaVacia();
	printf("\n");
	pilaVaciaConElementos();
	printf("\n");
	pa2m_nuevo_grupo("Pruebas de lista");
	crearLista();
	printf("\n");
	agregarALaLista();
	printf("\n");
	agregarDosElementoALaListaEnPosicion();
	printf("\n");
	agregarUnElementoALaListaNulo();
	printf("\n");
	eliminarUnElementoDeLaLista();
	printf("\n");
	eliminarUnElementoNuloDeLaLista();
	printf("\n");
	buscarUnElementoDeLaLista();
	printf("\n");
	buscarUnElementoNuloDeLaLista();
	printf("\n");
	obtenerElementoDeLaLista();
	printf("\n");
	obtenerUnElementoNoexistente();
	printf("\n");
	crearIteradorLista();
	printf("\n");
	crearIteradorListaNull();
	printf("\n");
	obtenerElementoDeLaListaIterada();
	printf("\n");
	mostrarListaIteradorInterno();
	printf("\n");
	detenerIteradorInterno();
	printf("\n");
	sumarElementosConIteradorInterno();
	printf("\n");
	iteradorInternoConListaNula();
	printf("\n");
	iterarConInternoConUnaFuncionNula();
	printf("\n");
	crearUnaListaYAgregarUnElementoAumentaLaCantidadDeElementos();
	printf("\n");
	recorrerLaListaConElIteradorInternoLimitadoADosInvocacionesDevuelveTres();
	printf("\n");
	iteradorInternoLimitadoEn3();
	printf("\n");
	destruirTodoAplicaLaFuncionDadaACadaElemento();
	pa2m_nuevo_grupo("Pruebas de menu");
	crearMenu();
	printf("\n");
	agregarOpciones();
	printf("\n");
	elegirOpcion();
	printf("\n");
	mostrarMenu();
	printf("\n");
	//seleccionarOpcion();
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
	//menuMostrarPokedex();
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
