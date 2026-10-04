#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u8 D_80086498[];
extern u8 D_80086598[];
extern s32 D_8007CA7C;


void func_8001D5C0(s32 arg0) {
    s32 var_a0;
    s32 var_a1;
    s32 var_a1_2;
    s32 var_a2;
    s32 var_v0;
    s32 var_v1;
    u8 *temp_a1;
    u8 *var_v1_2;

    var_a1 = 4;
    if (arg0 == 0) {
        var_a1 = 0;
        var_v1 = 4;
    } else {
        var_v1 = 8;
    }
    var_v0 = var_a1;
    var_a2 = var_a1 << 6;
loop_10:
    if (var_v0 < var_v1) {
        temp_a1 = &D_80086498[var_a2];
        if (M2C_FIELD(temp_a1, s32 *, 0) != 0) {
            if (M2C_FIELD(temp_a1, u8 *, 0xC) != 0) {
                M2C_FIELD(temp_a1, u8 *, 0xC) = 0U;
                D_8007CA7C -= 0xA;
            }
            if (M2C_FIELD(temp_a1, u8 *, 0xD) != 0) {
                M2C_FIELD(temp_a1, u8 *, 0xD) = 0U;
                D_8007CA7C -= 0x14;
            }
        }
        M2C_FIELD(temp_a1, u8 *, 0x26) = 0x80U;
        M2C_FIELD(temp_a1, u8 *, 0x27) = 0x80U;
        M2C_FIELD(temp_a1, u8 *, 0x28) = 0x80U;
        M2C_FIELD(temp_a1, u8 *, 0x29) = 0x80U;
        var_v0 += 1;
        M2C_FIELD(temp_a1, u8 *, 0x22) = (u8) M2C_FIELD(temp_a1, u8 *, 0x26);
        var_a2 += 0x40;
        M2C_FIELD(temp_a1, u8 *, 0x23) = (u8) M2C_FIELD(temp_a1, u8 *, 0x27);
        M2C_FIELD(temp_a1, u8 *, 0x24) = (u8) M2C_FIELD(temp_a1, u8 *, 0x28);
        M2C_FIELD(temp_a1, u8 *, 0x25) = (u8) M2C_FIELD(temp_a1, u8 *, 0x29);
        M2C_FIELD(temp_a1, u8 *, 0x2A) = (u8) M2C_FIELD(temp_a1, u8 *, 0x26);
        M2C_FIELD(temp_a1, u8 *, 0x2B) = (u8) M2C_FIELD(temp_a1, u8 *, 0x27);
        M2C_FIELD(temp_a1, u8 *, 0x2C) = (u8) M2C_FIELD(temp_a1, u8 *, 0x28);
        M2C_FIELD(temp_a1, u8 *, 0x2D) = (u8) M2C_FIELD(temp_a1, u8 *, 0x29);
        M2C_FIELD(temp_a1, u8 *, 0x2E) = (u8) M2C_FIELD(temp_a1, u8 *, 0x26);
        M2C_FIELD(temp_a1, u8 *, 0x2F) = (u8) M2C_FIELD(temp_a1, u8 *, 0x27);
        M2C_FIELD(temp_a1, u8 *, 0x30) = (u8) M2C_FIELD(temp_a1, u8 *, 0x28);
        M2C_FIELD(temp_a1, u8 *, 0x31) = (u8) M2C_FIELD(temp_a1, u8 *, 0x29);
        goto loop_10;
    }
    if (arg0 == 0) {
        var_v1_2 = D_80086598;
    } else {
        var_v1_2 = D_80086598;
    }
    var_a0 = 4;
    var_a1_2 = 0x14;
loop_16:
    if (var_a0 < 8) {
        M2C_FIELD(var_v1_2, s32 *, 0) = 0;
        M2C_FIELD(var_v1_2, s32 *, 4) = 0;
        M2C_FIELD(var_v1_2, s32 *, 8) = 0;
        M2C_FIELD(var_v1_2, s8 *, 0xC) = 0;
        M2C_FIELD(var_v1_2, s8 *, 0xD) = 0;
        M2C_FIELD(var_v1_2, s32 *, 0x10) = 0;
        M2C_FIELD(var_v1_2, s32 *, 0x14) = 0;
        M2C_FIELD(var_v1_2, s32 *, 0x18) = 6;
        M2C_FIELD(var_v1_2, s32 *, 0x1C) = var_a1_2;
        var_v1_2 += 0x40;
        var_a0 += 1;
        var_a1_2 += 1;
        goto loop_16;
    }
}
