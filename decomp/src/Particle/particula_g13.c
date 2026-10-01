#include "juego.h"

/* El paso de una particula. */

typedef struct {
    u8 _00[4];
    s32 pos[3];                      /* 0x04 */
    s32 vel[3];                      /* 0x10 */
    u8 r, g, b;                      /* 0x1C */
    u8 _1F[5];
    s32 tam;                         /* 0x24 */
    u8 _28[4];
    s32 acel[3];                     /* 0x2C */
    s32 crece;                       /* 0x38 */
    s32 cambio;                      /* 0x3C, lo que cambia el tamano en cada paso */
    s16 vida;                        /* 0x40, -1: se borra */
    u16 banderas;                    /* 0x42 */
    s16 giro;                        /* 0x44 */
} Particula;

extern s32 func_80014AEC(s32 v);     /* valor absoluto */

/* Banderas: 0x38 que hacer con el suelo (0x10 rebota, 0x20 se queda, 0x08 y otras se borra), 0x1C0 como
 * se mueve (0x40 frena, 0x80 gira, 0x100 va hacia un punto), 0x400 quieta, 0x200 rozamiento, 4 se borra
 * casi quieta, 0x1000 gira, 2 se borra al apagarse. */
void func_8001EDE4(Particula *p) {
    u16 f = p->banderas;
    s32 a, b;

    switch (f & 0x38) {
    case 0:
        break;
    case 0x10:
        if (p->acel[1] * 2 < p->vel[1]) {
            p->vel[0] >>= 1;
            p->vel[2] >>= 1;
            p->vel[1] = -p->vel[1] >> 1;
            break;
        }
        p->banderas = f & ~0x10;
        /* sigue */
    case 0x20:
        p->vel[0] = 0;
        p->vel[1] = 0;
        p->vel[2] = 0;
        p->acel[0] = 0;
        p->acel[1] = 0;
        p->acel[2] = 0;
        p->cambio *= 2;
        p->vida >>= 1;
        p->banderas &= 0xFE5F;
        break;
    default:
        p->vida = -1;
        break;
    }
    if (!(p->banderas & 0x400)) {
        switch (p->banderas & 0x1C0) {
        case 0x80:
            p->acel[0] = p->vel[2] >> 3;
            p->acel[2] = p->vel[0] >> 3;
            p->vel[0] += p->acel[0];
            p->vel[2] -= p->acel[2];
            p->vel[0] -= p->vel[0] >> 8;
            p->vel[2] -= p->vel[2] >> 8;
            break;
        case 0x40:
            a = p->vel[0];
            b = p->vel[2];
            p->vel[0] += p->acel[0];
            p->vel[2] += p->acel[2];
            if ((p->vel[0] ^ a) < 0) {
                p->vel[0] = 0;
                p->acel[0] = 0;
            }
            if ((p->vel[2] ^ b) < 0) {
                p->vel[2] = 0;
                p->acel[2] = 0;
            }
            if ((p->acel[0] | p->acel[2]) == 0) {
                p->banderas &= 0xFFBF;
            }
            break;
        case 0x100:
            p->vel[0] += (p->acel[0] - p->pos[0]) >> 3;
            p->vel[2] += (p->acel[2] - p->pos[2]) >> 3;
            break;
        default:
            p->vel[0] += p->acel[0];
            p->vel[2] += p->acel[2];
            break;
        }
        p->pos[0] += p->vel[0];
        p->pos[2] += p->vel[2];
        p->vel[1] += p->acel[1];
        p->pos[1] += p->vel[1];
    }
    if (p->banderas & 0x200) {
        p->vel[0] -= p->vel[0] >> 4;
        p->vel[1] -= p->vel[1] >> 4;
        p->vel[2] -= p->vel[2] >> 4;
    }
    if (p->banderas & 4) {
        a = func_80014AEC(p->vel[0]);
        a += func_80014AEC(p->vel[1]);
        if (func_80014AEC(p->vel[2]) + a < 0x28F) {
            p->vida = -1;
        }
    }
    if (p->banderas & 0x1000) {
        p->giro = (p->giro + 0x40) & 0xFFF;
    }
    if ((p->banderas & 2) && p->b + (p->r + p->g) < 0xF) {
        p->vida = -1;
    }
    if (p->cambio != 0) {
        a = p->tam + p->cambio;
        if (a < 0x10) {
            p->tam = 1;
            p->cambio = 0;
            p->vida = -1;
            return;
        }
        p->tam = a;
    }
}
