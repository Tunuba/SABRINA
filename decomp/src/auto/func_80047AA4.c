#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"




s32 func_80047AA4(s32 arg0) {
    s32 sp5C;
    s32 sp60;
    s32 sp64;
    s16 temp_v0;
    s16 var_s0;
    s32 temp_s0;
    s32 temp_s3;
    s32 temp_s3_2;
    s32 temp_v0_2;
    s32 temp_v1;
    s32 var_s2;
    u32 var_s2_2;

    M2C_FIELD(arg0, s32 *, 0xC) = (s32) (p_sabrina->x - M2C_FIELD(arg0, s32 *, 0));
    M2C_FIELD(arg0, s32 *, 0x14) = (s32) (p_sabrina->z - M2C_FIELD(arg0, s32 *, 8));
    M2C_FIELD(arg0, s32 *, 0x10) = (s32) (((p_sabrina->y - 0x4001) - 0x7FFF) - M2C_FIELD(arg0, s32 *, 4));
    M2C_FIELD(arg0, s32 *, 0xC) = (s32) ((s32) M2C_FIELD(arg0, s32 *, 0xC) >> 1);
    M2C_FIELD(arg0, s32 *, 0x10) = (s32) ((s32) M2C_FIELD(arg0, s32 *, 0x10) >> 1);
    M2C_FIELD(arg0, s32 *, 0x14) = (s32) ((s32) M2C_FIELD(arg0, s32 *, 0x14) >> 1);
    M2C_FIELD(arg0, s32 *, 0) = (s32) (M2C_FIELD(arg0, s32 *, 0) + M2C_FIELD(arg0, s32 *, 0xC));
    M2C_FIELD(arg0, s32 *, 4) = (s32) (M2C_FIELD(arg0, s32 *, 4) + M2C_FIELD(arg0, s32 *, 0x10));
    M2C_FIELD(arg0, s32 *, 8) = (s32) (M2C_FIELD(arg0, s32 *, 8) + M2C_FIELD(arg0, s32 *, 0x14));
    temp_v1 = M2C_FIELD(arg0, s32 *, 0x18);
    M2C_FIELD(arg0, s32 *, 0x18) = (s32) (temp_v1 - (temp_v1 >> 4));
    M2C_FIELD(arg0, s32 *, 0x1C) = (s32) M2C_FIELD(arg0, s32 *, 0x18);
    M2C_FIELD(arg0, s32 *, 0x20) = (s32) M2C_FIELD(arg0, s32 *, 0x18);
    temp_s0 = M2C_FIELD(arg0, s32 *, 0) + (((func_80014F10() & 0x3F) - 0x20) << 8);
    temp_s3 = M2C_FIELD(arg0, s32 *, 4) + (((func_80014F10() & 0x3F) - 0x20) << 8);
    CrearParticula((s32) (s8) M2C_FIELD(arg0, s16 *, 0x26), 0, 0, temp_s0, /* extra? */ temp_s3, /* extra? */ (M2C_FIELD(arg0, s32 *, 8) + (((func_80014F10() & 0x3F) - 0x20) << 8)), /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 7, /* extra? */ 2, /* extra? */ 0);
    M2C_FIELD(arg0, s16 *, 0x28) = (s16) (M2C_FIELD(arg0, s16 *, 0x28) + 0x17);
    sp5C = p_sabrina->x - M2C_FIELD(arg0, s32 *, 0);
    sp60 = 0;
    sp64 = p_sabrina->z - M2C_FIELD(arg0, s32 *, 8);
    var_s2 = func_8001C180((s32) &sp5C);
    if ((u32) var_s2 < 0x40U) {
        temp_v0 = M2C_FIELD(M2C_FIELD(arg0, void **, 0x30), s16 *, 0xC);
        if (temp_v0 != 0x17) {
            if (temp_v0 != 0x13) {
                if (temp_v0 != 0x12) {
                    if (temp_v0 == 4) {
                        func_8004C480((s32) M2C_FIELD(arg0, s16 *, 0x24));
                    } else {
                        TocarSonido(0x28, 0, 0x2A, 0x7F);
                    }
                } else {
                    func_8004C514((s32) M2C_FIELD(arg0, s16 *, 0x24));
                }
            } else {
                func_8004C5A8((s32) M2C_FIELD(arg0, s16 *, 0x24));
            }
        } else {
            func_8004C63C((s32) M2C_FIELD(arg0, s16 *, 0x24));
        }
        var_s2_2 = 0;
loop_17:
        if (var_s2_2 < 0x1000U) {
            var_s0 = 0;
loop_15:
            if (var_s0 < 0x1000) {
                temp_s3_2 = (s32) (rsin((s32) var_s2_2) * 0xCCC) >> 0xC;
                temp_v0_2 = CrearParticula((s32) (s8) M2C_FIELD(arg0, s16 *, 0x26), 0, (s32) var_s0, M2C_FIELD(arg0, s32 *, 0), /* extra? */ M2C_FIELD(arg0, s32 *, 4), /* extra? */ M2C_FIELD(arg0, s32 *, 8), /* extra? */ 0, /* extra? */ temp_s3_2, /* extra? */ ((s32) (rcos((s32) var_s2_2) * 0xCCC) >> 0xC), /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0xF, /* extra? */ 0x202, /* extra? */ 0);
                if (temp_v0_2 != 0) {
                    M2C_FIELD(temp_v0_2, s32 *, 0x3C) = -0x51E;
                }
                var_s0 += 0x3E8;
                goto loop_15;
            }
            var_s2_2 += 0x384;
            goto loop_17;
        }
        M2C_FIELD(arg0, s16 *, 0x2A) = 0x64;
        var_s2 = -1;
        M2C_FIELD(M2C_FIELD(arg0, void **, 0x30), s16 *, 0x1A) = 4;
    }
    return var_s2;
}
