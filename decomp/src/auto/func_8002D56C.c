#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u8 D_80061774[];
extern u8 * D_8006D5D0;
extern s32 * D_8006D5E4;
extern void * D_8006D5E8;


void func_8002D56C(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5_reg) {
    u8 arg5 = (u8) arg5_reg;
    s32 temp_a1;
    s32 temp_v0;
    s32 var_a0;
    s8 var_v0;
    void *temp_a1_2;

    var_a0 = 0;
    temp_a1 = arg0 * 0x10;
    if (M2C_FIELD((temp_a1 + 0x1F800000), s32 *, 0x1088) & 0x01000000) {
loop_1:
        if (var_a0 != 0x10000) {
            var_a0 += 1;
            if (!(M2C_FIELD((temp_a1 + 0x1F800000), s32 *, 0x1088) & 0x01000000)) {

            } else {
                goto loop_1;
            }
        } else {
            printf((s32) D_80061774, M2C_FIELD((temp_a1 + 0x1F800000), s32 *, 0x1088), 0x10000);
        }
    }
    if (arg5 == 1) {
        var_v0 = M2C_FIELD(D_8006D5E8, u8 *, 2) | (1 << arg0);
    } else {
        var_v0 = M2C_FIELD(D_8006D5E8, u8 *, 2) & ~(1 << arg0);
    }
    M2C_FIELD(D_8006D5E8, s8 *, 2) = var_v0;
    temp_v0 = arg0 * 0x10;
    temp_a1_2 = temp_v0 + 0x1F801080;
    *D_8006D5E4 |= 1 << ((arg0 * 4) + 3);
    *(0x1F801080 + temp_v0) = arg1;
    M2C_FIELD(temp_a1_2, s32 *, 4) = (s32) ((arg2 << 0x10) | arg3);
    if (!(*D_8006D5D0 & 0x40)) {
        do {

        } while (!(*D_8006D5D0 & 0x40));
    }
    M2C_FIELD((temp_a1_2 + 4), s32 *, 4) = arg4;
}
