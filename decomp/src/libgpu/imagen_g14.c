#include "gpu_g00.h"

/* LoadImage, StoreImage y DrawOTag de libgpu (PsyQ): esperan a que el GPU este libre y pasan el pedido al
 * controlador (D_800636C8). */

extern char D_80060D2C[];            /* nombre para el aviso de LoadImage */
extern char D_80060C50[];            /* "StoreImage" */
extern char D_80060C98[];            /* "DrawOTag(%08x)...\n" */
extern volatile u32 *D_80063754;     /* GP1: estado del GPU */
extern volatile u32 *D_80063760;     /* control del DMA del GPU */
extern s32 D_80063780;               /* hasta cuando esperar */
extern s32 D_80063784;               /* vueltas de la espera */
extern void func_800112C0(char *nombre, RectVram *r);   /* checkRECT */
extern s32 func_8001626C(s32 modo);                      /* VSync */
extern s32 func_80012900(void);                          /* se paso el tiempo (avisa y reinicia) */
extern void func_80016970(s32 n, void *f);               /* DMACallback */
extern void func_80013D24(void);

/* Espera a que el DMA del GPU termine y el GPU acepte comandos, con un tope de 240 cuadros. -1 si se paso. */
static inline s32 esperar_gpu(void) {
    D_80063780 = func_8001626C(-1) + 0xF0;
    D_80063784 = 0;
    while ((*D_80063760 & 0x1000000) || !(*D_80063754 & 0x4000000)) {
        if (func_80012900() != 0) {
            return -1;
        }
    }
    func_80016970(2, func_80013D24);
    return 0;
}

/* LoadImage(r, p): de la RAM a la VRAM. */
s32 func_8001390C(RectVram *r, u32 *p) {
    func_800112C0(D_80060D2C, r);
    if (esperar_gpu() != 0) {
        return -1;
    }
    ((s32 (*)(RectVram *, u32 *))D_800636C8->escribirVram)(r, p);
    return 0;
}

/* StoreImage(r, p): de la VRAM a la RAM. */
s32 func_800139F8(RectVram *r, u32 *p) {
    func_800112C0(D_80060C50, r);
    if (esperar_gpu() != 0) {
        return -1;
    }
    ((s32 (*)(RectVram *, u32 *))D_800636C8->leerVram)(r, p);
    return 0;
}

/* DrawOTag(ot): dibuja una tabla de orden. */
s32 func_80013C28(u32 *ot) {
    if (D_8006379A.depuracion >= 2) {
        D_80063794(D_80060C98, ot);
    }
    if (esperar_gpu() != 0) {
        return -1;
    }
    ((s32 (*)(u32 *))D_800636C8->dibujarOT)(ot);
    return 0;
}

extern char D_80060C5C[];            /* "MoveImage" */
extern u32 D_800636EC[3];            /* el pedido de copia: origen, destino y tamano */

/* MoveImage(r, x, y): copia un rectangulo de la VRAM a (x, y). -1 si el rectangulo esta vacio. */
s32 func_80013AE4(RectVram *r, s32 x, s32 y) {
    func_800112C0(D_80060C5C, r);
    if (esperar_gpu() != 0) {
        return -1;
    }
    if (r->w == 0) {
        return -1;
    }
    if (r->h == 0) {
        return -1;
    }
    D_800636EC[1] = (y << 16) | (x & 0xFFFF);
    D_800636EC[0] = *(u32 *)r;
    D_800636EC[2] = *(u32 *)&r->w;
    ((s32 (*)(u32 *))D_800636C8->dibujarOT)(D_800636EC - 2);
    return 0;
}
