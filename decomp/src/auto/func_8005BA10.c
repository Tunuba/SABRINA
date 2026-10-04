#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u8 D_800C8561[];
extern s8 D_800C8566;

void func_8005BA10(s32 arg0) {
    s32 temp_v0;
    s32 var_s1;
    s32 var_s1_2;
    s32 var_s2;
    s32 var_s3;
    void *temp_s0;
    void *temp_v1;
    void *var_v0;

    temp_s0 = arg0 + 0x74;
    M2C_FIELD(temp_s0, s32 *, 0x34) = 0;
    var_s1 = 0;
    var_s3 = 0;
loop_28:
    if (var_s1 < 5) {
        *(temp_s0 + var_s3) = -1;
        switch (var_s1) {
        case 0:
            if (D_800C8566 != 0) {
                *(temp_s0 + (M2C_FIELD(temp_s0, s32 *, 0x34) * 4)) = 0x15;
                M2C_FIELD((M2C_FIELD(temp_s0, s32 *, 0x34) + temp_s0), s8 *, 0x14) = 1;
                M2C_FIELD(((M2C_FIELD(temp_s0, s32 *, 0x34) * 4) + temp_s0), s32 *, 0x3C) = func_8005B8D4(arg0);
                M2C_FIELD(temp_s0, s32 *, 0x34) = (s32) (M2C_FIELD(temp_s0, s32 *, 0x34) + 1);
            } else {
                *(temp_s0 + (M2C_FIELD(temp_s0, s32 *, 0x34) * 4)) = -1;
                var_v0 = M2C_FIELD(temp_s0, s32 *, 0x34) + temp_s0;
block_26:
                M2C_FIELD(var_v0, s8 *, 0x14) = 0;
            }
            break;
        case 1:
            if ((s8) D_800C8561[var_s1] == 1) {
                if (D_800C8566 != 1) {
                    M2C_FIELD((M2C_FIELD(temp_s0, s32 *, 0x34) + temp_s0), s8 *, 0x14) = 1;
                    *(temp_s0 + (M2C_FIELD(temp_s0, s32 *, 0x34) * 4)) = 0x16;
                    M2C_FIELD(((M2C_FIELD(temp_s0, s32 *, 0x34) * 4) + temp_s0), s32 *, 0x3C) = func_8005B8D4(arg0);
                    M2C_FIELD(temp_s0, s32 *, 0x34) = (s32) (M2C_FIELD(temp_s0, s32 *, 0x34) + 1);
                } else {
                    *(temp_s0 + (M2C_FIELD(temp_s0, s32 *, 0x34) * 4)) = -1;
                    var_v0 = M2C_FIELD(temp_s0, s32 *, 0x34) + temp_s0;
                    goto block_26;
                }
            } else {
                *(temp_s0 + (M2C_FIELD(temp_s0, s32 *, 0x34) * 4)) = -1;
                var_v0 = M2C_FIELD(temp_s0, s32 *, 0x34) + temp_s0;
                goto block_26;
            }
            break;
        case 2:
            if ((s8) D_800C8561[var_s1] == 2) {
                if (D_800C8566 != 2) {
                    M2C_FIELD((M2C_FIELD(temp_s0, s32 *, 0x34) + temp_s0), s8 *, 0x14) = 1;
                    *(temp_s0 + (M2C_FIELD(temp_s0, s32 *, 0x34) * 4)) = 0x18;
                    M2C_FIELD(((M2C_FIELD(temp_s0, s32 *, 0x34) * 4) + temp_s0), s32 *, 0x3C) = func_8005B8D4(arg0);
                    M2C_FIELD(temp_s0, s32 *, 0x34) = (s32) (M2C_FIELD(temp_s0, s32 *, 0x34) + 1);
                } else {
                    *(temp_s0 + (M2C_FIELD(temp_s0, s32 *, 0x34) * 4)) = -1;
                    var_v0 = M2C_FIELD(temp_s0, s32 *, 0x34) + temp_s0;
                    goto block_26;
                }
            } else {
                *(temp_s0 + (M2C_FIELD(temp_s0, s32 *, 0x34) * 4)) = -1;
                var_v0 = M2C_FIELD(temp_s0, s32 *, 0x34) + temp_s0;
                goto block_26;
            }
            break;
        case 3:
            if ((s8) D_800C8561[var_s1] == 3) {
                if (D_800C8566 != 3) {
                    M2C_FIELD((M2C_FIELD(temp_s0, s32 *, 0x34) + temp_s0), s8 *, 0x14) = 1;
                    *(temp_s0 + (M2C_FIELD(temp_s0, s32 *, 0x34) * 4)) = 0x19;
                    M2C_FIELD(((M2C_FIELD(temp_s0, s32 *, 0x34) * 4) + temp_s0), s32 *, 0x3C) = func_8005B8D4(arg0);
                    M2C_FIELD(temp_s0, s32 *, 0x34) = (s32) (M2C_FIELD(temp_s0, s32 *, 0x34) + 1);
                } else {
                    *(temp_s0 + (M2C_FIELD(temp_s0, s32 *, 0x34) * 4)) = -1;
                    var_v0 = M2C_FIELD(temp_s0, s32 *, 0x34) + temp_s0;
                    goto block_26;
                }
            } else {
                *(temp_s0 + (M2C_FIELD(temp_s0, s32 *, 0x34) * 4)) = -1;
                var_v0 = M2C_FIELD(temp_s0, s32 *, 0x34) + temp_s0;
                goto block_26;
            }
            break;
        case 4:
            if ((s8) D_800C8561[var_s1] == 4) {
                if (D_800C8566 != 4) {
                    M2C_FIELD((M2C_FIELD(temp_s0, s32 *, 0x34) + temp_s0), s8 *, 0x14) = 1;
                    *(temp_s0 + (M2C_FIELD(temp_s0, s32 *, 0x34) * 4)) = 0x17;
                    M2C_FIELD(((M2C_FIELD(temp_s0, s32 *, 0x34) * 4) + temp_s0), s32 *, 0x3C) = func_8005B8D4(arg0);
                    M2C_FIELD(temp_s0, s32 *, 0x34) = (s32) (M2C_FIELD(temp_s0, s32 *, 0x34) + 1);
                } else {
                    *(temp_s0 + (M2C_FIELD(temp_s0, s32 *, 0x34) * 4)) = -1;
                    var_v0 = M2C_FIELD(temp_s0, s32 *, 0x34) + temp_s0;
                    goto block_26;
                }
            } else {
                *(temp_s0 + (M2C_FIELD(temp_s0, s32 *, 0x34) * 4)) = -1;
                var_v0 = M2C_FIELD(temp_s0, s32 *, 0x34) + temp_s0;
                goto block_26;
            }
            break;
        }
        var_s1 += 1;
        var_s3 += 4;
        goto loop_28;
    }
    var_s1_2 = 0;
    var_s2 = 0;
loop_33:
    if (var_s1_2 < 5) {
        temp_v1 = temp_s0 + var_s2;
        temp_v0 = M2C_FIELD(temp_v1, s32 *, 0);
        if (temp_v0 != -1) {
            func_800249CC(M2C_FIELD(temp_v1, s32 *, 0x3C), temp_v0);
            thunk_FUN_8001e588(M2C_FIELD((temp_s0 + var_s2), s32 *, 0x3C));
        }
        var_s1_2 += 1;
        var_s2 += 4;
        goto loop_33;
    }
}
