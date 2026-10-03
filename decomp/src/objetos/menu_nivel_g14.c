#include "juego.h"

/* Entrar a un nivel desde el menu de seleccion. */

extern u16 D_8007CC00;               /* la opcion elegida */
extern u16 D_8007C8D8[];             /* el nivel de cada opcion */
extern s8 D_800C86C6[];              /* por nivel (0x141 bytes cada uno): si esta abierto */
extern s16 jugando;
extern s8 nivel_actual;
extern s8 D_8007CA01;                /* el nivel de antes */
extern s8 D_8007CA38;
extern s32 D_8007CB34;
extern s8 D_8007C7AC;
extern s32 D_8007CC04;
extern s32 TocarSonido(s32, s32, s32, s32);

/* Si el nivel (el de la opcion mas mas) esta abierto, sale del nivel actual hacia el; si no, suena el
 * aviso. Devuelve lo que el original deja en v0. */
static inline s32 entrar(s32 n) {
    s32 r;
    if (D_800C86C6[n * 0x141] != 0) {
        r = nivel_actual;
        jugando = 0;
        D_8007CA01 = r;
        nivel_actual = n;
        D_8007CA38 = 0;
        D_8007CB34 = 0;
    } else {
        r = TocarSonido(0x30, 0, 0x2A, 0x7F);
        D_8007C7AC = 0;
    }
    D_8007CC04 = 0;
    return r;
}

s32 func_80046ED8(void) {
    return entrar(D_8007C8D8[D_8007CC00] + 2);
}

s32 func_80046F74(void) {
    return entrar(D_8007C8D8[D_8007CC00] + 1);
}
