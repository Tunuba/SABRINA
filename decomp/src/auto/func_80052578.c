#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u8 D_800D53D0[];
extern u8 D_800D53D4[];
extern u8 D_800D53D8[];
extern u8 D_800D55B0[];
extern u8 D_800D5600[];

s32 func_80052578(s32 arg0) {
    s32 temp_s0;
    s32 temp_s0_2;
    s32 var_s2;
    s32 var_s2_2;
    s32 var_v0;
    u8 *var_s0;

    var_s2 = 0;
loop_1:
    bzero((s32) D_800D5600, 0x80);
    temp_s0 = var_s2 << 5;
    bzero((s32) (temp_s0 + D_800D53D0), 0x20);
    *(D_800D53D0 + temp_s0) = 0xA0;
    *(D_800D53D4 + temp_s0) = 0;
    *(D_800D53D8 + temp_s0) = 0xFFFF;
    M2C_FIELD(D_800D5600, M2C_UNK *, 3) = M2C_UNALIGNED32(M2C_ERROR(/* Unable to handle lwr; missing a corresponding lwl */));
    M2C_FIELD(D_800D5600, M2C_UNK *, 7) = M2C_UNALIGNED32(M2C_ERROR(/* Unable to handle lwr; missing a corresponding lwl */));
    M2C_FIELD(D_800D5600, M2C_UNK *, 0xB) = M2C_UNALIGNED32(M2C_ERROR(/* Unable to handle lwr; missing a corresponding lwl */));
    M2C_FIELD(D_800D5600, M2C_UNK *, 0xF) = M2C_UNALIGNED32(M2C_ERROR(/* Unable to handle lwr; missing a corresponding lwl */));
    M2C_FIELD(D_800D5600, M2C_UNK *, 0x13) = M2C_UNALIGNED32(M2C_ERROR(/* Unable to handle lwr; missing a corresponding lwl */));
    M2C_FIELD(D_800D5600, M2C_UNK *, 0x17) = M2C_UNALIGNED32(M2C_ERROR(/* Unable to handle lwr; missing a corresponding lwl */));
    M2C_FIELD(D_800D5600, M2C_UNK *, 0x1B) = M2C_UNALIGNED32(M2C_ERROR(/* Unable to handle lwr; missing a corresponding lwl */));
    M2C_FIELD(D_800D5600, M2C_UNK *, 0x1F) = M2C_UNALIGNED32(M2C_ERROR(/* Unable to handle lwr; missing a corresponding lwl */));
    temp_s0_2 = var_s2 + 1;
    var_v0 = 0;
    if (func_80052434(arg0, temp_s0_2, (s32) D_800D5600) == 1) {
        var_s2 = temp_s0_2;
        if (var_s2 >= 0xF) {
            var_s2_2 = 0;
            var_s0 = D_800D55B0;
loop_4:
            M2C_FIELD(var_s0, s32 *, 0) = -1;
            bzero((s32) D_800D5600, 0x80);
            M2C_FIELD(D_800D5600, M2C_UNK *, 3) = M2C_UNALIGNED32(M2C_ERROR(/* Unable to handle lwr; missing a corresponding lwl */));
            var_s2_2 += 1;
            if (func_80052434(arg0, var_s2_2 + 0x10, (s32) D_800D5600) != 1) {
                return 0;
            }
            var_s0 += 4;
            if (var_s2_2 >= 0x14) {
                bzero((s32) D_800D5600, 0x80);
                M2C_FIELD(D_800D5600, u8 *, 0) = 0x4D;
                M2C_FIELD(D_800D5600, s8 *, 1) = 0x43;
                var_v0 = func_80052434(arg0, 0, (s32) D_800D5600) == 1;
                /* Duplicate return node #8. Try simplifying control flow for better match */
                return var_v0;
            }
            goto loop_4;
        }
        goto loop_1;
    }
    return var_v0;
}
