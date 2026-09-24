#include "objeto.h"
#include "dibujo.h"

/* Funciones de objetos entre 0x800479E8 y 0x80049384 (modulo sin nombre en modulos.tsv). */

/* Algo que flota: posicion en +0, un angulo que da vueltas en +0x28 y la altura de reposo en +0x2C. */
typedef struct {
    s32 x, y, z;                     /* 0x00 */
    u8 _0C[0x1C];
    s16 angulo;                      /* 0x28, sube 0x28 en cada paso y vuelve a 0 al pasar 0x1000 */
    s16 estado;                      /* 0x2A, 2 = Sabrina llego cerca */
    s32 y_base;                      /* 0x2C */
} Flotante;
EN(Flotante, angulo, 0x28);
EN(Flotante, y_base, 0x2C);

/* Lo que el objeto de func_800492B4 recibe como segundo argumento. */
typedef struct {
    u8 _00[0x29];
    s8 _29;                          /* 0x29 */
    u8 _2A[2];
    s32 _2C;                         /* 0x2C, distinto de 0: el objeto pasa al estado 7 */
    u8 _30[5];
    s8 sentido;                      /* 0x35, 1 o -1: se da vuelta cuando Sabrina queda detras */
    u8 _36[0x0E];
    s16 _44;                         /* 0x44 */
} DatosG10;
EN(DatosG10, _29, 0x29);
EN(DatosG10, _2C, 0x2C);
EN(DatosG10, sentido, 0x35);
EN(DatosG10, _44, 0x44);

extern s32 D_8007CA2C;

u32 func_8001C180(s32 *v);           /* largo de un vector */
s32 func_8001C1D4(s32 *a, s32 *b);   /* producto de dos vectores */
void func_8001C45C(s32 *v);          /* deja el vector de largo 1 (4.12) */
void func_8002205C(s32 *v, s32 a, s32 angulo);
s32 func_800223E8(s32 *pos);         /* altura del suelo debajo de pos */
EstadoAnim *func_8002ECFC(Objeto *o);
s32 func_80030068(void *e);
s32 func_800607AC(Objeto *o, s32 a, s32 *p, s32 b, s32 c);
void *CrearParticula(s32 tipo, s32 a, s32 b, s32 x, s32 y, s32 z, s32 dx, s32 dy, s32 dz, s32 c, s32 d,
                     s32 e, s32 vida, s32 f, s32 g);

/* Sube y baja la cosa con un seno y, si Sabrina esta a menos de 0xB7 (en el plano), la marca con 2.
 * Devuelve la distancia a Sabrina (el llamador la recibe en v0). */
u32 func_800479E8(Flotante *f) {
    s32 v[3];
    u32 largo;

    f->angulo = f->angulo + 0x28;
    if (f->angulo > 0x1000) {
        f->angulo = 0;
    }
    f->y = f->y_base + rsin(f->angulo * 4) * 2;
    v[0] = p_sabrina->x - f->x;
    v[2] = p_sabrina->z - f->z;
    v[1] = 0;
    largo = func_8001C180(v);
    if (largo < 0x6401 && largo < 0xB7) {
        f->estado = 2;
    }
    return largo;
}

/* Prepara a Sabrina: reinicia su animacion con la segunda de su tabla, la deja como p_sabrina y le pone
 * escala 3 en los tres ejes. */
void func_80047F24(Objeto *o) {
    u16 *tabla = o->animaciones;
    EstadoAnim *a;

    if (func_8002ECFC(o) != NULL) {
        a = o->anim;
        a->velocidad = 0;
        a->_4E = 0x1000;
        a->animacion = tabla[1];
        a->_50 = 0;
        a->_53 = a->animacion;
        a->_52 = a->_50;
        a->_00[8] = func_80030068(((void **)o->modelo)[1]);
    }
    p_sabrina = o;
    o->escala[0] = 3;
    o->escala[1] = 3;
    o->escala[2] = 3;
}

/* Baja el objeto al suelo si lo hay debajo (busca desde 0xE666 mas abajo). */
s32 func_800483F8(Objeto *o) {
    s32 v[3];
    s32 y = o->y - 0x6667 - 0x7FFF;

    v[0] = o->x;
    v[1] = y;
    v[2] = o->z;
    v[1] = func_800223E8(v);
    if (v[1] != y) {
        o->y = v[1];
    }
    return v[1];
}

/* Si el objeto tiene algo en +0x74, se lo pasa a func_800607AC para que lo cambie. */
s32 func_80048754(Objeto *o, s32 a, s32 b, s32 c) {
    s32 p = *(s32 *)&o->extra;

    if (p != 0) {
        func_800607AC(o, a, &p, b & 0xFFFF, c & 0xFFFF);
        *(s32 *)&o->extra = p;
    }
    return p;
}

/* Velocidad hacia un punto: la direccion de o a p con largo 1 por rapidez (16.16). */
void func_80048CF4(Objeto *o, s32 *p, s32 rapidez, s32 *vel) {
    s32 d[3];
    s32 r;

    d[0] = p[0] - o->x;
    d[1] = p[1] - o->y;
    d[2] = p[2] - o->z;
    func_8001C45C(d);
    r = rapidez >> 8;
    vel[0] = (((d[0] >> 4) * r) >> 8) << 8;
    vel[1] = (((d[1] >> 4) * r) >> 8) << 8;
    vel[2] = (((d[2] >> 4) * r) >> 8) << 8;
}

/* 1 si s queda detras de o (segun hacia donde mira o), 0 si no. */
s32 func_8004906C(Objeto *o, Objeto *s) {
    s32 frente[3];
    s32 d[3];

    func_8002205C(frente, 0, o->rot[1]);
    frente[0] = frente[0] >> 4;
    frente[1] = 0;
    frente[2] = frente[2] >> 4;
    d[0] = o->x - s->x;
    d[2] = o->z - s->z;
    d[1] = 0;
    if (func_8001C1D4(frente, d) < 0) {
        return 1;
    }
    return 0;
}

/* Un anillo de 16 particulas del tipo 0xE que salen en todas las direcciones del plano desde pos. */
void func_80049110(s32 *pos, s32 dato) {
    s32 ang;
    s32 d[3];
    u8 *p;

    for (ang = 0; ang < 0x1000; ang += 0x100) {
        d[0] = rsin(ang);
        d[1] = 0;
        d[2] = rcos(ang);
        func_8001C45C(d);
        p = CrearParticula(0xE, 0, 0, pos[0], pos[1], pos[2], d[0], d[1], d[2], 0, 0, 0, 0x19, 2, 0);
        if (p != NULL) {
            *(s32 *)(p + 0x3C) = dato;
            *(s32 *)(p + 0x10) = d[0];
            *(s32 *)(p + 0x14) = d[1];
            *(s32 *)(p + 0x18) = d[2];
        }
    }
}

/* Un paso: si Sabrina queda detras se da vuelta, corre la funcion de +0x0C y, si +0x2C de los datos no
 * es 0, pasa al estado 7; si no, sigue con func_80048754. */
void func_800492B4(Objeto *o, DatosG10 *e, s16 *t) {
    if (D_8007CA2C == 0 && func_8004906C(o, p_sabrina) != 0) {
        if (e->sentido >= 0) {
            e->sentido = -1;
        } else {
            e->sentido = 1;
        }
    }
    (*(FuncObjeto *)((u8 *)o + 0x0C))(o);
    if (e->_2C != 0) {
        o->estado = 7;
        e->_29 = 2;
        e->_44 = 0;
    } else {
        func_80048754(o, (s32)((u8 *)e + 0x30), t[0], t[1]);
    }
}
