#include "objeto.h"

/* La pieza de hechizo de un nivel: gira, chispea, crece cuando se puede tomar (si es la del jefe, solo despues
 * de vencerlo) y al tocarla da el hechizo del mundo. */

extern s8 nivel_actual;
extern s8 D_800C855E;                /* piezas juntadas */
extern u8 D_800C8567[];              /* cual pieza se tomo */
extern s8 D_800C8582, D_800C8583, D_800C8584, D_800C8585;  /* el jefe de cada mundo */
extern s32 D_800C98B8;
extern s8 D_8007C890, D_8007C891, D_8007C892;
extern s32 func_8002225C(Objeto *o, s32 x, s32 y, s32 z);
extern s32 func_80021CE4(s32 n);
extern s32 rsin(s32 a);
extern s32 rcos(s32 a);
extern u8 *CrearParticula(s32 tipo, Objeto *o, s32 b, s32 x, s32 y, s32 z, s32 dx, s32 dy, s32 dz, s32 c,
                          s32 d, s32 e, s32 f, s32 g, s32 h);
extern s32 TocarSonido(s32 prog, s32 tono, s32 nota, s32 prioridad);

/* El estado del jefe del mundo del nivel (o -1 si el nivel no tiene jefe). */
static s32 jefe(void) {
    switch (nivel_actual) {
    case 3:
        return D_800C8582;
    case 6:
        return D_800C8583;
    case 9:
        return D_800C8584;
    case 12:
        return D_800C8585;
    }
    return -1;
}

void func_80054C5C(Objeto *o) {
    u8 *e = (u8 *)&o->extra;
    s32 numero = *(s32 *)(e + 4);
    s32 del_jefe = *(s32 *)(e + 8);
    s32 j, d, ang, giro, s, c;

    if ((s8)D_800C8567[numero] != 0) {
        *(u8 *)&o->_20 |= 0x80;
        return;
    }
    o->rot[1] += 0x64;
    if (o->rot[1] >= 0x1000) {
        o->rot[1] -= 0x1000;
    }
    switch (o->estado) {
    case 0:
        if (del_jefe == 0) {
            return;
        }
        j = jefe();
        if (j != -1 && j != 0) {
            o->estado = 1;
        }
        return;
    case 1:
        if (del_jefe != 0) {
            j = jefe();
            if (j == 2) {
                o->estado = 4;
                return;
            }
        }
        if (o->escala[0] < 0x1000) {
            o->escala[0] += (0x1000 - o->escala[0]) >> 2;
            if (o->escala[0] >= 0x1000) {
                o->escala[0] = 0x1000;
            }
            o->escala[2] = o->escala[0];
            o->escala[1] = o->escala[0];
        }
        if (p_sabrina != NULL) {
            d = func_8002225C(o, p_sabrina->x, p_sabrina->y, p_sabrina->z);
            if (d >= 0x140001) {
                o->estado = 1;
            } else if (d < 0x20000) {
                o->estado = 2;
            }
        }
        ang = func_80021CE4(0x1000);
        giro = func_80021CE4(0x1000);
        s = (rsin(ang) * 0xC000) >> 12;
        c = (rcos(ang) * 0xC000) >> 12;
        CrearParticula(0xE, o, (s16)giro, 0, s - 0x5999, c, 0, -s >> 5, -c >> 5, 0, 0, 0, 0xF, 0x202, 0);
        return;
    case 2:
        switch (nivel_actual) {
        case 1: case 4: case 7: case 10:
            D_8007C890 = 1;
            break;
        case 2: case 5: case 8: case 11:
            D_8007C891 = 1;
            break;
        case 3: case 6: case 9: case 12:
            D_8007C892 = 1;
            break;
        }
        TocarSonido(0x20, 0, 0x2A, 0x7F);
        TocarSonido(0x12, 0, 0x2A, 0x7F);
        D_800C855E++;
        D_800C8567[numero] = 1;
        D_800C98B8 = 1;
        o->estado = 4;
        if (del_jefe != 0) {
            switch (nivel_actual) {
            case 3:
                D_800C8582 = 2;
                break;
            case 6:
                D_800C8583 = 2;
                break;
            case 9:
                D_800C8584 = 2;
                break;
            case 12:
                D_800C8585 = 2;
                break;
            }
        }
        return;
    case 4:
        *(u8 *)&o->_20 |= 0x80;
        return;
    }
}
