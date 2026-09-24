#include "juego.h"

/* Texturas animadas por ciclo: hasta cinco. Cada una tiene un bufer de 48 filas de 24 bytes (D_8008AF60)
 * que se arma desde la imagen original corriendo cada fila, y se sube a la VRAM cada cierta cantidad de
 * cuadros (D_8007CB14 cuenta los cuadros de espera). */

typedef struct {
    s16 x, y, w, h;
} Rect;

typedef struct {
    u8 _00[8];
    u8 *imagen;                      /* 0x08, los pixeles originales, 48 filas de 24 bytes */
    Rect rect;                       /* 0x0C, donde va en la VRAM */
    u8 _14;
    u8 fase;                         /* 0x15, cuanto se corre el ciclo */
} TexCiclo;
EN(TexCiclo, imagen, 0x08);
EN(TexCiclo, rect, 0x0C);
EN(TexCiclo, fase, 0x15);

extern u8 *D_8008AF60[5];            /* bufer de cada textura */
extern TexCiclo *D_8008AF74[5];
extern s8 D_8007CB10;                /* cuantas hay */
extern u8 D_8007CB14[5];             /* 0 = toca subirla en este cuadro */
extern u8 D_8006C484[24];            /* comienzo de cada fila segun la fase */
extern u8 D_8006C49C[];              /* desplazamiento de cada columna */

extern void Liberar(void *p);
extern void SubirAVRAM(Rect *r, void *datos);  /* LoadImage */

void func_80022528(void) {
    u8 i;
    s32 k;

    for (i = 0, k = 0; i != 5; i++, k++) {
        D_8008AF60[k] = 0;
    }
    D_8007CB10 = 0;
}

void func_80022564(void) {
    u8 i;

    for (i = 0; i != 5; i++) {
        if (D_8008AF60[i] != 0) {
            Liberar(D_8008AF60[i]);
            if (D_8008AF74[i]->imagen != 0) {
                Liberar(D_8008AF74[i]->imagen);
            }
            Liberar(D_8008AF74[i]);
        }
    }
}

void func_80022BCC(s32 n) {
    u8 *dst;
    u8 *src;
    u8 *p;
    u8 fase;
    u8 fila;
    u8 col;
    u8 j;
    TexCiclo *t;

    dst = D_8008AF60[n];
    if (dst != 0 && D_8007CB14[n] != 0) {
        D_8007CB14[n] = 0;
        t = D_8008AF74[n];
        src = t->imagen;
        fase = t->fase;
        for (fila = 0; fila != 0x30; fila++, src += 0x18) {
            fase = fase % 24;
            p = src + D_8006C484[fase];
            j = fase;
            fase = fase + 1;
            for (col = 0; col != 0x18; col++, j++) {
                *dst++ = p[D_8006C49C[j]];
                p++;
            }
        }
        SubirAVRAM(&D_8008AF74[n]->rect, D_8008AF60[n]);
        D_8008AF74[n]->fase = fase + 1;
    } else {
        D_8007CB14[n]++;
    }
}
