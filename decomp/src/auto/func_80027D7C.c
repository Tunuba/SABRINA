#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"



void func_80027D7C(void *arg0) {
    s32 var_v0;
    s8 *var_v1;

    if (M2C_FIELD(arg0, u8 *, 0x49) != 0) {
        var_v1 = arg0 + 0x5D;
        var_v0 = 5;
        M2C_FIELD(arg0, u8 *, 0x49) = 0U;
        M2C_FIELD(arg0, s8 *, 0x46) = 0;
        M2C_FIELD(arg0, s16 *, 0xE6) = 0;
        M2C_FIELD(arg0, s32 *, 0x14) = 0;
        M2C_FIELD(arg0, s32 *, 0x18) = 0;
        M2C_FIELD(arg0, s8 *, 0xE3) = 0;
        M2C_FIELD(arg0, s8 *, 0xE4) = 0;
        M2C_FIELD(arg0, s16 *, 0xE6) = 0;
        M2C_FIELD(arg0, s8 *, 0xE9) = 0;
        M2C_FIELD(arg0, s8 *, 0xEA) = 0;
        M2C_FIELD(arg0, s32 *, 0) = 0;
        M2C_FIELD(arg0, s32 *, 4) = 0;
        M2C_FIELD(arg0, s32 *, 8) = 0;
        M2C_FIELD(arg0, s8 *, 0x37) = 0;
        M2C_FIELD(arg0, s8 *, 0x38) = 0;
        M2C_FIELD(arg0, s8 *, 0x39) = 0;
        do {
            *var_v1 = 0xFF;
            var_v0 -= 1;
            var_v1 += 1;
        } while (var_v0 >= 0);
    }
}
