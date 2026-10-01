#include "juego.h"

/* Los sprites de pantalla (los de la seccion 2 del INO, que lee LeerSpritesINO): dibujar la fila de
 * casillas con un recuadro sobre la elegida. */

/* Un sprite de la tabla (0x20 bytes). */
typedef struct {
    u8 _00[8];
    s16 w, h;                        /* 0x08 */
    u16 tpage;                       /* 0x0C */
    u16 clut;                        /* 0x0E */
    u8 u, v;                         /* 0x10 */
    u8 _12[0x0E];
} Sprite;
EN(Sprite, w, 0x08);
EN(Sprite, clut, 0x0E);
EN(Sprite, u, 0x10);

/* SPRT de la GPU (0x14 bytes). */
typedef struct {
    u32 tag;
    u8 r, g, b, code;                /* 0x04 */
    s16 x, y;                        /* 0x08 */
    u8 u, v;                         /* 0x0C */
    u16 clut;                        /* 0x0E */
    s16 w, h;                        /* 0x10 */
} PrimSprt;
EN(PrimSprt, x, 0x08);
EN(PrimSprt, w, 0x10);

/* TILE de la GPU (0x10 bytes). */
typedef struct {
    u32 tag;
    u8 r, g, b, code;                /* 0x04 */
    s16 x, y;                        /* 0x08 */
    s16 w, h;                        /* 0x0C */
} PrimTile;
EN(PrimTile, w, 0x0C);

extern Sprite D_800D50B0[];
extern PrimSprt *D_8007CACC;         /* siguientes primitivas libres de cada clase */
extern u8 *D_8007CAD0;               /* DR_TPAGE, 8 bytes */
extern PrimTile *D_8007CAD4;
extern u16 D_8007CC58, D_8007CC5A;   /* cuantas casillas hay (las dos partes) */
extern u16 D_8007CC50;               /* la casilla elegida */

extern void AddPrim(void *ot, void *prim);
extern void SetDrawTPage(void *p, s32 dfe, s32 dtd, s32 tpage);

/* Pone en la tabla de orden ot (+4 las casillas, +8 el recuadro) un sprite por casilla, uno cada 26
 * pixeles desde x = 50 a la altura 100, y un recuadro rojo de 26 x 26 sobre la casilla elegida. */
void func_80023FD4(u8 *ot) {
    u16 i;
    s32 j = 0;
    PrimSprt *s;
    u8 *t;
    PrimTile *r;

    if (D_8007CC58 + D_8007CC5A == 0) {
        return;
    }
    for (i = 0; i != D_8007CC58 + D_8007CC5A; i++, j++) {
        D_8007CACC->x = j * 16 + j * 10 + 50;
        D_8007CACC->y = 100;
        D_8007CACC->w = D_800D50B0[j].w;
        D_8007CACC->h = D_800D50B0[j].h;
        D_8007CACC->b = 0xFF;
        D_8007CACC->g = 0xFF;
        D_8007CACC->r = 0xFF;
        D_8007CACC->v = D_800D50B0[j].v;
        D_8007CACC->u = D_800D50B0[j].u;
        D_8007CACC->clut = D_800D50B0[j].clut;
        s = D_8007CACC;
        D_8007CACC = s + 1;
        AddPrim(ot + 4, s);
        SetDrawTPage(D_8007CAD0, 1, 0, D_800D50B0[j].tpage);
        t = D_8007CAD0;
        D_8007CAD0 = t + 8;
        AddPrim(ot + 4, t);
    }
    D_8007CAD4->r = 200;
    D_8007CAD4->g = 0;
    D_8007CAD4->b = 100;
    D_8007CAD4->x = D_8007CC50 * 26 + 45;
    D_8007CAD4->y = 95;
    D_8007CAD4->w = 26;
    D_8007CAD4->h = 26;
    r = D_8007CAD4;
    D_8007CAD4 = r + 1;
    AddPrim(ot + 8, r);
}
