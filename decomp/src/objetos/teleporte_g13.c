#include "objeto.h"

/* El remolino que lleva a Sabrina de un lugar a otro del nivel: solo con el hechizo del mundo; la achica
 * hacia su centro, la pasa al destino (con la camara y el companero) y la vuelve a agrandar. */

#define E32(e, d) (*(s32 *)((u8 *)(e) + (d)))
#define FUNC(o, d) (*(void **)((u8 *)(o) + (d)))

extern s8 nivel_actual;
extern s8 D_800C8566;                /* el hechizo puesto */
extern s32 D_8007CC5C;               /* 1: hay que borrar los objetos 0x1D de estado 6 y 7 */
extern s32 D_8007CC60;
extern s8 D_8008AF88[0x50];          /* que objetos estan en uso */
extern u8 D_8008AFD8[];              /* los objetos (0x120 bytes cada uno) */
extern Objeto *D_8007CB8C;           /* el companero */
extern Objeto *D_8007CAFC;           /* la camara */
extern s32 func_800221FC(s32 ax, s32 ay, s32 az, s32 bx, s32 by, s32 bz);  /* distancia al cuadrado */
extern void func_80025064(void);
extern void func_80033AD8(Objeto *o);
extern void func_80055CAC(Objeto *o);
extern void func_80055CA4(void);
extern void func_80030208(Objeto *o);
extern void func_800350A4(s32 *p);
extern void func_80037278(Objeto *camara, Objeto *a);

void func_800528AC(Objeto *o) {
    u8 *e = (u8 *)&o->extra;
    u8 *p;
    s32 i, d;

    if (e[0x24] == 0) {
        return;
    }
    switch (nivel_actual) {
    case 1: case 2: case 3:
        if (D_800C8566 != 1) {
            *(u8 *)&o->_20 |= 0x80;
            return;
        }
        break;
    case 4: case 5: case 6:
        if (D_800C8566 != 4) {
            *(u8 *)&o->_20 |= 0x80;
            return;
        }
        break;
    case 7: case 8: case 9:
        if (D_800C8566 != 3) {
            *(u8 *)&o->_20 |= 0x80;
            return;
        }
        break;
    case 10: case 11: case 12:
        if (D_800C8566 != 2) {
            *(u8 *)&o->_20 |= 0x80;
            return;
        }
        break;
    }
    if (D_8007CC5C != 0) {
        for (i = 0; i < 0x50; i++) {
            p = D_8008AFD8 + i * 0x120;
            if (D_8008AF88[i] != 0 && *(u16 *)(p + 0x22) == 0x1D) {
                if (E32(p, 0x74 + 0x18) == 6) {
                    p[0x20] |= 0x80;
                }
                if (E32(p, 0x74 + 0x18) == 7) {
                    p[0x20] |= 0x80;
                }
            }
        }
        D_8007CC5C = 0;
    }
    d = func_800221FC(o->x, o->y, o->z, p_sabrina->x, p_sabrina->y, p_sabrina->z);
    switch (o->estado) {
    case 0:
        if (d < E32(e, 8)) {
            o->estado = 1;
        }
        break;
    case 1:
        FUNC(p_sabrina, 0x14) = func_80025064;
        FUNC(D_8007CB8C, 0x14) = func_80025064;
        FUNC(p_sabrina, 0) = func_80025064;
        FUNC(D_8007CB8C, 0) = func_80025064;
        *(s16 *)((u8 *)p_sabrina->datos + 0x1A) = 2;
        *(s16 *)((u8 *)D_8007CB8C->datos + 0x1A) = 2;
        *(s16 *)((u8 *)o->datos + 0x1A) = 2;
        p_sabrina->x -= (p_sabrina->x - E32(e, 0x18)) >> 3;
        p_sabrina->y -= (p_sabrina->y - E32(e, 0x1C)) >> 3;
        p_sabrina->z -= (p_sabrina->z - E32(e, 0x20)) >> 3;
        p_sabrina->escala[0] -= 0x8C;
        p_sabrina->escala[1] -= 0x8C;
        p_sabrina->escala[2] -= 0x8C;
        if (p_sabrina->escala[0] < 5) {
            o->estado = 2;
            p_sabrina->escala[0] = 5;
            p_sabrina->escala[1] = 5;
            p_sabrina->escala[2] = 5;
            FUNC(p_sabrina, 0x14) = func_80033AD8;
            FUNC(D_8007CB8C, 0x14) = func_80055CAC;
            FUNC(p_sabrina, 0) = func_80030208;
            FUNC(D_8007CB8C, 0) = func_80055CA4;
            D_8007CC60 = D_8007CC60 == 0 ? 0x640000 : 0;
        }
        D_8007CB8C->x = p_sabrina->x;
        D_8007CB8C->y = p_sabrina->y;
        D_8007CB8C->z = p_sabrina->z;
        D_8007CB8C->escala[0] = p_sabrina->escala[0];
        D_8007CB8C->escala[1] = p_sabrina->escala[1];
        D_8007CB8C->escala[2] = p_sabrina->escala[2];
        func_80033AD8(p_sabrina);
        func_80055CAC(D_8007CB8C);
        break;
    case 2:
        *(s16 *)((u8 *)o->datos + 0x1A) = 2;
        p_sabrina->x = E32(e, 0xC);
        p_sabrina->y = E32(e, 0x10);
        p_sabrina->z = E32(e, 0x14);
        D_8007CAFC->x = E32(e, 0xC);
        D_8007CAFC->y = E32(e, 0x10);
        D_8007CAFC->z = E32(e, 0x14);
        D_8007CB8C->x = E32(e, 0xC);
        D_8007CB8C->y = E32(e, 0x10);
        D_8007CB8C->z = E32(e, 0x14);
        D_8007CAFC->y -= 0x40000;
        o->estado = 3;
        func_800350A4(&p_sabrina->x);
        func_80037278(D_8007CAFC, p_sabrina);
        break;
    case 3:
        *(s16 *)((u8 *)o->datos + 0x1A) = 2;
        if (p_sabrina->escala[0] < 0x1000) {
            p_sabrina->escala[0] += 0x9B;
            p_sabrina->escala[1] += 0x9B;
            p_sabrina->escala[2] += 0x9B;
            break;
        }
        o->estado = 0;
        p_sabrina->escala[0] = 0x1666;
        p_sabrina->escala[1] = 0x1000;
        p_sabrina->escala[2] = 0x1666;
        break;
    }
}
