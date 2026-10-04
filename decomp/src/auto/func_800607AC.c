#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"



s32 func_800607AC(s32 arg0, s32 arg1, s32 arg2, s32 arg4_reg) {
    u16 arg4 = (u16) arg4_reg;
    s32 sp34;
    s32 sp38;
    s32 sp3C;
    s16 temp_v0;
    s16 temp_v0_2;
    s32 temp_s4;
    s32 var_s4;
    s32 var_v0;
    void *temp_s0;
    void *temp_s3;

    temp_s3 = *arg2;
    var_s4 = M2C_FIELD(arg1, s32 *, 0);
    temp_s0 = M2C_FIELD(arg0, void **, 0x1C);
    sp34 = M2C_FIELD(temp_s3, s32 *, 0) - M2C_FIELD(arg0, s32 *, 0x24);
    sp38 = M2C_FIELD(temp_s3, s32 *, 4) - M2C_FIELD(arg0, s32 *, 0x28);
    sp3C = M2C_FIELD(temp_s3, s32 *, 8) - M2C_FIELD(arg0, s32 *, 0x2C);
    if (func_8001C0D0(sp34, sp38, sp3C) < 0x8000) {
        if (M2C_FIELD(arg1, s8 *, 5) >= 0) {
            var_v0 = func_80060558((s32) *arg2);
        } else {
            var_v0 = func_80060590((s32) *arg2);
        }
        *arg2 = (void *) var_v0;
        if (*arg2 == NULL) {
            return 8;
        }
        goto block_13;
    }
    if (temp_s0 != NULL) {
        if (M2C_FIELD(temp_s0, u8 *, 0x51) == arg4) {
            temp_v0 = M2C_FIELD(temp_s0, s16 *, 0x4E);
            if (temp_v0 < 0x1000) {
                M2C_FIELD(temp_s0, s16 *, 0x4E) = (s16) (temp_v0 + 0x80);
                var_s4 = (s32) (var_s4 * M2C_FIELD(temp_s0, s16 *, 0x4E)) >> 0xC;
            }
        } else {
            M2C_FIELD(temp_s0, u8 *, 0x51) = (u8) arg4;
            M2C_FIELD(temp_s0, s8 *, 0x50) = 0;
            M2C_FIELD(temp_s0, s16 *, 0x4E) = 0;
        }
    }
    temp_v0_2 = func_80021D44(arg0 + 0x32, (s32) func_8002218C(arg0, M2C_FIELD(temp_s3, s32 *, 0), M2C_FIELD(temp_s3, s32 *, 8)), 0x96);
    if (temp_v0_2 < 0x400) {
        func_8001C45C((s32) &sp34);
        temp_s4 = (s32) (var_s4 * (s16) (0x400 - temp_v0_2)) >> 0xA;
        func_80022298(arg0, (s32) M2C_FIELD(arg0, s16 *, 0x32), temp_s4);
        M2C_FIELD(arg0, s32 *, 0x28) = (s32) (M2C_FIELD(arg0, s32 *, 0x28) + (((s32) ((sp38 >> 8) * (temp_s4 >> 4)) >> 8) << 8));
    }
block_13:
    return 0;
}
