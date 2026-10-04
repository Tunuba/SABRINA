#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"




void func_80056584(void *arg0) {
    s16 temp_v0;
    s16 var_s0;
    s32 temp_s0;
    s32 temp_s2;
    s32 temp_s2_2;
    s32 temp_v0_2;
    s32 temp_v1;
    s32 var_s1;
    void *temp_s4;

    temp_s4 = arg0 + 0x74;
    M2C_FIELD(M2C_FIELD(temp_s4, void **, 0xC), s16 *, 0x40) = 0x64;
    temp_v0 = M2C_FIELD(arg0, s16 *, 0x70);
    if (temp_v0 != 2) {
        if (temp_v0 != 1) {
            if (temp_v0 == 0) {
                if ((p_sabrina != NULL) && (func_8002225C((s32) arg0, p_sabrina->x, p_sabrina->y, p_sabrina->z) < 0x140000)) {
                    M2C_FIELD(arg0, s16 *, 0x70) = 1;
                }
            } else {
                goto block_20;
            }
        } else {
            M2C_FIELD(arg0, s16 *, 0x32) = (s16) (M2C_FIELD(arg0, s16 *, 0x32) + 0x28);
            M2C_FIELD(arg0, s32 *, 0x28) = (s32) (M2C_FIELD(temp_s4, s32 *, 8) + (rsin(M2C_FIELD(arg0, s16 *, 0x32) * 4) * 4));
            M2C_FIELD(M2C_FIELD(temp_s4, void **, 0xC), s32 *, 8) = (s32) M2C_FIELD(arg0, s32 *, 0x28);
            if (p_sabrina != NULL) {
                temp_v0_2 = func_8002225C((s32) arg0, p_sabrina->x, p_sabrina->y, p_sabrina->z);
                if (temp_v0_2 >= 0x140001) {
block_20:
                    M2C_FIELD(arg0, s16 *, 0x70) = 0;
                } else if (temp_v0_2 < 0x20000) {
                    M2C_FIELD(arg0, s16 *, 0x70) = 2;
                }
            }
        }
    } else {
        M2C_FIELD(arg0, s32 *, 0x38) = (s32) ((s32) (p_sabrina->x - M2C_FIELD(arg0, s32 *, 0x24)) >> 3);
        M2C_FIELD(arg0, s32 *, 0x40) = (s32) ((s32) (p_sabrina->z - M2C_FIELD(arg0, s32 *, 0x2C)) >> 3);
        M2C_FIELD(arg0, s32 *, 0x3C) = (s32) ((s32) (((p_sabrina->y - 0x4001) - 0x7FFF) - M2C_FIELD(arg0, s32 *, 0x28)) >> 3);
        M2C_FIELD(arg0, s32 *, 0x38) = (s32) (((s32) (((s32) M2C_FIELD(arg0, s32 *, 0x38) >> 8) * 0x2E6) >> 8) << 8);
        M2C_FIELD(arg0, s32 *, 0x3C) = (s32) (((s32) (((s32) M2C_FIELD(arg0, s32 *, 0x3C) >> 8) * 0x2E6) >> 8) << 8);
        M2C_FIELD(arg0, s32 *, 0x40) = (s32) (((s32) (((s32) M2C_FIELD(arg0, s32 *, 0x40) >> 8) * 0x2E6) >> 8) << 8);
        M2C_FIELD(arg0, s32 *, 0x24) = (s32) (M2C_FIELD(arg0, s32 *, 0x24) + M2C_FIELD(arg0, s32 *, 0x38));
        M2C_FIELD(arg0, s32 *, 0x28) = (s32) (M2C_FIELD(arg0, s32 *, 0x28) + M2C_FIELD(arg0, s32 *, 0x3C));
        M2C_FIELD(arg0, s32 *, 0x2C) = (s32) (M2C_FIELD(arg0, s32 *, 0x2C) + M2C_FIELD(arg0, s32 *, 0x40));
        M2C_FIELD(M2C_FIELD(temp_s4, void **, 0xC), s32 *, 4) = (s32) M2C_FIELD(arg0, s32 *, 0x24);
        M2C_FIELD(M2C_FIELD(temp_s4, void **, 0xC), s32 *, 8) = (s32) M2C_FIELD(arg0, s32 *, 0x28);
        M2C_FIELD(M2C_FIELD(temp_s4, void **, 0xC), s32 *, 0xC) = (s32) M2C_FIELD(arg0, s32 *, 0x2C);
        temp_v1 = M2C_FIELD(arg0, s32 *, 0x54);
        M2C_FIELD(arg0, s32 *, 0x54) = (s32) (temp_v1 - (temp_v1 >> 4));
        M2C_FIELD(arg0, s32 *, 0x58) = (s32) M2C_FIELD(arg0, s32 *, 0x54);
        M2C_FIELD(arg0, s32 *, 0x5C) = (s32) M2C_FIELD(arg0, s32 *, 0x54);
        temp_s0 = ((func_80014F10() & 0x3F) - 0x20) << 8;
        temp_s2 = ((func_80014F10() & 0x3F) - 0x20) << 8;
        CrearParticula((s32) M2C_FIELD(temp_s4, s8 *, 4), (s32) arg0, 0, temp_s0, /* extra? */ temp_s2, /* extra? */ (((func_80014F10() & 0x3F) - 0x20) << 8), /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 7, /* extra? */ 2, /* extra? */ 0);
        M2C_FIELD(arg0, s16 *, 0x30) = (s16) (M2C_FIELD(arg0, s16 *, 0x30) + 0xF);
        M2C_FIELD(arg0, s16 *, 0x32) = (s16) (M2C_FIELD(arg0, s16 *, 0x32) + 0x17);
        if ((p_sabrina != NULL) && (func_8002225C((s32) arg0, p_sabrina->x, (p_sabrina->y - 0x4001) - 0x7FFF, p_sabrina->z) < 0x6666)) {
            M2C_FIELD(M2C_FIELD(temp_s4, void **, 0xC), s16 *, 0x40) = 1;
            TocarSonido(0x1E, 0, 0x2A, 0x7F);
            func_8004C730(M2C_FIELD(arg0, s32 *, 0x74));
            var_s1 = 0;
loop_18:
            if (var_s1 < 0x1000) {
                var_s0 = 0;
loop_16:
                if (var_s0 < 0x1000) {
                    temp_s2_2 = (s32) (rsin(var_s1) * 0xCCC) >> 0xC;
                    CrearParticula((s32) M2C_FIELD(temp_s4, s8 *, 4), (s32) arg0, (s32) var_s0, 0, /* extra? */ 0, /* extra? */ 0x28F, /* extra? */ 0, /* extra? */ temp_s2_2, /* extra? */ ((s32) (rcos(var_s1) * 0xCCC) >> 0xC), /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0xF, /* extra? */ 0x202, /* extra? */ 0);
                    var_s0 += 0x3E8;
                    goto loop_16;
                }
                var_s1 += 0x320;
                goto loop_18;
            }
            M2C_FIELD(arg0, u8 *, 0x20) = (u8) (M2C_FIELD(arg0, u8 *, 0x20) | 0x80);
        }
    }
}
