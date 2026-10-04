#include "juego.h"

/* El controlador del GPU de libgpu: pasar imagenes entre la RAM y la VRAM. */

extern volatile u32 *D_80063750;     /* GP0: comandos y datos */
extern volatile u32 *D_80063754;     /* GP1: control y estado */
extern volatile u32 *D_80063758;     /* DMA del GPU: direccion */
extern volatile u32 *D_8006375C;     /* DMA del GPU: tamano de bloque */
extern volatile u32 *D_80063760;     /* DMA del GPU: control */
extern s16 D_8006379C;               /* ancho de la VRAM */
extern s16 D_8006379E;               /* alto de la VRAM */
extern void func_800128CC(void);     /* preparar la espera */
extern s32 func_80012900(void);      /* se paso el tiempo de espera */

/* Recorta el ancho y el alto del rectangulo r a la VRAM (0 si son negativos). Devuelve los pixeles. */
static inline s32 recortar(s16 *r) {
    u16 w, h;

    if (r[2] < 0) {
        w = 0;
    } else {
        w = D_8006379C < r[2] ? (u16)D_8006379C : (u16)r[2];
    }
    r[2] = w;
    if (r[3] < 0) {
        h = 0;
    } else {
        h = D_8006379E < r[3] ? (u16)D_8006379E : (u16)r[3];
    }
    r[3] = h;
    return r[2] * (s16)h;
}

/* LoadImage del controlador: recorta r, espera a que el GPU acepte comandos, manda el comando de copia a la
 * VRAM con el rectangulo, los primeros pixeles por el GP0 y el resto (de a 16 palabras) por DMA. 0 si lo
 * mando, -1 si el rectangulo esta vacio o se paso el tiempo. */
s32 func_80011B60(s16 *r, u32 *p) {
    s32 t, palabras, bloques, resto;

    func_800128CC();
    t = recortar(r) + 1;
    t += (u32)t >> 31;
    palabras = t >> 1;
    bloques = t >> 5;
    if (palabras <= 0) {
        return -1;
    }
    resto = palabras - bloques * 16;
    while (!(*D_80063754 & 0x4000000)) {
        if (func_80012900() != 0) {
            return -1;
        }
    }
    *D_80063754 = 0x4000000;
    *D_80063750 = 0x1000000;
    *D_80063750 = 0xA0000000;
    *D_80063750 = *(u32 *)&r[0];
    *D_80063750 = *(u32 *)&r[2];
    for (resto--; resto != -1; resto--) {
        *D_80063750 = *p++;
    }
    if (bloques != 0) {
        *D_80063754 = 0x4000002;
        *D_80063758 = (u32)p;
        *D_8006375C = (bloques << 16) | 0x10;
        *D_80063760 = 0x1000201;
    }
    return 0;
}

/* StoreImage del controlador: igual, pero manda el comando de copia desde la VRAM, espera a que el GPU
 * tenga los datos listos y los lee: los primeros por el GP0 y el resto por DMA. */
s32 func_80011D9C(s16 *r, u32 *p) {
    s32 t, palabras, bloques, resto;

    func_800128CC();
    t = recortar(r) + 1;
    t += (u32)t >> 31;
    palabras = t >> 1;
    bloques = t >> 5;
    if (palabras <= 0) {
        return -1;
    }
    resto = palabras - bloques * 16;
    while (!(*D_80063754 & 0x4000000)) {
        if (func_80012900() != 0) {
            return -1;
        }
    }
    *D_80063754 = 0x4000000;
    *D_80063750 = 0x1000000;
    *D_80063750 = 0xC0000000;
    *D_80063750 = *(u32 *)&r[0];
    *D_80063750 = *(u32 *)&r[2];
    while (!(*D_80063754 & 0x8000000)) {
        if (func_80012900() != 0) {
            return -1;
        }
    }
    for (resto--; resto != -1; resto--) {
        *p++ = *D_80063750;
    }
    if (bloques != 0) {
        *D_80063754 = 0x4000003;
        *D_80063758 = (u32)p;
        *D_8006375C = (bloques << 16) | 0x10;
        *D_80063760 = 0x1000200;
    }
    return 0;
}
