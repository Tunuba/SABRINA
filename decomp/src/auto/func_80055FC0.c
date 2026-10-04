#include "objeto.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s8 D_800C855F;
extern s8 nivel_actual;


void func_80055FC0(void *arg0) {
    s16 var_s0;
    s32 temp_s3;
    s32 temp_v0;
    s32 var_s2;

    M2C_FIELD(arg0, s32 *, 0x38) = (s32) ((s32) (p_sabrina->x - M2C_FIELD(arg0, s32 *, 0x24)) >> 3);
    M2C_FIELD(arg0, s32 *, 0x40) = (s32) ((s32) (p_sabrina->z - M2C_FIELD(arg0, s32 *, 0x2C)) >> 3);
    M2C_FIELD(arg0, s32 *, 0x3C) = (s32) ((s32) (((p_sabrina->y - 0x4001) - 0x7FFF) - M2C_FIELD(arg0, s32 *, 0x28)) >> 3);
    M2C_FIELD(arg0, s32 *, 0x38) = (s32) (((s32) (((s32) M2C_FIELD(arg0, s32 *, 0x38) >> 8) * 0x2E6) >> 8) << 8);
    M2C_FIELD(arg0, s32 *, 0x3C) = (s32) (((s32) (((s32) M2C_FIELD(arg0, s32 *, 0x3C) >> 8) * 0x2E6) >> 8) << 8);
    M2C_FIELD(arg0, s32 *, 0x40) = (s32) (((s32) (((s32) M2C_FIELD(arg0, s32 *, 0x40) >> 8) * 0x2E6) >> 8) << 8);
    M2C_FIELD(arg0, s32 *, 0x24) = (s32) (M2C_FIELD(arg0, s32 *, 0x24) + M2C_FIELD(arg0, s32 *, 0x38));
    M2C_FIELD(arg0, s32 *, 0x28) = (s32) (M2C_FIELD(arg0, s32 *, 0x28) + M2C_FIELD(arg0, s32 *, 0x3C));
    M2C_FIELD(arg0, s32 *, 0x2C) = (s32) (M2C_FIELD(arg0, s32 *, 0x2C) + M2C_FIELD(arg0, s32 *, 0x40));
    if (func_8001C004(0, 0, 0, p_sabrina->x - M2C_FIELD(arg0, s32 *, 0x24), /* extra? */ 0, /* extra? */ (p_sabrina->z - M2C_FIELD(arg0, s32 *, 0x2C))) < 0x4CCC) {
        var_s2 = 0;
loop_6:
        if (var_s2 < 0x1000) {
            var_s0 = 0;
loop_4:
            if (var_s0 < 0x1000) {
                temp_s3 = (s32) (rsin(var_s2) * 0xCCC) >> 0xC;
                CrearParticula(0xE, 0, (s32) var_s0, M2C_FIELD(arg0, s32 *, 0x24), /* extra? */ M2C_FIELD(arg0, s32 *, 0x28), /* extra? */ M2C_FIELD(arg0, s32 *, 0x2C), /* extra? */ 0, /* extra? */ temp_s3, /* extra? */ ((s32) (rcos(var_s2) * 0xCCC) >> 0xC), /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0xF, /* extra? */ 0x202, /* extra? */ 0);
                var_s0 += 0x3E8;
                goto loop_4;
            }
            var_s2 += 0x384;
            goto loop_6;
        }
        M2C_FIELD(arg0, u8 *, 0x20) = (u8) (M2C_FIELD(arg0, u8 *, 0x20) | 0x80);
        D_800C855F += 1;
        temp_v0 = M2C_FIELD(arg0, s32 *, 0x74);
        switch (temp_v0) {                          /* irregular */
        case 2:
            func_80030F18(8);
            break;
        case 1:
            func_80030F18(4);
            break;
        case 3:
            func_80030F18(0xA);
            break;
        case 4:
            func_80030F18(6);
            break;
        }
        func_80056290((s32) nivel_actual);
    }
}
