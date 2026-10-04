#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u8 D_800D52D4[];
extern u8 D_800621BC[];
extern u8 D_800622E0[];
extern u8 D_80062304[];
extern u8 D_80062330[];
extern s32 func_800502DC();


s32 func_80050C84(s32 arg0, s32 arg1, s32 arg2) {
    u8 *temp_v1;
    u8 *var_a0;

    if (M2C_FIELD(D_800D52D4, s32 *, 0) < 0) {
        var_a0 = D_800622E0;
        goto block_9;
    }
    temp_v1 = D_800D52D4 - 0x14;
    if (M2C_FIELD(D_800D52D4, s32 *, -0x14) > 0) {
        var_a0 = D_800621BC;
        goto block_9;
    }
    if (arg2 & 0x7F) {
        var_a0 = D_80062304;
        goto block_9;
    }
    if (!(arg1 & 0x7F)) {
        M2C_FIELD(D_800D52D4, s32 *, -0x14) = 5;
        M2C_FIELD(temp_v1, s32 *, 4) = 0;
        M2C_FIELD(temp_v1, s32 *, 8) = 0;
        M2C_FIELD(temp_v1, s32 *, 0x18) = arg1;
        M2C_FIELD(temp_v1, s32 *, 0x20) = arg0;
        M2C_FIELD(temp_v1, s32 *, 0x1C) = arg2;
        UserFuncOpen((s32) func_800502DC);
        return 1;
    }
    var_a0 = D_80062330;
block_9:
    printf((s32) var_a0, D_800D52D4);
    return 0;
}
