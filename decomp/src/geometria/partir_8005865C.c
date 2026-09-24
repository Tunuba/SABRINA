#include "gte.h"
#include "dibujo.h"
#include "modelo.h"

extern s32 D_8007CAC0;               /* donde va escribiendo la lista de dibujo */
extern u16 D_8007CA9C;               /* triangulos ya puestos en la lista de este cuadro */

/* Parte en dos un triangulo al que se le paso de largo el lado del vertice 0 al 2 (entrada 7 de la tabla
 * D_80068878). El triangulo ya esta en pantalla en la pieza que apunta D_8007CAC0 (la cola del
 * coprocesador aun tiene sus tres puntos): esa pieza solo sirve de molde, y los dos triangulos nuevos van
 * en las dos siguientes. Se saca el punto medio del lado 0-2 (posicion, color y esquina de la textura), se
 * pasa a pantalla y queda:
 *   primero: 0, 1, medio        segundo: 1, 2, medio
 * Los dos van a la lista en la misma z que el original. En el Triangulo las esquinas de la textura van
 * de a pares (u, v) desde 0x10. */
void func_8005865C(Triangulo *t, s32 fin, s32 z) {
    TriTex *molde = (TriTex *) D_8007CAC0;
    TriTex *p1 = molde + 1;
    TriTex *p2 = molde + 2;
    u8 *uv = t->u;
    Vertice *a, *c;
    Vertice medio;
    s16 sxy[3][2];
    s16 m[2];
    u32 *ot;
    u8 mu, mv;

    gte_guardar_sxy0(sxy[0]);
    gte_guardar_sxy1(sxy[1]);
    gte_guardar_sxy2(sxy[2]);
    a = t->v[0];
    c = t->v[2];
    medio.x = (a->x + c->x) >> 1;
    medio.y = (a->y + c->y) >> 1;
    medio.z = (a->z + c->z) >> 1;
    gte_poner_v0(&medio);
    molde = (TriTex *) D_8007CAC0;
    medio.r = (molde->r0 + molde->r2) >> 1;
    medio.g = (molde->g0 + molde->g2) >> 1;
    medio.b = (molde->b0 + molde->b2) >> 1;
    gte_rtps();
    mu = (uv[0] + uv[4]) >> 1;
    mv = (uv[1] + uv[5]) >> 1;
    gte_guardar_sxy2(m);

    if (t->textura->banderas & 1) {
        p1->codigo = p2->codigo = p2->codigo | 2;
    }
    p2->pagina = p1->pagina = ((u16 *) t->textura)[6];
    p2->paleta = p1->paleta = ((u16 *) t->textura)[7];

    p1->x0 = sxy[0][0];
    p1->y0 = sxy[0][1];
    p2->x0 = p1->x1 = sxy[1][0];
    p2->y0 = p1->y1 = sxy[1][1];
    p2->x2 = p1->x2 = m[0];
    p2->y2 = p1->y2 = m[1];
    p2->x1 = sxy[2][0];
    p2->y1 = sxy[2][1];

    p1->r0 = ((TriTex *) D_8007CAC0)->r0;
    p1->g0 = ((TriTex *) D_8007CAC0)->g0;
    p1->b0 = ((TriTex *) D_8007CAC0)->b0;
    p2->r0 = p1->r1 = ((TriTex *) D_8007CAC0)->r1;
    p2->g0 = p1->g1 = ((TriTex *) D_8007CAC0)->g1;
    p2->b0 = p1->b1 = ((TriTex *) D_8007CAC0)->b1;
    p2->r2 = p1->r2 = medio.r;
    p2->g2 = p1->g2 = medio.g;
    p2->b2 = p1->b2 = medio.b;
    p2->r1 = ((TriTex *) D_8007CAC0)->r2;
    p2->g1 = ((TriTex *) D_8007CAC0)->g2;
    p2->b1 = ((TriTex *) D_8007CAC0)->b2;

    p1->u0 = uv[0];
    p1->v0 = uv[1];
    p2->u0 = p1->u1 = uv[2];
    p2->v0 = p1->v1 = uv[3];
    p2->u2 = p1->u2 = mu;
    p2->v2 = p1->v2 = mv;
    p2->u1 = uv[4];
    p2->v1 = uv[5];

    ot = (u32 *) (fin + (z << 2));
    AddPrim(ot, p1);
    AddPrim(ot, p2);
    D_8007CAC0 += 0x78;
    D_8007CA9C += 2;
}
