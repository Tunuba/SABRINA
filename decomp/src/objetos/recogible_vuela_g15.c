#include "objeto.h"

/* Un recogible que vuela hacia Sabrina: cada paso se acerca un octavo de lo que falta (a la altura de su pecho,
 * y - 0xC000), frenado a 0x2CC/0x100, suelta una chispa al azar y gira. Cuando queda a menos de 0x6666 suma uno
 * a partida, suelta 20 chispas en circulo y queda marcado para borrarse (bit 0x80 de +0x20). */

extern s16 partida;
extern u8 *CrearParticula(s32 tipo, Objeto *o, s32 b, s32 x, s32 y, s32 z, s32 dx, s32 dy, s32 dz, s32 c,
                          s32 d, s32 e, s32 f, s32 g, s32 h);
extern s32 func_80014F10(void);         /* al azar */
extern s32 func_80021CE4(s32 n);        /* al azar, hasta n */
extern s32 func_8002225C(Objeto *o, s32 x, s32 y, s32 z);  /* distancia */

#define FRENAR(v) ((((v) >> 8) * 0x2CC >> 8) << 8)

void func_8004AB24(Objeto *o) {
    s32 dx, dy, dz;
    s32 i;

    o->empuje_x = (p_sabrina->x - o->x) >> 3;
    o->empuje_z = (p_sabrina->z - o->z) >> 3;
    o->vel_y = (p_sabrina->y - 0x4001 - 0x7FFF - o->y) >> 3;
    o->empuje_x = FRENAR(o->empuje_x);
    o->vel_y = FRENAR(o->vel_y);
    o->empuje_z = FRENAR(o->empuje_z);
    o->x += o->empuje_x;
    o->y += o->vel_y;
    o->z += o->empuje_z;
    dx = ((func_80014F10() & 0x3F) - 0x20) << 8;
    dy = ((func_80014F10() & 0x3F) - 0x20) << 8;
    dz = ((func_80014F10() & 0x3F) - 0x20) << 8;
    CrearParticula(0, o, 0, dx, dy, dz, 0, 0, 0, 0, 0, 0, 7, 2, 0);
    o->rot[1] += 0x2D;
    if (func_8002225C(o, p_sabrina->x, p_sabrina->y - 0x4001 - 0x7FFF, p_sabrina->z) < 0x6666) {
        partida++;
        for (i = 0; i < 0x14; i++) {
            CrearParticula(0, o, (s16) func_80021CE4(0x1000), 0, 0, 0x4000, 0, 0, 0x4CCC, 0, 0, 0, 0xF, 0x202, 0);
        }
        *(u8 *) &o->_20 |= 0x80;
    }
}
