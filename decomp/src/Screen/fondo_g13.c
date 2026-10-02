#include "juego.h"

/* Una imagen de fondo de 4 filas por 8 columnas de sprites (SPRT de 0x14 bytes, cada uno con su TPAGE),
   sacados de la tabla de 0x20 bytes por pieza de D_8007CB24 (la segunda mitad, salvo en los modos 0x13 y
   0x5F). */

extern u16 D_8007CA20;
extern u8 *D_8007CB24;
extern u8 *D_8007CACC;          /* donde se arma el siguiente sprite */
extern u8 *D_8007CAD0;          /* donde se arma el siguiente TPAGE */
extern s32 AddPrim(void *ot, void *p);
extern void SetDrawTPage(void *p, s32 dfe, s32 dtd, s32 tpage);

/* Devuelve 4 (lo que queda en v0). */
s32 func_80023E3C(u8 *db) {
    u8 *t;
    u32 fila, col;
    u8 *p;
    if (D_8007CA20 == 0x13 || D_8007CA20 == 0x5F) {
        t = D_8007CB24;
    } else {
        t = D_8007CB24 + 0x400;
    }
    for (fila = 0; fila != 4; fila = (fila + 1) & 0xFFFF) {
        for (col = 0; col != 8; col = (col + 1) & 0xFFFF) {
            *(s16 *)(D_8007CACC + 8) = *(s16 *)(t + 8) * col;
            *(s16 *)(D_8007CACC + 0xA) = fila << 6;
            *(s16 *)(D_8007CACC + 0x10) = *(s16 *)(t + 8);
            *(s16 *)(D_8007CACC + 0x12) = *(s16 *)(t + 0xA);
            D_8007CACC[4] = 0xFF;
            D_8007CACC[5] = 0xFF;
            D_8007CACC[6] = 0xFF;
            D_8007CACC[0xD] = t[0x11];
            D_8007CACC[0xC] = t[0x10];
            *(u16 *)(D_8007CACC + 0xE) = *(u16 *)(t + 0xE);
            p = D_8007CACC;
            D_8007CACC = p + 0x14;
            AddPrim(db + 0x190, p);
            SetDrawTPage(D_8007CAD0, 1, 0, *(u16 *)(t + 0xC));
            p = D_8007CAD0;
            D_8007CAD0 = p + 8;
            AddPrim(db + 0x190, p);
            t += 0x20;
        }
    }
    return 4;
}

extern u16 D_8007CC58, D_8007CC5A, D_8007CC50;
extern u8 D_800D50B0[];         /* piezas de 0x20 bytes, como las de D_8007CB24 */
extern u8 *D_8007CAD4;          /* donde se arma el siguiente rectangulo */

/* La fila de iconos del menu (D_8007CC58 + D_8007CC5A, cada uno 26 pixeles a la derecha del anterior desde
   x = 50) y el recuadro rojo sobre el elegido (D_8007CC50). Devuelve lo que queda en v0. */
s32 func_80023FD4(u8 *db) {
    u32 i;
    s32 k, dx;
    u8 *p;
    if (SUMA_TRAMPA(D_8007CC58, D_8007CC5A) == 0) {
        return 0;
    }
    for (i = 0, k = 0, dx = 0; i != SUMA_TRAMPA(D_8007CC58, D_8007CC5A); i = (i + 1) & 0xFFFF) {
        u8 *t = D_800D50B0 + k;
        *(s16 *)(D_8007CACC + 8) = SUMA_TRAMPA(dx, 0x32);
        *(s16 *)(D_8007CACC + 0xA) = 0x64;
        *(s16 *)(D_8007CACC + 0x10) = *(s16 *)(t + 8);
        *(s16 *)(D_8007CACC + 0x12) = *(s16 *)(t + 0xA);
        D_8007CACC[6] = 0xFF;
        D_8007CACC[5] = 0xFF;
        D_8007CACC[4] = 0xFF;
        D_8007CACC[0xD] = t[0x11];
        D_8007CACC[0xC] = t[0x10];
        *(u16 *)(D_8007CACC + 0xE) = *(u16 *)(t + 0xE);
        p = D_8007CACC;
        D_8007CACC = p + 0x14;
        AddPrim(db + 4, p);
        SetDrawTPage(D_8007CAD0, 1, 0, *(u16 *)(t + 0xC));
        p = D_8007CAD0;
        D_8007CAD0 = p + 8;
        AddPrim(db + 4, p);
        k = SUMA_TRAMPA(k, 0x20);
        dx = SUMA_TRAMPA(dx, 0x1A);
    }
    D_8007CAD4[4] = 0xC8;
    D_8007CAD4[5] = 0;
    D_8007CAD4[6] = 0x64;
    *(s16 *)(D_8007CAD4 + 8) = SUMA_TRAMPA(D_8007CC50 * 26, 0x2D);
    *(s16 *)(D_8007CAD4 + 0xA) = 0x5F;
    *(s16 *)(D_8007CAD4 + 0xC) = 0x1A;
    *(s16 *)(D_8007CAD4 + 0xE) = 0x1A;
    p = D_8007CAD4;
    D_8007CAD4 = p + 0x10;
    return AddPrim(db + 8, p);
}
