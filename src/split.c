#include "split.h"
#include <stdlib.h>
#include <string.h>

size_t cantidad_separadores(const char *string, char separador)
{
	size_t cantidad = 0;
	int i = 0;

	while (string[i] != 0) {
		if (string[i] == separador)
			cantidad++;

		i++;
	}

	return cantidad + 1;
}

size_t *contador_caracteres(const char *string, char separador, size_t cantidad)
{
	size_t *ptr = malloc(sizeof(size_t) * (cantidad + 1));

	if (ptr == NULL)
		return NULL;

	size_t caracteres = 0;
	size_t posicion = 0;

	while (string[caracteres] != 0) {
		if (string[caracteres] == separador) {
			ptr[posicion] = caracteres;
			posicion++;
		}
		caracteres++;
	}

	ptr[posicion] = caracteres;

	return ptr;
}

void pegar_strings(const char *string, char separador, struct Partes *partes,
		   size_t *vector_caracteres)
{
	size_t inicio = 0;
	size_t fin;

	for (size_t i = 0; i < partes->cantidad; i++) {
		fin = vector_caracteres[i];
		size_t longitud = fin - inicio;

		partes->string[i] = malloc(sizeof(char) * (longitud + 1));

		if (partes->string[i] == NULL) {
			for (size_t j = 0; j < i; j++)
				free(partes->string[j]);
			free(partes->string);
			return;
		}

		strncpy(partes->string[i], string + inicio, longitud);
		partes->string[i][longitud] = '\0';

		inicio = fin + 1;
	}
}

struct Partes *crear_partes(size_t cantidad)
{
	struct Partes *partes = malloc(sizeof(struct Partes));

	if (partes == NULL)
		return NULL;

	partes->string = malloc(sizeof(char *) * cantidad);

	if (partes->string == NULL) {
		free(partes);
		return NULL;
	}

	partes->cantidad = cantidad;

	return partes;
}

struct Partes *inicializar_partes(const char *string, char separador)
{
	size_t cantidad = cantidad_separadores(string, separador);
	struct Partes *partes = crear_partes(cantidad);

	if (partes == NULL)
		return NULL;

	size_t *vector_caracteres =
		contador_caracteres(string, separador, cantidad);

	if (vector_caracteres == NULL) {
		liberar_partes(partes);
		return NULL;
	}

	pegar_strings(string, separador, partes, vector_caracteres);
	free(vector_caracteres);

	return partes;
}

struct Partes *dividir_string(const char *string, char separador)
{
	if (string == NULL) {
		struct Partes *partes = malloc(sizeof(struct Partes));
		if (partes == NULL)
			return NULL;

		partes->cantidad = 0;
		partes->string = NULL;
		return partes;
	}

	return inicializar_partes(string, separador);
}

void liberar_partes(struct Partes *partes)
{
	for (size_t i = 0; i < partes->cantidad; i++) {
		free(partes->string[i]);
	}

	free(partes->string);

	free(partes);
}
