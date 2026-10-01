#include "juego.h"

/* libgpu: llenar un rectangulo de la VRAM con un color (como ClearImage de la biblioteca). */

typedef struct {
    s16 x, y, w, h;
} Rect;

extern u32 D_800831B0[11];           /* el paquete para la GPU */
extern u32 D_800831D8[4];            /* lo que restaura el area de dibujo despues */
extern volatile u32 *D_80063754;     /* el registro de estado de la GPU (0x1F801814) */
extern s16 D_8006379C, D_8006379E;   /* ancho y alto de la VRAM */

extern s32 func_800120DC(s32 n);     /* el valor actual de un registro de entorno de la GPU */
extern void func_80012094(u32 *paquete);  /* manda el paquete */

/* Recorta el ancho y el alto a la VRAM. Si x o el ancho no son multiplos de 64 dibuja un rectangulo de
 * color (abriendo el area de dibujo a toda la VRAM y dejando para despues la que habia); si lo son usa el
 * llenado rapido. Devuelve 0. */
s32 func_80011930(Rect *r, u32 color) {
    s16 w, h;

    w = r->w;
    if (w < 0) {
        r->w = 0;
    } else if (D_8006379C - 1 < w) {
        r->w = (u16)D_8006379C - 1;
    } else {
        r->w = w;
    }
    h = r->h;
    if (h < 0) {
        r->h = 0;
    } else if (D_8006379E - 1 < h) {
        r->h = (u16)D_8006379E - 1;
    } else {
        r->h = h;
    }
    if ((r->x & 0x3F) || (r->w & 0x3F)) {
        D_800831B0[0] = ((u32)D_800831D8 & 0xFFFFFF) | 0x08000000;
        D_800831B0[4] = 0xE6000000;
        D_800831B0[1] = 0xE3000000;
        D_800831B0[2] = 0xE4FFFFFF;
        D_800831B0[3] = 0xE5000000;
        D_800831B0[6] = (color & 0xFFFFFF) | 0x60000000;
        D_800831B0[5] = (*D_80063754 & 0x7FF) | ((color >> 31) << 10) | 0xE1000000;
        D_800831B0[7] = *(u32 *)&r->x;
        D_800831D8[0] = 0x03FFFFFF;
        D_800831B0[8] = *(u32 *)&r->w;
        D_800831D8[1] = func_800120DC(3) | 0xE3000000;
        D_800831D8[2] = func_800120DC(4) | 0xE4000000;
        D_800831D8[3] = func_800120DC(5) | 0xE5000000;
    } else {
        D_800831B0[0] = 0x05FFFFFF;
        D_800831B0[1] = 0xE6000000;
        D_800831B0[3] = (color & 0xFFFFFF) | 0x02000000;
        D_800831B0[2] = (*D_80063754 & 0x7FF) | ((color >> 31) << 10) | 0xE1000000;
        D_800831B0[4] = *(u32 *)&r->x;
        D_800831B0[5] = *(u32 *)&r->w;
    }
    func_80012094(D_800831B0);
    return 0;
}
