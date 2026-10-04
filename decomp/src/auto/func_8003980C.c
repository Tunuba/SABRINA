#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"



void func_8003980C(void *arg0) {
    s32 temp_s0_2;
    s32 temp_s2;
    s32 temp_s3;
    s32 temp_s5;
    s32 temp_v1;
    s32 var_s1;
    void *temp_s0;
    void *temp_s6;
    void *temp_v0;

    temp_s6 = arg0 + 0x74;
    temp_s0 = M2C_FIELD(temp_s6, void **, 0xC);
    temp_s3 = func_80021C3C();
    if (temp_s0 == NULL) {
        M2C_FIELD(arg0, u8 *, 0x20) = (u8) (M2C_FIELD(arg0, u8 *, 0x20) | 0x80);
        return;
    }
    temp_v1 = M2C_FIELD(temp_s6, s32 *, 4);
    M2C_FIELD(temp_s6, s32 *, 4) = (s32) (temp_v1 - 1);
    if (temp_v1 < 0) {
        M2C_FIELD(temp_s6, M2C_UNK (**)(void *, void *), 0x10)(arg0, temp_s0);
        if (M2C_FIELD(arg0, u8 *, 0x20) & 0x80) {
            M2C_FIELD(temp_s6, M2C_UNK (**)(void *, void *), 0x10) = NULL;
        }
    } else {
        M2C_FIELD(arg0, s32 *, 0x24) = (s32) M2C_FIELD(temp_s0, s32 *, 0x24);
        M2C_FIELD(arg0, s32 *, 0x28) = (s32) M2C_FIELD(temp_s0, s32 *, 0x28);
        M2C_FIELD(arg0, s32 *, 0x2C) = (s32) M2C_FIELD(temp_s0, s32 *, 0x2C);
        var_s1 = (s32) (M2C_FIELD(temp_s6, s32 *, 4) * 8) / (s32) M2C_FIELD(temp_s6, s32 *, 8);
loop_7:
        if (var_s1 >= 0) {
            temp_s0_2 = func_80021CE4(0x1000);
            temp_s5 = func_80021CE4(0x1000);
            temp_s2 = (s32) (temp_s3 * rsin(temp_s0_2)) >> 0xC;
            temp_v0 = CrearParticula((s32) M2C_FIELD(temp_s6, s8 *, 1), (s32) arg0, (s32) (s16) temp_s5, 0, /* extra? */ temp_s2, /* extra? */ ((s32) (temp_s3 * rcos(temp_s0_2)) >> 0xC), /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0xF, /* extra? */ 0x202, /* extra? */ 0);
            var_s1 -= 1;
            M2C_FIELD(temp_v0, s32 *, 0x24) = (s32) (M2C_FIELD(temp_v0, s32 *, 0x24) * 2);
            goto loop_7;
        }
    }
}
