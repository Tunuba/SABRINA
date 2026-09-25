#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s32 D_8006C450;
extern s32 D_8006C458;
extern u8 D_8007CB88;


void func_80032F90(s32 arg0, s32 arg1) {
    s16 var_s0_2;
    s32 temp_s4;
    s32 var_s0;
    s32 var_s2;
    void *temp_s3;

    temp_s3 = arg0 + 0x74;
    var_s2 = 0;
    var_s0 = 0;
    if (D_8007CB88 != 1) {
        if (arg1 & 0x1000) {
            var_s0 = 0x1000;
        }
        if (arg1 & 0x4000) {
            var_s0 = -0x1000;
        }
        if (arg1 & 0x8000) {
            var_s2 = -0x1000;
        }
        if (arg1 & 0x2000) {
            var_s2 = 0x1000;
        }
        if ((var_s2 | var_s0) != 0) {
            temp_s4 = func_8001BE8C(0, 0, D_8006C450, D_8006C458);
            var_s0_2 = temp_s4 + func_8001BE8C(0, 0, var_s2, var_s0);
            if (var_s0_2 >= 0x1000) {
                var_s0_2 -= 0x1000;
            }
            if (var_s0_2 < -0xFFF) {
                var_s0_2 += 0x1000;
            }
            M2C_FIELD(temp_s3, s16 *, 0x16) = var_s0_2;
            if (func_80014AEC(M2C_FIELD(arg0, s16 *, 0x32) - var_s0_2) >= 0x258) {
                func_80021D44(arg0 + 0x32, (s32) var_s0_2, 0xDC);
                return;
            }
            func_80021D44(arg0 + 0x32, (s32) var_s0_2, 0x50);
            M2C_FIELD(arg0, s32 *, 0x38) = (s32) (M2C_FIELD(arg0, s32 *, 0x38) + func_8001C304(rsin((s32) M2C_FIELD(arg0, s16 *, 0x32)) * 0x10, (s32) M2C_FIELD(temp_s3, s32 *, 4) >> 2));
            M2C_FIELD(arg0, s32 *, 0x40) = (s32) (M2C_FIELD(arg0, s32 *, 0x40) + func_8001C304(rcos((s32) M2C_FIELD(arg0, s16 *, 0x32)) * 0x10, (s32) M2C_FIELD(temp_s3, s32 *, 4) >> 2));
            return;
        }
        func_80021D44(arg0 + 0x32, (s32) M2C_FIELD(temp_s3, s16 *, 0x16), 0x50);
    }
}
