/* La letra grande del juego para los mods (kart.inc, halloween.inc; se incluye en camara_g08.c dentro de su
 * #ifdef). */

/* ---- La letra grande del juego (la de los menus y la barra de vida) ----
 * Lo mismo que hace DibujarTexto con sus textos de tabla, para un texto cualquiera: cada letra es un SPRT de 32 de alto
 * de la fuente D_8007CA10 y va a la lista de dibujo (OT) del cuadro, delante de todo. Se puede hacer durante la
 * actualizacion porque la lista y los buferes de primitivas de este cuadro ya estan limpios (func_800218D4 y
 * func_800217D0 los cambian al terminar de dibujar el anterior). */
typedef struct {
    u8 _00[4];
    u8 tpage, ancho;                 /* 0x04 */
    u16 clut;                        /* 0x06 */
    s8 u, v;                         /* 0x08 */
    u8 w, _0B;                       /* 0x0A */
} GLetra;
typedef struct {
    u32 tag;
    u8 r, g, b, code;                /* 0x04 */
    s16 x, y;                        /* 0x08 */
    s8 u, v;                         /* 0x0C */
    u16 clut;                        /* 0x0E */
    s16 w, h;                        /* 0x10 */
} GPrimLetra;
extern GLetra *D_8007CA10;           /* la fuente */
extern GPrimLetra *D_8007CACC;       /* el bufer de SPRT del cuadro */
extern u8 *D_8007CAD0;               /* el de cambios de pagina de textura */
extern u8 *D_8007C9E8;               /* la lista de dibujo (OT) del cuadro */
extern s8 ascii_a_letra[];
extern void AddPrim(void *ot, void *prim);
extern void SetDrawTPage(void *p, s32 dfe, s32 dtd, s32 tpage);

static s32 g_ancho(const char *t) {
    s32 w = 0;

    for (; *t; t++) {
        w += *t == ' ' ? 7 : D_8007CA10[(u8)ascii_a_letra[(u8)*t]].ancho;
    }
    return w;
}

static void __attribute__((noinline)) g_letras(const char *t, s32 x, s32 y, s32 r, s32 g, s32 b) {
    GLetra *l;
    GPrimLetra *p;
    u8 *tp;

    for (; *t; t++) {
        if (*t == ' ') {
            x += 7;
            continue;
        }
        l = &D_8007CA10[(u8)ascii_a_letra[(u8)*t]];
        p = D_8007CACC;
        D_8007CACC = p + 1;
        p->x = x;
        p->y = y - 16;
        p->w = l->w;
        p->h = 32;
        p->u = l->u;
        p->v = l->v;
        p->clut = l->clut;
        p->r = r;
        p->g = g;
        p->b = b;
        AddPrim(D_8007C9E8 + 8, p);
        tp = D_8007CAD0;
        D_8007CAD0 = tp + 8;
        SetDrawTPage(tp, 1, 0, l->tpage);
        AddPrim(D_8007C9E8 + 8, tp);
        x += l->ancho;
    }
}

/* Un texto con la letra grande, centrado en cx, con su sombra negra para que se lea sobre cualquier cosa. */
static void g_grande(const char *t, s32 cx, s32 y, s32 r, s32 g, s32 b) {
    s32 x;

    if (D_8007CA10 == NULL) {
        return;
    }
    x = cx - g_ancho(t) / 2;
    g_letras(t, x, y, r, g, b);
    g_letras(t, x + 2, y + 2, 8, 4, 12);        /* la sombra: va despues en la OT, se dibuja antes */
}

