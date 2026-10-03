#include "objeto.h"

/* Un objeto que espera, salta hacia Sabrina y cae (con humo o rebote segun sus banderas). */

extern u8 *CrearParticula(s32 tipo, Objeto *o, s32 b, s32 x, s32 y, s32 z, s32 dx, s32 dy, s32 dz, s32 c,
                          s32 d, s32 e, s32 f, s32 g, s32 h);
extern s32 func_80021CE4(s32 n);                      /* al azar */
extern s32 func_8002225C(u8 *o, s32 x, s32 y, s32 z); /* distancia a un punto */
extern s32 func_8002218C(u8 *o, s32 x, s32 z);        /* angulo hacia un punto */
extern s32 func_80021D44(s16 *ang, s32 hacia, s32 paso);
extern s32 func_8002244C(u8 *o, s32 a, s32 b);        /* altura del suelo */
extern void func_800221A8(u8 *o, s32 x, s32 y, s32 z);
extern s32 func_8003BE38(u8 *o);                      /* al tocar el suelo */
extern s32 rsin(s32 a);
extern s32 rcos(s32 a);

#define C8(p, d) (*(u8 *)((u8 *)(p) + (d)))
#define C16(p, d) (*(s16 *)((u8 *)(p) + (d)))
#define C32(p, d) (*(s32 *)((u8 *)(p) + (d)))

/* Zona extra: 0 parametro del suelo, 4 velocidad hacia arriba, 8 velocidad de avance, 0xC banderas
 * (1 solo si Sabrina esta cerca, 2 gira de a poco, 4 apunta a la altura de Sabrina, 0x20 humo al volar,
 * 0x40 espera al azar, 0x80 salto al azar, 0x200 avisa la posicion), 0xE espera, 0x10 cuenta, 0x12 tipo de
 * humo. Estados: 1 en el suelo esperando, 2 apuntando, 3 en el aire. Devuelve lo que el original deja en v0. */
s32 func_8003C9DC(u8 *o) {
    u8 *e = o + 0x74;
    s32 b = C16(e, 0xC);
    s32 st = C16(o, 0x70);
    s32 d, q, w, r1, r2, r3, s;
    s16 ang;

    if (st == 3) {
        s = C32(o, 0x54);
        if (s < 0x1000) {
            C32(o, 0x54) = SUMA_TRAMPA(s, RESTA_TRAMPA(0x1000, s) >> 1);
            if (C32(o, 0x54) >= 0x1000) {
                C32(o, 0x54) = 0x1000;
            }
            C32(o, 0x58) = C32(o, 0x54);
            C32(o, 0x5C) = C32(o, 0x54);
        }
        C32(o, 0x50) = func_8002244C(o, C32(e, 0), 0);
        C32(o, 0x3C) = SUMA_TRAMPA(C32(o, 0x3C), 0x51E);
        C32(o, 0x24) = SUMA_TRAMPA(C32(o, 0x24), C32(o, 0x38));
        C32(o, 0x28) = SUMA_TRAMPA(C32(o, 0x28), C32(o, 0x3C));
        C32(o, 0x2C) = SUMA_TRAMPA(C32(o, 0x2C), C32(o, 0x40));
        if (b & 0x20) {
            r1 = SUMA_TRAMPA(func_80021CE4(0x800), -0x400);
            r2 = SUMA_TRAMPA(func_80021CE4(0x800), -0x400);
            r3 = SUMA_TRAMPA(func_80021CE4(0x800), -0x400);
            CrearParticula((s8)C8(e, 0x12), (Objeto *)o, 0, r1 << 2, r2 << 2, r3 << 2, r1, r2, r3, 0, 0, 0, 7, 2,
                           0);
        }
        if (b & 0x200) {
            func_800221A8(o, SUMA_TRAMPA(C32(o, 0x24), C32(o, 0x38)), SUMA_TRAMPA(C32(o, 0x28), C32(o, 0x3C)),
                          SUMA_TRAMPA(C32(o, 0x2C), C32(o, 0x40)));
        }
        if (C32(o, 0x50) < C32(o, 0x28)) {
            C32(o, 0x28) = C32(o, 0x50);
            return func_8003BE38(o);
        }
        return C32(o, 0x50);
    }
    if (st == 2) {
        d = func_8002225C(o, p_sabrina->x, SUMA_TRAMPA(SUMA_TRAMPA(p_sabrina->y, -0x4001), -0x7FFF), p_sabrina->z);
        if ((b & 1) && d >= 0x80001) {
            return 1;
        }
        ang = func_8002218C(o, p_sabrina->x, p_sabrina->z);
        if (b & 4) {
            if (b & 2) {
                ang = func_80021D44((s16 *)(o + 0x32), ang, 0x14);
            } else {
                C16(o, 0x32) = ang;
            }
            q = d / 0x4444;
            C32(e, 4) = RESTA_TRAMPA(RESTA_TRAMPA(p_sabrina->y, C32(o, 0x28)) / q, (q * 0x51E) >> 1);
        }
        if (b & 2) {
            ang = func_80021D44(&ang, C16(o, 0x32), 0x32);
            if (ang != 0) {
                return ang;
            }
        }
        C32(o, 0x38) = (C32(e, 8) * rsin(C16(o, 0x32))) >> 12;
        C32(o, 0x40) = (C32(e, 8) * rcos(C16(o, 0x32))) >> 12;
        if (b & 0x80) {
            C32(o, 0x3C) = func_80021CE4(C32(e, 4));
        } else {
            C32(o, 0x3C) = C32(e, 4);
        }
        C16(o, 0x70) = 3;
        C8(C32(o, 0x60), 0x64) &= 0xFE;
        C16(o, 0x112) = 0x880;
        return 0x880;
    }
    if (st != 1) {
        return st;
    }
    C16(o, 0x112) = 0;
    C32(o, 0x28) = C32(o, 0x50);
    w = C16(e, 0x10);
    C16(e, 0x10) = SUMA_TRAMPA(w, -1);
    if (w != 0) {
        return SUMA_TRAMPA(w, -1);
    }
    if (b & 0x40) {
        C16(e, 0x10) = func_80021CE4(C16(e, 0xE));
    } else {
        C16(e, 0x10) = C16(e, 0xE);
    }
    C16(o, 0x70) = 2;
    return 2;
}
