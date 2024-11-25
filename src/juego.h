#ifndef JUEGO_H
#define JUEGO_H

#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "pokedex.h"
#include "lista.h"
#include "pila.h"
#include "../extra/ansi.h"
#include "../extra/engine.h"

#define ANCHO_TABLERO 32
#define ALTO_TABLERO 15

typedef struct pokemonTablero {
	int x;
	int y;
	char *nombre;
	char letra;
	int puntaje;
	char *color;
	char *movimientos;
} pokemonTablero_t;

typedef struct jugador {
	int x;
	int y;
	int puntaje;
	int multiplicador;
	int movimientos;
	int pokemonesAtrapados;
	Pila *rachaActual;
	Pila *rachaMayor;
} jugador_t;

typedef struct tablero {
	int ancho;
	int alto;
	char **celdas;
	Lista *pokemones;
} tablero_t;

typedef struct juego {
	jugador_t *jugador;
	tablero_t *tablero;
	Lista *pokemones;
	int iteraciones;
	int semilla;
	bool terminado;
} juego_t;

/*
* Crea un tablero con las dimensiones de 15 filas y 32 columnas.
* Se encarga de asignar memoria a los elementos que sean necesarios y asigna el puntero a lista pasada por parametro.
* Si todo salio bien devuelve el tablero, sino devuelve NULL.
*/
tablero_t *tablero_crear(Lista *pokemones);

/*
* Destruye el tablero liberando la memoria que se asigno a los elementos.
* Se llama a la funcion de lista_destruir_todo para liberar la memoria de los pokemones.
*/
void tablero_destruir(tablero_t *tablero, void (*destructor)(void *));

/*
* Imprime el tablero con la informacion en pantalla.
* Esta informacion esta relacionada la contiene juego.
*/
void tablero_imprimir(juego_t *juego);

/*
* Devuelve el pokemon en la posición x = 0 e y = 0.
*/
jugador_t *jugador_crear();

/*
* Destruye el jugador liberando la memoria que se asigno a los elementos.
* Se llama a la funcion de pila_destruir_todo para liberar la memoria de los pokemones atrapados.
*/
void jugador_destruir(jugador_t *jugador, void (*destructor)(void *));

/*
* Limitaran o ajustaran los valores de x e y para que no se salgan de los limites del tablero.
* Devuelve el mayor/menor valor.
*/
int max(int a, int b);
int min(int a, int b);

/*
* Realizar que el jugador y pokemones se muevan.
*/
void procesar_entrada(int entrada, jugador_t *jugador, Lista *pokemones);

/*
* Realiza las operaciones relacionadas al puntaje.
*/
void administrar_puntaje(jugador_t *jugador, pokemonTablero_t *pokemon);

/*
* Contiene la logica del juego.
*/
int logica(int entrada, void *data);

#endif // JUEGO_H