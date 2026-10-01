#include "juego.h"

/* Preparar los textos de pantalla: pasar de ASCII a letras de la fuente y la barra de un texto. */

/* Un texto de pantalla (u16). */
typedef struct {
    u16 x, y;                        /* 0x00, donde termina */
    u16 _04;
    u16 x0, y0;                      /* 0x06 */
    u16 r, g, b;                     /* 0x0A, el color de la primera letra */
    u16 dr, dg, db;                  /* 0x10, el de la ultima; queda el paso por letra */
    s16 largo;                       /* 0x16 */
} TextoInicio;

extern TextoInicio *D_800798BC[];    /* termina en D_8007C9D2 */
extern s8 *D_80079D48[];
extern s8 ascii_a_letra[];
extern u8 D_8007C9D2[];

/* Para cada texto de la tabla pasa sus letras de ASCII a la fuente (hasta el 0, incluido), anota cuantas
 * son y reparte el cambio de color por letra. La vuelta mira primero lo que trae v0 (el juego no le da
 * valor antes): si ya es el fin de la tabla no hace nada. Devuelve el fin de la tabla. */
u8 *func_800190C0(void) {
    TextoInicio *t;
    s8 *s;
    s32 i, c;
    u32 k;

    __asm__ volatile("move %0, $2" : "=r"(t));
    for (i = 0; (u8 *)t != D_8007C9D2; i++) {
        s = D_80079D48[i];
        t = D_800798BC[i];
        if ((u8 *)t == D_8007C9D2 || t == NULL) {
            continue;
        }
        k = 0;
        c = 0x45;
        while (c != 0) {
            c = s[k] & 0xFF;
            s[k] = ascii_a_letra[c];
            k = (k + 1) & 0xFF;
        }
        t->largo = k - 1;
        t->dr = (s32)(t->dr - t->r) / (s32)k;
        t->dg = (s32)(t->dg - t->g) / (s32)k;
        t->db = (s32)(t->db - t->b) / (s32)k;
        t->x0 = t->x;
        t->y0 = t->y;
    }
    return D_8007C9D2;
}

/* Llena 8 letras del texto n desde la posicion dada: las primeras 'llenas' con la barra llena (0x50) y el
 * resto vacia (0x4D). Devuelve 8. */
s32 func_800193F8(s32 n, s32 llenas, s32 desde) {
    s8 *s = D_80079D48[n];
    s8 i;

    for (i = 0; i != 8; i++) {
        s[desde + i] = i < llenas ? 0x50 : 0x4D;
    }
    return 8;
}
