#include "juego.h"

/* Animacion de paletas (CLUT): hasta cinco a la vez. Cada una tiene una tabla de colores de 48 filas de
 * 6 palabras (12 colores de 16 bits por fila) y una copia de trabajo que se sube a la VRAM girada: la
 * fila de arriba de la copia es la fila `fase` de la tabla, y en cada paso la fase avanza de a 3. */

typedef struct {
    s16 x, y, w, h;
} RectVram;

typedef struct {
    u8 _00[8];
    u32 *colores;                    /* 0x08, 48 filas de 6 palabras */
    RectVram rect;                   /* 0x0C, donde va la paleta en la VRAM */
    u8 tipo;                         /* 0x14, que funcion de D_8007C80C la actualiza */
    u8 fase;                         /* 0x15, fila de la tabla que va arriba */
} PaletaAnim;
EN(PaletaAnim, colores, 0x08);
EN(PaletaAnim, rect, 0x0C);
EN(PaletaAnim, tipo, 0x14);
EN(PaletaAnim, fase, 0x15);

typedef void (*FuncPaleta)(s32);

extern u32 *D_8008AF60[5];           /* copia de trabajo de cada paleta; 0 = ranura libre */
extern PaletaAnim *D_8008AF74[5];
extern FuncPaleta D_8007C80C[];      /* por tipo */

s32 SubirAVRAM(RectVram *r, u32 *datos);

/* Arma la copia girada de la paleta n, la sube y avanza la fase 3 filas. El siguiente de la fila se saca
 * con & 0x2F, no con % 48: de la fila 15 se pasa a la 0 y de la 47 a la 32 (asi esta en el juego). */
void func_80022D4C(s32 n) {
    PaletaAnim *p = D_8008AF74[n];
    u32 *src = p->colores;
    u32 *dst = D_8008AF60[n];
    u8 fila = p->fase;
    u8 i, k;

    for (i = 0; i != 0x30; i++) {
        for (k = 0; k != 6; k++) {
            *dst++ = src[fila * 6 + k];
        }
        fila = (u8)(fila + 1) & 0x2F;
    }
    SubirAVRAM(&D_8008AF74[n]->rect, D_8008AF60[n]);
    D_8008AF74[n]->fase += 3;
}

/* Actualiza las paletas animadas que estan en uso, cada una con la funcion de su tipo. */
void func_80022E58(void) {
    u8 n;

    for (n = 0; n != 5; n++) {
        if (D_8008AF60[n] != NULL) {
            D_8007C80C[D_8008AF74[n]->tipo](n);
        }
    }
}
