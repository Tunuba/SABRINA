#include "objeto.h"

/* Campos de la segunda parte del objeto (+0x74) que usan estas funciones. */
#define EXTRA_S32(o, d) (*(s32 *)((u8 *)(o) + 0x74 + (d)))
#define EXTRA_S16(o, d) (*(s16 *)((u8 *)(o) + 0x74 + (d)))
#define EXTRA_U8(o, d) (*(u8 *)((u8 *)(o) + 0x74 + (d)))

extern u8 D_800D588C[];              /* tabla de registros de 24 bytes */
extern u32 func_8001C180(s32 *v);    /* largo de un vector */

/* Arranca el objeto: con la bandera 1 (extra+8) y un indice positivo en extra+0, cambia el indice por su
 * registro de D_800D588C, pone extra+0x1C = 0x1999, extra+0x21 = 0 y el estado 2; con indice 0 o menos
 * quita la bandera. Sin registro el estado queda en 0. El dano queda en el segundo argumento (1 si es 0). */
void func_8003CF60(Objeto *o, s32 dano) {
    s16 banderas = EXTRA_S16(o, 8);
    s32 i;

    if (banderas & 1) {
        if ((s16)EXTRA_S32(o, 0) > 0) {
            EXTRA_S32(o, 0x1C) = 0x1999;
            EXTRA_U8(o, 0x21) = 0;
            o->estado = 2;
            i = (s16)EXTRA_S32(o, 0);
            EXTRA_S32(o, 0) = (s32)(D_800D588C + i * 24);
        } else {
            EXTRA_S16(o, 8) = banderas & ~1;
            o->estado = 0;
        }
    } else {
        o->estado = 0;
    }
    if (dano) {
        o->dano = dano;
    } else {
        o->dano = 1;
    }
}

/* Borra extra+0x2C. Si Sabrina existe, su forma tiene la bandera 1 y esta a no mas de extra+8 (24.8) del
 * objeto, llama a la funcion del objeto en 0x10 con el y Sabrina. */
void func_80044D64(Objeto *o) {
    Objeto *s;
    s32 v[3];

    EXTRA_S32(o, 0x2C) = 0;
    s = p_sabrina;
    if (s != NULL && (s->forma.banderas & 1)) {
        v[0] = o->x - s->x;
        v[1] = o->y - s->y;
        v[2] = o->z - s->z;
        if (!((u32)(EXTRA_S32(o, 8) >> 8) < func_8001C180(v))) {
            (*(FuncObjeto2 *)((u8 *)o + 0x10))(o, p_sabrina);
        }
    }
}
