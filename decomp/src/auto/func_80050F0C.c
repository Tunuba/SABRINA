#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u8 D_800D52C0[];
extern u8 D_800622B8[];
extern u8 D_80062304[];
extern u8 D_80062330[];
extern u8 D_80062360[];
extern s32 func_80050694();


s32 func_80050F0C(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    u8 *temp_s0;
    u8 *var_a0;

    if (M2C_FIELD(D_800D52C0, s32 *, 0) > 0) {
        var_a0 = D_80062360;
        goto block_9;
    }
    if (M2C_FIELD(D_800D52C0, s32 *, 0x14) >= 0) {
        var_a0 = D_800622B8;
        goto block_9;
    }
    if (arg4 & 0x7F) {
        var_a0 = D_80062304;
        goto block_9;
    }
    if (!(arg3 & 0x7F)) {
        temp_s0 = D_800D52C0 + 0x24;
        func_800508D4(arg0, (s32) temp_s0);
        strcat((s32) temp_s0, arg1);
        M2C_FIELD(D_800D52C0, s32 *, 0) = 4;
        M2C_FIELD(D_800D52C0, s32 *, 4) = 0;
        M2C_FIELD(D_800D52C0, s32 *, 8) = 0;
        M2C_FIELD(D_800D52C0, s32 *, 0x18) = arg3;
        M2C_FIELD(D_800D52C0, s32 *, 0x20) = arg2;
        M2C_FIELD(D_800D52C0, s32 *, 0x1C) = arg4;
        M2C_FIELD(D_800D52C0, s32 *, 0x10) = arg0;
        UserFuncOpen((s32) func_80050694);
        return 1;
    }
    var_a0 = D_80062330;
block_9:
    printf((s32) var_a0);
    return 0;
}
