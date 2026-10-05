#include "juego.h"

/* Dibuja un rectangulo lleno de color (r, g, b): llena la primitiva TILE del bufer actual (D_80084BAC) con la
 * posicion del bufer (D_80084C24/C28), el ancho D_80084C48 (por 1.5 si D_80084C1D) y el alto D_80084C4C, y la
 * agrega a la tabla de orden de pantalla->+0x10. */

typedef struct {
    u32 tag;
    u8 r, g, b, code;
    s16 x, y, w, h;
} Tile;

extern Tile D_80084B8C[2];
extern s16 D_80084BAC;                  /* el bufer actual */
extern u8 D_80084C1D;
extern s16 D_80084C24[];                /* x de cada bufer */
extern s16 D_80084C28[];                /* y de cada bufer */
extern s32 D_80084C48;                  /* ancho */
extern u16 D_80084C4C;                  /* alto */

extern void AddPrim(void *ot, void *prim);

void func_800171CC(s32 r, s32 g, s32 b, u8 *pantalla) {
    D_80084B8C[D_80084BAC].r = r;
    D_80084B8C[D_80084BAC].g = g;
    D_80084B8C[D_80084BAC].b = b;
    D_80084B8C[D_80084BAC].x = D_80084C24[D_80084BAC];
    D_80084B8C[D_80084BAC].h = D_80084C4C;
    D_80084B8C[D_80084BAC].y = D_80084C28[D_80084BAC];
    if (D_80084C1D != 0) {
        D_80084B8C[D_80084BAC].w = D_80084C48 * 3 / 2;
    } else {
        D_80084B8C[D_80084BAC].w = D_80084C48;
    }
    AddPrim(*(void **) (pantalla + 0x10), &D_80084B8C[D_80084BAC]);
}
