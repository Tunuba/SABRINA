#include "juego.h"

/* libgpu: el modo de un canal (de a 0x10 bytes desde D_80063824). */

extern u8 *D_80063824;            /* la base de los canales */

/* Arma el modo del canal (0 a 2) con su valor y las banderas: 0x10 y 1 en los canales 0 y 1, 1 en el 2, y
 * 0x1000 en todos. Devuelve 1, o 0 si el canal no existe. */
s32 func_800144C4(s32 canal, s32 valor, s32 banderas) {
    u32 c = canal & 0xFFFF;
    s16 modo = 0x48;

    if ((s32)c >= 3) {
        return 0;
    }
    *(s16 *)(D_80063824 + c * 0x10 + 4) = 0;
    *(s16 *)(D_80063824 + c * 0x10 + 8) = valor;
    if (c < 2) {
        if (banderas & 0x10) {
            modo = 0x49;
        }
        if (!(banderas & 1)) {
            modo |= 0x100;
        }
    } else if (c == 2 && !(banderas & 1)) {
        modo = 0x248;
    }
    if (banderas & 0x1000) {
        modo |= 0x10;
    }
    *(s16 *)(D_80063824 + c * 0x10 + 4) = modo;
    return 1;
}

/* Apaga el canal (0 a 2): borra su modo. Devuelve 1, o 0 si el canal no existe. */
s32 func_80014598(s32 canal) {
    u32 c = canal & 0xFFFF;

    if ((s32)c >= 3) {
        return 0;
    }
    *(s16 *)(D_80063824 + c * 0x10) = 0;
    return 1;
}

/* El modo del canal (0 a 2), o 0 si no existe. */
s32 func_80014560(s32 canal) {
    u32 c = canal & 0xFFFF;

    if ((s32)c >= 3) {
        return 0;
    }
    return *(u16 *)(D_80063824 + c * 0x10);
}
