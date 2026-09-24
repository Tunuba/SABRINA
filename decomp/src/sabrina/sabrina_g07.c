#include "objeto.h"

extern Objeto *D_8007CB8C;           /* el objeto que va con Sabrina */

extern s32 func_800249CC(Objeto *o, s32 n);

/* Banderas de un byte que func_80030F18 marca segun el numero (D_800C8566 guarda la ultima). */
extern u8 D_800C8561, D_800C8562, D_800C8563, D_800C8564, D_800C8565, D_800C8566;

/* Llama a func_800249CC con Sabrina y n y con su acompanante y n + 1. Para n = 2, 4, 6, 8 y 10 marca la
 * bandera que le toca y la deja tambien en D_800C8566 (0, 1, 4, 2 y 3). */
void func_80030F18(s32 n) {
    func_800249CC(p_sabrina, n);
    func_800249CC(D_8007CB8C, n + 1);
    switch (n) {
    case 10:
        D_800C8566 = 3;
        D_800C8564 = 3;
        break;
    case 8:
        D_800C8566 = 2;
        D_800C8563 = 2;
        break;
    case 6:
        D_800C8566 = 4;
        D_800C8565 = 4;
        break;
    case 4:
        D_800C8566 = 1;
        D_800C8562 = 1;
        break;
    case 2:
        D_800C8566 = 0;
        D_800C8561 = 0;
        break;
    }
}

extern s8 D_8008AF88[0x50];          /* uno por objeto: si esta en uso */

/* Recorre los 0x50 objetos y a los que estan en uso, salvo los tipos 0, 1, 0x1C, 0x23, 0x2A, 0x2B y
 * 0x32, les prende el bit 0x40 del byte 0x20.
 * Ojo: el original nunca le da valor al puntero de los objetos; usa lo que trae v1 al entrar (su unico
 * llamador, func_80031698, deja ahi D_8007CAFC). Aqui se lee v1 igual. */
void func_80031494(void) {
    u8 *o;
    s32 i;

    __asm__ volatile("move %0, $3" : "=r"(o));
    for (i = 0; i < 0x50; i++, o += 0x120) {
        if (D_8008AF88[i] != 0) {
            u16 tipo = *(u16 *)(o + 0x22);

            if (tipo != 0x32 && tipo != 0x2B && tipo != 0x2A && tipo != 0x23 && tipo != 0x1C && tipo != 1 &&
                tipo != 0) {
                o[0x20] |= 0x40;
            }
        }
    }
}

extern s32 D_8007CB00, D_8007CB04, D_8007CB08;   /* posicion de Sabrina guardada */
extern s16 D_8007CB0C;               /* y su giro en y */
extern u8 D_8007CB1C;
extern s16 D_8007CBF0;

extern void func_800483F8(Objeto *o);
extern Objeto *func_800252A0(s32 clase, s32 a, s32 b, s32 c, s32 d, s32 e, s32 f, s32 g, s32 h, s32 i,
                             s32 j, s32 k, s32 l);
extern EstadoAnim *func_8002ECFC(Objeto *o);
extern s32 func_80030068(s32 a);
extern s32 func_80031698(Objeto *o);

/* Arranque de Sabrina: pone en limpio su parte extra, vida 20, crea su acompanante (clase 0x2A) y le da la
 * primera animacion de su tabla, guarda su posicion y giro y la deja en p_sabrina. */
s32 func_80031538(Objeto *o) {
    u16 *tabla = o->animaciones;
    u8 *e = (u8 *)&o->extra;
    EstadoAnim *a;

    func_800483F8(o);
    *(s32 *)(e + 0x04) = 0x5F9;
    *(s16 *)(e + 0x10) = 0;
    e[0x1A] = 0xFF;
    e[0x1B] = 0xFF;
    *(s16 *)(e + 0x18) = 0;
    e[0x26] = 0;
    *(s32 *)(e + 0x00) = 0;
    e[0x1F] = 0;
    e[0x20] = 0;
    e[0x24] = 0xFF;
    o->vida = 0x14;
    e[0x1D] = 0;
    D_8007CB8C = func_800252A0(0x2A, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
    if (func_8002ECFC(o) != NULL) {
        a = o->anim;
        a->velocidad = 0;
        a->animacion = tabla[0];
        a->_50 = 0;
        a->_53 = a->animacion;
        a->_52 = a->_50;
        a->_4E = 0x1000;
        ((u8 *)a)[8] = func_80030068(((s32 *)o->modelo)[1]);
    }
    D_8007CB00 = o->x;
    D_8007CB04 = o->y;
    D_8007CB08 = o->z;
    D_8007CB0C = o->rot[1];
    D_8007CB1C = 0;
    p_sabrina = o;
    {
        s32 r = func_80031698(o);

        D_8007CBF0 = 0;
        return r;
    }
}
