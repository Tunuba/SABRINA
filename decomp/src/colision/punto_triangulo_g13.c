#include "juego.h"

/* Triangulo de colision: sus tres vertices (x, y, z en s16) y, en +0x1B, los dos ejes en los que se mira
 * (bits 0-1 el primero, bits 2-3 el segundo). */
typedef struct {
    s16 *v[3];                       /* 0x00 */
    u8 _0C[0x0F];
    s8 ejes;                         /* 0x1B */
} TrianguloEjes;
EN(TrianguloEjes, ejes, 0x1B);

/* Prueba si el punto cae dentro del triangulo mirado en dos de sus ejes (los de t->ejes): cuenta cuantos
 * lados cruza una semirrecta desde el punto (de a 24.8 en las cuentas). Devuelve 1 si cae dentro. Un eje
 * de numero 3 lee punto[3], como el original. La normal no se usa. */
s32 PuntoEnTriangulo(s32 *normal, s32 *punto, TrianguloEjes *t) {
    s32 eu = t->ejes & 3;
    s32 ev = (t->ejes >> 2) & 3;
    s32 pu = punto[eu];
    s32 pv = punto[ev];
    s32 dentro = 0;
    s32 i, sa, sb, izq, der;
    s16 *a, *b;

    a = t->v[2];
    sa = a[ev] >= pv;
    for (i = 0; i < 3; i++) {
        b = t->v[i];
        sb = b[ev] >= pv;
        if (sa != sb) {
            izq = ((b[ev] - pv) * (a[eu] - b[eu])) >> 8;
            der = ((b[eu] - pu) * (a[ev] - b[ev])) >> 8;
            if (sb == (izq >= der)) {
                dentro = !dentro;
            }
        }
        a = b;
        sa = sb;
    }
    return dentro;
}
