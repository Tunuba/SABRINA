#include "juego.h"

/* Cuadricula de colision del nivel: cubre de -128 a 128 en x y z (16.16) con celdas cuadradas. */

extern s16 D_8007CBC8;               /* celdas por lado */

/* Indice de la celda que contiene la posicion (x, z): columna + fila * celdas por lado. No revisa que caiga
 * dentro; los llamadores comparan con D_8007CBC4. */
s32 CeldaDePosicion(s32 x, s32 z) {
    s32 lado = D_8007CBC8;
    s32 tam = (0x100 / lado) << 16;
    s32 columna = (x + 0x800000) / tam;
    s32 fila = (z + 0x800000) / tam;

    return columna + fila * lado;
}
