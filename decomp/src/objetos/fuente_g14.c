#include "objeto.h"

/* Un objeto que, una vez activado, echa chispas y suelta objetos hacia arriba durante un rato. */

extern u8 *CrearParticula(s32 tipo, Objeto *o, s32 b, s32 x, s32 y, s32 z, s32 dx, s32 dy, s32 dz, s32 c,
                          s32 d, s32 e, s32 f, s32 g, s32 h);
extern Objeto *func_800252A0(s32 clase, Objeto *padre, s32 x, s32 y, s32 z, s32 vx, s32 vy, s32 vz, s32 rx,
                             s32 ry, s32 rz, s32 a, s32 b);
extern s32 func_800224B8(s32 *d);    /* una direccion al azar */
extern void func_800249CC(Objeto *o, s32 n);
extern s32 func_8003CE04();
extern s32 D_8007CC64;

#define C16(p, d) (*(s16 *)((u8 *)(p) + (d)))
#define C32(p, d) (*(s32 *)((u8 *)(p) + (d)))

static inline s32 escalar(s32 v) {
    return ((v >> 8) * 0x5B3 >> 8) << 8;
}

/* Estados: 0 espera a que lo activen (su contador deja de ser 0); 1 cuenta hasta 130 cuadros: hasta el 50
 * suelta un objeto cada dos cuadros, en el 50 cambia de modelo, y cada cuadro echa 5 chispas; despues pasa
 * al 2, que lo anota (D_8007CC64) y lo deja en 3. Devuelve lo que el original deja en v0. */
s32 func_8005359C(Objeto *o) {
    u8 *e = (u8 *)o + 0x74;
    s32 d[3];
    s32 st;
    s32 i;
    u8 *r;
    Objeto *h;

    C16(C32(o, 0x6C), 0x1A) = 2;
    st = C16(o, 0x70);
    switch (st) {
    case 3:
        return 3;
    case 2:
        D_8007CC64 = SUMA_TRAMPA(D_8007CC64, 1);
        C16(o, 0x70) = 3;
        return 3;
    case 1:
        break;
    case 0:
        if (C32(e, 0) != 0) {
            C16(o, 0x70) = 1;
            return 1;
        }
        return 0;
    default:
        return st;
    }
    if (C32(e, 0) >= 0x82) {
        C16(o, 0x70) = 2;
        return C32(e, 0);
    }
    C32(e, 0) = SUMA_TRAMPA(C32(e, 0), 1);
    if (C32(e, 0) < 0x32 && (C32(e, 0) & 1)) {
        func_800224B8(d);
        d[1] = escalar(d[1]);
        h = func_800252A0(0xC, o, 0, 0xFFFF0000, 0, d[0], d[1], d[2], 0, 0, 0, 0, 0);
        func_800249CC(h, 0x2F);
        C32(h, 0) = (s32)func_8003CE04;
        C16(h, 0x96) = 0x4B;
    }
    if (C32(e, 0) == 0x32) {
        func_800249CC(o, 0x2E);
    }
    for (i = 0; i < 5; i = SUMA_TRAMPA(i, 1)) {
        func_800224B8(d);
        r = CrearParticula(0x12, o, 0, d[0], d[1], d[2], d[0], escalar(d[1]), d[2], 0, 0, 0, 0x32, 0, 0);
    }
    return (s32)r;
}
