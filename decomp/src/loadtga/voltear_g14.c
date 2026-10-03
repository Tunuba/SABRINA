#include "juego.h"

/* Voltear una imagen de arriba a abajo (las TGA se guardan de abajo hacia arriba). */

extern char D_8006561C[];            /* el nombre del archivo fuente */
extern void *Reservar(s32 tam, char *archivo, s32 linea);
extern s32 Liberar(void *p);
extern void *memcpy(void *a, const void *de, s32 n);

/* Intercambia las filas de img (ancho x alto pixeles de bpp bytes) de afuera hacia adentro, usando una fila
 * de paso. Devuelve lo que deja Liberar. */
s32 func_8001A668(u8 *img, s32 ancho, u32 alto, s32 bpp) {
    s32 fila = ancho * bpp;
    u8 *abajo = img + bpp * (ancho * alto) - fila;
    u8 *paso = Reservar(fila, D_8006561C, 0x14F);
    u32 i;

    for (i = 0; i < alto >> 1; i++) {
        memcpy(paso, img, fila);
        memcpy(img, abajo, fila);
        memcpy(abajo, paso, fila);
        abajo -= fila;
        img += fila;
    }
    return Liberar(paso);
}
