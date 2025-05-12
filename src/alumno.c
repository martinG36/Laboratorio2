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

#include "alumno.h"
#include <stdio.h>

/* === Macros definitions ========================================================================================== */

/* === Private data type declarations ============================================================================== */

/* === Private function declarations =============================================================================== */

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

/* === Public variable definitions ================================================================================= */

/* === Private function definitions ================================================================================ */

static int SerializarCadena(char campo[], const char valor[], char buffer[], uint32_t disponibles){
    return snprintf(buffer, disponibles, "\"%s\":\"%s\",", campo, valor);
}

static int  SerializarEntero(char campo[], int valor, char buffer[], uint32_t disponibles){
    return snprintf(buffer, disponibles, "\"%s\":%d", campo, valor);
}

/* === Public function definitions ============================================================================== */

int Serializar(const alumno_t alumno, char buffer[], uint32_t size) {
    int escritos;
    int resultado;

    buffer[0] = '{';
    buffer++;
    escritos = 1;
    resultado = SerializarCadena("nombre", alumno->nombre, buffer, size - escritos);
    if (resultado < 0) {
        return -1;
    }
    buffer += resultado;
    escritos += resultado;
    resultado = escritos;
    
    escritos += SerializarCadena("aplellido", alumno->apellido, buffer, size - escritos);
    if (escritos < 0) {
        return -1;
    }
    buffer += escritos - resultado;

    resultado = escritos;

    escritos += SerializarEntero("documento", alumno->documento, buffer, size - escritos);

    if (escritos < 0) {
        return -1;
    }

    buffer += escritos - resultado;

    if (size - escritos <= 2)
    {
        return -1;
    }else{
        *buffer = '}';
        buffer++;
        *buffer = '\0';
        escritos += 1;
    }
    
    return escritos;
}

/* === End of documentation ======================================================================================== */
