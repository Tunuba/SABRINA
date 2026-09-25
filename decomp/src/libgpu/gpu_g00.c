#include "gpu_g00.h"

/* Funciones de libgpu (PsyQ) enlazadas en el juego. Todas pasan por la tabla del controlador del GPU
 * (D_800636C8) y, con la depuracion encendida, avisan por GPU_printf (D_80063794). */

extern char D_80060BF4[];  /* "DrawSync(%d)...\n" */
extern char D_80060C08[];  /* "%s:bad RECT" */
extern char D_80060C14[];  /* "(%d,%d)-(%d,%d)\n" */
extern char D_80060C28[];  /* "%s:" */
extern char D_80060C2C[];  /* "ClearImage" */
extern char D_80060C44[];  /* "LoadImage" */
extern char D_80060C50[];  /* "StoreImage" */
extern char D_80060C80[];  /* "ClearOTagR(%08x,%d)...\n" */
extern char D_80060C98[];  /* "DrawOTag(%08x)...\n" */

extern u8 D_800636F8[];    /* primitivo vacio del final de las tablas de orden */
extern u32 D_8006370C;     /* etiqueta que apunta a el (termina la lista) */

/* Revisa un RECT antes de mandarlo al GPU (checkRECT de libgpu). Con depuracion 1 avisa solo si el
 * rectangulo se sale de la VRAM o esta vacio; con 2 lo imprime siempre. */
void func_800112C0(char *nombre, RectVram *r) {
    switch (D_8006379A.depuracion) {
    case 1:
        if (D_8006379A.ancho < r->w || D_8006379A.ancho < r->w + r->x || D_8006379A.alto < r->y ||
            D_8006379A.alto < r->y + r->h || r->w <= 0 || r->x < 0 || r->y < 0 || r->h <= 0) {
            D_80063794(D_80060C08, nombre);
            D_80063794(D_80060C14, r->x, r->y, r->w, r->h);
        }
        break;
    case 2:
        D_80063794(D_80060C28, nombre);
        D_80063794(D_80060C14, r->x, r->y, r->w, r->h);
        break;
    }
}

/* DrawSync: espera a que el GPU termine (modo 0) o dice cuanto le falta (modo 1). */
s32 func_80012D74(s32 modo) {
    if (D_8006379A.depuracion >= 2) {
        D_80063794(D_80060BF4, modo);
    }
    return D_800636C8->sincronizar(modo);
}

/* ClearImage: rellena un rectangulo de la VRAM con un color. El original recorta cada componente a un
 * byte (andi 0xFF) sin fiarse de quien llama; GCC con un parametro u8 no lo haria, por eso van s32. */
s32 func_80012DDC(RectVram *r, s32 rojo, s32 verde, s32 azul) {
    func_800112C0(D_80060C2C, r);
    return D_800636C8->encolar(D_800636C8->limpiar, r, 8,
                               ((azul & 0xFF) << 16) | ((verde & 0xFF) << 8) | (rojo & 0xFF));
}

/* LoadImage: copia datos de la RAM a un rectangulo de la VRAM (sube un .PIC o .TEX). */
s32 SubirAVRAM(RectVram *r, u32 *datos) {
    func_800112C0(D_80060C44, r);
    return D_800636C8->encolar(D_800636C8->escribirVram, r, 8, (s32)datos);
}

/* StoreImage: copia un rectangulo de la VRAM a la RAM. */
s32 func_80012ECC(RectVram *r, u32 *datos) {
    func_800112C0(D_80060C50, r);
    return D_800636C8->encolar(D_800636C8->leerVram, r, 8, (s32)datos);
}

/* ClearOTagR: arma una tabla de orden de n entradas al reves y deja la primera apuntando al primitivo
 * de cierre. */
u32 *func_80012FE4(u32 *ot, s32 n) {
    if (D_8006379A.depuracion >= 2) {
        D_80063794(D_80060C80, ot, n);
    }
    D_800636C8->limpiarOT(ot, n);
    D_8006370C = ((u32)D_800636F8 & 0xFFFFFF) | 0x4000000;
    *ot = (u32)&D_8006370C & 0xFFFFFF;
    return ot;
}

/* DrawPrim: espera al GPU y le manda un primitivo suelto (el largo en palabras esta en su byte 3). */
s32 func_80013090(u8 *prim) {
    s32 largo = prim[3];

    D_800636C8->sincronizar(0);
    return D_800636C8->dibujarPrim(prim + 4, largo);
}

/* DrawOTag: pone en la cola el dibujo de una tabla de orden. */
s32 func_800130EC(u32 *ot) {
    if (D_8006379A.depuracion >= 2) {
        D_80063794(D_80060C98, ot);
    }
    return D_800636C8->encolar(D_800636C8->dibujarOT, ot, 0, 0);
}
