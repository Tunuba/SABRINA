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

extern u16 D_8007C874[4], D_8007C87C[4];  /* x e y de las cuatro piezas del marcador */
extern u16 D_8007C884[4];            /* el sprite de cada pieza */
extern Sprite *D_8007CB24;           /* la tabla de sprites del marcador */
extern s16 D_8007CB1E, D_8007CB22;   /* el largo de las dos barras (hasta 0x80) */
extern s32 D_8007CB30;
extern void *D_8007CADC;             /* lo ultimo que se agrega en ot + 8 */

/* Pone en ot el marcador: sus cuatro piezas (en ot + 0xC) y dos barras semitransparentes de 12 de alto (en
 * ot + 8), rojas con mas verde cuanto mas largas; la primera crece hacia la derecha desde la pieza 1
 * y la segunda hacia la izquierda hasta 0x80 despues de la pieza 3. */
void func_80023B3C(u8 *ot) {
    u16 i;
    Sprite *sp;
    PrimSprt *s;
    u8 *t;
    PrimTile *r;
    u32 v;

    D_8007CB30 = 0;
    for (i = 0; i != 4; i++) {
        sp = &D_8007CB24[D_8007C884[i]];
        D_8007CACC->x = D_8007C874[i];
        D_8007CACC->y = D_8007C87C[i];
        D_8007CACC->w = sp->w;
        D_8007CACC->h = sp->h;
        D_8007CACC->r = 0xFF;
        D_8007CACC->g = 0xFF;
        D_8007CACC->b = 0xFF;
        D_8007CACC->v = sp->v;
        D_8007CACC->u = sp->u;
        D_8007CACC->clut = sp->clut;
        s = D_8007CACC;
        D_8007CACC = s + 1;
        AddPrim(ot + 0xC, s);
        SetDrawTPage(D_8007CAD0, 1, 0, sp->tpage);
        t = D_8007CAD0;
        D_8007CAD0 = t + 8;
        AddPrim(ot + 0xC, t);
    }
    v = (u16)D_8007CB1E;
    D_8007CAD4->r = (s32)((((0x100 - v) & 0xFFFF) << 7) + (v << 7)) >> 8;
    D_8007CAD4->g = (s32)(v << 7) >> 8;
    D_8007CAD4->b = 0;
    D_8007CAD4->x = D_8007C874[1];
    D_8007CAD4->y = D_8007C87C[1] + 2;
    D_8007CAD4->w = D_8007CB1E;
    D_8007CAD4->h = 12;
    D_8007CAD4->code |= 2;
    r = D_8007CAD4;
    D_8007CAD4 = r + 1;
    AddPrim(ot + 8, r);
    v = (u16)D_8007CB22;
    D_8007CAD4->r = (s32)((((0x100 - v) & 0xFFFF) << 7) + (v << 7)) >> 8;
    D_8007CAD4->g = (s32)(v << 7) >> 8;
    D_8007CAD4->b = 0;
    D_8007CAD4->x = D_8007C874[3] + (0x80 - D_8007CB22);
    D_8007CAD4->y = D_8007C87C[3] + 2;
    D_8007CAD4->w = D_8007CB22;
    D_8007CAD4->h = 12;
    D_8007CAD4->code |= 2;
    r = D_8007CAD4;
    D_8007CAD4 = r + 1;
    AddPrim(ot + 8, r);
    AddPrim(ot + 8, D_8007CADC);
}

extern u8 D_8007CA38;                /* distinto de 0: la pantalla de numeros (16 piezas) */
extern s32 D_8007CB34;               /* distinto de 0: no se dibujan */
extern s8 nivel_actual;
extern Sprite *D_8006CE10[7];        /* las piezas del marcador (las arma func_8002303C) */
extern u16 D_8006CE30[8], D_8006CE40[8];  /* sus x e y */
extern u8 D_8006CEF0[16];            /* las 16 piezas de la otra pantalla: sprite, x, y, brillo y capa */
extern u16 D_8006CE90[16], D_8006CEB0[16];
extern u8 D_8006CED0[16], D_8006CEE0[16];

/* Pone una pieza: el sprite s en (x, y) con brillo c, en la capa ot. */
static void poner_pieza(Sprite *s, u16 x, u16 y, u8 *c, u8 *ot) {
    PrimSprt *p;
    u8 *t;

    D_8007CACC->x = x;
    D_8007CACC->y = y;
    D_8007CACC->w = s->w;
    D_8007CACC->h = s->h;
    D_8007CACC->r = c[0];
    D_8007CACC->g = c[0];
    D_8007CACC->b = c[0];
    D_8007CACC->v = s->v;
    D_8007CACC->u = s->u;
    D_8007CACC->clut = s->clut;
    p = D_8007CACC;
    D_8007CACC = p + 1;
    AddPrim(ot, p);
    SetDrawTPage(D_8007CAD0, 1, 0, s->tpage);
    t = D_8007CAD0;
    D_8007CAD0 = t + 8;
    AddPrim(ot, t);
}

