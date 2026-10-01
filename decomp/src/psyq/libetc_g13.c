#include "juego.h"

/* libetc: prender o apagar el aviso de un canal de interrupciones. */

extern s32 D_8006391C[];             /* por canal, su funcion; D_8006391C[-1] (u16) distinto de 0: iniciado */
extern u16 *D_800649A8;              /* la mascara de interrupciones */
extern void ChangeClearPAD(s32 a);
extern void ChangeClearRCnt(s32 cuenta, s32 a);

/* Pone f como funcion del canal; si cambia, ajusta la mascara (con las interrupciones apagadas mientras) y
 * le dice a los mandos y a los contadores si tienen que limpiar solos. Devuelve la que habia. */
s32 func_8001668C(s32 canal, s32 f) {
    s32 *p = &D_8006391C[canal];
    s32 antes = *p;
    u16 *base = (u16 *)(D_8006391C - 1);
    u32 m;
    s32 b;

    if (f == antes) {
        return antes;
    }
    if (*base == 0) {
        return antes;
    }
    m = *D_800649A8;
    *D_800649A8 = 0;
    if (f != 0) {
        b = 1 << canal;
        *p = f;
        m |= b;
        base[0x30 / 2] |= b;
    } else {
        b = ~(1 << canal);
        *p = 0;
        m &= b;
        *(u16 *)((u8 *)D_8006391C + 0x2C) &= b;
    }
    if (canal == 0) {
        ChangeClearPAD(f == 0);
        ChangeClearRCnt(3, f == 0);
    }
    if (canal == 4) {
        ChangeClearRCnt(0, f == 0);
    }
    if (canal == 5) {
        ChangeClearRCnt(1, f == 0);
    }
    if (canal == 6) {
        ChangeClearRCnt(2, f == 0);
    }
    *D_800649A8 = m;
    return antes;
}

/* Pone en cero n palabras desde p. Devuelve -1 (lo que queda de la cuenta). */
s32 func_800168EC(s32 *p, s32 n) {
    while (n-- != 0) {
        *p++ = 0;
    }
    return -1;
}

/* La tabla de funciones del modulo de interrupciones de libetc. */
typedef s32 (*FuncInt)(s32 a, s32 b, s32 c, s32 d);
extern FuncInt *D_800649A0;
extern s32 D_800649C0[8];            /* las funciones de cada vuelta de la pantalla */
extern volatile s32 *D_800649E0;
extern s32 D_800649EC;               /* cuantas vueltas van */
extern volatile s32 *D_800649F0;     /* DICR */
extern s32 D_800649F4[8];            /* una funcion por canal de DMA */
extern s32 func_80016A2C(void);
extern void func_80016A98(void);
extern s32 func_80016B4C(void);
extern void func_80016CCC(void);

/* ResetCallback, InterruptCallback y la entrada 5 de la tabla: pasan los argumentos tal cual. */
s32 func_80016910(s32 a, s32 b, s32 c, s32 d) {
    return D_800649A0[3](a, b, c, d);
}

s32 func_80016940(s32 a, s32 b, s32 c, s32 d) {
    return D_800649A0[2](a, b, c, d);
}

s32 func_800169A0(s32 f) {
    return D_800649A0[5](4, f, 0, 0);
}

/* Pone en cero n palabras desde p. Devuelve -1. */
s32 func_80016AC4(s32 *p, s32 n) {
    while (n-- != 0) {
        *p++ = 0;
    }
    return -1;
}

s32 func_80016D78(s32 *p, s32 n) {
    while (n-- != 0) {
        *p++ = 0;
    }
    return -1;
}

/* Arranca las funciones de cada vuelta: sin ninguna, la cuenta en cero y su manejador en el canal 0. */
void *func_80016AF4(void) {
    *D_800649E0 = 0x100;
    D_800649EC = 0;
    func_80016AC4(D_800649C0, 8);
    func_80016940(0, (s32)func_80016A2C, 0, 0);
    return func_80016A98;
}

/* Arranca las funciones de DMA: ninguna, DICR en cero y su manejador en el canal 3. */
void *func_80016DA0(void) {
    func_80016D78(D_800649F4, 8);
    *D_800649F0 = 0;
    func_80016940(3, (s32)func_80016B4C, 0, 0);
    return func_80016CCC;
}

extern u8 D_80063918[];              /* el estado del modulo de interrupciones (0x41A palabras) */
extern u8 D_80063954[];              /* su pila (D_80063954 + 0xFDC es el tope) */
extern u16 *D_800649A4;
extern s32 *D_800649AC;
extern s32 func_80016170(void *jmp);  /* setjmp */
extern void func_800164BC(void);
extern void HookEntryInt(void *jmp);
extern void func_800142FC(void);
extern void func_800143F4(void);

/* Inicia el modulo de interrupciones (una sola vez): apaga y limpia, guarda el punto de vuelta, pone la pila
 * y el manejador, y arranca las funciones de cada vuelta y de DMA. Devuelve el estado, o NULL si ya estaba. */
u8 *func_800163E4(void) {
    if (*(u16 *)D_80063918 != 0) {
        return NULL;
    }
    *D_800649A8 = 0;
    *D_800649A4 = *D_800649A8;
    *D_800649AC = 0x33333333;
    func_800168EC((s32 *)D_80063918, 0x41A);
    if (func_80016170(D_80063918 + 0x38) != 0) {
        func_800164BC();
    }
    *(u8 **)D_80063954 = D_80063954 + 0xFDC;
    HookEntryInt(D_80063954 - 4);
    *(s16 *)(D_80063954 - 0x3C) = 1;
    ((s32 *)D_800649A0)[5] = (s32)func_80016AF4();
    ((s32 *)D_800649A0)[1] = (s32)func_80016DA0();
    func_800142FC();
    func_800143F4();
    return D_80063954 - 0x3C;
}
