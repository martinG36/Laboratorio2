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

/** @file main.c
 ** @brief Codigo fuente principal del proyecto
 **/

/* === Headers files inclusions ==================================================================================== */

#include "alumno.h"
#include <stdio.h>

/* === Macros definitions ========================================================================================== */

/* === Private data type declarations ============================================================================== */

/* === Private function declarations =============================================================================== */

/* === Private variable definitions ================================================================================ */

//static struct alumno_s YO = {
//    .nombre = "Martín",
//    .apellido = "Gareca",
//    .documento = 43291421
//};

/* === Public variable definitions ================================================================================= */

/* === Private function definitions ================================================================================ */

/* === Public function implementation ============================================================================== */

int main(void)
{
    alumno_t YO = AlumnoCrear("Martín", "Gareca", 43291421);
    alumno_t YOnt = AlumnoCrear("Pepe", "Ganem", 12345678);
    char buffer[100];
    int resultado;

    if (YO == NULL || YOnt == NULL) {
        printf("Error al crear el alumno\n");
        return -1;
    }
    
    resultado = AlumnoSerializar(YO, buffer, sizeof(buffer));
    
    if (resultado > 0) {
        printf("Serializado: %s\n", buffer);
        printf("Cantidad de caracteres escritos: %d\n", resultado);
    } else {
        printf("Error al serializar\n");
    }

    // Serializar el segundo alumno
    resultado = AlumnoSerializar(YOnt, buffer, sizeof(buffer) - sizeof(YO));

    if (resultado > 0) {
        printf("Serializado: %s\n", buffer);
        printf("Cantidad de caracteres escritos: %d\n", resultado);
    } else {
        printf("Error al serializar\n");
    }
}
/* === End of documentation ======================================================================================== */
