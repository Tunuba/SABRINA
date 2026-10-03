#include "juego.h"

/* Crear una particula (humo, chispas, polvo, estrellas...). */

extern u16 D_8007CA84;               /* particulas vivas */
extern u8 *D_8007CA88;               /* base de los cuadros de animacion de las particulas (32 bytes c/u) */
extern u8 tabla_efectos[];           /* por tipo, 20 bytes: colores, cuadro, duracion, escala... */
extern u8 *func_8001ED9C(void);      /* una particula libre */
extern s32 rsin(s32 a);
extern s32 rcos(s32 a);
extern s32 func_8001EDE4();          /* lo que mueve cada particula */

#define P8(p, d) (*(u8 *)((p) + (d)))
#define P16(p, d) (*(s16 *)((p) + (d)))
#define P32(p, d) (*(s32 *)((p) + (d)))

/* Crea una particula del tipo dado (menos de 40) si hay lugar (menos de 200 vivas). Si hay objeto o, la
 * posicion (x, y, z) y el angulo b son relativos a el: se giran por b + su angulo y se suman a su posicion.
 * La velocidad (dx, dz) se gira por el angulo; dy no. c y e (si g no tiene 0x100) son otro vector que tambien
 * se gira. d, f y g se copian; h + 0x200 tambien. El resto sale de tabla_efectos. Devuelve la particula o 0. */
u8 *CrearParticula(s32 tipo, u8 *o, s32 b, s32 x, s32 y, s32 z, s32 dx, s32 dy, s32 dz, s32 c, s32 d, s32 e,
                   s32 f, s32 g, s32 h) {
    u8 *p = 0;
    u8 *t;
    s32 ang, s, co, px, py, pz;

    if (tipo >= 0x28) {
        return 0;
    }
    if (D_8007CA84 < 0xC8) {
        p = func_8001ED9C();
    }
    if (p == 0) {
        return 0;
    }
    D_8007CA84++;
    if (o != 0) {
        ang = (s16)((b + P16(o, 0x32)) & 0xFFF);
        s = (s16)rsin(ang);
        co = (s16)rcos(ang);
        px = ((co * x) >> 12) + ((s * z) >> 12);
        pz = ((-s * x) >> 12) + ((co * z) >> 12);
        px += P32(o, 0x24);
        pz += P32(o, 0x2C);
        py = y + P32(o, 0x28);
        /* en un registro: si no, GCC lo guarda en el lugar del argumento y (pila del que llama), y el
           original no toca esa pila */
        __asm__("" : "+r"(py));
    } else {
        s = (s16)rsin(b);
        co = (s16)rcos(b);
        px = x;
        py = y;
        pz = z;
    }
    P32(p, 0x04) = px;
    P32(p, 0x08) = py;
    P32(p, 0x0C) = pz;
    P32(p, 0x10) = (co * dx + s * dz) >> 12;
    P32(p, 0x18) = (-s * dx + co * dz) >> 12;
    P32(p, 0x14) = dy;
    /* las dos ramas separadas: si no, GCC las junta guardando el resultado en el lugar del argumento c (la
       pila del que llama), que el original no toca */
    if (g & 0x100) {
        P32(p, 0x2C) = c;
        P32(p, 0x34) = e;
        __asm__ volatile("" ::: "memory");
    } else {
        s32 r1 = (co * c + s * e) >> 12;
        s32 r2 = (-s * c + co * e) >> 12;
        __asm__("" : "+r"(r1), "+r"(r2));
        P32(p, 0x2C) = r1;
        P32(p, 0x34) = r2;
    }
    P32(p, 0x30) = d;
    P16(p, 0x40) = f;
    P16(p, 0x42) = g;
    P16(p, 0x44) = (s16)h + 0x200;
    t = tabla_efectos + tipo * 20;
    P8(p, 0x1C) = t[0];
    P8(p, 0x1D) = t[1];
    P8(p, 0x1E) = t[2];
    P32(p, 0x24) = *(s32 *)(t + 8);
    P32(p, 0x3C) = *(s32 *)(t + 0xC);
    P8(p, 0x4B) = t[3];
    P32(p, 0x20) = (s32)(D_8007CA88 + t[3] * 32);
    P8(p, 0x4A) = t[4];
    P8(p, 0x4C) = 0;
    P8(p, 0x48) = t[0x11];
    P8(p, 0x49) = t[0x11];
    P8(p, 0x28) = t[0x10];
    P32(p, 0x50) = (s32)func_8001EDE4;
    return p;
}
