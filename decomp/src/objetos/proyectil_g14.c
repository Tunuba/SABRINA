#include "objeto.h"

/* Un proyectil que vuela un rato (persiguiendo a Sabrina o derecho) y se deshace en particulas. */

extern u8 *CrearParticula(s32 tipo, Objeto *o, s32 b, s32 x, s32 y, s32 z, s32 dx, s32 dy, s32 dz, s32 c,
                          s32 d, s32 e, s32 f, s32 g, s32 h);
extern s32 func_80021CE4(s32 n);                      /* al azar */
extern s32 func_8002218C(u8 *o, s32 x, s32 z);        /* angulo hacia un punto */
extern void func_80021D44(s16 *ang, s32 hacia, s32 paso);
extern void func_8002205C(s32 *v, s32 a, s32 ang);    /* vector de largo 0x1000 con ese angulo */

#define C8(p, d) (*(u8 *)((u8 *)(p) + (d)))
#define C16(p, d) (*(s16 *)((u8 *)(p) + (d)))
#define C32(p, d) (*(s32 *)((u8 *)(p) + (d)))

/* 0x74 son los cuadros que le quedan (al acabarse pasa al estado 2); 0x78 = 0 lo hace girar hacia Sabrina;
 * 0x7C es la velocidad. En el estado 2 (o 3) suelta 13 particulas y se marca para borrar. Devuelve lo que el
 * original deja en v0. */
s32 func_8005B52C(u8 *o) {
    s32 v[3];
    s32 st;
    s32 i;
    s32 r1, r2;
    u8 *p;

    if (C32(o, 0x74) > 0) {
        C32(o, 0x74) = SUMA_TRAMPA(C32(o, 0x74), -1);
    } else {
        C16(o, 0x70) = 2;
    }
    st = C16(o, 0x70);
    switch (st) {
    case 0:
        if (C32(o, 0x78) == 0) {
            func_80021D44((s16 *)(o + 0x32), (s16)func_8002218C(o, p_sabrina->x, p_sabrina->z), 0xC8);
        }
        func_8002205C(v, 0, C16(o, 0x32));
        v[0] = ((v[0] >> 4) * C32(o, 0x7C) >> 8) << 8;
        v[2] = ((v[2] >> 4) * C32(o, 0x7C) >> 8) << 8;
        v[1] = 0;
        C32(o, 0x24) = SUMA_TRAMPA(C32(o, 0x24), v[0]);
        C32(o, 0x2C) = SUMA_TRAMPA(C32(o, 0x2C), v[2]);
        C32(o, 0x28) = SUMA_TRAMPA(C32(o, 0x28), v[1]);
        return C32(o, 0x28);
    case 2:
        C16(o, 0x112) = 0;
    case 3:
        for (i = 0; i < 0xD; i = SUMA_TRAMPA(i, 1)) {
            r1 = SUMA_TRAMPA(func_80021CE4(0x1999), -0xCCC);
            r2 = SUMA_TRAMPA(func_80021CE4(0x1999), -0xCCC);
            p = CrearParticula(0xE, (Objeto *)o, 0, 0, 0, 0, r1, r2, SUMA_TRAMPA(func_80021CE4(0x1999), -0xCCC),
                               0, 0, 0, 0xF, 0, 0);
            if (p != NULL) {
                C32(p, 0x3C) = 0x112;
            }
        }
        C8(o, 0x20) |= 0x80;
        return C8(o, 0x20);
    default:
        return st;
    }
}
