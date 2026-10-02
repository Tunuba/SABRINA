#include "objeto.h"

/* Dos clases de enemigo que patrullan y atacan con el disparo de func_800498F4 / func_80049388 (cada una
 * con su tabla de disparos, D_8007CBD8 y D_8007CBF4). */

#define E8(e, d) (*(s8 *)((u8 *)(e) + (d)))
#define E16(e, d) (*(s16 *)((u8 *)(e) + (d)))

extern void *D_8007CBD8, *D_8007CBF4;
extern s32 func_800487B0(Objeto *o, Objeto *a, s32 paso);  /* gira hacia a; devuelve la distancia */
extern s32 func_80048908(Objeto *o, s16 *a, void *b, s32 modo);
extern s32 func_80049218(Objeto *o, u8 *e, u16 *t);
extern s32 func_80048804(Objeto *o, s32 modo, EstadoAnim *a, s32 anim);
extern s32 func_800498F4(Objeto *o, u8 *e, u16 *t, void *tabla);
extern s32 func_80049388(Objeto *o, u8 *e, u16 *t, void *tabla);
extern s32 func_80048228(Objeto *o, s16 *p);
extern void func_800489C4(Objeto *o);
extern s32 func_8004951C(Objeto *o, u8 *e, u16 *t);
extern s32 func_800496E4(Objeto *o, u8 *e, u16 *t);
extern s32 func_8002EFD0(Objeto *o);  /* si termino la animacion */

/* Un paso de la maquina de estados. Devuelve lo que queda en v0 en cada camino; en los estados 5 y 9 el
 * original deja la direccion a la que salta su tabla de casos (sin_estado). */
