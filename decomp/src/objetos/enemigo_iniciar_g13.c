#include "objeto.h"

/* Iniciar un enemigo que patrulla: la boca y los cuadros del ataque segun el mundo, su ruta (o quieto) y
 * los alcances al cuadrado. */

#define E8(e, d) (*(s8 *)((u8 *)(e) + (d)))
#define E16(e, d) (*(s16 *)((u8 *)(e) + (d)))
#define E32(e, d) (*(s32 *)((u8 *)(e) + (d)))

extern s8 nivel_actual;
extern u8 D_800D588C[];              /* los puntos de ruta, 0x18 bytes */
extern void func_80048164(Objeto *o, void *punto);
extern s32 func_8002ECFC(Objeto *o);  /* 1 si tiene animacion */
extern s8 func_80030068(s32 a);

/* Pone la boca (x, y, z), los dos cuadros del ataque y la vida. */
static void boca(u8 *e, Objeto *o, s32 y, s32 z, s8 c1, s8 c2, s8 vida) {
    E32(e, 0xC) = 0;
    E32(e, 0x10) = y;
    E32(e, 0x14) = z;
    E8(e, 0x27) = c1;
    E8(e, 0x28) = c2;
    o->vida = vida;
}

void func_800460CC(Objeto *o) {
    u8 *e = (u8 *)&o->extra;
    u16 *t = o->animaciones;
    EstadoAnim *a;
    s32 v;

    E32(e, 0x2C) = 0;
    o->vida = 2;
    switch (nivel_actual) {
    case 1: case 2: case 3:
        boca(e, o, -0xD999, 0xD999, 0x10, 0x10, 1);
        break;
    case 4: case 5: case 6:
        boca(e, o, -0x18D91, 0x9439, 0x1E, 0x22, 1);
        break;
    case 7: case 8: case 9:
        boca(e, o, 0, 0, 0xA, 0xA, 2);
        break;
    case 10: case 11: case 12:
        boca(e, o, -0x16000, 0x953F, 0xE, 0xE, 1);
        break;
    }
    o->dano = 1;
    E16(e, 0x44) = 0;
    if ((s16)E32(e, 0) > 0) {
        E32(e, 0x30) = 0x1999;
        E8(e, 0x35) = 0;
        o->estado = 2;
        E32(e, 0) = (s32)(D_800D588C + (s16)E32(e, 0) * 0x18);
        E8(e, 0x24) |= 1;
        func_80048164(o, (void *)E32(e, 0));
        if (o->estado == 0xB) {
            E8(e, 0x24) = 4;
        } else if (nivel_actual == 9 || nivel_actual == 8 || nivel_actual == 7) {
            E16(o, 0x112) |= 0x100;
        }
        o->x = ((s32 *)E32(e, 0))[0];
        o->y = ((s32 *)E32(e, 0))[1];
        o->z = ((s32 *)E32(e, 0))[2];
    } else {
        E8(e, 0x24) &= ~1;
        o->estado = 0xC;
    }
    if (func_8002ECFC(o)) {
        a = o->anim;
        a->velocidad = 0;
        a->_4E = 0x800;
        a->animacion = t[0];
        a->_50 = 0;
        a->_53 = a->animacion;
        a->_52 = a->_50;
        *((s8 *)a + 8) = func_80030068(((s32 *)o->modelo)[1]);
    }
    E32(e, 0x38) = o->x;
    E32(e, 0x3C) = o->y;
    E32(e, 0x40) = o->z;
    v = E32(e, 8) >> 8;
    E32(e, 8) = ((v * v) >> 8) << 8;
    v = E32(e, 4) >> 8;
    E32(e, 4) = ((v * v) >> 8) << 8;
    if (nivel_actual == 9 || nivel_actual == 8 || nivel_actual == 7) {
        E16(o, 0x112) |= 0x100;
    }
}
