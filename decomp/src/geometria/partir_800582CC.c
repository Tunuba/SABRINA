#include "gte.h"
#include "dibujo.h"
#include "modelo.h"

extern s32 D_8007CAC0;               /* donde va escribiendo la lista de dibujo */
extern u16 D_8007CA9C;               /* triangulos ya puestos en la lista de este cuadro */

/* Entrada 4 de D_80068878: parte en dos un triangulo cuyo lado v1-v2 salio demasiado largo en pantalla.
 * Lo llama func_8001FD50 con el triangulo recien pasado a pantalla (los tres puntos siguen en la cola del
 * coprocesador) y con la pieza de D_8007CAC0 ya llena de textura y colores. Saca el punto medio del lado
 * (posicion, color y esquina de textura), lo pasa a pantalla y arma dos piezas nuevas justo detras de la
 * primera: (v0, v1, medio) y (v0, medio, v2). Las dos van a la misma z de la lista. */
void func_800582CC(Triangulo *t, s32 fin, s32 z) {
    TriTex *p = (TriTex *) D_8007CAC0;
    TriTex *a = (TriTex *) (D_8007CAC0 + 0x28);
    TriTex *b = (TriTex *) (D_8007CAC0 + 0x50);
    u8 *uv = t->u;                   /* u0 v0 u1 v1 u2 v2 */
    Vertice *v1, *v2;
    s16 medio[4];
    u8 color[3];
    s16 pant[6];
    s16 nuevo[2];
    u8 um, vm;
    u32 *lista;

    gte_guardar_sxy0(&pant[0]);
    gte_guardar_sxy1(&pant[2]);
    gte_guardar_sxy2(&pant[4]);
    v1 = t->v[1];
    v2 = t->v[2];
    medio[0] = (v2->x + v1->x) >> 1;
    medio[1] = (v2->y + v1->y) >> 1;
    medio[2] = (v2->z + v1->z) >> 1;
    gte_poner_v0(medio);
    p = (TriTex *) D_8007CAC0;
    color[0] = (p->r2 + p->r1) >> 1;
    color[1] = (p->g2 + p->g1) >> 1;
    color[2] = (p->b2 + p->b1) >> 1;
    gte_rtps();
    um = (uv[4] + uv[2]) >> 1;
    vm = (uv[5] + uv[3]) >> 1;
    gte_guardar_sxy2(nuevo);

    if (t->textura->banderas & 1) {
        u8 c = b->codigo | 2;
        b->codigo = c;
        a->codigo = c;
    }
    b->pagina = a->pagina = ((u16 *) t->textura)[6];
    b->paleta = a->paleta = ((u16 *) t->textura)[7];

    b->x0 = a->x0 = pant[0];
    b->y0 = a->y0 = pant[1];
    a->x1 = pant[2];
    a->y1 = pant[3];
    b->x1 = a->x2 = nuevo[0];
    b->y1 = a->y2 = nuevo[1];
    b->x2 = pant[4];
    b->y2 = pant[5];

    b->r0 = a->r0 = ((TriTex *) D_8007CAC0)->r0;
    b->g0 = a->g0 = ((TriTex *) D_8007CAC0)->g0;
    b->b0 = a->b0 = ((TriTex *) D_8007CAC0)->b0;
    a->r1 = ((TriTex *) D_8007CAC0)->r1;
    a->g1 = ((TriTex *) D_8007CAC0)->g1;
    a->b1 = ((TriTex *) D_8007CAC0)->b1;
    b->r1 = a->r2 = color[0];
    b->g1 = a->g2 = color[1];
    b->b1 = a->b2 = color[2];
    b->r2 = ((TriTex *) D_8007CAC0)->r2;
    b->g2 = ((TriTex *) D_8007CAC0)->g2;
    b->b2 = ((TriTex *) D_8007CAC0)->b2;

    b->u0 = a->u0 = uv[0];
    b->v0 = a->v0 = uv[1];
    a->u1 = uv[2];
    a->v1 = uv[3];
    b->u1 = a->u2 = um;
    b->v1 = a->v2 = vm;
    b->u2 = uv[4];
    b->v2 = uv[5];

    lista = (u32 *) (fin + (z << 2));
    AddPrim(lista, a);
    AddPrim(lista, b);
    D_8007CAC0 += 0x78;
    D_8007CA9C += 2;
}
