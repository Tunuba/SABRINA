#include "gpu_g00.h"

/* MoveImage (libgpu): copia un rectangulo de la VRAM a otro lugar de la VRAM. */

extern char D_80060C5C[];            /* "MoveImage" */
extern u32 D_800636EC[3];            /* el paquete (lo precede la cabecera con la orden de copia, 0x80) */

extern void func_800112C0(char *nombre, RectVram *r);   /* checkRECT */

/* Arma el paquete (origen x,y; destino x,y; ancho y alto) y lo manda a la cola para que lo dibuje como una
 * tabla de orden. Devuelve lo que da la cola, o -1 si el rectangulo esta vacio. */
s32 func_80012F2C(RectVram *r, s32 x, s32 y) {
    func_800112C0(D_80060C5C, r);
    if (r->w == 0 || r->h == 0) {
        return -1;
    }
    D_800636EC[1] = (y << 16) | (x & 0xFFFF);
    D_800636EC[0] = *(u32 *) &r->x;
    D_800636EC[2] = *(u32 *) &r->w;
    return D_800636C8->encolar(D_800636C8->dibujarOT, (u8 *) D_800636EC - 8, 0x14, 0);
}
