#include "gte.h"
#include "dibujo.h"
#include "modelo.h"

extern s32 D_8007CAC0;               /* donde va escribiendo la lista de dibujo */
extern u16 D_8007CA9C;               /* triangulos ya puestos en la lista de este cuadro */

/* Un punto de pantalla tal como lo deja el coprocesador (SXY): x e y de 16 bits. */
typedef struct {
    s16 x, y;
} PuntoPantalla;

/* Parte en cuatro el triangulo que func_8001FD50 acaba de pasar a pantalla (y cuyo TriTex ya esta en
 * D_8007CAC0 con la textura puesta) cuando el coprocesador marco que algo se salio de rango. Toma los
 * puntos medios de los tres lados (posicion, color y esquina de textura), los pasa a pantalla y arma
 * cuatro TriTex nuevos a continuacion del original:
 *   P = (0, m01, m20), A = (m20, m12, 2), B = (m20, m01, m12), C = (m01, 1, m12).
 * Los cuatro van a la lista en la z del triangulo entero. El TriTex original no se usa como pieza: solo
 * se leen de el sus colores. */
void func_800598DC(Triangulo *t, s32 fin, s32 z) {
    PuntoPantalla viejo[3];          /* los tres vertices en pantalla, del rtpt de quien llama */
    PuntoPantalla nuevo[3];          /* los tres puntos medios en pantalla: m01, m12, m20 */
    Vertice medio[3];                /* m01, m12, m20 */
    TriTex *base;
    TriTex *p, *a, *b, *c;
    Vertice *v0, *v1, *v2;
    u8 *uv;
    u8 u01, v01, u12, v12, u20, v20;
    u16 valor;
    u32 *lista;

    base = (TriTex *) D_8007CAC0;
    p = base + 1;
    a = base + 2;
    b = base + 3;
    c = base + 4;

    gte_guardar_sxy0(&viejo[0]);
    gte_guardar_sxy1(&viejo[1]);
    gte_guardar_sxy2(&viejo[2]);

    v0 = t->v[0];
    v1 = t->v[1];
    v2 = t->v[2];
    medio[0].x = (v1->x + v0->x) >> 1;
    medio[0].y = (v1->y + v0->y) >> 1;
    medio[0].z = (v1->z + v0->z) >> 1;
    medio[1].x = (v2->x + v1->x) >> 1;
    medio[1].y = (v2->y + v1->y) >> 1;
    medio[1].z = (v2->z + v1->z) >> 1;
    medio[2].x = (v0->x + v2->x) >> 1;
    medio[2].y = (v0->y + v2->y) >> 1;
    medio[2].z = (v0->z + v2->z) >> 1;

    gte_poner_v0(&medio[0]);
    gte_poner_v1(&medio[1]);
    gte_poner_v2(&medio[2]);

    base = (TriTex *) D_8007CAC0;
    medio[0].r = (base->r1 + base->r0) >> 1;
    medio[0].g = (base->g1 + base->g0) >> 1;
    medio[0].b = (base->b1 + base->b0) >> 1;
    gte_rtpt();
    medio[1].r = (base->r2 + base->r1) >> 1;
    medio[1].g = (base->g2 + base->g1) >> 1;
    medio[1].b = (base->b2 + base->b1) >> 1;
    medio[2].r = (base->r0 + base->r2) >> 1;
    medio[2].g = (base->g0 + base->g2) >> 1;
    medio[2].b = (base->b0 + base->b2) >> 1;

    gte_guardar_sxy0(&nuevo[0]);
    gte_guardar_sxy1(&nuevo[1]);
    gte_guardar_sxy2(&nuevo[2]);

    /* Esquinas de textura: (u, v) de cada vertice, corridas de a dos bytes. */
    uv = t->u;
    u01 = (uv[2] + uv[0]) >> 1;
    v01 = (uv[3] + uv[1]) >> 1;
    u12 = (uv[4] + uv[2]) >> 1;
    v12 = (uv[5] + uv[3]) >> 1;
    u20 = (uv[0] + uv[4]) >> 1;
    v20 = (uv[1] + uv[5]) >> 1;

    valor = *(u16 *) ((u8 *) t->textura + 0xC);
    c->pagina = valor;
    b->pagina = valor;
    a->pagina = valor;
    p->pagina = valor;
    valor = *(u16 *) ((u8 *) t->textura + 0xE);
    c->paleta = valor;
    b->paleta = valor;
    a->paleta = valor;
    p->paleta = valor;
    if (t->textura->banderas & 1) {
        u8 codigo = c->codigo | 2;

        c->codigo = codigo;
        b->codigo = codigo;
        a->codigo = codigo;
        p->codigo = codigo;
    }

    /* Puntos de pantalla. */
    p->x0 = viejo[0].x;
    p->y0 = viejo[0].y;
    a->x2 = viejo[2].x;
    a->y2 = viejo[2].y;
    c->x1 = viejo[1].x;
    c->y1 = viejo[1].y;
    c->x0 = b->x1 = p->x1 = nuevo[0].x;
    c->y0 = b->y1 = p->y1 = nuevo[0].y;
    b->x0 = a->x0 = p->x2 = nuevo[2].x;
    b->y0 = a->y0 = p->y2 = nuevo[2].y;
    c->x2 = b->x2 = a->x1 = nuevo[1].x;
    c->y2 = b->y2 = a->y1 = nuevo[1].y;

    /* Colores. */
    p->r0 = ((TriTex *) D_8007CAC0)->r0;
    p->g0 = ((TriTex *) D_8007CAC0)->g0;
    p->b0 = ((TriTex *) D_8007CAC0)->b0;
    a->r2 = ((TriTex *) D_8007CAC0)->r2;
    a->g2 = ((TriTex *) D_8007CAC0)->g2;
    a->b2 = ((TriTex *) D_8007CAC0)->b2;
    c->r1 = ((TriTex *) D_8007CAC0)->r1;
    c->g1 = ((TriTex *) D_8007CAC0)->g1;
    c->b1 = ((TriTex *) D_8007CAC0)->b1;
    c->r0 = b->r1 = p->r1 = medio[0].r;
    c->g0 = b->g1 = p->g1 = medio[0].g;
    c->b0 = b->b1 = p->b1 = medio[0].b;
    b->r0 = a->r0 = p->r2 = medio[2].r;
    b->g0 = a->g0 = p->g2 = medio[2].g;
    b->b0 = a->b0 = p->b2 = medio[2].b;
    c->r2 = b->r2 = a->r1 = medio[1].r;
    c->g2 = b->g2 = a->g1 = medio[1].g;
    c->b2 = b->b2 = a->b1 = medio[1].b;

    /* Esquinas de textura. */
    p->u0 = uv[0];
    p->v0 = uv[1];
    a->u2 = uv[4];
    a->v2 = uv[5];
    c->u1 = uv[2];
    c->v1 = uv[3];
    c->u0 = b->u1 = p->u1 = u01;
    c->v0 = b->v1 = p->v1 = v01;
    b->u0 = a->u0 = p->u2 = u20;
    b->v0 = a->v0 = p->v2 = v20;
    c->u2 = b->u2 = a->u1 = u12;
    c->v2 = b->v2 = a->v1 = v12;

    lista = (u32 *) (fin + (z << 2));
    AddPrim(lista, p);
    AddPrim(lista, a);
    AddPrim(lista, b);
    AddPrim(lista, c);
    D_8007CAC0 += 0xC8;
    D_8007CA9C += 4;
}
