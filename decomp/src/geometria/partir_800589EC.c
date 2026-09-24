#include "gte.h"
#include "dibujo.h"
#include "modelo.h"

extern s32 D_8007CAC0;               /* donde va escribiendo la lista de dibujo */
extern u16 D_8007CA9C;               /* triangulos ya puestos en la lista de este cuadro */

/* Partidor 5 de la tabla D_80068878 (se pasaron de largo los lados 0-1 y 1-2): parte el triangulo en tres
 * con los puntos medios de esos dos lados, m01 y m12:
 *
 *     A = (v0, m01, m12)    B = (m01, v1, m12)    C = (v0, m12, v2)
 *
 * El llamador ya paso el triangulo por rtpt, asi que los tres puntos de pantalla de v0, v1 y v2 siguen en
 * la cola del coprocesador; solo hay que pasar a pantalla los dos puntos medios. El color de cada punto
 * medio sale del que ya se le puso a la pieza en D_8007CAC0 (func_8001FD28), que se queda sin usar: las
 * tres piezas nuevas van en las tres siguientes y la lista avanza cuatro. Cada una va al mismo lugar de la
 * lista (la z que calculo el llamador). */
void func_800589EC(Triangulo *t, s32 fin, s32 z) {
    TriTex *a = (TriTex *) (D_8007CAC0 + 0x28);
    TriTex *b = (TriTex *) (D_8007CAC0 + 0x50);
    TriTex *c = (TriTex *) (D_8007CAC0 + 0x78);
    TriTex *p;
    Vertice medio[3];                /* el tercero no se llena: el juego lo manda asi a rtpt y no lo usa */
    s16 antes[6];                    /* v0, v1 y v2 en pantalla */
    s16 ahora[6];                    /* m01, m12 y lo que salga del tercero */
    u8 *uv = t->u;                   /* u0 v0 u1 v1 u2 v2 */
    u8 u01, v01, u12, v12;
    u16 dato;
    u8 codigo;
    s32 lista;

    gte_guardar_sxy0(&antes[0]);
    gte_guardar_sxy1(&antes[2]);
    gte_guardar_sxy2(&antes[4]);

    medio[0].x = (t->v[1]->x + t->v[0]->x) >> 1;
    medio[0].y = (t->v[1]->y + t->v[0]->y) >> 1;
    medio[0].z = (t->v[1]->z + t->v[0]->z) >> 1;
    medio[1].x = (t->v[2]->x + t->v[1]->x) >> 1;
    medio[1].y = (t->v[2]->y + t->v[1]->y) >> 1;
    medio[1].z = (t->v[2]->z + t->v[1]->z) >> 1;
    gte_poner_v0(&medio[0]);
    gte_poner_v1(&medio[1]);
    gte_poner_v2(&medio[2]);

    p = (TriTex *) D_8007CAC0;
    medio[0].r = (p->r1 + p->r0) >> 1;
    medio[0].g = (p->g1 + p->g0) >> 1;
    medio[0].b = (p->b1 + p->b0) >> 1;
    gte_rtpt();
    medio[1].r = (p->r2 + p->r1) >> 1;
    medio[1].g = (p->g2 + p->g1) >> 1;
    medio[1].b = (p->b2 + p->b1) >> 1;
    gte_guardar_sxy0(&ahora[0]);
    gte_guardar_sxy1(&ahora[2]);
    gte_guardar_sxy2(&ahora[4]);

    u01 = (uv[2] + uv[0]) >> 1;
    v01 = (uv[3] + uv[1]) >> 1;
    u12 = (uv[4] + uv[2]) >> 1;
    v12 = (uv[5] + uv[3]) >> 1;

    dato = *(u16 *) ((u8 *) t->textura + 0xC);
    c->pagina = dato;
    b->pagina = dato;
    a->pagina = dato;
    dato = *(u16 *) ((u8 *) t->textura + 0xE);
    c->paleta = dato;
    b->paleta = dato;
    a->paleta = dato;
    if (t->textura->banderas & 1) {
        codigo = c->codigo | 2;
        c->codigo = codigo;
        b->codigo = codigo;
        a->codigo = codigo;
    }

    /* Los puntos de pantalla. */
    c->x0 = antes[0];
    a->x0 = antes[0];
    c->y0 = antes[1];
    a->y0 = antes[1];
    b->x0 = ahora[0];
    a->x1 = ahora[0];
    b->y0 = ahora[1];
    a->y1 = ahora[1];
    c->x1 = ahora[2];
    b->x2 = ahora[2];
    a->x2 = ahora[2];
    c->y1 = ahora[3];
    b->y2 = ahora[3];
    a->y2 = ahora[3];
    b->x1 = antes[2];
    b->y1 = antes[3];
    c->x2 = antes[4];
    c->y2 = antes[5];

    /* Los colores. */
    c->r0 = ((TriTex *) D_8007CAC0)->r0;
    a->r0 = ((TriTex *) D_8007CAC0)->r0;
    c->g0 = ((TriTex *) D_8007CAC0)->g0;
    a->g0 = ((TriTex *) D_8007CAC0)->g0;
    c->b0 = ((TriTex *) D_8007CAC0)->b0;
    a->b0 = ((TriTex *) D_8007CAC0)->b0;
    b->r0 = medio[0].r;
    a->r1 = medio[0].r;
    b->g0 = medio[0].g;
    a->g1 = medio[0].g;
    b->b0 = medio[0].b;
    a->b1 = medio[0].b;
    c->r1 = medio[1].r;
    b->r2 = medio[1].r;
    a->r2 = medio[1].r;
    c->g1 = medio[1].g;
    b->g2 = medio[1].g;
    a->g2 = medio[1].g;
    c->b1 = medio[1].b;
    b->b2 = medio[1].b;
    a->b2 = medio[1].b;
    b->r1 = ((TriTex *) D_8007CAC0)->r1;
    b->g1 = ((TriTex *) D_8007CAC0)->g1;
    b->b1 = ((TriTex *) D_8007CAC0)->b1;
    c->r2 = ((TriTex *) D_8007CAC0)->r2;
    c->g2 = ((TriTex *) D_8007CAC0)->g2;
    c->b2 = ((TriTex *) D_8007CAC0)->b2;

    /* Las esquinas en la textura. */
    c->u0 = uv[0];
    a->u0 = uv[0];
    c->v0 = uv[1];
    a->v0 = uv[1];
    b->u0 = u01;
    a->u1 = u01;
    b->v0 = v01;
    a->v1 = v01;
    c->u1 = u12;
    b->u2 = u12;
    a->u2 = u12;
    c->v1 = v12;
    b->v2 = v12;
    a->v2 = v12;
    b->u1 = uv[2];
    b->v1 = uv[3];
    c->u2 = uv[4];
    c->v2 = uv[5];

    lista = fin + (z << 2);
    AddPrim((u32 *) lista, a);
    AddPrim((u32 *) lista, b);
    AddPrim((u32 *) lista, c);
    D_8007CAC0 += 0xA0;
    D_8007CA9C += 3;
}
