#include "juego.h"

/* libsnd: el reloj de la secuencia de musica (SsSetTickMode y compania). */

extern s8 D_80075504[3];             /* [0] usar la vuelta de la pantalla, [1] cuenta, [2] canal */
extern s32 D_800754F8;               /* distinto de 0: no tocar el reloj */
#define MODO (*(s32 *)((u8 *)D_80075504 - 0x10))       /* el modo, o el tempo pedido (0x800754F4) */
#define PROPIA (*(s32 *)((u8 *)D_80075504 - 8))       /* la funcion propia de cada vuelta */
#define VIEJA (*(s32 *)((u8 *)D_80075504 - 4))        /* la funcion de vuelta que habia */

extern void func_800143E4(void);     /* EnterCriticalSection */
extern s32 func_800143F4(void);      /* ExitCriticalSection */
extern s32 func_80014598(s32 canal);
extern s32 func_800144C4(s32 canal, s32 valor, s32 banderas);
extern s32 func_800169A0(s32 f);
extern s32 func_80016940(s32 canal, s32 f);
extern void func_80041F08(void), func_80041F54(void);

/* Pone el reloj de la musica segun el modo: con la pantalla o con un contador del sistema (a 60 o 120
 * golpes, o al tempo pedido). Devuelve lo que devuelve la ultima llamada. */
s32 func_80041CD8(s32 propio) {
    volatile s32 espera;
    u32 canal = 0xF2000002;
    s32 valor = 0x44E8;

    for (espera = 0x3E6; espera >= 0; espera--) {
    }
    D_80075504[2] = 6;
    D_80075504[0] = 0;
    D_80075504[1] = 0;
    VIEJA = 0;
    switch (MODO) {
    case 2:
        break;
    case 0:
        D_80075504[2] = 0x7F;
        return 0x7F;
    case 3:
        valor = 0x89D0;
        break;
    case 5:
        D_80075504[2] = 0;
        if (propio == 0) {
            D_80075504[0] = 1;
        } else {
            canal = 0xF2000003;
            valor = 1;
        }
        break;
    default:
        if (D_800754F8 != 0) {
            return D_800754F8;
        }
        if (MODO < 0x46) {
            valor = 0x204CC0 / MODO;
            D_80075504[1]++;
        } else {
            valor = 0x409980 / MODO;
        }
        break;
    }
    if (D_80075504[0] != 0) {
        func_800143E4();
        func_800169A0(PROPIA);
    } else {
        func_800143E4();
        func_80014598(canal);
        func_800144C4(canal, valor & 0xFFFF, 0x1000);
        if (D_80075504[2] == 0) {
            VIEJA = func_80016940(0, 0);
            func_80016940(D_80075504[2], (s32)func_80041F08);
        } else {
            func_80016940(D_80075504[2], D_80075504[1] != 0 ? (s32)func_80041F54 : PROPIA);
        }
    }
    return func_800143F4();
}

extern s32 func_80016970(s32 canal, s32 f);

/* Pone f en el canal 4 de interrupciones. */
s32 func_8003EAF8(s32 f) {
    return func_80016970(4, f);
}
