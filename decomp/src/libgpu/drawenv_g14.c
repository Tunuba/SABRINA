#include "juego.h"

/* Armado del paquete de un DRAWENV (setDrawEnv interno de libgpu). */

extern s16 D_8006379C;               /* ancho de la VRAM */
extern s16 D_8006379E;               /* alto de la VRAM */
extern u32 func_8001166C(s32 x, s32 y);                /* comando de esquina de arriba */
extern u32 func_80011704(s32 x, s32 y);                /* comando de esquina de abajo */
extern u32 func_8001179C(s32 x, s32 y);                /* comando de desplazamiento */
extern u32 func_8001164C(s32 dtd, s32 dfe, s32 tpage); /* comando de modo de dibujo */
extern u32 func_800117B8(s16 *tw);                     /* comando de ventana de textura */

/* Llena el paquete p desde el DRAWENV e: las esquinas del area de dibujo, el desplazamiento, el modo, la
 * ventana de textura y la mascara; si e pide borrar el fondo, agrega un rectangulo del color de fondo del
 * tamano del area (recortado a la VRAM). Deja en p[3] el largo del paquete y lo devuelve. */
s32 func_80013714(u32 *p, s16 *e) {
    u8 *b = (u8 *)e;
    u32 rr[2];
    s16 *r = (s16 *)rr;
    s32 n = 7;

    p[1] = func_8001166C(e[0], e[1]);
    p[2] = func_80011704((s16)((u16)e[2] + (u16)e[0] - 1), (s16)((u16)e[1] + (u16)e[3] - 1));
    p[3] = func_8001179C(e[4], e[5]);
    p[4] = func_8001164C(b[0x17], b[0x16], *(u16 *)(b + 0x14));
    p[5] = func_800117B8(e + 6);
    p[6] = 0xE6000000;
    if (b[0x18] != 0) {
        r[0] = e[0];
        r[1] = e[1];
        r[2] = e[2];
        r[3] = e[3];
        if (r[2] < 0) {
            r[2] = 0;
        } else if (D_8006379C - 1 < r[2]) {
            r[2] = D_8006379C - 1;
        }
        if (r[3] < 0) {
            r[3] = 0;
        } else if (D_8006379E - 1 < r[3]) {
            r[3] = D_8006379E - 1;
        }
        r[0] -= e[4];
        r[1] -= e[5];
        p[7] = (b[0x1B] << 16) | (b[0x1A] << 8) | 0x60000000 | b[0x19];
        p[8] = rr[0];
        p[9] = rr[1];
        n = 10;
    }
    ((u8 *)p)[3] = n - 1;
    return n - 1;
}
