#include "juego.h"

/* FntFlush de libgpu (PsyQ): dibujar el texto acumulado de una corriente de la fuente de depuracion. */

extern s32 D_80062AF8;               /* cuantas corrientes hay */
extern s32 D_80062AFC;               /* la corriente por defecto */
extern u8 D_80063508[][0x30];        /* las corrientes */
extern void func_800140BC(u32 *ot);  /* ClearOTag */
extern void AddPrim(u32 *ot, void *p);
extern void func_800130EC(u32 *ot);  /* DrawOTag */

#define C8(p, d) (*(u8 *)((p) + (d)))
#define C16(p, d) (*(s16 *)((p) + (d)))
#define C32(p, d) (*(s32 *)((p) + (d)))

/* Corriente: 0x7 fondo, 0x8 x, 0xA y, 0xC ancho, 0xE alto, 0x10 tabla de orden, 0x1C letras que quedan,
 * 0x20 sprites, 0x24 texto, 0x28 cuenta, 0x2C ajustar el fondo al texto. Cada letra es un sprite de 8x8 de
 * la imagen de la fuente (las minusculas como mayusculas); ' ' corre 8, tab 32, '\n' baja una linea y
 * "~cRGB" cambia el color. Al pasar el borde baja de linea (si no se ajusta el fondo). Devuelve la tabla de
 * orden, o 0 si la corriente no existe. */
u32 *func_80010BD8(s32 id) {
    u8 *s;
    u32 *ot;
    u8 *t;
    u8 *spr;
    s32 quedan, x, y, xmax, ymax, ancho, ajustar, linea, v, fila;
    s32 r = 0x80, g = 0x80, b = 0x80;
    s8 c;

    ancho = 0;
    if (id < 0 || id >= D_80062AF8) {
        id = D_80062AFC;
        if (C32(D_80063508[id], 0x24) == 0) {
            return 0;
        }
    }
    s = D_80063508[id];
    ot = (u32 *)(s + 0x10);
    t = (u8 *)C32(s, 0x24);
    quedan = C32(s, 0x1C);
    x = C16(s, 0x8);
    y = C16(s, 0xA);
    ymax = y + C16(s, 0xE);
    spr = (u8 *)C32(s, 0x20);
    ajustar = C32(s, 0x2C);
    xmax = x + C16(s, 0xC);
    func_800140BC(ot);
    while ((c = *t) != 0) {
        if (quedan == 0) {
            break;
        }
        linea = 0;
        if (c == ' ') {
            x += 8;
        } else if (c == '\t') {
            x += 0x20;
        } else if (c == '\n') {
            linea = 1;
            goto salto;
        } else if (c == '~') {
            t++;
            if (*t == 'c') {
                t++;
                r = ((s8)t[0] - '0') << 4;
                g = ((s8)t[1] - '0') << 4;
                t += 2;
                b = ((s8)t[0] - '0') << 4;
            }
            goto salto;
        } else {
            v = (u8)(*t - 'a') < 26 ? (s8)*t - 0x40 : (s8)*t - 0x20;
            fila = v / 16;
            spr[0xC] = (v - fila * 16) << 3;
            spr[0xD] = fila << 3;
            C16(spr, 0x8) = x;
            C16(spr, 0xA) = y;
            spr[4] = r;
            spr[5] = g;
            spr[6] = b;
            AddPrim(ot, spr);
            spr += 0x10;
            x += 8;
        }
        if (x >= xmax && ajustar == 0) {
            linea = 1;
        }
salto:
        if (linea) {
            if (ancho < x) {
                ancho = x;
            }
            y += 8;
            x = C16(s, 0x8);
            if (y >= ymax) {
                break;
            }
        }
        t++;
        quedan--;
    }
    if (C8(s, 0x7) != 0) {
        AddPrim(ot, s);
        if (ajustar != 0) {
            C16(s, 0xC) = ancho - *(u16 *)(s + 0x8);
            C16(s, 0xE) = y - (*(u16 *)(s + 0xA) - 8);
        }
    }
    func_800130EC(ot);
    t = (u8 *)C32(s, 0x24);
    C32(s, 0x28) = 0;
    *t = 0;
    return ot;
}
