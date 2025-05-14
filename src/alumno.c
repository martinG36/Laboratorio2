/*********************************************************************************************************************
Copyright (c) 2025, Martín Fernando Gareca <mfgareca36@gmail.com>


Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
documentation files (the "Software"), to deal in the Software without restriction, including without limitation the
rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit
persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the
Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

SPDX-License-Identifier: MIT
*********************************************************************************************************************/

/** @file alumno.c
 ** @brief Codigo fuente del modulo para la gestión de alumnos
 **/

/* === Headers files inclusions ==================================================================================== */

#include <config.h>
#include "alumno.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

/* === Macros definitions ========================================================================================== */

#ifndef ALUMNOS_MAX_INSTANCIAS // Si está definido en el make, no se redefine
#define ALUMNOS_MAX_INSTANCIAS 2 // Cantidad máxima de alumnos que se pueden crear
#endif

/* === Private data type declarations ============================================================================== */

struct alumno_s {
    char nombre[20];    //! Nombre del alumno
    char apellido[20];  //! Apellido del alumno
    uint32_t documento; //! Documento de identidad del alumno
#ifndef USAR_MEMORIA_DINAMICA
    bool ocupado;       //! Indica si la instancia está ocupada
#endif
};

/* === Private function declarations =============================================================================== */

/**
 * @brief //! Función para crear una instancia de alumno
 * 
 * @return alumno_t 
 */
static alumno_t CrearInstancia();

/**
 * @brief //! Función para serializar una cadena de caracteres
 * 
 * @param campo //! Cadena que representa el nombre del campo
 * @param valor //! Cadena que representa el valor asociado al campo
 * @param buffer //! Buffer donde se escribirá la cadena serializada
 * @param disponibles //! Cantidad de bytes disponibles en el buffer, incluyendo el terminador nulo
 * @return int //! Numero de caracteres escritos (sin contar el terminador nulo), o un valor negativo si ocurre un error
 */
static int SerializarCadena (char campo[], const char valor[], char buffer[], uint32_t disponibles);

/**
 * @brief //! Función para serializar un entero
 * 
 * @param campo //! Cadena que representa el nombre del campo
 * @param valor //! Cadena que representa el valor asociado al campo
 * @param buffer //! Buffer donde se escribirá el entero serializado
 * @param disponibles //! Cantidad de bytes disponibles en el buffer, incluyendo el terminador nulo
 * @return int //! Numero de caracteres escritos (sin contar el terminador nulo), o un valor negativo si ocurre un error
 */
static int SerializarEntero(char campo[], int valor, char buffer[], uint32_t disponibles);

/* === Private variable definitions ================================================================================ */

#ifndef USAR_MEMORIA_DINAMICA
static struct alumno_s instancias[ALUMNOS_MAX_INSTANCIAS] = {0}; // Cantidad máxima de alumnos que se pueden crear
#endif

/* === Public variable definitions ================================================================================= */

/* === Private function definitions ================================================================================ */

#ifndef USAR_MEMORIA_DINAMICA
static alumno_t CrearInstancia() {
    int i;
    alumno_t self = NULL;
    for (i = 0; i < ALUMNOS_MAX_INSTANCIAS; i++) {
        if (!instancias[i].ocupado) { // Verifica si la instancia está vacía
            instancias[i].ocupado = true; // Marca la instancia como ocupada
            self = &instancias[i];
            break;
        }
    }
    return self;
}
#endif

static int SerializarCadena(char campo[], const char valor[], char buffer[], uint32_t disponibles){
    return snprintf(buffer, disponibles, "\"%s\":\"%s\",", campo, valor);
}

static int  SerializarEntero(char campo[], int valor, char buffer[], uint32_t disponibles){
    return snprintf(buffer, disponibles, "\"%s\":%d", campo, valor);
}

/* === Public function definitions ============================================================================== */

alumno_t AlumnoCrear(char * nombre, char * apellido, uint32_t documento) {
#ifdef USAR_MEMORIA_DINAMICA
    alumno_t self = malloc(sizeof(struct alumno_s));
#else
    alumno_t self = CrearInstancia();
#endif

    if (self != NULL) {
        self->documento = documento;
        strncpy(self->nombre, nombre, sizeof(self->nombre) - 1);
        strncpy(self->apellido, apellido, sizeof(self->apellido) - 1);
    }
    return self;
}

int AlumnoSerializar(const alumno_t alumno, char buffer[], uint32_t size) {
    int escritos = 0;
    int resultado;
    char *ptr = buffer;

    if (size < 3)
    {
        return -1;
    }

    *ptr++ = '{';
    escritos++;

    resultado = SerializarCadena("nombre", alumno->nombre, ptr, size - escritos);
    if (resultado < 0 || resultado >= (int)(size - escritos))
    {
        return -1;
    }
    ptr += resultado;
    escritos += resultado;

    resultado = SerializarCadena("apellido", alumno->apellido, ptr, size - escritos);
    if (resultado < 0 || resultado >= (int)(size - escritos))
    {
        return -1;
    }
    ptr += resultado;
    escritos += resultado;

    resultado = SerializarEntero("documento", alumno->documento, ptr, size - escritos);
    if (resultado < 0 || resultado >= (int)(size - escritos))
    {
        return -1;
    }
    ptr += resultado;
    escritos += resultado;

    if (size - escritos <= 2)
    {
        return -1;
    }

    *ptr++ = '}';
    *ptr = '\0';
    escritos++;

    return escritos;
}

/* === End of documentation ======================================================================================== */
