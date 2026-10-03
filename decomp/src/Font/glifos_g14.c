#include "juego.h"

/* Recorte de los glifos de la imagen de una fuente. */

extern char D_8006561C[];            /* el nombre del archivo fuente */
extern void *Reservar(s32 tam, char *archivo, s32 linea);

/* Mide el glifo que empieza en la columna x de la imagen (ancho_img pixeles por fila): llega hasta el
 * pixel de marca 0x1F0 o hasta el final de la fila. Deja en g el ancho (0xA), el alto 32 (0xB) y en 5 la
 * ultima columna con algo dibujado mas uno. Si no llego al final de la fila copia el glifo (32 filas) a un
 * bufer nuevo y lo devuelve; si no, devuelve 0. */
u16 *func_8001ADD8(u16 *img, u8 *g, s32 ancho_img, s32 x) {
    u16 *buf = 0;
    u16 *fila;
    u16 *d;
    u8 w = 0;
    u8 i, j;
    s32 k;
    s32 p;

    g[5] = 0;
    for (;;) {
        p = x + w;
        if (img[p] == 0x1F0 || ancho_img == p) {
            break;
        }
        w++;
    }
    g[0xA] = w;
    g[0xB] = 0x20;
    if (ancho_img != x + w) {
        buf = Reservar(w << 7, D_8006561C, 0x2F3);
        fila = img + x;
        d = buf;
        for (j = 0; j != 0x20; j++) {
            for (i = 0, k = 0; i != w; i++, k++) {
                if (fila[k] != 0 && g[5] < i) {
                    g[5] = i;
                }
                *d++ = fila[k];
            }
            fila += ancho_img;
        }
    }
    g[5]++;
    return buf;
}
