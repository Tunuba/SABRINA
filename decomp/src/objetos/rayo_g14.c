#include "objeto.h"

/* Un rayo de particulas entre dos objetos. */

extern u8 *CrearParticula(s32 tipo, Objeto *o, s32 b, s32 x, s32 y, s32 z, s32 dx, s32 dy, s32 dz, s32 c,
                          s32 d, s32 e, s32 f, s32 g, s32 h);
extern s32 func_8002225C(u8 *o, s32 dx, s32 dy, s32 dz);   /* largo de un vector */
extern s32 func_80021CE4(s32 n);     /* al azar */

#define C32(p, d) (*(s32 *)((u8 *)(p) + (d)))

/* Parte el camino de a hasta b en tramos de unos `paso` de largo y une los puntos con particulas del tipo
 * dado; cada punto intermedio se corre al azar hasta paso/4 para cada lado. */
void func_8003B894(u8 *a, u8 *b, s32 paso, s32 tipo) {
    s32 p[3];
    s32 d[3];
    s32 x, y, z, nx, ny, nz;
    s32 mitad, cuarto;
    s16 k, v;

    p[0] = C32(a, 0x24);
    p[1] = C32(a, 0x28);
    p[2] = C32(a, 0x2C);
    d[0] = RESTA_TRAMPA(C32(b, 0x24), p[0]);
    d[1] = RESTA_TRAMPA(C32(b, 0x28), p[1]);
    d[2] = RESTA_TRAMPA(C32(b, 0x2C), p[2]);
    k = func_8002225C(a, d[0], d[1], d[2]) / paso;
    x = p[0];
    y = p[1];
    z = p[2];
    cuarto = paso >> 2;
    mitad = paso >> 1;
    d[0] /= k;
    d[1] /= k;
    d[2] /= k;
    for (;;) {
        v = k;
        k = v - 1;
        if (v < 2) {
            break;
        }
        p[0] = SUMA_TRAMPA(p[0], d[0]);
        p[1] = SUMA_TRAMPA(p[1], d[1]);
        p[2] = SUMA_TRAMPA(p[2], d[2]);
        nx = SUMA_TRAMPA(p[0], RESTA_TRAMPA(func_80021CE4(mitad), cuarto));
        ny = SUMA_TRAMPA(p[1], RESTA_TRAMPA(func_80021CE4(mitad), cuarto));
        nz = SUMA_TRAMPA(p[2], RESTA_TRAMPA(func_80021CE4(mitad), cuarto));
        CrearParticula((s8)tipo, NULL, 0, x, y, z, RESTA_TRAMPA(nx, x), RESTA_TRAMPA(ny, y), RESTA_TRAMPA(nz, z),
                       0, 0, 0, 0xF, 0x402, 0);
        x = nx;
        y = ny;
        z = nz;
    }
    CrearParticula((s8)tipo, NULL, 0, x, y, z, RESTA_TRAMPA(C32(b, 0x24), x), RESTA_TRAMPA(C32(b, 0x28), y),
                   RESTA_TRAMPA(C32(b, 0x2C), z), 0, 0, 0, 0xF, 0x402, 0);
}
