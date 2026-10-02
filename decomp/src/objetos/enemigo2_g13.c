#include "objeto.h"

/* Dos clases de enemigo que patrullan y atacan con el disparo de func_800498F4 / func_80049388 (cada una
 * con su tabla de disparos, D_8007CBD8 y D_8007CBF4). */

#define E8(e, d) (*(s8 *)((u8 *)(e) + (d)))
#define E16(e, d) (*(s16 *)((u8 *)(e) + (d)))

extern void *D_8007CBD8, *D_8007CBF4;
extern s32 func_800487B0(Objeto *o, Objeto *a, s32 paso);  /* gira hacia a; devuelve la distancia */
extern void func_80048908(Objeto *o, s16 *a, void *b, s32 modo);
extern void func_80049218(Objeto *o, u8 *e, u16 *t);
extern void func_80048804(Objeto *o, s32 modo, EstadoAnim *a, s32 anim);
extern void func_800498F4(Objeto *o, u8 *e, u16 *t, void *tabla);
extern void func_80049388(Objeto *o, u8 *e, u16 *t, void *tabla);
extern void func_80048228(Objeto *o, s16 *p);
extern void func_800489C4(Objeto *o);
extern void func_8004951C(Objeto *o, u8 *e, u16 *t);
extern void func_800496E4(Objeto *o, u8 *e, u16 *t);
extern s32 func_8002EFD0(Objeto *o);  /* si termino la animacion */

static void paso(Objeto *o, void *tabla, s32 marca) {
    EstadoAnim *a = o->anim;
    u16 *t = o->animaciones;
    u8 *e = (u8 *)&o->extra;

    switch (o->estado) {
    case 0:
        E16(e, 0x40) = 0xC;
        o->estado = 1;
        break;
    case 1:
        func_80048908(o, &E16(e, 0x40), e + 0x28, E8(e, 0x20));
        break;
    case 2:
        func_80049218(o, e, t);
        break;
    case 3:
    case 4:
        if (func_800487B0(o, p_sabrina, 0x96) >= 0x200) {
            break;
        }
        if (o->estado != 4 && a->animacion != t[4]) {
            a->animacion = t[4];
            a->_50 = 0;
            a->_4E = 0x800;
            o->estado = 4;
        }
        if (marca) {
            E8(e, 0x24) = 3;
        }
        func_80048804(o, E8(e, 0x20), a, (s8)t[0]);
        break;
    case 7:
        func_800498F4(o, e, t, tabla);
        break;
    case 8:
        func_800487B0(o, p_sabrina, 0x96);
        if (func_8002EFD0(o) != 0) {
            o->estado = (E8(e, 0x20) & 4) ? 11 : 4;
        }
        break;
    case 10:
        func_80048228(o, &E16(e, 0x40));
        break;
    case 11:
        func_800489C4(o);
        func_80049388(o, e, t, tabla);
        break;
    case 12:
        func_8004951C(o, e, t);
        break;
    case 6:
        func_800496E4(o, e, t);
        break;
    default:
        o->estado = 0;
        break;
    }
}

void func_8003D5F4(Objeto *o) {
    paso(o, D_8007CBD8, 1);
}

void func_80045CF4(Objeto *o) {
    paso(o, D_8007CBF4, 0);
}

extern u32 func_8001C180(s32 *v);    /* largo de un vector */
extern s32 func_8002225C(Objeto *o, s32 x, s32 y, s32 z);

/* Si Sabrina (tocable) esta a su alcance, le avisa con su funcion de 0x10. */
void func_8002E030(Objeto *o) {
    u8 *e = (u8 *)&o->extra;
    s32 v[3];

    *(s32 *)(e + 0x2C) = 0;
    if (p_sabrina != NULL && (p_sabrina->forma.banderas & 1)) {
        v[0] = o->x - p_sabrina->x;
        v[1] = o->y - p_sabrina->y;
        v[2] = o->z - p_sabrina->z;
        if ((u32)(*(s32 *)(e + 8) >> 8) >= func_8001C180(v)) {
            (*(void (**)(Objeto *, Objeto *))((u8 *)o + 0x10))(o, p_sabrina);
        }
    }
}

/* Si Sabrina esta cerca la anota como su blanco. Devuelve (v0) Sabrina, o la distancia si esta lejos. */
s32 func_80034710(Objeto *o) {
    s32 d = func_8002225C(o, p_sabrina->x, p_sabrina->y, p_sabrina->z);

    if (d >= 0x40001) {
        return d;
    }
    *(Objeto **)((u8 *)&o->extra + 0x10) = p_sabrina;
    return (s32)p_sabrina;
}
