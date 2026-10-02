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

extern void func_8001C45C(s32 *v);   /* dejar el vector de largo 1 */

/* Enemigo huyendo (estado 12): si Sabrina esta a su alcance pasa a atacar (7); si no, se aleja de ella con
 * su rapidez (extra 0x20) mientras no se salga de su zona (extra 4 alrededor de su casa); si se saldria,
 * vuelve (6). */
void func_80049A28(Objeto *o, u8 *e, u16 *t) {
    EstadoAnim *a = o->anim;
    s32 v[3];
    s32 nx, nz;

    func_800487B0(o, p_sabrina, 0x96);
    v[0] = o->x - p_sabrina->x;
    v[1] = 0;
    v[2] = o->z - p_sabrina->z;
    if ((*(s32 *)(e + 8) >> 8) >= (s32)func_8001C180(v)) {
        o->estado = 7;
        E8(e, 0x29) = 0xC;
        E16(e, 0x44) = 0;
        return;
    }
    if (a->animacion != t[1]) {
        a->animacion = t[1];
        a->_50 = 0;
        a->_4E = 0x800;
    }
    func_8001C45C(v);
    v[0] = (((v[0] >> 4) * (*(s32 *)(e + 0x20) >> 8)) >> 8) << 8;
    v[2] = (((v[2] >> 4) * (*(s32 *)(e + 0x20) >> 8)) >> 8) << 8;
    nx = o->x - v[0];
    nz = o->z - v[2];
    v[0] = *(s32 *)(e + 0x38) - nx;
    v[2] = *(s32 *)(e + 0x40) - nz;
    if ((s32)func_8001C180(v) < (*(s32 *)(e + 4) >> 8)) {
        o->x = nx;
        o->z = nz;
        return;
    }
    o->estado = 6;
    E8(e, 0x29) = 0xC;
}

/* Enemigo volviendo a su casa (estado 6): mira hacia la casa (poniendo a Sabrina ahi un momento), camina
 * hacia ella con su rapidez y, al llegar, vuelve a quieto (12) con la primera animacion. */
void func_80049BD0(Objeto *o, u8 *e, u16 *t) {
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
        v[0] = o->x - *(s32 *)(e + 0x38);
        v[2] = o->z - *(s32 *)(e + 0x40);
        v[1] = 0;
        if ((s32)func_8001C180(v) < 0x4C) {
            o->x = *(s32 *)(e + 0x38);
            o->z = *(s32 *)(e + 0x40);
            return;
        }
        func_8001C45C(v);
        v[0] = (((v[0] >> 4) * (*(s32 *)(e + 0x20) >> 8)) >> 8) << 8;
        v[2] = (((v[2] >> 4) * (*(s32 *)(e + 0x20) >> 8)) >> 8) << 8;
        o->x -= v[0];
        o->z -= v[2];
        return;
    }
    if (a->_53 != t[0]) {
        if (a->animacion != t[0]) {
            a->animacion = t[0];
            a->_50 = 0;
            a->_4E = 0x800;
            o->estado = 0xC;
        }
    } else {
        o->estado = 0xC;
    }
}

/* Lo mismo para la otra clase de enemigo (casa en extra 0x34, rapidez en 0x1C): volver a casa. */
void func_800496E4(Objeto *o, u8 *e, u16 *t) {
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
        v[0] = o->x - *(s32 *)(e + 0x34);
        v[2] = o->z - *(s32 *)(e + 0x3C);
        v[1] = 0;
        if ((s32)func_8001C180(v) < 0x17) {
            o->x = *(s32 *)(e + 0x34);
            o->z = *(s32 *)(e + 0x3C);
            return;
        }
        func_8001C45C(v);
        v[0] = (((v[0] >> 4) * (*(s32 *)(e + 0x1C) >> 8)) >> 8) << 8;
        v[2] = (((v[2] >> 4) * (*(s32 *)(e + 0x1C) >> 8)) >> 8) << 8;
        o->x -= v[0];
        o->z -= v[2];
        return;
    }
    if (a->_53 != t[0]) {
        if (a->animacion != t[0]) {
            a->animacion = t[0];
            a->_50 = 0;
            a->_4E = 0x800;
            o->estado = 0xC;
        }
    } else {
        o->estado = 0xC;
    }
}

/* Y quieta mirando a Sabrina (estado 12): muy cerca ataca (7); dentro de su alcance la persigue sin salir
 * de su zona; si no, vuelve a casa (6). */
void func_8004951C(Objeto *o, u8 *e, u16 *t) {
    EstadoAnim *a = o->anim;
    s32 v[3], d, nx, nz;

    func_800487B0(o, p_sabrina, 0x96);
    v[0] = o->x - p_sabrina->x;
    v[1] = 0;
    v[2] = o->z - p_sabrina->z;
    d = func_8001C180(v);
    if (d < 0x80) {
        o->estado = 7;
        E8(e, 0x24) = 0xC;
        E16(e, 0x42) = 0;
        return;
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
        nx = o->x - v[0];
        nz = o->z - v[2];
        v[0] = *(s32 *)(e + 0x34) - nx;
        v[2] = *(s32 *)(e + 0x3C) - nz;
        if ((s32)func_8001C180(v) < (*(s32 *)(e + 8) >> 8)) {
            o->x = nx;
            o->z = nz;
            return;
        }
    }
    o->estado = 6;
    E8(e, 0x24) = 0xC;
}
