/* Las piezas de un modelo del .INO: vertices, triangulos y texturas. */
#ifndef MODELO_H
#define MODELO_H

#include "juego.h"

typedef struct {
    s16 x, y, z;                     /* 0x00 */
    s16 _06;
    u8 r, g, b;                      /* 0x08 */
    u8 _0B;
} Vertice;

/* Lo que el juego guarda de cada textura cargada; solo se entiende el byte de banderas. */
typedef struct {
    u8 _00[0x1C];
    u8 banderas;                     /* 0x1C, bit 0 se mezcla con lo de abajo, bit 2 se ve de los dos lados */
    u8 _1D[3];
} Textura;
EN(Textura, banderas, 0x1C);

/* Triangulo de 28 bytes, tal como viene en el archivo. */
typedef struct {
    Vertice *v[3];                   /* 0x00 */
    Textura *textura;                /* 0x0C */
    u8 u[3], v_[3];                  /* 0x10, las esquinas en la textura */
    u8 _16[6];
} Triangulo;
EN(Triangulo, textura, 0x0C);

#endif
