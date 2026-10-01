#include "juego.h"

/* Dibujar los textos de pantalla (la tabla D_800798BC de registros y D_80079D48 de cadenas). */

/* Una letra de la fuente (12 bytes, en D_8007CA10). */
typedef struct {
    u8 _00[4];
    u8 tpage;                        /* 0x04 */
    u8 ancho;                        /* 0x05, lo que avanza */
    u16 clut;                        /* 0x06 */
    s8 u, v;                         /* 0x08 */
    u8 w;                            /* 0x0A */
    u8 _0B;
} Letra;

/* Un texto de pantalla (u16). */
typedef struct {
    u16 x, y;                        /* 0x00, x del centro */
    u16 fundido;                     /* 0x04, 0x1000 = todo del color D_8007C7A0 */
    u16 _06, _08;
    u16 r, g, b;                     /* 0x0A */
    u16 _10, _12, _14;
    u16 largo;                       /* 0x16, cuantas letras */
    u16 medio;                       /* 0x18, la mitad del ancho (0: se calcula y se guarda) */
} TextoPantalla;

/* SPRT de la GPU. */
typedef struct {
    u32 tag;
    u8 r, g, b, code;                /* 0x04 */
    s16 x, y;                        /* 0x08 */
    s8 u, v;                         /* 0x0C */
    u16 clut;                        /* 0x0E */
    s16 w, h;                        /* 0x10 */
} PrimLetra;

extern TextoPantalla *D_800798BC[];
extern s8 *D_80079D48[];
extern u16 D_8007C7A0, D_8007C7A2, D_8007C7A4;  /* el color al que se funde */
extern Letra *D_8007CA10;
extern PrimLetra *D_8007CACC;
extern u8 *D_8007CAD0;
extern void AddPrim(void *ot, void *prim);
extern void SetDrawTPage(void *p, s32 dfe, s32 dtd, s32 tpage);

/* Dibuja en ot + 8 los textos desde el numero n hasta el primero vacio, centrados en su x, con letras de
 * 32 de alto ('~' es un espacio de 7). */
void DibujarTexto(u8 *ot, s32 n) {
    TextoPantalla *t;
    s8 *s;
    Letra *l;
    PrimLetra *p;
    u8 *tp;
    u16 x, ancho, i;
    u32 resto;
    s32 k = n * 4;

    do {
        t = *(TextoPantalla **)((u8 *)D_800798BC + k);
        s = *(s8 **)((u8 *)D_80079D48 + k);
        if (t != NULL) {
            ancho = t->medio;
            if (ancho == 0) {
                for (i = 0; i != t->largo; i++) {
                    if (s[i] == 0x7E) {
                        ancho = ancho + 7;
                    } else {
                        ancho = ancho + D_8007CA10[s[i]].ancho;
                    }
                }
                ancho = ancho >> 1;
                t->medio = ancho;
            }
            x = t->x - ancho;
            resto = (0x1000 - t->fundido) & 0xFFFF;
            for (i = 0; i != t->largo; i++, s++) {
                l = &D_8007CA10[*s];
                if (*s == 0x7E) {
                    x = x + 7;
                    continue;
                }
                D_8007CACC->x = x;
                D_8007CACC->y = t->y - 16;
                D_8007CACC->w = l->w;
                D_8007CACC->h = 32;
                D_8007CACC->v = l->v;
                D_8007CACC->u = l->u;
                D_8007CACC->clut = l->clut;
                D_8007CACC->r = (t->r * resto + D_8007C7A0 * t->fundido) >> 12;
                D_8007CACC->g = (t->g * resto + D_8007C7A2 * t->fundido) >> 12;
                D_8007CACC->b = (t->b * resto + D_8007C7A4 * t->fundido) >> 12;
                p = D_8007CACC;
                D_8007CACC = p + 1;
                AddPrim(ot + 8, p);
                SetDrawTPage(D_8007CAD0, 1, 0, l->tpage);
                tp = D_8007CAD0;
                D_8007CAD0 = tp + 8;
                AddPrim(ot + 8, tp);
                x = x + l->ancho;
            }
        }
        n = (n + 1) & 0xFFFF;
        k += 4;
    } while (t != NULL);
}
