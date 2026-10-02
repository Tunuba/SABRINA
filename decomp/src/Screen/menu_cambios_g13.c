#include "juego.h"

/* Cambios de menu: guardan el menu y la opcion actuales para volver y abren otro. Devuelven lo que queda
   en v0 (el ultimo valor cargado o puesto). */

extern u16 D_8007CA1C;               /* el menu actual */
extern u16 D_8007CA1E;               /* la opcion actual */
extern u16 D_8007CBF8, D_8007CBFA;   /* la opcion guardada (dos lugares) */
extern u8 D_8007CBFC, D_8007CBFD;    /* el menu guardado (dos lugares) */

static s32 abrir(s32 menu) {
    D_8007CBF8 = D_8007CA1E;
    D_8007CA1E = 0;
    D_8007CBFC = D_8007CA1C;
    D_8007CA1C = menu;
    return menu;
}

s32 func_80046B2C(void) {
    return abrir(4);
}

s32 func_80046B6C(void) {
    return abrir(1);
}

s32 func_800471A8(void) {
    return abrir(8);
}

/* Vuelve al menu guardado en el primer lugar. */
s32 func_80046BAC(void) {
    D_8007CA1C = D_8007CBFC;
    D_8007CA1E = D_8007CBF8;
    return D_8007CBF8;
}

/* Lo mismo que func_80046BAC (otra entrada de la tabla). */
s32 func_80046EC0(void) {
    D_8007CA1C = D_8007CBFC;
    D_8007CA1E = D_8007CBF8;
    return D_8007CBF8;
}

/* Vuelve al menu guardado en el segundo lugar. */
s32 func_80046D54(void) {
    D_8007CA1C = D_8007CBFD;
    D_8007CA1E = D_8007CBFA;
    return D_8007CBFA;
}

extern s32 D_8006C444, D_8006C448, D_8006C44C, D_8006C450, D_8006C454, D_8006C458, D_8006C45C, D_8006C460,
    D_8006C464;
extern s16 D_8007CA20;

/* Abre el menu 7 con su camara de partida. */
s32 func_80048024(void) {
    D_8007CA1C = 7;
    D_8006C444 = 0x300;
    D_8006C448 = -0x28E;
    D_8006C44C = -0xB4;
    D_8006C450 = -0x1000;
    D_8006C454 = 0x400;
    D_8006C458 = 0;
    D_8006C45C = 0;
    D_8006C460 = 0x1000;
    D_8007CA20 = 0;
    D_8006C464 = 0;
    return 0x1000;
}
