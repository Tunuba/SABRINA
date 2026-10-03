#include "objeto.h"

/* Un objeto que atrapa a otros (los guarda en una lista en su zona extra). */

extern u8 *CrearParticula(s32 tipo, Objeto *o, s32 b, s32 x, s32 y, s32 z, s32 dx, s32 dy, s32 dz, s32 c,
                          s32 d, s32 e, s32 f, s32 g, s32 h);
extern s32 func_80021CE4(s32 n);     /* al azar */
extern void func_80048468(u8 *a, u8 *o);
extern s32 func_80014AEC(s32 x);
extern s32 TocarSonido(s32 prog, s32 tono, s32 nota, s32 prioridad);
extern s32 func_80024DE4(), func_80024DF4(), func_80024F6C(), func_80024F74(), func_80024F84();
extern s32 thunk_FUN_8001e588();

#define C16(p, d) (*(s16 *)((u8 *)(p) + (d)))
#define C32(p, d) (*(s32 *)((u8 *)(p) + (d)))

/* o atrapa a a (salvo los tipos 0x1C y 1, los marcados 0x8000 y los que ya tiene): si a esta marcado 0x200
 * suelta un abanico de particulas y o pasa al estado 3; si no, lo atrapa (si a no estaba quieto le cambia
 * las funciones por las de objeto atrapado y suena), lo anota con su altura relativa y su 0x58, y o pasa al
 * estado 1. Devuelve lo que el original deja en v0. */
s32 func_80039104(u8 *o, u8 *a) {
    u8 *e = o + 0x74;
    s32 t = *(u16 *)(a + 0x22);
    s32 f;
    s32 i;
    s32 ang;
    s32 r1;

    if (t == 0x1C) {
        return 0x1C;
    }
    if (t == 1) {
        return 1;
    }
    f = C16(a, 0x112);
    if (f & 0x8000) {
        return f & 0x8000;
    }
    for (i = 0; i < C16(e, 0x32); i++) {
        if (a == *(u8 **)(e + 0x14 + i * 4)) {
            return (s32)a;
        }
    }
    if (f & 0x200) {
        for (ang = 0; ang < 0x1000; ang = SUMA_TRAMPA(ang, func_80021CE4(0x64) + 0x32)) {
            r1 = func_80021CE4(-0x1999);
            CrearParticula(6, (Objeto *)o, (s16)ang, 0, -0x1999, 0x8000, 0, r1, func_80021CE4(0x1999), 0, 0x51E,
                           0, 0x3E8, 0x214, 0);
        }
        C16(o, 0x70) = 3;
        return 3;
    }
    func_80048468(a, o);
    if (!(C16(a, 0x112) & 1)) {
        C32(a, 0x00) = (s32)func_80024DE4;
        C32(a, 0x04) = (s32)func_80024DF4;
        C32(a, 0x08) = (s32)func_80024F6C;
        C32(a, 0x0C) = (s32)func_80024F74;
        C32(a, 0x10) = (s32)func_80024F84;
        C32(a, 0x14) = (s32)thunk_FUN_8001e588;
        TocarSonido(0x21, 0, 0x2A, 0x7F);
    }
    *(u8 **)(e + 0x14 + C16(e, 0x32) * 4) = a;
    C32(e, C16(e, 0x32) * 4) = func_80014AEC(RESTA_TRAMPA(C32(o, 0x28), C32(a, 0x28)));
    C16(e, 0x28 + C16(e, 0x32) * 2) = C32(a, 0x58);
    C16(e, 0x32) = SUMA_TRAMPA(C16(e, 0x32), 1);
    C16(o, 0x70) = 1;
    return 1;
}