/* Dibuja el marcador del nivel: sus 7 piezas (en los niveles 13 y 14 solo la 2, 4, 5 y 6; con
 * D_8007CB30 sin las dos primeras) y la barra de vida; o, con D_8007CA38, las 16 piezas de la otra
 * pantalla (en los niveles 13 y 14 solo las 3 ultimas). */
void func_8002367C(u8 *ot) {
    static u8 blanco = 0xFF;
    u16 i;
    u32 v;
    PrimTile *r;

    if (D_8007CA38 == 0) {
        for (i = 0; i != 7; i++) {
            if ((nivel_actual == 14 || nivel_actual == 13) && (i == 0 || i == 1 || i == 3)) {
                continue;
            }
            if (D_8007CB30 != 0 && i < 2) {
                continue;
            }
            poner_pieza(D_8006CE10[i], D_8006CE30[i], D_8006CE40[i], &blanco, ot + 0xC);
        }
        v = (u16)D_8007CB1E;
        D_8007CAD4->r = (s32)((((0x100 - v) & 0xFFFF) << 7) + (v << 7)) >> 8;
        D_8007CAD4->g = (s32)(v << 7) >> 8;
        D_8007CAD4->b = 0;
        D_8007CAD4->x = 0x20;
        D_8007CAD4->y = 0x16;
        D_8007CAD4->w = D_8007CB1E;
        D_8007CAD4->h = 12;
        D_8007CAD4->code |= 2;
        r = D_8007CAD4;
        D_8007CAD4 = r + 1;
        AddPrim(ot + 8, r);
        AddPrim(ot + 8, D_8007CADC);
        return;
    }
    for (i = 0; i != 16; i++) {
        if (D_8007CB34 != 0) {
            return;
        }
        if ((nivel_actual == 14 || nivel_actual == 13) && i < 13) {
            continue;
        }
        poner_pieza(&D_8007CB24[D_8006CEF0[i]], D_8006CE90[i], D_8006CEB0[i], &D_8006CED0[i],
                    ot + D_8006CEE0[i] * 4);
    }
}

typedef void (*FuncAccion)(s32 a, s32 b, s32 c, s32 d);
extern FuncAccion *D_80075AA4[];     /* por lista: la funcion de cada accion */
extern u16 D_80075AC0[], D_80075AD0[];  /* por lista: su numero y su ultima accion */
extern s32 D_800D160C;               /* sonido de elegir */
extern s32 D_8007CC44;               /* 1: no se puede elegir */
extern s16 D_8007CC4A;
extern u16 D_8007CC52;               /* la accion marcada */
extern u16 D_8007CC54;               /* la lista que se mostro la ultima vez */

/* Las acciones de la casilla elegida (la lista D_8007CC4E): al cambiar de lista marca la ultima; arriba y
 * abajo (0x4000 y 0x1000) la mueven, 0x40 la hace. */
void func_8004FA54(s32 a, s32 b) {
    u16 n = D_8007CC4E;

    if (D_8007CC54 != D_80075AC0[n]) {
        D_8007CC52 = D_80075AD0[n];
        D_8007CC54 = D_80075AC0[n];
    }
    if (D_8007CC44 == 1) {
        return;
    }
    if (D_8007CA58 & 0x4000) {
        if (D_8007CC52 != D_80075AD0[n]) {
            TocarSonido((s16)D_800D1604, 0, 0x2A, 0x7F);
            D_8007CC52++;
        } else {
            TocarSonido((s16)D_800D1608, 0, 0x2A, 0x7F);
        }
    }
    if (D_8007CA58 & 0x1000) {
        if (D_8007CC52 != 0) {
            TocarSonido((s16)D_800D1604, 0, 0x2A, 0x7F);
            D_8007CC52--;
        } else {
            TocarSonido((s16)D_800D1608, 0, 0x2A, 0x7F);
        }
    }
    if (D_8007CA58 & 0x40) {
        TocarSonido((s16)D_800D160C, 0, 0x2A, 0x7F);
        D_80075AA4[(u16)D_8007CC4E][D_8007CC52](a, b, (u16)D_8007CC4A, (u16)D_8007CC4E * 4);
    }
}
