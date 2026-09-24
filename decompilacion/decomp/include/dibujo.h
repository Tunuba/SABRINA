/* Lo que se le manda al dibujante: los triangulos y cuadrados que van a la lista de dibujo (la OT), que
 * el juego arma en un espacio corrido y encadena por profundidad. */
#ifndef DIBUJO_H
#define DIBUJO_H

#include "juego.h"

/* Cuadrado con textura y un solo color, 0x28 bytes (el POLY_FT4 de Sony). */
typedef struct {
    u32 etiqueta;                    /* 0x00, el que sigue en la lista y el largo */
    u8 r, g, b, codigo;              /* 0x04, bit 1 del codigo: mezclar con lo que hay debajo */
    s16 x0, y0;                      /* 0x08 */
    u8 u0, v0;                       /* 0x0C */
    u16 paleta;                      /* 0x0E */
    s16 x1, y1;                      /* 0x10 */
    u8 u1, v1;                       /* 0x14 */
    u16 pagina;                      /* 0x16 */
    s16 x2, y2;                      /* 0x18 */
    u8 u2, v2;                       /* 0x1C */
    u16 _1E;
    s16 x3, y3;                      /* 0x20 */
    u8 u3, v3;                       /* 0x24 */
    u16 _26;
} CuadroTex;
EN(CuadroTex, x0, 0x08);
EN(CuadroTex, x1, 0x10);
EN(CuadroTex, x2, 0x18);
EN(CuadroTex, x3, 0x20);
EN(CuadroTex, pagina, 0x16);

/* Triangulo con textura y un color por vertice, 0x28 bytes (el POLY_GT3 de Sony). */
typedef struct {
    u32 etiqueta;                    /* 0x00 */
    u8 r0, g0, b0, codigo;           /* 0x04 */
    s16 x0, y0;                      /* 0x08 */
    u8 u0, v0;                       /* 0x0C */
    u16 paleta;                      /* 0x0E */
    u8 r1, g1, b1, _13;              /* 0x10 */
    s16 x1, y1;                      /* 0x14 */
    u8 u1, v1;                       /* 0x18 */
    u16 pagina;                      /* 0x1A */
    u8 r2, g2, b2, _1F;              /* 0x1C */
    s16 x2, y2;                      /* 0x20 */
    u8 u2, v2;                       /* 0x24 */
    u16 _26;
} TriTex;
EN(TriTex, x0, 0x08);
EN(TriTex, x1, 0x14);
EN(TriTex, x2, 0x20);

extern void AddPrim(u32 *lista, void *pieza);
extern s32 rsin(s32 angulo);         /* seno y coseno en 4.12, vuelta completa 0x1000 */
extern s32 rcos(s32 angulo);

#endif
