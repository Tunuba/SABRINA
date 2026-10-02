#include "juego.h"

/* Lugar para las paletas (CLUT) en la VRAM: 63 filas desde y = 0x1C0, 29 columnas de 16 colores desde
   x = 0x200. D_800676C4 guarda por fila y columna cuanto queda libre (0 = ocupada). */

extern u8 D_800676C4[];         /* 0x3F filas de 0x40 bytes (u16 por columna) */
extern char D_800656A0[];       /* el aviso de que no hay lugar */
extern s32 printf(const char *f, ...);

/* Busca lugar para una paleta de t+0x1A colores; deja su x en t+0x16 y su y en t+0x18 y marca las
   columnas como ocupadas. Si no hay lugar avisa y se queda colgada. */
s32 func_8001A4C0(u8 *t) {
    u32 tam = *(u16 *)(t + 0x1A);
    u32 fila, col, k, fin, j;
    u16 *f;
    s32 ocupado, v;
    for (fila = 0; fila != 0x3F; fila = (fila + 1) & 0xFF) {
        f = (u16 *)(D_800676C4 + fila * 0x40);
        for (col = 0; col != 0x1D; col = (col + 1) & 0xFF) {
            if (f[col] < tam) {
                continue;
            }
            fin = SUMA_TRAMPA((s32)tam / 16, col) & 0xFF;
            ocupado = 0;
            for (k = col, j = col; k != fin; k = (k + 1) & 0xFF, j++) {
                if (f[j] == 0) {
                    ocupado = 1;
                }
            }
            if (ocupado) {
                continue;
            }
            *(s16 *)(t + 0x16) = col * 16 + 0x200;
            v = fila + 0x1C0;
            *(s16 *)(t + 0x18) = v;
            for (k = col, j = col; k != fin; j++) {
                f[j] = 0;
                v = k + 1;
                k = v & 0xFF;
            }
            return v;
        }
    }
    printf(D_800656A0);
    for (;;) {
    }
}

extern void *Reservar(s32 tam, char *archivo, s32 linea);
extern char D_8006561C[];       /* el nombre del archivo fuente, para Reservar */

/* Recorta un cuadro de 32 filas de una imagen de 16 bits (fila de ancho pixeles, empieza en x0): el ancho
   llega hasta la marca 0x1F0 o el borde; copia el cuadro a un bloque nuevo y deja en d[5] uno mas que la
   ultima columna con algo pintado, en d[0xA] el ancho y en d[0xB] el alto (32). Devuelve el bloque, o 0 si
   el cuadro llega al borde. */
void *func_8001ADD8(u16 *img, u8 *d, s32 ancho, s32 x0) {
    u32 w = 0, y, x;
    s32 i;
    u16 *src, *dst;
    void *buf;
    d[5] = 0;
    for (;;) {
        i = SUMA_TRAMPA(x0, w);
        if (img[i] == 0x1F0 || ancho == i) {
            break;
        }
        w = (w + 1) & 0xFF;
    }
    d[0xA] = w;
    d[0xB] = 0x20;
    if (ancho == SUMA_TRAMPA(x0, w)) {
        d[5]++;
        return 0;
    }
    buf = Reservar(w << 7, D_8006561C, 0x2F3);
    src = img + x0;
    dst = buf;
    for (y = 0; y != 0x20; y = (y + 1) & 0xFF) {
        for (x = 0; x != w; x = (x + 1) & 0xFF) {
            if (src[x] != 0 && d[5] < x) {
                d[5] = x;
            }
            *dst++ = src[x];
        }
        src = (u16 *)SUMA_TRAMPA((s32)src, ancho * 2);
    }
    d[5]++;
    return buf;
}
