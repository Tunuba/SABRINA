#include "juego.h"

/* Los menus: moverse por las opciones con arriba y abajo, elegir y volver. */

typedef void (*FuncOpcion)(s32 a, s32 b, s32 c);
typedef void (*FuncVolver)(void);

extern FuncOpcion *D_80075690[];     /* por menu: la funcion de cada opcion */
extern FuncVolver D_800756B8[];      /* por menu: volver */
extern u16 D_800756E0[];             /* por menu: lo que se muestra */
extern u16 D_800756F4[];             /* por menu: cuantas opciones no se pueden elegir al final */
extern u8 D_800C86C6[];              /* partida: 1 si el nivel se visito (0x141 bytes por nivel) */
extern u8 D_8007C7AC;                /* 1 si la opcion elegida no cambio de menu */
extern u16 D_8007CA14;               /* distinto de 0: la opcion abierta recibe los botones */
extern s32 D_8007CA18;               /* primer nivel del menu de niveles */
extern u16 D_8007CA1C;               /* el menu actual */
extern u16 D_8007CA1E;               /* la opcion actual */
extern u16 D_8007CA20;
extern u16 D_8007CA22;               /* cuantas opciones hay */
extern s32 D_8007CA34;
extern s32 D_8007CA58;               /* botones recien apretados */
extern s32 TocarSonido(s32 prog, s32 tono, s32 nota, s32 prioridad);

/* En el menu 5 (niveles) no se puede quedar en un nivel no visitado: vuelve atras con el sonido de
 * error. */
static void revisar_nivel(s32 atras) {
    if (D_800C86C6[(D_8007CA18 + D_8007CA1E) * 0x141] == 0) {
        TocarSonido(0x30, 0, 0x2A, 0x7F);
        D_8007CA1E = D_8007CA1E + atras;
    } else {
        TocarSonido(0x2E, 0, 0x2A, 0x7F);
    }
}

void func_8001981C(void) {
    u16 n = D_8007CA1C;
    s32 b;

    D_8007CA20 = D_800756E0[n];
    if (D_8007CA14 != 0) {
        D_80075690[n][D_8007CA1E](n, n * 2, n);
        b = D_8007CA58;
        if (b & 0x40) {
            D_8007CA14 = 0;
        }
        if (b & 0x10) {
            D_8007CA14 = 0;
        }
        return;
    }
    if (D_8007CA58 & 0x4000) {
        if (D_8007CA1E == D_8007CA22 - D_800756F4[n]) {
            TocarSonido(0x30, 0, 0x2A, 0x7F);
        } else {
            D_8007CA1E = D_8007CA1E + 1;
            if (n == 5) {
                revisar_nivel(-1);
            } else {
                TocarSonido(0x2E, 0, 0x2A, 0x7F);
            }
        }
    }
    if (D_8007CA58 & 0x1000) {
        if (D_8007CA1E == 0) {
            TocarSonido(0x30, 0, 0x2A, 0x7F);
        } else {
            D_8007CA1E = D_8007CA1E - 1;
            if (D_8007CA1C == 5) {
                revisar_nivel(1);
            } else {
                TocarSonido(0x2E, 0, 0x2A, 0x7F);
            }
        }
    }
    if (D_8007CA58 & 0x40) {
        D_8007C7AC = 1;
        D_80075690[D_8007CA1C][D_8007CA1E](D_8007CA1C * 4, 0, 0);
        if (D_8007C7AC == 1) {
            TocarSonido(0x2F, 0, 0x2A, 0x7F);
        }
    }
    if (D_8007CA58 & 0x10) {
        TocarSonido(0x30, 0, 0x2A, 0x7F);
        D_800756B8[D_8007CA1C]();
    }
    if (D_8007CA58 & 0x800) {
        if (D_8007CA34 == 1 && (D_8007CA1C == 7 || D_8007CA1C == 0)) {
            TocarSonido(0x30, 0, 0x2A, 0x7F);
            D_800756B8[D_8007CA1C]();
            D_8007CA34 = 0;
        }
    } else if (D_8007CA34 == 2) {
        D_8007CA34 = 1;
    }
}
