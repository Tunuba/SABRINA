#include "objeto.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"




void func_8005B52C(Objeto *arg0) {
    s32 sp5C;
    s32 sp60;
    s32 sp64;
    s16 temp_v0_2;
    s32 temp_s2;
    s32 temp_s3;
    s32 temp_v0;
    s32 temp_v0_3;
    s32 var_s1;
    s32 var_v0;

    temp_v0 = M2C_FIELD(arg0, s32 *, 0x74);
    if (temp_v0 > 0) {
        M2C_FIELD(arg0, s32 *, 0x74) = (s32) (temp_v0 - 1);
    } else {
        arg0->estado = 2;
    }
    temp_v0_2 = arg0->estado;
    switch (temp_v0_2) {                            /* irregular */
    case 0:
        if (M2C_FIELD(arg0, s32 *, 0x78) == 0) {
            func_80021D44((s32) &arg0->rot[1], (s32) func_8002218C(arg0, p_sabrina->x, p_sabrina->z), 0xC8);
            func_8002205C((s32) &sp5C, 0, (s32) arg0->rot[1]);
            sp5C = ((s32) ((sp5C >> 4) * M2C_FIELD(arg0, s32 *, 0x7C)) >> 8) << 8;
            var_v0 = ((s32) ((sp64 >> 4) * M2C_FIELD(arg0, s32 *, 0x7C)) >> 8) << 8;
        } else {
            func_8002205C((s32) &sp5C, 0, (s32) arg0->rot[1]);
            sp5C = ((s32) ((sp5C >> 4) * M2C_FIELD(arg0, s32 *, 0x7C)) >> 8) << 8;
            var_v0 = ((s32) ((sp64 >> 4) * M2C_FIELD(arg0, s32 *, 0x7C)) >> 8) << 8;
        }
        sp64 = var_v0;
        sp60 = 0;
        arg0->x += sp5C;
        arg0->z += var_v0;
        arg0->y += sp60;
        return;
    case 2:
        arg0->forma.banderas = 0;
        /* fallthrough */
    case 3:
        var_s1 = 0;
loop_16:
        if (var_s1 < 0xD) {
            temp_s3 = func_80021CE4(0x1999) - 0xCCC;
            temp_s2 = func_80021CE4(0x1999) - 0xCCC;
            temp_v0_3 = CrearParticula(0xE, (s32) arg0, 0, 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ temp_s3, /* extra? */ temp_s2, /* extra? */ (func_80021CE4(0x1999) - 0xCCC), /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0xF, /* extra? */ 0, /* extra? */ 0);
            if (temp_v0_3 != 0) {
                M2C_FIELD(temp_v0_3, s32 *, 0x3C) = 0x112;
            }
            var_s1 += 1;
            goto loop_16;
        }
        M2C_FIELD(arg0, u8 *, 0x20) = (u8) (M2C_FIELD(arg0, u8 *, 0x20) | 0x80);
        /* fallthrough */
    case 1:
        return;
    }
}
