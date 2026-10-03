#include "objeto.h"

/* Crear un objeto lanzado hacia Sabrina (un proyectil de enemigo). */

extern Objeto *func_800252A0(s32 clase, Objeto *padre, s32 x, s32 y, s32 z, s32 vx, s32 vy, s32 vz, s32 rx,
                             s32 ry, s32 rz, s32 a, s32 b);
extern void func_800249CC(Objeto *o, s32 n);
extern void func_80048CF4(Objeto *o, s32 *destino, s32 alcance, s32 *vel);   /* tiro hacia un punto */
extern void func_8001C45C(s32 *v);   /* normaliza un vector (largo 0x1000) */
extern void func_8003B38C(s32 *consulta, s32 *desde, s32 *hasta);
extern s32 func_8003AE84(void);      /* el segmento choca con algo */
extern s32 D_800C6594[3];            /* la consulta de colision: desde */
extern s32 D_800C65A0[3];            /* hasta */
extern s32 func_8003C528(), func_80024DF4(), func_8003BFC4(), func_80024F74(), func_80024F84();
extern s32 thunk_FUN_8001e588(), thunk_FUN_8004866c();

#define C8(p, d) (*(u8 *)((u8 *)(p) + (d)))
#define C16(p, d) (*(s16 *)((u8 *)(p) + (d)))
#define C32(p, d) (*(s32 *)((u8 *)(p) + (d)))

static inline s32 por_0x280(s32 v) {
    s32 q = v >> 4;
    return (SUMA_TRAMPA(q << 2, q) << 7) >> 8;
}

/* Crea el objeto de la clase 0xC en pos (hijo de padre), con sus parametros (a..d y el tipo), sus funciones
 * de proyectil, y le da la velocidad para llegar a Sabrina (un poco por encima de ella); si el primer tramo
 * del vuelo ya choca con algo, lo marca para borrar. Devuelve lo que el original deja en v0. */
s32 func_8003C678(Objeto *padre, s32 *pos, s32 x2, s32 tipo, s32 a, s32 b, s32 c, s32 d) {
    Objeto *o;
    u8 *e;
    s32 dest[3];
    s32 v[3];

    o = func_800252A0(0xC, padre, pos[0], pos[1], pos[2], 0, 0, 0, 0, 0, 0, 1, 1);
    if (o == NULL) {
        return 0;
    }
    e = (u8 *)o + 0x74;
    C16(e, 0x24) = (s16)b;
    C16(e, 0x20) = (s16)c;
    C8(e, 0x12) = tipo;
    C16(e, 0x22) = (s16)a;
    C16(e, 0x26) = (s16)d;
    func_800249CC(o, -1);
    C32(o, 0x00) = (s32)func_8003C528;
    C32(o, 0x04) = (s32)func_80024DF4;
    C32(o, 0x08) = (s32)func_8003BFC4;
    C32(o, 0x0C) = (s32)func_80024F74;
    C32(o, 0x10) = (s32)func_80024F84;
    C32(o, 0x14) = (s32)thunk_FUN_8001e588;
    C32(o, 0x18) = (s32)thunk_FUN_8004866c;
    C16(o, 0x112) = 0x803;
    C16(o, 0x114) = 1;
    C8(o, 0x119) = 1;
    dest[0] = p_sabrina->x;
    dest[1] = SUMA_TRAMPA(SUMA_TRAMPA(p_sabrina->y, -0xCCD), -0x7FFF);
    dest[2] = p_sabrina->z;
    func_80048CF4(o, dest, 0x4000, v);
    C32(o, 0x38) = v[0];
    C32(o, 0x3C) = v[1];
    C32(o, 0x40) = v[2];
    func_8001C45C(v);
    v[0] = por_0x280(v[0]);
    v[1] = por_0x280(v[1]);
    v[2] = por_0x280(v[2]);
    D_800C6594[0] = C32(o, 0x24);
    D_800C6594[1] = C32(o, 0x28);
    D_800C6594[2] = C32(o, 0x2C);
    D_800C65A0[0] = SUMA_TRAMPA(C32(o, 0x24), C32(o, 0x38));
    D_800C65A0[1] = SUMA_TRAMPA(C32(o, 0x28), C32(o, 0x3C));
    D_800C65A0[2] = SUMA_TRAMPA(C32(o, 0x2C), C32(o, 0x40));
    func_8003B38C(D_800C6594, D_800C6594, D_800C65A0);
    if (func_8003AE84() == 0) {
        return 0;
    }
    C8(o, 0x20) |= 0x80;
    return C8(o, 0x20);
}
