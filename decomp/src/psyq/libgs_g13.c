#include "juego.h"

/* libgs: el arranque de las matrices y la pantalla (GsInitGraph / GsInit3D). */

extern s32 D_80084C48, D_80084C4C;   /* ancho y alto */
extern s16 D_80084C90[16];           /* la matriz identidad (0x20 bytes) */
extern s32 D_80084CB0[8];            /* la de la camara */
extern s32 D_80084C50[8];            /* la de las luces */
extern s32 D_80084C70[8];            /* la del color de las luces */
extern s16 D_80084C30[2], D_80084C34[2], D_80084C38[2], D_80084C3C[4];
extern u8 D_80084B8C[0x20];
extern s32 D_80084C44;

/* Devuelve 1. */
s32 func_80016F38(s32 ancho, s32 alto) {
    s32 *m = (s32 *)D_80084C90;
    s32 r, i;

    D_80084C48 = ancho & 0xFFFF;
    D_80084C4C = alto & 0xFFFF;
    r = (D_80084C4C << 14) / D_80084C48;
    D_80084C90[2] = 0;
    D_80084C90[1] = 0;
    D_80084C90[5] = 0;
    D_80084C90[3] = 0;
    D_80084C90[7] = 0;
    D_80084C90[6] = 0;
    m[7] = 0;
    m[6] = 0;
    m[5] = 0;
    D_80084C90[0] = 0x1000;
    D_80084C90[4] = 0x1000;
    D_80084C90[8] = 0x1000;
    for (i = 0; i < 8; i++) {
        D_80084CB0[i] = m[i];
    }
    for (i = 0; i < 8; i++) {
        D_80084C50[i] = m[i];
    }
    ((s16 *)D_80084C50)[8] = 0;
    ((s16 *)D_80084C50)[4] = 0;
    ((s16 *)D_80084C50)[0] = 0;
    for (i = 0; i < 8; i++) {
        D_80084C70[i] = D_80084C50[i];
    }
    D_80084C30[0] = 0;
    D_80084C30[1] = 0;
    D_80084C34[0] = 0;
    D_80084C34[1] = 0;
    D_80084C38[1] = 0;
    D_80084C38[0] = 0;
    D_80084C3C[1] = 0;
    ((s16 *)D_80084CB0)[4] = r / 3;
    D_80084C3C[0] = 0;
    D_80084B8C[3] = 3;
    D_80084B8C[7] = 2;
    D_80084B8C[0x13] = 3;
    D_80084B8C[0x17] = 2;
    D_80084C44 = 1;
    D_80084C3C[2] = D_80084C48;
    D_80084C3C[3] = D_80084C4C;
    return 1;
}
