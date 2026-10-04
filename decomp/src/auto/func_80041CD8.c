#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u8 D_800754F8[];
extern u8 D_80075504[];


void func_80041CD8(s32 arg0) {
    s32 var_s1;
    s32 var_s2;
    s32 var_v0;
    u8 *temp_a1;

    var_v0 = 0x3E6;
    do {
        var_v0 -= 1;
    } while (var_v0 >= 0);
    var_s2 = -0x0DFFFFFE;
    var_s1 = 0x44E8;
    D_80075504[2] = 6;
    M2C_FIELD(D_80075504, u8 *, 0) = 0;
    D_80075504[1] = 0;
    M2C_FIELD(D_80075504, s32 *, -4) = 0;
    switch (M2C_FIELD(D_80075504, s32 *, -0x10)) {  /* irregular */
    case 0:
        D_80075504[2] = 0x7F;
        return;
    case 5:
        D_80075504[2] = 0;
        if (arg0 == 0) {
            M2C_FIELD(D_80075504, u8 *, 0) = 1;
        } else {
            var_s2 = -0x0DFFFFFD;
            var_s1 = 1;
        }
    case 2:
block_18:
        if ((s8) M2C_FIELD(D_80075504, u8 *, 0) != 0) {
            func_800143E4();
            func_800169A0(M2C_FIELD(D_80075504, s32 *, -8));
        } else {
            func_800143E4();
            func_80014598(var_s2);
            func_800144C4(var_s2, var_s1 & 0xFFFF, 0x1000);
            if ((s8) D_80075504[2] == 0) {
                M2C_FIELD(D_80075504, s32 *, -4) = func_80016940();
            } else if ((s8) D_80075504[1] == 0) {

            }
            func_80016940();
        }
        func_800143F4();
        return;
    case 3:
        var_s1 = 0x89D0;
        goto block_18;
    default:
        if (M2C_FIELD(D_800754F8, s32 *, 0) == 0) {
            temp_a1 = D_800754F8 - 4;
            if (M2C_FIELD(D_800754F8, s32 *, -4) < 0x46) {
                M2C_FIELD(temp_a1, u8 *, 0x11) = (u8) (M2C_FIELD(temp_a1, u8 *, 0x11) + 1);
                var_s1 = 0x204CC0 / (s32) M2C_FIELD(D_800754F8, s32 *, -4);
            } else {
                var_s1 = 0x409980 / (s32) M2C_FIELD(D_800754F8, s32 *, -4);
            }
            goto block_18;
        }
        break;
    }
}
