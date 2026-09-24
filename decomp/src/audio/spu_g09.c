#include "juego.h"

extern u16 D_80075508[];             /* multiplicador de cada semitono (12) */
extern u16 D_80075520[];             /* multiplicador de cada fraccion de semitono (128) */
extern u8 D_800C76CC[];              /* marcas de uso */
extern u16 D_800C76DE;               /* cuantos hay en uso */

extern s32 SpuMalloc(s32 tamano);
extern void func_8003FD68(s32 a);

/* Nota a tono del SPU (como _spu_note2pitch de la biblioteca): nota de centro y su fraccion, nota pedida
 * y su fraccion (en 128 avos). Devuelve el tono en 4.12, 0x3FFF desde dos octavas arriba. */
u16 func_800433C0(s32 centro, s32 fcentro, s32 nota, s32 fnota) {
    s16 t = (u8)fnota + fcentro;
    s32 q = t / 128;
    s32 n = centro + q - (u8)nota;
    s32 f = t - (q << 7);
    s32 fr = f;
    s16 nn;
    s32 oct, semi, p, s;

    if ((s16)f < 0) {
        fr = f + 0x80;
        n = n - 1 + (s16)(f + 0x80) / 128;
    }
    nn = n;
    q = nn / 12;
    oct = q - 2;
    semi = nn - q * 12;
    if ((s16)semi < 0) {
        semi += 12;
        oct = q - 3;
    }
    p = (s32)((u32)D_80075508[(s16)semi] * D_80075520[(s16)fr]) >> 16;
    if ((s16)oct >= 0) {
        p = 0x3FFF;
    } else {
        s = -(s16)oct;
        p = (u32)(p + (1 << ((s - 1) & 31))) >> (s & 31);
    }
    return p;
}

/* SpuMalloc; si no hay lugar borra la marca del tercer argumento en D_800C76CC, llama a func_8003FD68(0),
 * descuenta D_800C76DE y devuelve -1. */
s32 func_80044BD4(s32 tamano, s32 a1, s32 indice) {
    s32 r = SpuMalloc(tamano);

    if (r == -1) {
        D_800C76CC[(s16)indice] = 0;
        func_8003FD68(0);
        D_800C76DE--;
        return -1;
    }
    return r;
}
