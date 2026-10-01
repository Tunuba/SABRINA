#include "objeto.h"

/* Un objeto que se arma una sola vez por lugar: anota donde se creo (hasta 31) y, si ya habia uno a
 * menos de 0x100 (/256), se borra. */

typedef struct {
    u8 _00[0x18];
    s32 estado;                      /* 0x18, se copia al estado del objeto */
    s32 _1C;                         /* 0x1C */
    s32 _20, _24, _28, _2C, _30;     /* 0x20 */
    s32 *lista;                      /* 0x34 */
    s32 datos[1];                    /* 0x38 */
} ExtraMarca;

extern s32 D_800D568C[][3];          /* los lugares ya usados */
extern s32 D_8007CC6C;               /* cuantos */
extern char D_80075B58[];
extern s32 func_80053A98(s32 *pos);
extern void func_80053B30(ExtraMarca *e);
extern s32 func_8001C390(s32 ax, s32 ay, s32 az, s32 bx, s32 by, s32 bz);  /* producto escalar */
extern s32 Afirmar(s32 cond, char *archivo, s32 linea);

void func_80053C74(Objeto *o) {
    ExtraMarca *e = (ExtraMarca *)&o->extra;
    s32 i, v[3];

    o->estado = e->estado;
    switch ((u16)o->estado) {
    case 4:
        e->_28 = e->_1C;
        break;
    case 6:
        e->_20 = 0;
        e->_24 = 0;
        e->lista = e->datos;
        if (func_80053A98(&o->x) == 1) {
            *((u8 *)o + 0x20) |= 0x80;
        }
        break;
    case 8:
        for (i = 0; i < D_8007CC6C; i++) {
            v[0] = (o->x - D_800D568C[i][0]) >> 8;
            v[1] = (o->y - D_800D568C[i][1]) >> 8;
            v[2] = (o->z - D_800D568C[i][2]) >> 8;
            if (func_8001C390(v[0], v[1], v[2], v[0], v[1], v[2]) < 0x100) {
                *((u8 *)o + 0x20) |= 0x80;
                return;
            }
        }
        e->_20 = 0;
        e->_24 = 0;
        e->lista = e->datos;
        if (func_80053A98(&o->x) == 1) {
            *((u8 *)o + 0x20) |= 0x80;
        }
        if (D_8007CC6C < 31) {
            D_800D568C[D_8007CC6C][0] = o->x;
            D_800D568C[D_8007CC6C][1] = o->y;
            D_800D568C[D_8007CC6C][2] = o->z;
            D_8007CC6C++;
        } else {
            Afirmar(0, D_80075B58, 0xDF);
        }
        break;
    case 7:
        e->_20 = 0;
        break;
    }
    e->_30 = 0;
    e->_2C = 1;
    func_80053B30(e);
}
