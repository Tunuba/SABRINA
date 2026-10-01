#include "juego.h"

/* libgpu: la fuente de depuracion (FntOpen). */

typedef struct {
    s16 x, y, w, h;
} RectF;

/* Un flujo de texto de depuracion (0x30 bytes; hay 8 desde D_80063518 - 0x10). */
typedef struct {
    u32 tag;                         /* 0x00, el fondo (TILE) */
    u8 r, g, b, code;                /* 0x04 */
    s16 x, y, w, h;                  /* 0x08 */
    u32 modo[3];                     /* 0x10, DR_MODE */
    s32 n;                           /* 0x1C, cuantas letras caben */
    u8 *letras;                      /* 0x20, sus SPRT_8 (0x10 bytes cada uno) */
    char *texto;                     /* 0x24 */
    s32 largo;                       /* 0x28 */
    s32 sin_fondo;                   /* 0x2C */
} FlujoTexto;

extern s32 D_80062AF8;               /* cuantos flujos hay */
extern s32 D_80063500;               /* letras ya repartidas */
extern u8 D_80063518[];              /* el modo del primer flujo */
extern char D_8007ED9C[];            /* el texto de todos (0x400) */
extern u8 D_8007F19C[];              /* las letras de todos */
extern u16 D_8008319C;               /* la pagina de la fuente */
extern u16 D_800831A0;               /* su paleta */

extern void SetDrawMode(void *p, s32 dfe, s32 dtd, s32 tpage, RectF *tw);
extern void func_800141AC(void *p);  /* SetTile */
extern void func_800140DC(void *p, s32 semi);  /* SetSemiTrans */
extern void func_8001416C(void *p);  /* SetSprt8 */

#define FLUJOS ((FlujoTexto *)(D_80063518 - 0x10))

/* Abre un flujo en (x, y) de w por h con hasta n letras (las que queden de 0x400). Con fondo != 0 lleva
 * un rectangulo negro (semitransparente si es 2). Devuelve el numero del flujo, o -1 si ya hay 8. */
s32 func_80010920(s32 x, s32 y, s32 w, s32 h, s32 fondo, s32 n) {
    RectF tw;
    u8 *s;
    s32 i, k;

    if (D_80062AF8 >= 8) {
        return -1;
    }
    if (D_80062AF8 == 0) {
        D_80063500 = 0;
    }
    FLUJOS[D_80062AF8].sin_fondo = w == 0;
    if (D_80063500 + n > 0x400) {
        n = 0x400 - D_80063500;
    }
    tw.w = 0x100;
    tw.h = 0x100;
    tw.x = 0;
    tw.y = 0;
    SetDrawMode(FLUJOS[D_80062AF8].modo, 0, 0, D_8008319C, &tw);
    if (fondo != 0) {
        func_800141AC(&FLUJOS[D_80062AF8]);
        FLUJOS[D_80062AF8].r = 0;
        FLUJOS[D_80062AF8].g = 0;
        FLUJOS[D_80062AF8].b = 0;
        func_800140DC(&FLUJOS[D_80062AF8], fondo == 2);
    }
    k = D_80062AF8;
    i = D_80063500;
    FLUJOS[k].x = x;
    FLUJOS[k].y = y;
    FLUJOS[k].w = w;
    FLUJOS[k].h = h;
    FLUJOS[k].n = n;
    FLUJOS[k].largo = 0;
    FLUJOS[k].texto = &D_8007ED9C[i];
    FLUJOS[k].letras = &D_8007F19C[i * 0x10];
    FLUJOS[k].texto[0] = 0;
    s = FLUJOS[D_80062AF8].letras;
    for (i = 0; i < n; i++) {
        func_8001416C(s);
        *(u16 *)(s + 0xE) = D_800831A0;
        s += 0x10;
    }
    /* se relee: con el flujo -1 el largo de arriba cae justo en D_80063500 */
    D_80063500 = *(volatile s32 *)&D_80063500 + n;
    return D_80062AF8++;
}
