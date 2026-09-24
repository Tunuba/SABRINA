#include "gte.h"
#include "dibujo.h"
#include "modelo.h"

extern s32 D_8007CAC0;               /* donde va escribiendo la lista de dibujo */
extern u16 D_8007CA9C;               /* triangulos ya puestos en la lista de este cuadro */

/* Parte en tres un triangulo al que se le pasaron de largo los lados 1-2 y 0-2 (entrada 11 = 4 + 7 de la
 * tabla D_80068878). El triangulo ya esta en pantalla en la pieza que apunta D_8007CAC0 (la cola del
 * coprocesador aun tiene sus tres puntos): esa pieza solo sirve de molde, y los tres triangulos nuevos van
 * en las tres siguientes. Se sacan los puntos medios de los lados 1-2 y 0-2 (posicion, color y esquina de
 * la textura), se pasan a pantalla de una sola orden y queda:
 *   primero: 0, 1, medio02     segundo: medio02, 1, medio12     tercero: medio02, medio12, 2
 * El tercer vector de la orden rtpt no se llena: el juego pasa lo que haya en la pila y descarta su punto.
 * Los tres van a la lista en la misma z que el original. */
void func_80058EE4(Triangulo *t, s32 fin, s32 z) {
    TriTex *p1 = (TriTex *) D_8007CAC0 + 1;
    TriTex *p2 = (TriTex *) D_8007CAC0 + 2;
    TriTex *p3 = (TriTex *) D_8007CAC0 + 3;
    TriTex *molde;
    u8 *uv = t->u;
    Vertice *a, *b, *c;
    Vertice m12, m02, nada;
    s16 sxy[3][2];
    s16 m[3][2];
    u32 *ot;
    u8 u12, v12, u02, v02;

    gte_guardar_sxy0(sxy[0]);
    gte_guardar_sxy1(sxy[1]);
    gte_guardar_sxy2(sxy[2]);
    a = t->v[0];
    b = t->v[1];
    c = t->v[2];
    m12.x = (c->x + b->x) >> 1;
    m12.y = (c->y + b->y) >> 1;
    m12.z = (c->z + b->z) >> 1;
    m02.x = (a->x + c->x) >> 1;
    m02.y = (a->y + c->y) >> 1;
    m02.z = (a->z + c->z) >> 1;
    gte_poner_v0(&m12);
    gte_poner_v1(&m02);
    gte_poner_v2(&nada);
    molde = (TriTex *) D_8007CAC0;
    m12.r = (molde->r2 + molde->r1) >> 1;
    m12.g = (molde->g2 + molde->g1) >> 1;
    m12.b = (molde->b2 + molde->b1) >> 1;
    gte_rtpt();
    m02.r = (molde->r0 + molde->r2) >> 1;
    m02.g = (molde->g0 + molde->g2) >> 1;
    m02.b = (molde->b0 + molde->b2) >> 1;
    gte_guardar_sxy0(m[0]);
    gte_guardar_sxy1(m[1]);
    gte_guardar_sxy2(m[2]);
    u12 = (uv[4] + uv[2]) >> 1;
    v12 = (uv[5] + uv[3]) >> 1;
    u02 = (uv[0] + uv[4]) >> 1;
    v02 = (uv[1] + uv[5]) >> 1;

    p3->pagina = p2->pagina = p1->pagina = ((u16 *) t->textura)[6];
    p3->paleta = p2->paleta = p1->paleta = ((u16 *) t->textura)[7];
    if (t->textura->banderas & 1) {
        p1->codigo = p2->codigo = p3->codigo = p3->codigo | 2;
    }

    p3->x0 = p1->x2 = p2->x0 = m[1][0];
    p1->y2 = p2->y0 = p3->y0 = m[1][1];
    p1->x1 = p2->x1 = sxy[1][0];
    p1->y1 = p2->y1 = sxy[1][1];
    p3->x1 = p2->x2 = m[0][0];
    p3->y1 = p2->y2 = m[0][1];
    p3->x2 = sxy[2][0];
    p3->y2 = sxy[2][1];
    p1->x0 = sxy[0][0];
    p1->y0 = sxy[0][1];

    p1->r0 = ((TriTex *) D_8007CAC0)->r0;
    p1->g0 = ((TriTex *) D_8007CAC0)->g0;
    p1->b0 = ((TriTex *) D_8007CAC0)->b0;
    p1->r1 = p2->r1 = ((TriTex *) D_8007CAC0)->r1;
    p1->g1 = p2->g1 = ((TriTex *) D_8007CAC0)->g1;
    p1->b1 = p2->b1 = ((TriTex *) D_8007CAC0)->b1;
    p3->r0 = p2->r0 = p1->r2 = m02.r;
    p3->g0 = p2->g0 = p1->g2 = m02.g;
    p3->b0 = p2->b0 = p1->b2 = m02.b;
    p3->r1 = p2->r2 = m12.r;
    p3->g1 = p2->g2 = m12.g;
    p3->b1 = p2->b2 = m12.b;
    p3->r2 = ((TriTex *) D_8007CAC0)->r2;
    p3->g2 = ((TriTex *) D_8007CAC0)->g2;
    p3->b2 = ((TriTex *) D_8007CAC0)->b2;

    p1->u0 = uv[0];
    p1->v0 = uv[1];
    p3->u0 = p2->u0 = p1->u2 = u02;
    p3->v0 = p2->v0 = p1->v2 = v02;
    p1->u1 = p2->u1 = uv[2];
    p1->v1 = p2->v1 = uv[3];
    p3->u1 = p2->u2 = u12;
    p3->v1 = p2->v2 = v12;
    p3->u2 = uv[4];
    p3->v2 = uv[5];

    ot = (u32 *) (fin + (z << 2));
    AddPrim(ot, p1);
    AddPrim(ot, p2);
    AddPrim(ot, p3);
    D_8007CAC0 += 0xA0;
    D_8007CA9C += 3;
}
