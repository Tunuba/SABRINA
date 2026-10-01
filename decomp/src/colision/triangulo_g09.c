#include "juego.h"

/* Consulta de suelo (la misma de suelo.c). */
typedef struct {
    s32 x, y, z;
    u8 _0C[0x18];
    s32 dir[3];                      /* 0x24, hacia donde se mueve (24.8) */
    s32 punto_x;                     /* 0x30 */
    s32 altura;                      /* 0x34 */
    s32 punto_z;                     /* 0x38 */
    s32 normal[3];                   /* 0x3C */
} ConsultaSuelo;

/* Triangulo de colision: el primer campo apunta a su primer vertice (x, y, z en s16). */
typedef struct {
    s16 *v0;
    u8 _04[0x12];
    u16 tipo;                        /* 0x16, se salta si comparte un bit con D_8007CBD4 */
    s8 n[3];                         /* 0x18, la normal (a la mitad) */
    u8 ejes;                         /* 0x1B, los dos ejes que mira PuntoEnTriangulo */
} TrianguloCol;

extern s32 PuntoEnTriangulo(s32 *normal, s32 *punto, TrianguloCol *t);

/* Prueba si la posicion (x, z) de la consulta cae en el triangulo, a la altura de su primer vertice. Si
 * cae guarda el punto de contacto y la normal (pasada a 24.8). Devuelve si cayo. */
u8 func_8003A46C(ConsultaSuelo *c, TrianguloCol *t, s32 *normal) {
    s32 p[4];
    u8 dentro;

    p[0] = c->x;
    p[1] = t->v0[1];
    p[2] = c->z;
    /* PuntoEnTriangulo elige los dos ejes con dos bits del byte 0x1B del triangulo; si alguno vale 3 lee
     * p[3]. En el original p esta en sp+0x1C de un marco de 0x28, asi que p[3] es la primera palabra de la
     * pila del llamador (__builtin_dwarf_cfa es la pila al entrar). */
    p[3] = *(volatile s32 *)__builtin_dwarf_cfa();
    dentro = PuntoEnTriangulo(normal, p, t) != 0;
    if (dentro) {
        c->punto_x = p[0];
        c->altura = p[1];
        c->punto_z = p[2];
        c->normal[0] = normal[0] << 8;
        c->normal[1] = normal[1] << 8;
        c->normal[2] = normal[2] << 8;
    }
    return dentro;
}

extern u16 D_8007CBD4;               /* tipos de triangulo que no chocan */
extern s32 func_8001C33C(s32 *a, s32 *b);  /* producto punto */

/* Prueba si el movimiento de la consulta (desde x, y, z hacia dir) cruza el plano del triangulo de
 * frente y el punto de cruce cae dentro. Si cae guarda el punto y la normal (en 24.8) y devuelve 1. Si
 * n[0] + n[2] da 0 se prueba como suelo, con func_8003A46C. */
s32 func_8003A524(ConsultaSuelo *c, TrianguloCol *t) {
    /* normal, punto de cruce y primer vertice seguidos, como en la pila del original: PuntoEnTriangulo
     * puede leer un cuarto valor del punto, que es la x del vertice */
    s32 m[9];
    s32 *n = m, *p = m + 3, *v = m + 6;
    s32 hacia, desde, k;
    u8 dentro;

    if (t->tipo & D_8007CBD4) {
        return 0;
    }
    v[0] = t->v0[0];
    v[1] = t->v0[1];
    v[2] = t->v0[2];
    n[0] = t->n[0] * 2;
    n[1] = t->n[1] * 2;
    n[2] = t->n[2] * 2;
    hacia = func_8001C33C(n, c->dir);
    if (hacia >= 0) {
        return 0;
    }
    if (n[0] + n[2] == 0) {
        return func_8003A46C(c, t, n);
    }
    desde = -func_8001C33C(v, n);
    desde = -(desde + func_8001C33C(n, &c->x));
    if ((hacia * 2) >> 8 < desde) {
        return 0;
    }
    k = (desde << 8) / hacia;
    p[0] = c->x + ((c->dir[0] * k) >> 8);
    p[1] = c->y + ((c->dir[1] * k) >> 8);
    p[2] = c->z + ((c->dir[2] * k) >> 8);
    dentro = PuntoEnTriangulo(n, p, t) != 0;
    if (dentro) {
        c->punto_x = p[0];
        c->altura = p[1];
        c->punto_z = p[2];
        c->normal[0] = n[0] << 8;
        c->normal[1] = n[1] << 8;
        c->normal[2] = n[2] << 8;
    }
    return dentro;
}
