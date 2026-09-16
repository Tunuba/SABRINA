/* El monton de memoria del juego (membank.cpp): bloques seguidos en memoria, con listas de libres por
 * tamano. Cada bloque lleva su tamano al principio y repetido al final, asi se puede mirar el de atras. */
#ifndef BANCO_H
#define BANCO_H

#include "juego.h"

/* Cabecera de un bloque. En la palabra 0 va el tamano mas el bit 0, que vale 1 si esta ocupado. */
typedef struct Bloque {
    s32 cab;                         /* 0x00, tamano | 1 si esta ocupado */
    struct Bloque *sig;              /* 0x04, siguiente libre de su clase */
    struct Bloque *ant;              /* 0x08, anterior libre de su clase */
} Bloque;

/* Un banco de memoria: 0x38 listas de bloques libres, una por clase de tamano. */
typedef struct {
    u8 _00[0x0C];
    Bloque *libres[0x38];            /* 0x0C, hasta 0xEC */
    u8 _EC[4];
    u8 *ini;                         /* 0xF0, primer byte del monton */
    u8 *fin;                         /* 0xF4, el final */
    s32 libre;                       /* 0xF8, cuanto hay libre */
    s32 usado;                       /* 0xFC */
} Banco;
EN(Banco, libres, 0x0C);
EN(Banco, ini, 0xF0);
EN(Banco, libre, 0xF8);

#endif
