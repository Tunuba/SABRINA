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

extern s32 D_8007CA58;               /* botones apretados en este cuadro */
extern s32 D_800D1604, D_800D1608;   /* sonido de moverse y de tope */
extern s16 D_8007CC4E;               /* lo que se puede hacer con la casilla elegida */
extern u16 D_800D5090[];             /* por casilla: distinto de 0 si tiene algo */
extern s8 D_800D2AD0[][64];          /* por casilla: su nombre */
extern s8 D_8007594C[16];            /* el nombre de la casilla vacia */
extern s32 TocarSonido(s32 prog, s32 tono, s32 nota, s32 prioridad);
extern s32 func_80019738(void);

/* Mueve la casilla elegida con izquierda (0x8000) y derecha (0x2000), con su sonido (otro si ya esta en
 * la punta), y deja en D_8007CC4E que hacer con ella: con elegir (el tercer argumento) 6 si tiene algo, 2
 * si no y 0 si no hay casillas; si no, 1 salvo que su nombre no sea el de la vacia. Lo que devuelve (v0)
 * es lo de func_80019738 si la casilla tiene algo, si no 0. */
s32 func_8004F2D8(s32 a0, s32 a1, s32 elegir) {
    u16 i;
    s32 r;

    if (D_8007CA58 & 0x8000) {
        if (D_8007CC50 != 0) {
            TocarSonido((s16)D_800D1604, 0, 0x2A, 0x7F);
            D_8007CC50--;
        } else {
            TocarSonido((s16)D_800D1608, 0, 0x2A, 0x7F);
        }
    }
    if (D_8007CA58 & 0x2000) {
        if (D_8007CC50 != D_8007CC58 + D_8007CC5A - 1) {
            TocarSonido((s16)D_800D1604, 0, 0x2A, 0x7F);
            D_8007CC50++;
        } else {
            TocarSonido((s16)D_800D1608, 0, 0x2A, 0x7F);
        }
    }
    if (elegir != 0) {
        if (D_8007CC58 + D_8007CC5A != 0) {
            D_8007CC4E = D_800D5090[D_8007CC50] != 0 ? 6 : 2;
        } else {
            D_8007CC4E = 0;
        }
    } else {
        D_8007CC4E = 1;
        for (i = 0; i != 16; i++) {
            if (D_8007594C[i] != D_800D2AD0[D_8007CC50][i]) {
                D_8007CC4E = 0;
            }
        }
    }
    r = D_800D5090[D_8007CC50];
    if (r != 0) {
        r = func_80019738();
    }
    return r;
}
