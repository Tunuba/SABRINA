#include "juego.h"

/* Funciones chicas sueltas que no tienen todavia un sistema propio. */

/* Devuelve el segundo argumento (un "no hace nada" de una tabla de funciones). */
s32 func_800447DC(s32 a, s32 b) {
    return b;
}

/* El tamano guardado justo antes de un bloque (0 si no hay bloque). */
s32 func_8004EA90(s32 a, s32 *bloque) {
    if (bloque == NULL) {
        return 0;
    }
    return bloque[-1];
}

extern s32 func_80016970(s32 canal, s32 f);

/* Instala f en el canal 3 de libetc. */
s32 func_8005C940(s32 f) {
    return func_80016970(3, f);
}

extern s32 func_80052114();
extern s32 func_80052184();

/* Copia el trozo de codigo func_80052114..func_80052184 a 0xDF80 (lo que corre desde ahi). */
void func_800522B0(void) {
    u32 *d = (u32 *)0xDF80;
    u32 *s = (u32 *)func_80052114;
    do {
        *d++ = *s++;
    } while (s != (u32 *)func_80052184);
}

extern s32 func_8003AF48(s32 *consulta);

/* Pregunta por la posicion de o (0x24..0x2C) y, si hay respuesta, guarda en o+0x50 la palabra 0x34
   de la consulta y la devuelve. */
s32 func_8002244C(u8 *o) {
    s32 c[0x13];
    c[0] = *(s32 *)(o + 0x24);
    c[1] = *(s32 *)(o + 0x28);
    c[2] = *(s32 *)(o + 0x2C);
    if (func_8003AF48(c) == 0) {
        return 0;
    }
    *(s32 *)(o + 0x50) = c[13];
    return *(s32 *)(o + 0x50);
}

extern char *D_8006D3A8[];
extern char D_80061234[];      /* "none" */

/* El nombre de un tipo (0 a 6), o "none". */
char *func_80029A1C(s32 n) {
    u32 i = n & 0xFF;
    if (i < 7) {
        return D_8006D3A8[i];
    }
    return D_80061234;
}
