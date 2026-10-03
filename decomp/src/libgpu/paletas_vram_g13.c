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

extern s32 ArchivoLeer(s32 archivo, void *buf, s32 n);
extern void Liberar(void *p);

/* Lee una imagen de 16 bits del archivo y la pasa a indices de 12 bits (4 por canal) mas 1, con 0 para el
   color transparente (0x7C1F) y 1 para el negro. Devuelve 0x10 (queda en v0). */
s32 func_8001A108(s32 archivo, u8 *t, u16 *dst) {
    s32 n = *(s16 *)(t + 8) * *(s16 *)(t + 0xA);
    u16 *buf = Reservar(n * 2, D_8006561C, 0x40);
    u16 *s = buf;
    ArchivoLeer(archivo, buf, n * 2);
    while (n-- != 0) {
        u32 c = *s;
        if (c == 0) {
            *dst = 1;
        } else if (c == 0x7C1F) {
            *dst = 0;
        } else {
            *dst = SUMA_TRAMPA(((c << 9) & 0x3C00) | ((c >> 11) & 0xF) | ((c >> 1) & 0x1E0), 1);
        }
        dst++;
        s++;
    }
    Liberar(buf);
    *(s16 *)(t + 0x1A) = 0x10;
    t[0x1D] = 0;
    return 0x10;
}

/* Lo mismo para una imagen de 24 bits (3 bytes por pixel), con (FF, 00, FF) como transparente. Devuelve
   1 (queda en v0). */
s32 func_80019FBC(s32 archivo, u8 *t, u16 *dst) {
    u32 n = (*(s16 *)(t + 8) * *(s16 *)(t + 0xA)) & 0xFFFF;
    s32 tam = SUMA_TRAMPA(n * 2, n);
    u8 *buf = Reservar(tam, D_8006561C, 0x1C);
    u8 *s = buf;
    u32 k;
    ArchivoLeer(archivo, buf, tam);
    for (;;) {
        k = n;
        n = (k - 1) & 0xFFFF;
        if (k == 0) {
            break;
        }
        if (s[0] == 0xFF && s[1] == 0 && s[2] == 0xFF) {
            *dst++ = 0;
        } else {
            *dst++ = SUMA_TRAMPA(((s[0] >> 4) << 10) | (s[2] >> 4) | ((s[1] >> 4) << 5), 1);
        }
        s = (u8 *)SUMA_TRAMPA((s32)s, 3);
    }
    Liberar(buf);
    *(s16 *)(t + 0x1A) = 0x100;
    t[0x1D] = 1;
    return 1;
}

extern u8 D_800656C4[];         /* 0x18 filas de 0x100 bytes (u16 por columna): lo libre de cada lugar */
extern char D_8006562C[], D_80065654[], D_8006567C[];

/* Busca lugar en la VRAM para una textura de ancho w (en pixeles de 16) y alto t+0xA: 24 filas de 16 pixeles
   y 127 columnas de 4 desde x = 0x200. Deja su lugar en t+0x12/t+0x14 y marca las celdas como ocupadas;
   avisa si el ancho o el alto no son multiplos de 16 y se cuelga si no hay lugar. Devuelve lo que queda en
   v0. */
s32 func_8001A228(u8 *t, s32 w) {
    u32 tw = *(s16 *)(t + 8) & 0xFFFF;
    u32 h = *(s16 *)(t + 0xA) & 0xFFFF;
    u32 fila, col, f2, c2, cfin, ffin;
    s32 off, j, ocupado, v;

    for (fila = 0; fila != 0x18; fila = (fila + 1) & 0xFF) {
        for (col = 0, off = 0; col != 0x7F; col = (col + 1) & 0xFF, off = SUMA_TRAMPA(off, 2)) {
            u32 e = *(u16 *)(D_800656C4 + (fila << 8) + off);
            if ((s32)e < w || e < h) {
                continue;
            }
            cfin = SUMA_TRAMPA(w / 16, col) & 0xFF;
            if (tw & 0xF) {
                printf(D_8006562C, tw, *(s32 *)(t + 4));
            }
            ffin = SUMA_TRAMPA((s32)h / 16, fila) & 0xFF;
            if (h & 0xF) {
                printf(D_80065654, h, *(s32 *)(t + 4));
            }
            ocupado = 0;
            for (f2 = fila & 0xFF; f2 != ffin; f2 = (f2 + 1) & 0xFF) {
                for (c2 = col & 0xFF, j = col * 2; c2 != cfin; c2 = (c2 + 1) & 0xFF, j = SUMA_TRAMPA(j, 2)) {
                    if (*(u16 *)(D_800656C4 + (f2 << 8) + j) == 0) {
                        ocupado = 1;
                    }
                }
            }
            if (ocupado) {
                continue;
            }
            *(s16 *)(t + 0x12) = SUMA_TRAMPA(col * 4, 0x200);
            v = fila << 4;
            *(s16 *)(t + 0x14) = v;
            while (fila != ffin) {
                for (c2 = col & 0xFF, j = col * 2; c2 != cfin; c2 = (c2 + 1) & 0xFF, j = SUMA_TRAMPA(j, 2)) {
                    *(u16 *)(D_800656C4 + (fila << 8) + j) = 0;
                }
                v = fila + 1;
                fila = v & 0xFF;
            }
            return v;
        }
    }
    printf(D_8006567C);
    for (;;) {
    }
}
