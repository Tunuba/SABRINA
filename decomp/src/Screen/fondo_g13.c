#include "juego.h"

/* Una imagen de fondo de 4 filas por 8 columnas de sprites (SPRT de 0x14 bytes, cada uno con su TPAGE),
   sacados de la tabla de 0x20 bytes por pieza de D_8007CB24 (la segunda mitad, salvo en los modos 0x13 y
   0x5F). */

extern u16 D_8007CA20;
extern u8 *D_8007CB24;
extern u8 *D_8007CACC;          /* donde se arma el siguiente sprite */
extern u8 *D_8007CAD0;          /* donde se arma el siguiente TPAGE */
extern void AddPrim(void *ot, void *p);
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
