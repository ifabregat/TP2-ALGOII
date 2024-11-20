#include "csv.h"
#include "split.h"
#include <stdio.h>
#include <string.h>

struct archivo_csv {
	FILE *archivo;
	char separador;
};

struct archivo_csv *abrir_archivo_csv(const char *nombre_archivo,
				      char separador)
{
	FILE *archivo = fopen(nombre_archivo, "r");

	if (archivo == NULL)
		return NULL;

	struct archivo_csv *csv = calloc(1, sizeof(struct archivo_csv));

	if (csv == NULL) {
		fclose(archivo);
		return NULL;
	}

	csv->archivo = archivo;
	csv->separador = separador;

	return csv;
}

size_t leer_linea_csv(struct archivo_csv *archivo, size_t columnas,
		      bool (*funciones[])(const char *, void *), void *ctx[])
{
	if (archivo == NULL) {
		return 0;
	}

	size_t capacidad = 128;
	size_t longitud = 0;
	char *linea = malloc(capacidad * sizeof(char));

	if (linea == NULL) {
		return 0;
	}

	int c;
	while ((c = fgetc(archivo->archivo)) != '\n' && c != EOF) {
		if (longitud + 1 >= capacidad) {
			capacidad *= 2;

			char *nueva_linea =
				realloc(linea, capacidad * sizeof(char));

			if (nueva_linea == NULL) {
				free(linea);
				return 0;
			}

			linea = nueva_linea;
		}

		linea[longitud++] = (char)c;
	}

	linea[longitud] = 0;

	if (longitud == 0 && c == EOF) {
		free(linea);
		return 0;
	}

	struct Partes *partes = dividir_string(linea, archivo->separador);

	free(linea);

	if (partes == NULL) {
		return 0;
	}

	size_t columnas_leidas = 0;
	for (size_t i = 0; i < partes->cantidad && i < columnas; i++) {
		if (ctx[i] == NULL)
			columnas_leidas++;
		else {
			if (funciones[i] != NULL) {
				if (funciones[i](partes->string[i], ctx[i])) {
					columnas_leidas++;
				}
			}
		}
	}

	liberar_partes(partes);

	return columnas_leidas;
}

void cerrar_archivo_csv(struct archivo_csv *archivo)
{
	fclose(archivo->archivo);
	free(archivo);
}
