#include "juego.h"

/* Lugar libre en la VRAM para una textura. */

extern u16 D_800656C4[0x18][0x80];   /* casillas de 16x16 de la VRAM: lo libre que queda desde cada una */
extern char D_8006562C[];            /* aviso: ancho que no es multiplo de 16 */
extern char D_80065654[];            /* aviso: alto que no es multiplo de 16 */
extern char D_8006567C[];            /* aviso: no hay lugar */
extern s32 printf(char *fmt, ...);

/* Busca, fila por fila, la primera casilla con lugar para una textura de ancho x alto (el alto sale de la
 * cabecera t) en la que ninguna de las casillas que ocuparia este tomada; la marca tomada y deja en la
 * cabecera la posicion en la VRAM (x = 0x200 + 4 por columna, y = 16 por fila). Si no hay lugar avisa y se
 * queda ahi para siempre. */
void func_8001A228(u8 *t, s32 ancho) {
    u32 w = (u16)*(s16 *)(t + 8);
    u32 alto = (u16)*(s16 *)(t + 0xA);
    u8 fila, col, fin_col, fin_fila, f, c;
    s32 k;
    s32 ocupado;

    for (fila = 0; fila != 0x18; fila++) {
        for (col = 0; col != 0x7F; col++) {
            u32 v = D_800656C4[fila][col];
            if ((s32)v < ancho || v < alto) {
                continue;
            }
            fin_col = ancho / 16 + col;
            if (w & 0xF) {
                printf(D_8006562C, w, *(s32 *)(t + 4));
            }
            fin_fila = (s32)alto / 16 + fila;
            if (alto & 0xF) {
                printf(D_80065654, alto, *(s32 *)(t + 4));
            }
            ocupado = 0;
            for (f = fila; f != fin_fila; f++) {
                for (c = col, k = col; c != fin_col; c++, k++) {
                    if (D_800656C4[f][k] == 0) {
                        ocupado = 1;
                    }
                }
            }
            if (!ocupado) {
                *(s16 *)(t + 0x12) = col * 4 + 0x200;
                *(s16 *)(t + 0x14) = fila * 16;
                for (; fila != fin_fila; fila++) {
                    for (c = col, k = col; c != fin_col; c++, k++) {
                        D_800656C4[fila][k] = 0;
                    }
                }
                return;
            }
        }
    }
    printf(D_8006567C);
    for (;;) {
    }
}
