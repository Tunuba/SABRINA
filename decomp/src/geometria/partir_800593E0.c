#include "gte.h"
#include "dibujo.h"
#include "modelo.h"

extern s32 D_8007CAC0;               /* donde va escribiendo la lista de dibujo */
extern u16 D_8007CA9C;               /* triangulos ya puestos en la lista de este cuadro */

/* Entrada 1 de D_80068878: el lado del vertice 0 al 1 salio demasiado largo en pantalla.
 *
 * Al llegar, la pieza en D_8007CAC0 ya tiene el color de cada vertice y la cola de pantalla del
 * coprocesador guarda los tres puntos del triangulo (de la rtpt de func_8001FD50). Se sacan los puntos
 * medios de los lados 0-1 y 0-2 (posicion, color y esquina de la textura), se pasan a pantalla y el
 * triangulo se parte en tres:
 *   A = v0, m01, m02    B = m01, v1, m02    C = m02, v1, v2
 * que van en las tres piezas siguientes a la de D_8007CAC0. La pieza original se queda sin usar, pero el
 * espacio se avanza igual: cuatro piezas. La rtpt pasa tambien un tercer vector que nadie llena (y cuyo
 * resultado no se usa), como el juego. */
void func_800593E0(Triangulo *t, s32 fin, s32 z) {
    TriTex *base = (TriTex *) D_8007CAC0;
    TriTex *a = base + 1;
    TriTex *b = base + 2;
    TriTex *c = base + 3;
    Vertice medio[3];
    s16 orig[3][2];
    s16 nuevo[3][2];
    Vertice *v0 = t->v[0];
    Vertice *v1 = t->v[1];
    Vertice *v2 = t->v[2];
    u8 *uv = t->u;                   /* u0, v0, u1, v1, u2, v2 */
    u16 *tex = (u16 *) t->textura;
    u8 u01, v01, u02, v02;
    u8 codigo;
    u32 *lista;

    gte_guardar_sxy0(orig[0]);
    gte_guardar_sxy1(orig[1]);
    gte_guardar_sxy2(orig[2]);

    medio[0].x = (v1->x + v0->x) >> 1;
    medio[0].y = (v1->y + v0->y) >> 1;
    medio[0].z = (v1->z + v0->z) >> 1;
    medio[1].x = (v0->x + v2->x) >> 1;
    medio[1].y = (v0->y + v2->y) >> 1;
    medio[1].z = (v0->z + v2->z) >> 1;

    gte_poner_v0(&medio[0]);
    gte_poner_v1(&medio[1]);
    gte_poner_v2(&medio[2]);

    base = (TriTex *) D_8007CAC0;
    medio[0].r = (base->r1 + base->r0) >> 1;
    medio[0].g = (base->g1 + base->g0) >> 1;
    medio[0].b = (base->b1 + base->b0) >> 1;
    gte_rtpt();
    medio[1].r = (base->r0 + base->r2) >> 1;
    medio[1].g = (base->g0 + base->g2) >> 1;
    medio[1].b = (base->b0 + base->b2) >> 1;

    gte_guardar_sxy0(nuevo[0]);
    gte_guardar_sxy1(nuevo[1]);
    gte_guardar_sxy2(nuevo[2]);

    u01 = (uv[2] + uv[0]) >> 1;
    v01 = (uv[3] + uv[1]) >> 1;
    u02 = (uv[0] + uv[4]) >> 1;
    v02 = (uv[1] + uv[5]) >> 1;

    c->pagina = b->pagina = a->pagina = tex[6];
    c->paleta = b->paleta = a->paleta = tex[7];
    if (t->textura->banderas & 1) {
        codigo = c->codigo | 2;
        c->codigo = codigo;
        b->codigo = codigo;
        a->codigo = codigo;
    }

    a->x0 = orig[0][0];
    a->y0 = orig[0][1];
    b->x0 = a->x1 = nuevo[0][0];
    b->y0 = a->y1 = nuevo[0][1];
    c->x0 = b->x2 = a->x2 = nuevo[1][0];
    c->y0 = b->y2 = a->y2 = nuevo[1][1];
    c->x1 = b->x1 = orig[1][0];
    c->y1 = b->y1 = orig[1][1];
    c->x2 = orig[2][0];
    c->y2 = orig[2][1];

    a->r0 = ((TriTex *) D_8007CAC0)->r0;
    a->g0 = ((TriTex *) D_8007CAC0)->g0;
    a->b0 = ((TriTex *) D_8007CAC0)->b0;
    c->r1 = b->r1 = ((TriTex *) D_8007CAC0)->r1;
    c->g1 = b->g1 = ((TriTex *) D_8007CAC0)->g1;
    c->b1 = b->b1 = ((TriTex *) D_8007CAC0)->b1;
    c->r2 = ((TriTex *) D_8007CAC0)->r2;
    c->g2 = ((TriTex *) D_8007CAC0)->g2;
    c->b2 = ((TriTex *) D_8007CAC0)->b2;
    b->r0 = a->r1 = medio[0].r;
    b->g0 = a->g1 = medio[0].g;
    b->b0 = a->b1 = medio[0].b;
    c->r0 = b->r2 = a->r2 = medio[1].r;
    c->g0 = b->g2 = a->g2 = medio[1].g;
    c->b0 = b->b2 = a->b2 = medio[1].b;

    a->u0 = uv[0];
    a->v0 = uv[1];
    b->u0 = a->u1 = u01;
    b->v0 = a->v1 = v01;
    c->u1 = b->u1 = uv[2];
    c->v1 = b->v1 = uv[3];
    c->u0 = b->u2 = a->u2 = u02;
    c->v0 = b->v2 = a->v2 = v02;
    c->u2 = uv[4];
    c->v2 = uv[5];

    lista = (u32 *) (fin + (z << 2));
    AddPrim(lista, a);
    AddPrim(lista, b);
    AddPrim(lista, c);
    D_8007CAC0 += 0xA0;
    D_8007CA9C += 3;
}
