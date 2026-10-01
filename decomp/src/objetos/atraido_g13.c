#include "objeto.h"

/* Un objeto que flota y, cuando Sabrina se acerca, vuela hacia ella dejando chispas; al alcanzarla se
 * deshace en una lluvia de particulas. */

/* Su companero (lo que se dibuja): posicion en +4 y un contador en +0x40. */
typedef struct {
    u8 _00[4];
    s32 x, y, z;                     /* 0x04 */
    u8 _10[0x30];
    s16 vida;                        /* 0x40 */
} Companero;
EN(Companero, vida, 0x40);

typedef struct {
    s32 premio;                      /* 0x00, se pasa a func_8004C730 al alcanzar a Sabrina */
    s8 particula;                    /* 0x04, tipo de las chispas */
    u8 _05[3];
    s32 y_base;                      /* 0x08 */
    Companero *comp;                 /* 0x0C */
} ExtraAtraido;

extern s32 func_8002225C(Objeto *o, s32 x, s32 y, s32 z);  /* distancia del objeto a un punto */
extern s32 func_80014F10(void);      /* al azar */
extern void func_8004C730(s32 premio);
extern void *CrearParticula(s32 tipo, Objeto *o, s32 b, s32 x, s32 y, s32 z, s32 dx, s32 dy, s32 dz, s32 c,
                            s32 d, s32 e, s32 vida, s32 f, s32 g);
extern s32 TocarSonido(s32 prog, s32 tono, s32 nota, s32 prioridad);

/* Estado 0: espera a que Sabrina este a menos de 0x140000. 1: flota (sube y baja); si Sabrina se aleja
 * vuelve a 0 y si esta a menos de 0x20000 pasa a 2. 2: vuela hacia el pecho de Sabrina achicandose y
 * girando; al llegar a menos de 0x6666 da su premio, suena, suelta 6 x 5 particulas en abanico y se marca
 * para borrar (bit 0x80 de +0x20). */
void func_80056584(Objeto *o) {
    ExtraAtraido *e = (ExtraAtraido *)&o->extra;
    s32 d, rx, ry, rz, s, c, i, j;

    e->comp->vida = 100;
    switch (o->estado) {
    case 0:
        if (p_sabrina != NULL && func_8002225C(o, p_sabrina->x, p_sabrina->y, p_sabrina->z) < 0x140000) {
            o->estado = 1;
        }
        break;
    case 1:
        o->rot[1] = o->rot[1] + 0x28;
        o->y = e->y_base + rsin(o->rot[1] * 4) * 4;
        e->comp->y = o->y;
        if (p_sabrina != NULL) {
            d = func_8002225C(o, p_sabrina->x, p_sabrina->y, p_sabrina->z);
            if (d >= 0x140001) {
                o->estado = 0;
            } else if (d < 0x20000) {
                o->estado = 2;
            }
        }
        break;
    case 2:
        o->empuje_x = (p_sabrina->x - o->x) >> 3;
        o->empuje_z = (p_sabrina->z - o->z) >> 3;
        o->vel_y = (p_sabrina->y - 0x4001 - 0x7FFF - o->y) >> 3;
        o->empuje_x = (((o->empuje_x >> 8) * 0x2E6) >> 8) << 8;
        o->vel_y = (((o->vel_y >> 8) * 0x2E6) >> 8) << 8;
        o->empuje_z = (((o->empuje_z >> 8) * 0x2E6) >> 8) << 8;
        o->x = o->x + o->empuje_x;
        o->y = o->y + o->vel_y;
        o->z = o->z + o->empuje_z;
        e->comp->x = o->x;
        e->comp->y = o->y;
        e->comp->z = o->z;
        o->escala[0] = o->escala[0] - (o->escala[0] >> 4);
        o->escala[1] = o->escala[0];
        o->escala[2] = o->escala[0];
        rx = ((func_80014F10() & 0x3F) - 0x20) << 8;
        ry = ((func_80014F10() & 0x3F) - 0x20) << 8;
        rz = ((func_80014F10() & 0x3F) - 0x20) << 8;
        CrearParticula(e->particula, o, 0, rx, ry, rz, 0, 0, 0, 0, 0, 0, 7, 2, 0);
        o->rot[0] = o->rot[0] + 0xF;
        o->rot[1] = o->rot[1] + 0x17;
        if (p_sabrina == NULL ||
            func_8002225C(o, p_sabrina->x, p_sabrina->y - 0x4001 - 0x7FFF, p_sabrina->z) >= 0x6666) {
            break;
        }
        e->comp->vida = 1;
        TocarSonido(0x1E, 0, 0x2A, 0x7F);
        func_8004C730(e->premio);
        for (i = 0; i < 0x1000; i += 0x320) {
            for (j = 0; j < 0x1000; j += 0x3E8) {
                s = (rsin(i) * 0xCCC) >> 12;
                c = (rcos(i) * 0xCCC) >> 12;
                CrearParticula(e->particula, o, (s16)j, 0, 0, 0x28F, 0, s, c, 0, 0, 0, 0xF, 0x202, 0);
            }
        }
        *((u8 *)o + 0x20) |= 0x80;
        break;
    default:
        o->estado = 0;
        break;
    }
}
