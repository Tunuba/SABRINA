#include "objeto.h"

/* Un enemigo fijo que gira hacia Sabrina y dispara cada tanto. */

extern u8 *CrearParticula(s32 tipo, Objeto *o, s32 b, s32 x, s32 y, s32 z, s32 dx, s32 dy, s32 dz, s32 c,
                          s32 d, s32 e, s32 f, s32 g, s32 h);
extern Objeto *func_800252A0(s32 clase, Objeto *padre, s32 x, s32 y, s32 z, s32 vx, s32 vy, s32 vz, s32 rx,
                             s32 ry, s32 rz, s32 a, s32 b);
extern s32 func_8002218C(u8 *o, s32 x, s32 z);        /* angulo hacia un punto */
extern s32 func_80021D44(s16 *ang, s32 hacia, s32 paso);
extern void func_8002205C(s32 *v, s32 a, s32 ang);
extern void func_8001C45C(s32 *v);
extern void func_800249CC(Objeto *o, s32 n);
extern s32 func_80048228(u8 *o, s32 a);
extern s32 func_80038154(), func_80024F6C();

#define C16(p, d) (*(s16 *)((u8 *)(p) + (d)))
#define C32(p, d) (*(s32 *)((u8 *)(p) + (d)))

/* Zona extra: 0 la espera entre tiros, 8 la cuenta, 0xC si ya no esta (pasa al estado 3, que lo deshace).
 * Estado 0 espera a que la cuenta arranque; 1 gira hacia Sabrina mientras cuenta; 2 dispara (un objeto de
 * la clase 5 hacia donde mira, con humo) y vuelve a 1. Devuelve lo que el original deja en v0. */
s32 func_800552C0(u8 *o) {
    u8 *e = o + 0x74;
    s32 v[3];
    s32 st;
    s32 i, k, a, b;
    Objeto *h;
    u8 *he;
    u8 *r;

    C16(C32(o, 0x6C), 0x1A) = 2;
    if (C32(e, 0xC) != 0) {
        C16(o, 0x70) = 3;
    }
    st = C16(o, 0x70);
    switch (st) {
    case 3:
        return func_80048228(o, 0);
    case 0:
        if (C32(e, 8) == 0) {
            return 0;
        }
        C16(o, 0x70) = 1;
        return 1;
    case 1:
        if (C32(e, 8) <= 0) {
            C16(o, 0x70) = 2;
        } else {
            C32(e, 8) = SUMA_TRAMPA(C32(e, 8), -1);
        }
        return func_80021D44((s16 *)(o + 0x32), (s16)func_8002218C(o, p_sabrina->x, p_sabrina->z), 0x7D);
    case 2:
        break;
    default:
        return st;
    }
    C32(e, 8) = C32(e, 0);
    C16(o, 0x70) = 1;
    h = func_800252A0(5, (Objeto *)o, 0, 0xFFFE8000, 0xC000, 0, 0xFFFF0000, 0x20000, 0, 0, 0, 1, (s32)o);
    func_8002205C(v, 0, C16(o, 0x32));
    func_8001C45C(v);
    v[0] <<= 1;
    v[1] <<= 1;
    v[2] <<= 1;
    he = (u8 *)h + 0x74;
    C32(h, 0x38) = v[0];
    C32(h, 0x3C) = v[1];
    C32(h, 0x40) = v[2];
    C32(he, 8) = 0xC8;
    C32(he, 0xC) = (s32)o;
    C32(h, 0) = (s32)func_80038154;
    C32(h, 8) = (s32)func_80024F6C;
    C16(h, 0x114) |= 2;
    C16(h, 0x112) |= 0x1803;
    func_800249CC(h, 0x2F);
    C32(h, 0x54) = 0x1000;
    C32(h, 0x58) = 0x1000;
    C32(h, 0x5C) = 0x1000;
    for (i = 0, a = 0, b = 0; i < 3; i = SUMA_TRAMPA(i, 1), a = SUMA_TRAMPA(a, 0x80), b = SUMA_TRAMPA(b, 0x100)) {
        k = RESTA_TRAMPA(10, i);
        r = CrearParticula(6, (Objeto *)o, 0, 0, 0, 0, 0, RESTA_TRAMPA(0xFFFF0000, a), SUMA_TRAMPA(b, 0x20000), 0,
                           -(k << 4), -(k << 5), 5, 0, 0);
    }
    return (s32)r;
}
