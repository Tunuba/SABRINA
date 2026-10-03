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

/* Arma el cuadro siguiente de la textura n y lo sube, si le toca. Lo que devuelve es lo que queda en v0
 * en el original: el TexCiclo si la subio, o la cuenta de espera ya sumada (sin recortar a 8 bits). */
s32 func_80022BCC(s32 n) {
    s32 c;
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
        t = D_8008AF74[n];
        t->fase = fase + 1;
        return (s32) t;
    } else {
        c = D_8007CB14[n] + 1;
        D_8007CB14[n] = c;
        return c;
    }
}

extern void *Reservar(s32 tam, char *archivo, s32 linea);
extern char D_8006C478[];            /* "TexAnima.c" */
extern void func_80012ECC(Rect *r, void *datos);   /* StoreImage */
extern s32 func_80012D74(s32 modo);  /* DrawSync */

#define CICLO ((u8 *)D_8008AF74[(u8)D_8007CB10])

/* Agrega una textura animada para el pedazo de VRAM de t (x, y en 0x12/0x14, ancho en 0x8 en pixeles de
 * 4 bits, alto en 0xA): guarda su imagen y las 6 filas de abajo. Devuelve la nueva cuenta (queda en v0). */
s32 func_80022614(u8 *t) {
    D_8008AF60[(u8)D_8007CB10] = Reservar(0x1388, D_8006C478, 0x3F);
    D_8008AF74[(u8)D_8007CB10] = Reservar(0x18, D_8006C478, 0x40);
    *(u16 *)(CICLO + 0) = *(u16 *)(t + 0x12);
    *(u16 *)(CICLO + 2) = *(u16 *)(t + 0x14);
    CICLO[4] = *(s16 *)(t + 8) / 4;
    CICLO[5] = *(s16 *)(t + 0xA);
    *(u16 *)(CICLO + 0xC) = *(u16 *)(CICLO + 0);
    *(u16 *)(CICLO + 0xE) = *(u16 *)(CICLO + 2);
    *(s16 *)(CICLO + 0x10) = CICLO[4];
    *(s16 *)(CICLO + 0x12) = CICLO[5];
    *(void **)(CICLO + 8) = Reservar(CICLO[4] * SUMA_TRAMPA(CICLO[5], 6) * 4, D_8006C478, 0x4C);
    func_80012ECC((Rect *)(CICLO + 0xC), *(void **)(CICLO + 8));
    func_80012D74(0);
    *(s16 *)(CICLO + 0x12) = 6;
    func_80012ECC((Rect *)(CICLO + 0xC), (void *)SUMA_TRAMPA(*(s32 *)(CICLO + 8), 0x480));
    func_80012D74(0);
    *(s16 *)(CICLO + 0x12) = CICLO[5];
    CICLO[0x14] = 0;
    CICLO[0x15] = 0;
    CICLO[0x16] = 0;
    return (u8)D_8007CB10++ + 1;
}

/* Como func_80022614 pero sin las 6 filas de abajo y con 0x14 en 1. Devuelve la nueva cuenta. */
s32 func_80022918(u8 *t) {
    D_8008AF60[(u8)D_8007CB10] = Reservar(0x1388, D_8006C478, 0x63);
    D_8008AF74[(u8)D_8007CB10] = Reservar(0x18, D_8006C478, 0x64);
    *(u16 *)(CICLO + 0) = *(u16 *)(t + 0x12);
    *(u16 *)(CICLO + 2) = *(u16 *)(t + 0x14);
    CICLO[4] = *(s16 *)(t + 8) / 4;
    CICLO[5] = *(s16 *)(t + 0xA);
    *(u16 *)(CICLO + 0xC) = *(u16 *)(CICLO + 0);
    *(u16 *)(CICLO + 0xE) = *(u16 *)(CICLO + 2);
    *(s16 *)(CICLO + 0x10) = CICLO[4];
    *(s16 *)(CICLO + 0x12) = CICLO[5];
    *(void **)(CICLO + 8) = Reservar(CICLO[4] * SUMA_TRAMPA(CICLO[5], 6) * 4, D_8006C478, 0x70);
    func_80012ECC((Rect *)(CICLO + 0xC), *(void **)(CICLO + 8));
    func_80012D74(0);
    *(s16 *)(CICLO + 0x12) = CICLO[5];
    CICLO[0x14] = 1;
    CICLO[0x15] = 0;
    CICLO[0x16] = 0;
    return (u8)D_8007CB10++ + 1;
}
