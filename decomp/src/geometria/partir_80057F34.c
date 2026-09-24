#include "gte.h"
#include "dibujo.h"
#include "modelo.h"

extern s32 D_8007CAC0;               /* donde va escribiendo la lista de dibujo */
extern u16 D_8007CA9C;               /* triangulos ya puestos en la lista de este cuadro */

/* Las esquinas en la textura de un Triangulo, de a pares (u, v) por vertice desde el byte 0x10. */
#define ESQUINA(t, i) (((u8 *) (t))[0x10 + (i)])

/* Entrada 1 de D_80068878: el lado del vertice 0 al 1 salio demasiado largo en pantalla. Parte el
 * triangulo por el punto medio de ese lado en dos: (0, medio, 2) y (medio, 1, 2).
 *
 * Llega con los tres puntos de pantalla de rtpt todavia en la cola del coprocesador y con la pieza de
 * D_8007CAC0 ya con la textura puesta; esa pieza no se dibuja: solo se leen sus colores y los dos
 * triangulos van en las dos piezas siguientes. El punto medio se pasa a pantalla con rtps (la matriz de la
 * camara sigue puesta); su color y su esquina de textura son el promedio de los de los extremos. */
void func_80057F34(Triangulo *t, s32 fin, s32 z) {
    TriTex *a = (TriTex *) (D_8007CAC0 + 0x28);
    TriTex *b = (TriTex *) (D_8007CAC0 + 0x50);
    TriTex *base;
    s16 medio[4];
    u8 color[4];
    s16 p[6];                        /* los tres puntos de pantalla: x0 y0 x1 y1 x2 y2 */
    s16 pm[2];                       /* el punto medio en pantalla */
    u8 um, vm;
    u8 codigo;
    u16 h;
    u32 *lista;

    gte_guardar_sxy0(&p[0]);
    gte_guardar_sxy1(&p[2]);
    gte_guardar_sxy2(&p[4]);

    medio[0] = (t->v[1]->x + t->v[0]->x) >> 1;
    medio[1] = (t->v[1]->y + t->v[0]->y) >> 1;
    medio[2] = (t->v[1]->z + t->v[0]->z) >> 1;
    gte_poner_v0(medio);

    base = (TriTex *) D_8007CAC0;
    color[0] = (base->r1 + base->r0) >> 1;
    color[1] = (base->g1 + base->g0) >> 1;
    color[2] = (base->b1 + base->b0) >> 1;
    gte_rtps();
    um = (ESQUINA(t, 2) + ESQUINA(t, 0)) >> 1;
    vm = (ESQUINA(t, 3) + ESQUINA(t, 1)) >> 1;
    gte_guardar_sxy2(pm);

    if (t->textura->banderas & 1) {
        codigo = b->codigo | 2;
        b->codigo = codigo;
        a->codigo = codigo;
    }
    h = *(u16 *) ((u8 *) t->textura + 0xC);
    b->pagina = h;
    a->pagina = h;
    h = *(u16 *) ((u8 *) t->textura + 0xE);
    b->paleta = h;
    a->paleta = h;

    a->x0 = p[0];
    a->y0 = p[1];
    b->x0 = pm[0];
    a->x1 = pm[0];
    b->y0 = pm[1];
    a->y1 = pm[1];
    b->x2 = p[4];
    a->x2 = p[4];
    a->y2 = p[5];
    b->y2 = p[5];
    b->x1 = p[2];
    b->y1 = p[3];

    a->r0 = ((TriTex *) D_8007CAC0)->r0;
    a->g0 = ((TriTex *) D_8007CAC0)->g0;
    a->b0 = ((TriTex *) D_8007CAC0)->b0;
    b->r0 = color[0];
    a->r1 = color[0];
    b->g0 = color[1];
    a->g1 = color[1];
    b->b0 = color[2];
    a->b1 = color[2];
    b->r1 = ((TriTex *) D_8007CAC0)->r1;
    b->g1 = ((TriTex *) D_8007CAC0)->g1;
    b->b1 = ((TriTex *) D_8007CAC0)->b1;
    codigo = ((TriTex *) D_8007CAC0)->r2;
    b->r2 = codigo;
    a->r2 = codigo;
    codigo = ((TriTex *) D_8007CAC0)->g2;
    b->g2 = codigo;
    a->g2 = codigo;
    codigo = ((TriTex *) D_8007CAC0)->b2;
    b->b2 = codigo;
    a->b2 = codigo;

    a->u0 = ESQUINA(t, 0);
    a->v0 = ESQUINA(t, 1);
    b->u0 = um;
    a->u1 = um;
    b->v0 = vm;
    a->v1 = vm;
    b->u2 = ESQUINA(t, 4);
    a->u2 = ESQUINA(t, 4);
    b->v2 = ESQUINA(t, 5);
    a->v2 = ESQUINA(t, 5);
    b->u1 = ESQUINA(t, 2);
    b->v1 = ESQUINA(t, 3);

    lista = (u32 *) (fin + (z << 2));
    AddPrim(lista, a);
    AddPrim(lista, b);
    D_8007CAC0 += 0x78;
    D_8007CA9C += 2;
}
