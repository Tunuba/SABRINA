#include "objeto.h"

/* Un objeto que al abrirse suelta un objeto 0x18 con un sonido al azar y despues desaparece. */

extern s32 func_80021CE4(s32 n);     /* al azar, de 0 a n - 1 */
extern void func_8004C6D0(s32 a);
extern s32 TocarSonido(s32 prog, s32 tono, s32 nota, s32 prioridad);
extern Objeto *func_800252A0(s32 clase, Objeto *padre, s32 x, s32 y, s32 z, s32 vx, s32 vy, s32 vz, s32 rx,
                             s32 ry, s32 rz, s32 a, s32 b);
extern void func_8004A3B4(Objeto *o, s32 a, s32 b);
extern s32 func_8004C81C(Objeto *o);
extern s32 func_8002EFD0(Objeto *o);  /* si termino la animacion */

/* Devuelve (v0) lo que deja el original en cada estado; en el 1, la direccion a la que salta su tabla. */
s32 func_80055A38(Objeto *o) {
    u8 *e = (u8 *)&o->extra;
    Objeto *p;
    s32 s;

    switch (o->estado) {
    case 0:
        o->estado = 1;
        return 1;
    case 1:
        return 0x80055BE8;
    case 2:
        func_8004C6D0(*(s32 *)e);
        switch (func_80021CE4(4)) {
        case 0:
            s = 0xB;
            break;
        case 1:
            s = 0x11;
            break;
        case 2:
            s = 0xD;
            break;
        default:
            s = 0x10;
            break;
        }
        TocarSonido(s, 0, 0x2A, 0x7F);
        p = func_800252A0(0x18, o, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
        ((u8 *)p)[0x79] = 0;
        func_8004A3B4(p, 0, 0);
        o->estado = 4;
        return func_8004C81C(o);
    case 3:
        if (o->anim->_50 != (s8)e[5]) {
            return (s8)e[5];
        }
        o->estado = 2;
        return 2;
    case 4:
        if (!func_8002EFD0(o)) {
            return 0;
        }
        *(u8 *)&o->_20 |= 0x80;
        return *(u8 *)&o->_20;
    default:
        s = o->estado;
        o->estado = 0;
        return s;
    }
}
