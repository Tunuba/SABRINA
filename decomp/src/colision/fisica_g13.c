#include "objeto.h"

/* La fisica de un objeto que camina (Sabrina y su companero): mover con la velocidad, chocar de lado con
 * las paredes, limitar la rapidez, frenar, apoyarse en el suelo o caer. Termina con DanoPorSuelo y
 * devuelve lo que ella devuelve. */

/* Consulta de choque (0x4C bytes; la misma de colision/consulta_g13.c). */
typedef struct {
    s32 x, y, z;                     /* 0x00 */
    s32 x2, y2, z2;                  /* 0x0C */
    u8 _18[0x18];
    s32 punto[3];                    /* 0x30 */
    s32 normal[3];                   /* 0x3C */
    u16 tipo;                        /* 0x48 */
    u8 _4A[2];
} Consulta;
EN(Consulta, punto, 0x30);
EN(Consulta, tipo, 0x48);

#define CAMPO_S32_50(o) (*(s32 *)((u8 *)(o) + 0x50))   /* altura del suelo bajo el objeto */

/* La parte extra que usa la fisica. */
typedef struct {
    u8 _00[4];
    s32 rapidez_max;                 /* 0x04 */
    u8 _08[4];
    u16 suelo_tipo;                  /* 0x0C, el tipo del triangulo donde esta parado */
    u8 _0E[0x0A];
    s16 estado;                      /* 0x18, bit 3 choco o resbala, bit 4 en el suelo */
    s8 _1A, _1B;                     /* 0x1A */
    u8 _1C[0x0A];
    s8 golpe;                        /* 0x26, pasos que quedan del golpe contra la pared */
    u8 _27;
    s32 suelo_normal[3];             /* 0x28 */
} ExtraFisica;
EN(ExtraFisica, estado, 0x18);
EN(ExtraFisica, golpe, 0x26);
EN(ExtraFisica, suelo_normal, 0x28);

extern Consulta D_800C6594;          /* la consulta compartida */
extern s32 D_800C98C4[];             /* plataformas del nivel 13 */
extern s32 D_8007CC1C;               /* cuantas hay */
extern s8 nivel_actual;
extern Objeto *D_8007CB8C;

extern void func_8001C45C(s32 *v);
extern void func_8001C404(s32 *fuera, s32 *m, s32 *v);
extern void func_8003B38C(Consulta *c, Consulta *desde, s32 *hasta);
extern s32 func_8003AE84(void);
extern void func_80033EC8(s32 nx, s32 ny, s32 nz, s32 *v, s32 *fuera);
extern s32 func_8001C004(s32 ax, s32 ay, s32 az, s32 bx, s32 by, s32 bz);
extern s32 func_8001C304(s32 a, s32 b);
extern s32 func_8003AF48(Consulta *c);
extern s32 func_8004DB6C(s32 *altura, s32 x, s32 y, s32 z, s32 plataforma);
extern s32 DanoPorSuelo(Objeto *o);

/* Copia de una consulta a otra (19 palabras). */
static void copiar(Consulta *d, Consulta *s) {
    s32 *a = (s32 *)d, *b = (s32 *)s;
    s32 i;

    for (i = 0; i < 19; i++) {
        a[i] = b[i];
    }
}

/* Prueba el segmento de la consulta con la compartida; devuelve si choco (la consulta queda con el
 * resultado). */
static s32 probar(Consulta *l) {
    s32 r;

    func_8003B38C(l, l, &l->x2);
    copiar(&D_800C6594, l);
    r = func_8003AE84();
    copiar(l, &D_800C6594);
    return r;
}

