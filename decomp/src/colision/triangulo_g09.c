#include "juego.h"

/* Consulta de suelo (la misma de suelo.c). */
typedef struct {
    s32 x, y, z;
    u8 _0C[0x24];
    s32 punto_x;                     /* 0x30 */
    s32 altura;                      /* 0x34 */
    s32 punto_z;                     /* 0x38 */
    s32 normal[3];                   /* 0x3C */
} ConsultaSuelo;

/* Triangulo de colision: el primer campo apunta a su primer vertice (x, y, z en s16). */
typedef struct {
    s16 *v0;
} TrianguloCol;

extern s32 PuntoEnTriangulo(s32 *normal, s32 *punto, TrianguloCol *t);

/* Prueba si la posicion (x, z) de la consulta cae en el triangulo, a la altura de su primer vertice. Si
 * cae guarda el punto de contacto y la normal (pasada a 24.8). Devuelve si cayo. */
u8 func_8003A46C(ConsultaSuelo *c, TrianguloCol *t, s32 *normal) {
    s32 p[3];
    u8 dentro;

    p[0] = c->x;
    p[1] = t->v0[1];
    p[2] = c->z;
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
