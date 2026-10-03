#include "juego.h"

/* libsnd: las secuencias (SEQ/SEP). D_800C6EF8 tiene por cada secuencia abierta sus pistas de 0xB0 bytes. */

extern u8 *D_800C6EF8[];
extern void _SsVmSeqKeyOff(s32 cual);
extern void func_80042B68(void);

/* Para la pista n de la secuencia s y la deja como recien cargada: apaga sus notas, borra su estado y pone
   los 16 canales en su volumen y paneo de partida. Devuelve 0x7F (lo que queda en v0). */
s32 func_80041FC8(s32 s, s32 n) {
    s32 d = (s16)n * 0xB0;
    u8 *p = D_800C6EF8[(s16)s] + d;
    s32 i;
    *(s32 *)(p + 0x98) &= ~1;
    *(s32 *)(D_800C6EF8[(s16)s] + d + 0x98) &= ~2;
    *(s32 *)(D_800C6EF8[(s16)s] + d + 0x98) &= ~8;
    *(s32 *)(D_800C6EF8[(s16)s] + d + 0x98) &= ~0x400;
    *(s32 *)(D_800C6EF8[(s16)s] + d + 0x98) |= 4;
    _SsVmSeqKeyOff((s16)(s | (n << 8)));
    func_80042B68();
    p[0x14] = 0;
    *(s32 *)(p + 0x88) = 0;
    p[0x1C] = 0;
    p[0x18] = 0;
    p[0x19] = 0;
    p[0x1E] = 0;
    p[0x1A] = 0;
    p[0x1B] = 0;
    p[0x1F] = 0;
    p[0x17] = 0;
    p[0x21] = 0;
    p[0x1C] = 0;
    p[0x1D] = 0;
    p[0x15] = 0;
    p[0x16] = 0;
    *(s32 *)(p + 0x90) = *(s32 *)(p + 0x84);
    *(s32 *)(p + 0x94) = *(s32 *)(p + 0x8C);
    *(u16 *)(p + 0x54) = *(u16 *)(p + 0x56);
    *(s32 *)(p + 0) = *(s32 *)(p + 4);
    *(s32 *)(p + 8) = *(s32 *)(p + 4);
    for (i = 0; i < 0x10; i++) {
        p[0x37 + i] = i;
        p[0x27 + i] = 0x40;
        *(s16 *)(p + 0x60 + i * 2) = 0x7F;
    }
    *(s16 *)(p + 0x5C) = 0x7F;
    *(s16 *)(p + 0x5E) = 0x7F;
    return 0x7F;
}

extern s32 D_800754E8;
extern s32 (*D_800754FC)(void);      /* SsSeqCalledTbyT */

/* Llamada de cada interrupcion: la secuencia avanza una de cada dos. Devuelve lo que queda en v0. */
s32 func_80041F54(void) {
    if (D_800754E8 == 0) {
        D_800754E8 = 1;
        return 1;
    }
    D_800754E8 = 0;
    return D_800754FC();
}
