#include "juego.h"

/* Elegir un mundo en el menu. */

extern u16 D_8007CC00;               /* la opcion elegida */
extern s32 D_8007CA18;               /* el primer nivel del mundo */
extern u16 D_8007C7B0[];             /* por opcion: lo que va en D_800756EA */
extern u16 D_800756EA;
extern s8 D_8007CA38;
extern s16 D_8007CA1C;
extern s16 D_8007CA1E;
extern s32 D_8007CB34;
extern char D_8007C798[];            /* el nombre del archivo fuente */
extern void Afirmar(s32 cond, char *archivo, s32 linea);

/* Toma el mundo m (0 a 3: niveles 1, 4, 7 y 10; otro valor es un error) y pide el cambio. Devuelve lo que
 * el original deja en v0. */
s32 func_80019464(s32 m) {
    D_8007CC00 = m;
    D_8007CA18 = 0;
    switch (m) {
    case 0:
        D_8007CA18 = 1;
        break;
    case 1:
        D_8007CA18 = 4;
        break;
    case 2:
        D_8007CA18 = 7;
        break;
    case 3:
        D_8007CA18 = 10;
        break;
    default:
        Afirmar(0, D_8007C798, 0x169);
        break;
    }
    D_800756EA = D_8007C7B0[D_8007CC00];
    D_8007CA38 = 1;
    D_8007CA1C = 5;
    D_8007CA1E = 0;
    D_8007CB34 = 1;
    return 5;
}
