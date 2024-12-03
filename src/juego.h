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
	size_t indiceMovimiento;
} pokemonTablero_t;

typedef struct jugador {
	int x;
	int y;
	int puntaje;
	int multiplicador;
	int movimientos;
	int pokemonesAtrapados;
	pokemonTablero_t *pokemonAtrapado;
	Pila *rachaActual;
	Pila *rachaMayor;
} jugador_t;

typedef struct tablero {
	int ancho;
	int alto;
	char **celdas;
	Lista *pokemones;
	Lista *atrapados;
} tablero_t;

typedef struct juego {
	jugador_t *jugador;
	tablero_t *tablero;
	Lista *pokedex;
	int iteraciones;
	int semilla;
	bool terminado;
} juego_t;

/*
* Destruye un pokemonTablero.
*/
void destructor_pokemones_tablero(void *elemento);

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
* Itera con el iterador interno la lista de pokemones hasta encontrar uno que coinicida con la posicion x e y.
* Devuelve el pokemon encontrado, caso contrario NULL.
*/
pokemonTablero_t *encontrar_pokemon_en_posicion(Lista *pokemones, int x, int y);

/*
* Imprime el tablero con la informacion en pantalla.
* Esta informacion esta relacionada la contiene juego.
*/
void tablero_imprimir(juego_t *juego);

/*
* Itera con el iterador interno la lista de pokemones hasta encontrar el pokemon y eliminarlo.
*/
pokemonTablero_t *tablero_eliminar_pokemon(Lista *pokemones, Lista *atrapados,
					   pokemonTablero_t *pokemon);

/*
* Busca un pokemon aleatorio de la pokedex y lo agrega a la lista de pokemones.
*/
void tablero_agregar_pokemon(Lista *pokedex, Lista *pokemones);

/*
* Devuelve el pokemon en la posición x = 0 e y = 0.
*/
jugador_t *jugador_crear();

/*
* Destruye el jugador liberando la memoria que se asigno a los elementos.
* Se llama a la funcion de Pila_destruir_todo para liberar la memoria de los pokemones atrapados.
*/
void jugador_destruir(jugador_t *jugador, void (*destructor)(void *));

/*
* Limitaran o ajustaran los valores de x e y para que no se salgan de los limites del tablero.
* Devuelve el mayor/menor valor.
*/
int max(int a, int b);
int min(int a, int b);

/*
* Itera con el iterador interno la lista de pokemones y se encarga de moverlos segun el movimiento que le toca del patron.
* Si el pokemon llega al final del patron, se reinicia el indice de movimiento.
*/
void procesar_movimiento_pokemones(Lista *pokemones, int entrada);

/*
* Realiza mediante la entrada el moviente del jugador.
* Se encarga de llamar a la funcion de procesar_movimiento_pokemones para calcular el movimiento de estos.
*/
void procesar_entrada(int entrada, jugador_t *jugador, Lista *pokemones);

/*
* Realiza las operaciones relacionadas al puntaje.
*/
void administrar_puntaje(jugador_t *jugador, pokemonTablero_t *pokemon);

/*
* Junta las acciones que se deben realizar al atrapar un pokemon.
*/
void atrapar_pokemon(juego_t *juego, pokemonTablero_t *pokemon);

/*
* Contiene la logica del juego.
*/
int logica(int entrada, void *data);

#endif // JUEGO_H