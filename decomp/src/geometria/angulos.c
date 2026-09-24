#include "juego.h"

extern s32 func_8001BF8C(s32 x1, s32 z1, s32 x2, s32 z2);   /* distancia entre dos puntos */
extern s32 func_8001BE8C(s32 x1, s32 z1, s32 x2, s32 z2);   /* angulo de un punto respecto de otro */

/* Los dos angulos que hacen mirar en la direccion v: el de giro sale del plano xz y el de inclinacion, de
 * la altura contra la distancia en ese plano. */
void func_80022104(s16 *inclinacion, s16 *giro, s32 *v) {
    s32 distancia = func_8001BF8C(0, 0, v[0], v[2]);

    *giro = func_8001BE8C(0, 0, v[0], v[2]);
    *inclinacion = func_8001BE8C(0, 0, v[1], distancia);
}

extern u8 D_800687B0[0x80];          /* tabla de arcotangente, un octavo de vuelta en 128 pasos */

/* Angulo desde el punto 2 hasta el punto 1 en el plano xz, en 0x1000 por vuelta. Se trabaja en el primer
 * octante con la tabla y despues se corrige por el cuadrante. */
s32 func_8001BE8C(s32 x1, s32 z1, s32 x2, s32 z2) {
    s32 dx = x1 - x2;
    s32 dz = z1 - z2;
    s8 cuadrante = 1;
    s32 a;
    s32 i;

    if (dx < 0) {
        cuadrante = 0;
        dx = -dx;
    }
    if (dz < 0) {
        cuadrante = (s8) (cuadrante | 2);
        dz = -dz;
    }
    if (dx < dz) {
        i = 0;
        if (dz != 0) {
            i = ((dx << 7) / dz) & 0x7F;
        }
        a = D_800687B0[i];
    } else if (dz < dx) {
        i = 0;
        if (dx != 0) {
            i = ((dz << 7) / dx) & 0x7F;
        }
        a = 0x40 - D_800687B0[i];
    } else {
        a = 0x20;
    }
    if (cuadrante == 1) {
        a = (-a) & 0xFF;
    }
    if (cuadrante == 2) {
        a = (0x80 - a) & 0xFF;
    }
    if (cuadrante == 3) {
        a = (a + 0x80) & 0xFF;
    }
    return (0x800 - (a << 4)) & 0xFFF;
}

extern s32 func_80014AEC(s32 v);     /* valor absoluto */

/* Distancia aproximada entre dos puntos del plano xz, sin raiz: la coordenada mas larga mas tres octavos
 * de la mas corta. */
s32 func_8001BF8C(s32 x1, s32 z1, s32 x2, s32 z2) {
    s32 dx = func_80014AEC(x1 - x2);
    s32 dz = func_80014AEC(z1 - z2);

    if (dz < dx) {
        return dx + (dz >> 3) * 3;
    }
    return dz + (dx >> 3) * 3;
}