s32 FisicaObjeto(Objeto *o, s32 con_paredes) {
    ExtraFisica *e = (ExtraFisica *)&o->extra;
    Consulta l;
    s32 arriba[3], v[3], lado[3], sal[3], alto;
    s32 x0, y0, z0, r, choco, n, vy;
    s32 *viejo;

    /* El original no llena todos los campos de su consulta local antes de copiarla a la compartida: lo que
     * no llena es lo que habia en su pila (sp+0x40 de un marco de 0xC0). Se toma lo mismo, antes de llamar
     * a nada. */
    viejo = (s32 *)((u8 *)__builtin_dwarf_cfa() - 0xC0 + 0x40);
    for (r = 0; r < 19; r++) {
        ((s32 *)&l)[r] = ((volatile s32 *)viejo)[r];
    }
    __asm__ volatile("" ::: "memory");
    if (e->golpe > 0) {
        e->golpe--;
    }
    arriba[0] = 0;
    arriba[1] = -0x100;
    arriba[2] = 0;
    v[0] = o->x;
    v[1] = 0;
    v[2] = o->z;
    x0 = o->x;
    y0 = o->y;
    z0 = o->z;
    o->x = x0 + o->empuje_x;
    o->z = o->z + o->empuje_z;
    o->y = o->y + o->vel_y;
    v[0] = o->empuje_x;
    v[2] = o->empuje_z;
    r = ((v[0] * v[0]) >> 16) + ((v[2] * v[2]) >> 16);
    if (con_paredes == 1 && r != 0) {
        if (r < 0x1000) {
            func_8001C45C(v);
        }
        v[0] <<= 2;
        v[2] <<= 2;
        func_8001C404(lado, arriba, v);
        lado[0] <<= 2;
        lado[2] <<= 2;
        /* dos segmentos desde atras hacia adelante, corridos a cada lado */
        l.x = x0 - v[0];
        l.z = z0 - v[2];
        l.y = y0 - 0x16666;
        l.y2 = y0;
        l.x2 = lado[0] + (o->x + v[0] * 2);
        l.z2 = lado[2] + (o->z + v[2] * 2);
        choco = 0;
        if (probar(&l) != 0 && l.normal[1] >= -0xC7FF) {
            choco = 1;
        }
        if (choco == 0) {
            l.x2 = (o->x + v[0] * 2) - lado[0];
            l.z2 = (o->z + v[2] * 2) - lado[2];
            if (probar(&l) != 0 && D_800C6594.normal[1] >= -0xC7FF) {
                choco = 1;
            }
        }
        if (choco == 1 && l.normal[1] >= -0xC7FF) {
            /* resbalar por la pared */
            e->estado |= 8;
            e->golpe = 5;
            func_8001C45C(l.normal);
            l.normal[0] >>= 4;
            l.normal[1] >>= 4;
            l.normal[2] >>= 4;
            o->x -= o->empuje_x;
            o->z -= o->empuje_z;
            v[0] = o->empuje_x >> 8;
            v[1] = 0;
            v[2] = o->empuje_z >> 8;
            func_80033EC8(l.normal[0], l.normal[1], l.normal[2], v, sal);
            o->empuje_x = sal[0] << 8;
            o->empuje_z = sal[2] << 8;
            l.x = o->x;
            l.y = l.punto[1];
            l.z = o->z;
            l.x2 = l.punto[0] + (sal[0] << 10);
            l.z2 = l.punto[2] + (sal[2] << 10);
            l.y2 = l.y;
            if (probar(&l) != 0) {
                o->empuje_x = 0;
                o->empuje_z = 0;
            }
        }
    }
    if (e->rapidez_max < func_8001C004(0, 0, 0, o->empuje_x, 0, o->empuje_z)) {
        vy = o->vel_y;
        func_8001C45C(&o->empuje_x);
        o->empuje_x = func_8001C304(o->empuje_x << 4, e->rapidez_max);
        o->empuje_z = func_8001C304(o->empuje_z << 4, e->rapidez_max);
        o->vel_y = vy;
    }
    o->x += o->empuje_x;
    o->y += o->vel_y;
    o->z += o->empuje_z;
    l.x = o->x;
    l.y = o->y - 0x16666;
    l.z = o->z;
    if (e->estado & 0x10) {
        o->empuje_x -= o->empuje_x >> 2;
        o->empuje_z -= o->empuje_z >> 2;
    } else {
        o->empuje_x -= o->empuje_x >> 3;
        o->empuje_z -= o->empuje_z >> 3;
    }
    if (func_8003AF48(&l) != 0) {
        e->suelo_normal[0] = l.normal[0];
        e->suelo_normal[1] = l.normal[1];
        e->suelo_normal[2] = l.normal[2];
        CAMPO_S32_50(o) = l.punto[1];
        if (l.punto[1] >= o->y - 0x51E) {
            o->vel_y += 0x51E;
        } else {
            n = l.normal[1];
            l.normal[0] >>= 4;
            l.normal[1] >>= 4;
            l.normal[2] >>= 4;
            if (n >= -0xC7FF) {
                /* cuesta muy empinada: resbala */
                if (n >= -0x7FFF) {
                    e->estado |= 8;
                    e->golpe = 30;
                }
                if (n < 0) {
                    n = -n;
                }
                n >>= 6;
                o->empuje_x += ((l.normal[0] * n) >> 8) >> 2;
                o->empuje_z += ((l.normal[2] * n) >> 8) >> 2;
                o->x += o->empuje_x;
                o->z += o->empuje_z;
            } else if (e->estado == 0) {
                e->estado = 0x10;
                o->vel_y = 0;
            }
            CAMPO_S32_50(o) = l.punto[1];
            o->y = l.punto[1];
            e->suelo_tipo = l.tipo;
        }
    } else if (nivel_actual == 13) {
        EstadoAnim *a = o->anim;
        EstadoAnim *ca = D_8007CB8C->anim;
        u16 *ct = D_8007CB8C->animaciones;
        u16 *t = o->animaciones;
        s32 i;

        o->vel_y += 0x51E;
        for (i = 0; i < D_8007CC1C; i++) {
            if (func_8004DB6C(&alto, o->x, o->y, o->z, D_800C98C4[i]) == 1 && o->y >= alto &&
                o->y - alto < 0x8000) {
                CAMPO_S32_50(o) = alto;
                o->y = alto;
                o->vel_y = 0;
                e->estado |= 0x10;
            }
        }
        if (o->y >= 0xA0001) {
            a->animacion = t[0];
            a->_50 = 0;
            a->_4E = 0x800;
            ca->animacion = ct[0];
            ca->_50 = 0;
            ca->_4E = 0x800;
            e->_1A = -1;
            e->_1B = -1;
            o->estado = 2;
        }
    }
    return DanoPorSuelo(o);
}