static s32 paso(Objeto *o, void *tabla, s32 marca, s32 sin_estado) {
    EstadoAnim *a = o->anim;
    u16 *t = o->animaciones;
    u8 *e = (u8 *)&o->extra;

    switch (o->estado) {
    case 0:
        E16(e, 0x40) = 0xC;
        o->estado = 1;
        return 1;
    case 1:
        return func_80048908(o, &E16(e, 0x40), e + 0x28, E8(e, 0x20));
    case 2:
        return func_80049218(o, e, t);
    case 3:
    case 4:
        if (func_800487B0(o, p_sabrina, 0x96) >= 0x200) {
            return 0;
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
        return func_80048804(o, E8(e, 0x20), a, (s8)t[0]);
    case 7:
        return func_800498F4(o, e, t, tabla);
    case 8:
        func_800487B0(o, p_sabrina, 0x96);
        if (func_8002EFD0(o) == 0) {
            return 0;
        }
        o->estado = (E8(e, 0x20) & 4) ? 11 : 4;
        return o->estado;
    case 10:
        return func_80048228(o, &E16(e, 0x40));
    case 11:
        func_800489C4(o);
        return func_80049388(o, e, t, tabla);
    case 12:
        return func_8004951C(o, e, t);
    case 6:
        return func_800496E4(o, e, t);
    case 5:
    case 9:
        o->estado = 0;
        return sin_estado;
    default:
        o->estado = 0;
        return 0;
    }
}

s32 func_8003D5F4(Objeto *o) {
    return paso(o, D_8007CBD8, 1, 0x8003D7C8);
}

s32 func_80045CF4(Objeto *o) {
    return paso(o, D_8007CBF4, 0, 0x80045EC0);
}

extern void *D_8007CC74;

s32 func_80057CA0(Objeto *o) {
    return paso(o, D_8007CC74, 0, 0x80057E6C);
}

extern void *D_8007CC10;

s32 func_8004A140(Objeto *o) {
    return paso(o, D_8007CC10, 0, 0x8004A30C);
}

extern u32 func_8001C180(s32 *v);    /* largo de un vector */
extern s32 func_8002225C(Objeto *o, s32 x, s32 y, s32 z);

/* Si Sabrina (tocable) esta a su alcance, le avisa con su funcion de 0x10. */
s32 func_8002E030(Objeto *o) {
    u8 *e = (u8 *)&o->extra;
    s32 v[3];
    u32 d;

    *(s32 *)(e + 0x2C) = 0;
    if (p_sabrina == NULL || !(p_sabrina->forma.banderas & 1)) {
        return 0;
    }
    v[0] = RESTA_TRAMPA(o->x, p_sabrina->x);
    v[1] = RESTA_TRAMPA(o->y, p_sabrina->y);
    v[2] = RESTA_TRAMPA(o->z, p_sabrina->z);
    d = func_8001C180(v);
    if ((u32)(*(s32 *)(e + 8) >> 8) < d) {
        return d;   /* lo que queda en v0 */
    }
    return (*(s32 (**)(Objeto *, Objeto *))((u8 *)o + 0x10))(o, p_sabrina);
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

extern void func_8001C45C(s32 *v);   /* dejar el vector de largo 1 */

/* Enemigo huyendo (estado 12): si Sabrina esta a su alcance pasa a atacar (7); si no, se aleja de ella con
 * su rapidez (extra 0x20) mientras no se salga de su zona (extra 4 alrededor de su casa); si se saldria,
 * vuelve (6). */
s32 func_80049A28(Objeto *o, u8 *e, u16 *t) {
    EstadoAnim *a = o->anim;
    s32 v[3];
    s32 nx, nz, d;

    func_800487B0(o, p_sabrina, 0x96);
    v[0] = RESTA_TRAMPA(o->x, p_sabrina->x);
    v[1] = 0;
    v[2] = RESTA_TRAMPA(o->z, p_sabrina->z);
    if ((*(s32 *)(e + 8) >> 8) >= (s32)func_8001C180(v)) {
        o->estado = 7;
        E8(e, 0x29) = 0xC;
        E16(e, 0x44) = 0;
        return 0xC;
    }
    if (a->animacion != t[1]) {
        a->animacion = t[1];
        a->_50 = 0;
        a->_4E = 0x800;
    }
    func_8001C45C(v);
    v[0] = (((v[0] >> 4) * (*(s32 *)(e + 0x20) >> 8)) >> 8) << 8;
    v[2] = (((v[2] >> 4) * (*(s32 *)(e + 0x20) >> 8)) >> 8) << 8;
    nx = RESTA_TRAMPA(o->x, v[0]);
    nz = RESTA_TRAMPA(o->z, v[2]);
    v[0] = RESTA_TRAMPA(*(s32 *)(e + 0x38), nx);
    v[2] = RESTA_TRAMPA(*(s32 *)(e + 0x40), nz);
    d = func_8001C180(v);
    if (d < (*(s32 *)(e + 4) >> 8)) {
        o->x = nx;
        o->z = nz;
        return d;
    }
    o->estado = 6;
    E8(e, 0x29) = 0xC;
    return 0xC;
}

/* Enemigo volviendo a su casa (estado 6): mira hacia la casa (poniendo a Sabrina ahi un momento), camina
 * hacia ella con su rapidez y, al llegar, vuelve a quieto (12) con la primera animacion. */
s32 func_80049BD0(Objeto *o, u8 *e, u16 *t) {
    EstadoAnim *a = o->anim;
    s32 v[3], sx, sy, sz;

    if (o->x != *(s32 *)(e + 0x38) && o->z != *(s32 *)(e + 0x40)) {
        sx = p_sabrina->x;
        sy = p_sabrina->y;
        sz = p_sabrina->z;
        p_sabrina->x = *(s32 *)(e + 0x38);
        p_sabrina->z = *(s32 *)(e + 0x40);
        func_800487B0(o, p_sabrina, 0x96);
        p_sabrina->x = sx;
        p_sabrina->y = sy;
        p_sabrina->z = sz;
        if (a->animacion != t[1]) {
            a->animacion = t[1];
            a->_50 = 0;
            a->_4E = 0x800;
        }
        v[0] = RESTA_TRAMPA(o->x, *(s32 *)(e + 0x38));
        v[2] = RESTA_TRAMPA(o->z, *(s32 *)(e + 0x40));
        v[1] = 0;
        if ((s32)func_8001C180(v) < 0x4C) {
            o->x = *(s32 *)(e + 0x38);
            o->z = *(s32 *)(e + 0x40);
            return o->z;
        }
        func_8001C45C(v);
        v[0] = (((v[0] >> 4) * (*(s32 *)(e + 0x20) >> 8)) >> 8) << 8;
        v[2] = (((v[2] >> 4) * (*(s32 *)(e + 0x20) >> 8)) >> 8) << 8;
        o->x = RESTA_TRAMPA(o->x, v[0]);
        o->z = RESTA_TRAMPA(o->z, v[2]);
        return o->z;
    }
    if (a->_53 != t[0]) {
        if (a->animacion != t[0]) {
            a->animacion = t[0];
            a->_50 = 0;
            a->_4E = 0x800;
            o->estado = 0xC;
            return 0xC;
        }
        return a->animacion;
    }
    o->estado = 0xC;
    return 0xC;
}

/* Lo mismo para la otra clase de enemigo (casa en extra 0x34, rapidez en 0x1C): volver a casa. */
s32 func_800496E4(Objeto *o, u8 *e, u16 *t) {
    EstadoAnim *a = o->anim;
    s32 v[3], sx, sy, sz;

    if (o->x != *(s32 *)(e + 0x34) && o->z != *(s32 *)(e + 0x3C)) {
        sx = p_sabrina->x;
        sy = p_sabrina->y;
        sz = p_sabrina->z;
        p_sabrina->x = *(s32 *)(e + 0x34);
        p_sabrina->z = *(s32 *)(e + 0x3C);
        func_800487B0(o, p_sabrina, 0x96);
        p_sabrina->x = sx;
        p_sabrina->y = sy;
        p_sabrina->z = sz;
        if (a->animacion != t[1]) {
            a->animacion = t[1];
            a->_50 = 0;
            a->_4E = 0x800;
        }
        v[0] = RESTA_TRAMPA(o->x, *(s32 *)(e + 0x34));
        v[2] = RESTA_TRAMPA(o->z, *(s32 *)(e + 0x3C));
        v[1] = 0;
        if ((s32)func_8001C180(v) < 0x17) {
            o->x = *(s32 *)(e + 0x34);
            o->z = *(s32 *)(e + 0x3C);
            return o->z;    /* lo que queda en v0 */
        }
        func_8001C45C(v);
        v[0] = (((v[0] >> 4) * (*(s32 *)(e + 0x1C) >> 8)) >> 8) << 8;
        v[2] = (((v[2] >> 4) * (*(s32 *)(e + 0x1C) >> 8)) >> 8) << 8;
        o->x = RESTA_TRAMPA(o->x, v[0]);
        o->z = RESTA_TRAMPA(o->z, v[2]);
        return o->z;
    }
    if (a->_53 != t[0]) {
        if (a->animacion != t[0]) {
            a->animacion = t[0];
            a->_50 = 0;
            a->_4E = 0x800;
            o->estado = 0xC;
            return 0xC;
        }
        return a->animacion;
    }
    o->estado = 0xC;
    return 0xC;
}

/* Y quieta mirando a Sabrina (estado 12): muy cerca ataca (7); dentro de su alcance la persigue sin salir
 * de su zona; si no, vuelve a casa (6). Devuelve lo que queda en v0. */
s32 func_8004951C(Objeto *o, u8 *e, u16 *t) {
    EstadoAnim *a = o->anim;
    s32 v[3], d, nx, nz;

    func_800487B0(o, p_sabrina, 0x96);
    v[0] = RESTA_TRAMPA(o->x, p_sabrina->x);
    v[1] = 0;
    v[2] = RESTA_TRAMPA(o->z, p_sabrina->z);
    d = func_8001C180(v);
    if (d < 0x80) {
        o->estado = 7;
        E8(e, 0x24) = 0xC;
        E16(e, 0x42) = 0;
        return 0xC;
    }
    if (d < (*(s32 *)(e + 8) >> 8)) {
        if (a->animacion != t[1]) {
            a->animacion = t[1];
            a->_50 = 0;
            a->_4E = 0x800;
        }
        func_8001C45C(v);
        v[0] = (((v[0] >> 4) * (*(s32 *)(e + 0x1C) >> 8)) >> 8) << 8;
        v[2] = (((v[2] >> 4) * (*(s32 *)(e + 0x1C) >> 8)) >> 8) << 8;
        nx = RESTA_TRAMPA(o->x, v[0]);
        nz = RESTA_TRAMPA(o->z, v[2]);
        v[0] = RESTA_TRAMPA(*(s32 *)(e + 0x34), nx);
        v[2] = RESTA_TRAMPA(*(s32 *)(e + 0x3C), nz);
        d = func_8001C180(v);
        if (d < (*(s32 *)(e + 8) >> 8)) {
            o->x = nx;
            o->z = nz;
            return d;
        }
    }
    o->estado = 6;
    E8(e, 0x24) = 0xC;
    return 0xC;
}

extern s32 D_8007CBA8;
extern s32 TocarSonido(s32 prog, s32 tono, s32 nota, s32 prioridad);
extern s32 func_80048374(Objeto *o, Objeto *a, s32 dano);
extern void func_800483E8(Objeto *o);

/* Ataque (estado 11): cerca de Sabrina pone la animacion de ataque (t[7]) y, al llegar al cuadro del golpe
 * (extra 0x23), suena (tabla = numero de sonido) y le pega con el dano de extra 0xC; al terminar vuelve a
 * la primera animacion. Lejos, solo vuelve a la primera. Devuelve lo que queda en v0. */
s32 func_80049388(Objeto *o, u8 *e, u16 *t, void *tabla) {
    EstadoAnim *a = o->anim;
    s32 v[3];

    func_800487B0(o, p_sabrina, 0x96);
    v[0] = RESTA_TRAMPA(o->x, p_sabrina->x);
    v[1] = 0;
    v[2] = RESTA_TRAMPA(o->z, p_sabrina->z);
    if ((s32)func_8001C180(v) < 0x400) {
        if (a->animacion != t[7]) {
            a->animacion = t[7];
            a->_50 = 0;
            a->_4E = 0x800;
            return 0x800;
        }
        if (D_8007CBA8 != 0) {
            return D_8007CBA8;
        }
        a->_4E = 0x800;
        if (a->_50 >= E8(e, 0x23) && E16(e, 0x42) == 0) {
            E16(e, 0x42) = 1;
            TocarSonido((s16)(s32)tabla, 0, 0x2A, 0x7F);
            if (func_80048374(o, p_sabrina, *(s32 *)(e + 0xC)) == 1) {
                func_800483E8(o);
            }
        }
        if (func_8002EFD0(o) == 0) {
            return 0;
        }
        a->animacion = t[0];
        a->_50 = 0;
        E16(e, 0x42) = 0;
        return t[0];
    }
    if (a->animacion == t[0]) {
        return t[0];
    }
    a->animacion = t[0];
    a->_50 = 0;
    E16(e, 0x42) = 0;
    return t[0];
}
