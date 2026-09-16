/* El arbol de piezas de un modelo: cada nodo tiene su matriz local, la de mundo y sus hijos. */
#ifndef NODO_H
#define NODO_H

#include "juego.h"

/* La matriz de Sony: giro de 3x3 en 4.12 y traslacion, 0x20 bytes. */
typedef struct {
    s16 m[3][3];                     /* 0x00 */
    s16 _12;
    s32 t[3];                        /* 0x14 */
} Matriz;
EN(Matriz, t, 0x14);

typedef struct Nodo {
    u8 _00[4];
    struct Nodo *hijo;               /* 0x04 */
    struct Nodo *sig;                /* 0x08 */
    u8 _0C[8];
    Matriz local;                    /* 0x14, respecto del padre; su traslacion (0x28) es donde esta */
    Matriz mundo;                    /* 0x34; su traslacion (0x48) es la posicion en el mundo */
    u8 _54[4];
    void *dibujo;                    /* 0x58, lo que hay que dibujar */
    s16 visible;                     /* 0x5C */
    s16 triangulos;                  /* 0x5E, cuantos triangulos tiene el dibujo */
    u8 _60[4];
    u8 banderas;                     /* 0x64, bit 0 no dibujar, bit 1 la matriz de mundo esta al dia */
    u8 _65[3];
    u8 capa;                         /* 0x68 */
} Nodo;
EN(Nodo, hijo, 0x04);
EN(Nodo, local, 0x14);
EN(Nodo, mundo, 0x34);
EN(Nodo, dibujo, 0x58);
EN(Nodo, banderas, 0x64);
EN(Nodo, capa, 0x68);

#endif
