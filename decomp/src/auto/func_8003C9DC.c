#include "objeto.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"




void func_8003C9DC(Objeto *arg0) {
    s16 sp5E;
    s16 temp_s2;
    s16 temp_v0;
    s16 temp_v0_2;
    s16 temp_v1;
    s32 temp_a0;
    s32 temp_a0_2;
    s32 temp_s2_2;
    s32 temp_s3;
    s32 temp_s4;
    s32 temp_v0_3;
    s32 temp_v1_3;
    s32 var_v0;
    s32 var_v0_2;
    void *temp_s1;
    void *temp_v1_2;

    temp_s1 = arg0 + 0x74;
    temp_s2 = M2C_FIELD(temp_s1, s16 *, 0xC);
    temp_v0 = arg0->estado;
    switch (temp_v0) {                              /* irregular */
    case 1:
        arg0->forma.banderas = 0;
        arg0->y = M2C_FIELD(arg0, s32 *, 0x50);
        temp_v1 = M2C_FIELD(temp_s1, s16 *, 0x10);
        M2C_FIELD(temp_s1, s16 *, 0x10) = (s16) (temp_v1 - 1);
        if (temp_v1 == 0) {
            if (temp_s2 & 0x40) {
                var_v0 = func_80021CE4((s32) M2C_FIELD(temp_s1, s16 *, 0xE));
            } else {
                var_v0 = (s32) M2C_FIELD(temp_s1, s16 *, 0xE);
            }
            M2C_FIELD(temp_s1, s16 *, 0x10) = (s16) var_v0;
            arg0->estado = 2;
            return;
        }
        return;
    case 2:
        temp_s4 = func_8002225C((s32) arg0, p_sabrina->x, (p_sabrina->y - 0x4001) - 0x7FFF, p_sabrina->z);
        if (!(temp_s2 & 1) || (temp_s4 < 0x80001)) {
            sp5E = func_8002218C(arg0, p_sabrina->x, p_sabrina->z);
            if (temp_s2 & 4) {
                if (temp_s2 & 2) {
                    sp5E = func_80021D44((s32) &arg0->rot[1], (s32) sp5E, 0x14);
                } else {
                    arg0->rot[1] = sp5E;
                }
                temp_a0 = (temp_s4 / 17476) + ((u32) temp_s4 >> 0x1F);
                M2C_FIELD(temp_s1, s32 *, 4) = (s32) (((s32) (p_sabrina->y - arg0->y) / temp_a0) - ((s32) (temp_a0 * 0x51E) >> 1));
            }
            if (!(temp_s2 & 2) || (temp_v0_2 = func_80021D44((s32) &sp5E, (s32) arg0->rot[1], 0x32), sp5E = temp_v0_2, (temp_v0_2 == 0))) {
                arg0->empuje_x = (s32) (M2C_FIELD(temp_s1, s32 *, 8) * rsin((s32) arg0->rot[1])) >> 0xC;
                arg0->empuje_z = (s32) (M2C_FIELD(temp_s1, s32 *, 8) * rcos((s32) arg0->rot[1])) >> 0xC;
                if (temp_s2 & 0x80) {
                    var_v0_2 = func_80021CE4(M2C_FIELD(temp_s1, s32 *, 4));
                } else {
                    var_v0_2 = M2C_FIELD(temp_s1, s32 *, 4);
                }
                arg0->vel_y = var_v0_2;
                arg0->estado = 3;
                temp_v1_2 = arg0->modelo;
                M2C_FIELD(temp_v1_2, u8 *, 0x64) = (u8) (M2C_FIELD(temp_v1_2, u8 *, 0x64) & 0xFE);
                arg0->forma.banderas = 0x880;
                return;
            }
        }
        break;
    case 3:
        temp_a0_2 = arg0->escala[0];
        if (temp_a0_2 < 0x1000) {
            arg0->escala[0] = temp_a0_2 + ((s32) (0x1000 - temp_a0_2) >> 1);
            if (arg0->escala[0] >= 0x1000) {
                arg0->escala[0] = 0x1000;
            }
            arg0->escala[1] = arg0->escala[0];
            arg0->escala[2] = arg0->escala[0];
        }
        M2C_FIELD(arg0, s32 *, 0x50) = func_8002244C((s32) arg0);
        arg0->vel_y += 0x51E;
        arg0->x += arg0->empuje_x;
        arg0->y += arg0->vel_y;
        arg0->z += arg0->empuje_z;
        if (temp_s2 & 0x20) {
            temp_s3 = func_80021CE4(0x800) - 0x400;
            temp_s2_2 = func_80021CE4(0x800) - 0x400;
            temp_v1_3 = func_80021CE4(0x800) - 0x400;
            CrearParticula((s32) M2C_FIELD(temp_s1, s8 *, 0x12), (s32) arg0, 0, temp_s3 * 4, /* extra? */ (temp_s2_2 * 4), /* extra? */ (temp_v1_3 * 4), /* extra? */ temp_s3, /* extra? */ temp_s2_2, /* extra? */ temp_v1_3, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 7, /* extra? */ 2, /* extra? */ 0);
        }
        if (temp_s2 & 0x200) {
            func_800221A8((s32) arg0, arg0->x + arg0->empuje_x, arg0->y + arg0->vel_y, arg0->z + arg0->empuje_z);
        }
        temp_v0_3 = M2C_FIELD(arg0, s32 *, 0x50);
        if (temp_v0_3 < arg0->y) {
            arg0->y = temp_v0_3;
            func_8003BE38((s32) arg0);
        }
        break;
    }
}
