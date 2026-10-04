#include "juego.h"

/* Reproducir un video STR con la barra de avance de fondo. */

extern void func_800169A0(void *f);          /* VSyncCallback */
extern s32 func_8005D50C(u8 *pedido, void *cada_cuadro);   /* el reproductor de video */
extern s32 func_80012D74(s32 modo);          /* DrawSync */
extern s32 func_8001E040();
extern s32 func_800211D4();

#define P16(p, d) (*(s16 *)((p) + (d)))
#define P32(p, d) (*(s32 *)((p) + (d)))

/* Arma el pedido del video (nombre, 320 de ancho en la VRAM, alto, 320x240 en pantalla, cuadros - 4,
 * volumen 0x7F), lo reproduce y vuelve a poner la barra como funcion de cada cuadro; espera al GPU.
 * Devuelve lo que devolvio el reproductor (16 bits). */
s32 func_80021A94(s32 nombre, s32 alto, s32 a2, s32 cuadros) {
    u8 p[0x20];
    s16 r;

    func_800169A0(0);
    P32(p, 0x00) = nombre;
    P16(p, 0x04) = 0;
    P16(p, 0x06) = 1;
    P16(p, 0x08) = 0x140;
    P16(p, 0x0A) = alto;
    P16(p, 0x0C) = 0;
    P32(p, 0x18) = 0;
    P16(p, 0x1C) = 0x7F;
    P16(p, 0x0E) = 0x140;
    P16(p, 0x10) = 0xF0;
    P32(p, 0x14) = SUMA_TRAMPA(cuadros, -4);
    r = func_8005D50C(p, func_8001E040);
    func_800169A0(func_800211D4);
    while (func_80012D74(1) != 0) {
    }
    return r;
}
