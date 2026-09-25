#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s32 D_8006CFCC;


void func_8002805C(void *arg0) {
    s32 temp_v1;
    s32 var_a2;
    s32 var_a3;
    s32 var_t0;
    s32 var_t2;
    s32 var_v1;
    s32 var_v1_2;
    s32 var_v1_3;
    s8 *var_a0_2;
    u8 *temp_a0;
    u8 *var_a0;
    u8 *var_a1;
    u8 *var_a1_2;
    u8 temp_v1_2;
    u8 var_t1;
    void *var_a0_3;

    bzero(arg0 + 0x57, 6);
    if ((M2C_FIELD(arg0, u16 *, 0xE6) != 0) && (M2C_FIELD(arg0, u8 **, 0x28) != NULL)) {
        var_t1 = 6;
        if ((u8) M2C_FIELD(arg0, u8 *, 0x34) < 7U) {
            var_t1 = M2C_FIELD(arg0, u8 *, 0x34);
        }
        var_t0 = 0;
        if (M2C_FIELD(arg0, u8 *, 0xE9) != 0) {
            var_t2 = 0;
            do {
                var_a2 = 0;
                var_a3 = 1;
                if (M2C_FIELD((var_t2 + M2C_FIELD(arg0, s32 *, 4)), u8 *, 2) != 0) {
                    var_a3 = 0xFF;
                }
                var_a1 = arg0 + 0x5D;
                var_a0 = M2C_FIELD(arg0, u8 **, 0x28);
                var_v1 = 0;
                if (var_t1 != 0) {
loop_9:
                    if ((*var_a1 != var_t0) || !(*var_a0 & var_a3)) {
                        var_a1 += 1;
                        var_v1 += 1;
                        var_a0 += 1;
                        if (var_v1 < (s32) var_t1) {
                            goto loop_9;
                        }
                    } else {
                        var_a2 = 1;
                    }
                }
                if (var_a2 != 0) {
                    temp_v1 = D_8006CFCC + M2C_FIELD((var_t2 + M2C_FIELD(arg0, s32 *, 4)), u8 *, 3);
                    if (temp_v1 < 0x3D) {
                        D_8006CFCC = temp_v1;
                    } else {
                        var_a2 = 0;
                    }
                    if (var_a2 != 0) {
                        var_a1_2 = arg0 + 0x5D;
                        var_a0_2 = arg0 + 0x57;
                        var_v1_2 = 0;
                        if (var_t1 != 0) {
                            do {
                                var_a1_2 += 1;
                                if (*var_a1_2 == var_t0) {
                                    *var_a0_2 = 1;
                                }
                                var_v1_2 += 1;
                                var_a0_2 += 1;
                            } while (var_v1_2 < (s32) var_t1);
                        }
                    }
                }
                var_t0 += 1;
                var_t2 += 5;
            } while (var_t0 < (s32) M2C_FIELD(arg0, u8 *, 0xE9));
        }
    } else {
        temp_v1_2 = M2C_FIELD(arg0, u8 *, 0xE8);
        if ((((u32) (temp_v1_2 - 4) < 2U) || (temp_v1_2 == 7)) && (M2C_FIELD(arg0, u16 *, 0xE6) == 0) && ((u8) M2C_FIELD(arg0, u8 *, 0x34) >= 2U)) {
            temp_a0 = M2C_FIELD(arg0, u8 **, 0x28);
            if (((M2C_FIELD(temp_a0, u8 *, 0) & 0xC0) == 0x40) && (M2C_FIELD(temp_a0, u8 *, 1) & 1) && ((D_8006CFCC + 0xA) < 0x3D)) {
                M2C_FIELD(arg0, s8 *, 0x58) = 1;
                M2C_FIELD(arg0, s8 *, 0x57) = 1;
                D_8006CFCC += 0xA;
            }
        } else {
            if (M2C_FIELD(arg0, u8 *, 0xE8) == 3) {
                M2C_FIELD(arg0, s8 *, 0x57) = 1;
                return;
            }
            if (M2C_FIELD(arg0, u16 *, 0xE6) == 0) {
                var_v1_3 = 5;
                var_a0_3 = arg0 + 5;
                do {
                    M2C_FIELD(var_a0_3, s8 *, 0x57) = 1;
                    var_v1_3 -= 1;
                    var_a0_3 -= 1;
                } while (var_v1_3 >= 0);
            }
        }
    }
}
