#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s32 D_800C76B4;
extern u8 D_800C76CC[];
extern u16 D_800C76DE;
extern s16 D_800C76E0;
extern u8 D_800C7704[];
extern u8 D_800C7744[];
extern u8 D_800C7784[];
extern u8 D_800C77C4[];
extern u8 D_800C7804[];

s32 func_800447E4(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 sp10;
    s16 var_v0;
    s16 var_v0_3;
    s32 *var_a2_2;
    s32 *var_a2_3;
    s32 temp_a3_2;
    s32 temp_s0;
    s32 temp_v0;
    s32 temp_v1_2;
    s32 temp_v1_3;
    s32 var_a1;
    s32 var_a1_2;
    s32 var_a1_3;
    s32 var_a1_4;
    s32 var_a2;
    s32 var_s0;
    s32 var_s0_2;
    s32 var_s0_3;
    s32 var_s2;
    s32 var_v0_2;
    s32 var_v0_4;
    u16 *var_a3;
    u16 temp_v1;
    u32 temp_a1;
    u8 temp_s4;
    void *temp_a3;
    void *var_v1;

    var_s2 = 0x10;
    var_v0 = -1;
    if (func_8003FD90() != 1) {
        func_8003FD68(1);
        if ((s16) arg1 < 0x10) {
            var_a1 = 0;
            if ((s16) arg1 == -1) {
loop_3:
                if (D_800C76CC[var_a1] != 0) {
                    var_a1 += 1;
                    if (var_a1 >= 0x10) {
                        var_a2 = 0x10;
                    } else {
                        goto loop_3;
                    }
                } else {
                    D_800C76CC[var_a1] = 1;
                    var_s2 = var_a1;
                    goto block_9;
                }
            } else {
                var_v0_2 = 0x10 << 0x10;
                if (D_800C76CC[(s16) arg1] == 0) {
                    D_800C76CC[(s16) arg1] = 1;
                    var_s2 = arg1;
block_9:
                    D_800C76DE += 1;
                    var_v0_2 = var_s2 << 0x10;
                }
                var_a2 = var_v0_2 >> 0x10;
            }
            if (var_a2 >= 0x10) {
                goto block_12;
            }
            *(D_800C7704 + (var_a2 * 4)) = arg0;
            temp_a1 = M2C_FIELD(arg0, u32 *, 0);
            D_800C76B4 = 0;
            temp_a3 = arg0 + 0x20;
            if ((temp_a1 >> 8) != 0x564142) {
                D_800C76CC[var_a2] = 0;
                goto block_34;
            }
            var_v0_3 = 0x40;
            if ((temp_a1 & 0xFF) == 0x70) {
                var_v0_3 = 0x40;
                if (M2C_FIELD(arg0, s32 *, 4) >= 5) {
                    var_v0_3 = 0x80;
                }
            }
            D_800C76E0 = var_v0_3;
            if (D_800C76E0 < (s32) M2C_FIELD(arg0, u16 *, 0x12)) {
                D_800C76CC[(s16) var_s2] = 0;
                goto block_34;
            }
            D_800C7744[(s32) (var_s2 << 0x10) >> 0xE] = temp_a3;
            temp_a3_2 = temp_a3 + (D_800C76E0 * 0x10);
            var_a1_2 = 0;
            var_s0 = 0;
            if (D_800C76E0 > 0) {
                var_v1 = temp_a3;
                do {
                    M2C_FIELD(var_v1, s32 *, 8) = var_s0;
                    if (M2C_FIELD(var_v1, u8 *, 0) != 0) {
                        var_s0 += 1;
                    }
                    var_a1_2 += 1;
                    var_v1 += 0x10;
                } while (var_a1_2 < D_800C76E0);
            }
            var_s0_2 = 0;
            var_a1_3 = 0;
            var_a2_2 = &sp10;
            D_800C7784[(s32) (var_s2 << 0x10) >> 0xE] = temp_a3_2;
            temp_s4 = M2C_FIELD(arg0, u8 *, 0x16);
            var_a3 = temp_a3_2 + (M2C_FIELD(arg0, u16 *, 0x12) << 9);
            do {
                if ((temp_s4 & 0xFF) >= var_a1_3) {
                    temp_v1 = *var_a3;
                    var_v0_4 = temp_v1 * 4;
                    if (M2C_FIELD(arg0, s32 *, 4) >= 5) {
                        var_v0_4 = temp_v1 * 8;
                    }
                    *var_a2_2 = var_v0_4;
                    var_s0_2 += *var_a2_2;
                }
                var_a3 += 2;
                var_a1_3 += 1;
                var_a2_2 += 4;
            } while (var_a1_3 < 0x100);
            temp_s0 = (var_s0_2 + 0x3F) & ~0x3F;
            temp_v0 = ((s32 (*)(s32, s32, s16, u16 *)) arg2)(temp_s0, arg3, (s16) var_s2, var_a3);
            var_v0 = -1;
            if (temp_v0 != -1) {
                if ((u32) (temp_v0 + temp_s0) > 0x80000U) {
                    D_800C76CC[(s16) var_s2] = 0;
block_34:
                    func_8003FD68(0);
                    D_800C76DE -= 1;
                    return -1;
                }
                *(D_800C77C4 + ((s16) var_s2 * 4)) = temp_v0;
                var_s0_3 = 0;
                temp_v1_2 = temp_s4 & 0xFF;
                var_a1_4 = 0;
                if (temp_v1_2 >= 0) {
                    var_a2_3 = &sp10;
                    do {
                        var_s0_3 += *var_a2_3;
                        temp_v1_3 = var_a1_4 / 2;
                        if (!(var_a1_4 & 1)) {
                            M2C_FIELD(((temp_v1_3 * 0x10) + temp_a3), s16 *, 0xC) = (s16) ((u32) (temp_v0 + var_s0_3) >> 3);
                        } else {
                            M2C_FIELD(((((s32) (var_a1_4 + temp_v1_3) >> 1) * 0x10) + temp_a3), s16 *, 0xE) = (s16) ((u32) (temp_v0 + var_s0_3) >> 3);
                        }
                        var_a1_4 += 1;
                        var_a2_3 += 4;
                    } while (temp_v1_2 >= var_a1_4);
                }
                var_v0 = (s16) var_s2;
                *(D_800C7804 + (var_v0 * 4)) = var_s0_3;
                D_800C76CC[var_v0] = 2;
                /* Duplicate return node #42. Try simplifying control flow for better match */
                return (s32) var_v0;
            }
            /* Duplicate return node #42. Try simplifying control flow for better match */
            return (s32) var_v0;
        }
block_12:
        func_8003FD68(0);
        return -1;
    }
    return (s32) var_v0;
}
