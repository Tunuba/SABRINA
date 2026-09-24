#include "nodo.h"

/* Giro de la matriz local de un nodo a partir de tres angulos (vuelta completa 0x1000). */

extern s32 rsin(s32 angulo);
extern s32 rcos(s32 angulo);
extern Matriz *MulMatrix0(Matriz *m0, Matriz *m1, Matriz *m2);   /* m2 = m0 * m1 */

/* Pone en la parte de giro de la matriz local el giro en x (ax), y la multiplica a la izquierda por el giro
 * en y (ay) y despues por el giro en z (az). La traslacion no se toca. */
void func_8001E7A8(Nodo *n, s32 ax, s32 ay, s32 az) {
    Matriz g;
    Matriz *m = &n->local;

    m->m[0][0] = 0x1000;
    m->m[0][1] = 0;
    m->m[0][2] = 0;
    m->m[1][0] = 0;
    m->m[1][1] = rcos(ax);
    m->m[1][2] = -rsin(ax);
    m->m[2][0] = 0;
    m->m[2][1] = rsin(ax);
    m->m[2][2] = rcos(ax);

    g.m[0][0] = rcos(ay);
    g.m[0][1] = 0;
    g.m[0][2] = rsin(ay);
    g.m[1][0] = 0;
    g.m[1][1] = 0x1000;
    g.m[1][2] = 0;
    g.m[2][0] = -rsin(ay);
    g.m[2][1] = 0;
    g.m[2][2] = rcos(ay);
    MulMatrix0(&g, m, m);

    g.m[0][0] = rcos(az);
    g.m[0][1] = -rsin(az);
    g.m[0][2] = 0;
    g.m[1][0] = rsin(az);
    g.m[1][1] = rcos(az);
    g.m[1][2] = 0;
    g.m[2][0] = 0;
    g.m[2][1] = 0;
    g.m[2][2] = 0x1000;
    MulMatrix0(&g, m, m);
}
