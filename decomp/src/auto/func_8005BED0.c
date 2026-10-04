#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u8 D_800C8561[];
extern s8 D_800C8566;
extern s32 D_8007CC78;


void func_8005BED0(s32 arg0) {
    s32 var_a0;
    s32 var_a0_2;
    s32 var_a1;
    s32 var_a1_2;
    s32 var_a2;
    void *temp_s0;
    void *temp_v1;
    void *var_v0;

    temp_v1 = arg0 + 0x74;
    D_8007CC78 = 0;
    M2C_FIELD(temp_v1, s32 *, 0x1C) = 0;
    M2C_FIELD(temp_v1, s32 *, 0x30) = 0x1999;
    M2C_FIELD(temp_v1, s32 *, 0x34) = 0;
    var_a0 = 0;
    var_a1 = 0;
    var_a2 = 0;
loop_2:
    if (var_a0 < 5) {
        M2C_FIELD((var_a1 + temp_v1), s32 *, 0x3C) = 0;
        M2C_FIELD((var_a2 + temp_v1), s16 *, 0x20) = 0;
        M2C_FIELD((var_a0 + temp_v1), s8 *, 0x14) = 0;
        var_a0 += 1;
        var_a2 += 2;
        var_a1 += 4;
        goto loop_2;
    }
    var_a0_2 = 0;
    var_a1_2 = 0;
loop_31:
    if (var_a0_2 < 5) {
        *(temp_v1 + var_a1_2) = -1;
        switch (var_a0_2) {
        case 0:
            if (D_800C8566 != 0) {
                *(temp_v1 + (M2C_FIELD(temp_v1, s32 *, 0x34) * 4)) = 0x15;
                M2C_FIELD((M2C_FIELD(temp_v1, s32 *, 0x34) + temp_v1), s8 *, 0x14) = 1;
                M2C_FIELD(temp_v1, s32 *, 0x34) = (s32) (M2C_FIELD(temp_v1, s32 *, 0x34) + 1);
            } else {
                *(temp_v1 + (M2C_FIELD(temp_v1, s32 *, 0x34) * 4)) = -1;
                var_v0 = M2C_FIELD(temp_v1, s32 *, 0x34) + temp_v1;
block_29:
                M2C_FIELD(var_v0, s8 *, 0x14) = 0;
            }
            break;
        case 1:
            if ((s8) D_800C8561[var_a0_2] == 1) {
                if (D_800C8566 != 1) {
                    M2C_FIELD((M2C_FIELD(temp_v1, s32 *, 0x34) + temp_v1), s8 *, 0x14) = 1;
                    *(temp_v1 + (M2C_FIELD(temp_v1, s32 *, 0x34) * 4)) = 0x16;
                    M2C_FIELD(temp_v1, s32 *, 0x34) = (s32) (M2C_FIELD(temp_v1, s32 *, 0x34) + 1);
                } else {
                    *(temp_v1 + (M2C_FIELD(temp_v1, s32 *, 0x34) * 4)) = -1;
                    var_v0 = M2C_FIELD(temp_v1, s32 *, 0x34) + temp_v1;
                    goto block_29;
                }
            } else {
                *(temp_v1 + (M2C_FIELD(temp_v1, s32 *, 0x34) * 4)) = -1;
                var_v0 = M2C_FIELD(temp_v1, s32 *, 0x34) + temp_v1;
                goto block_29;
            }
            break;
        case 2:
            if ((s8) D_800C8561[var_a0_2] == 2) {
                if (D_800C8566 != 2) {
                    M2C_FIELD((M2C_FIELD(temp_v1, s32 *, 0x34) + temp_v1), s8 *, 0x14) = 1;
                    *(temp_v1 + (M2C_FIELD(temp_v1, s32 *, 0x34) * 4)) = 0x18;
                    M2C_FIELD(temp_v1, s32 *, 0x34) = (s32) (M2C_FIELD(temp_v1, s32 *, 0x34) + 1);
                } else {
                    *(temp_v1 + (M2C_FIELD(temp_v1, s32 *, 0x34) * 4)) = -1;
                    var_v0 = M2C_FIELD(temp_v1, s32 *, 0x34) + temp_v1;
                    goto block_29;
                }
            } else {
                *(temp_v1 + (M2C_FIELD(temp_v1, s32 *, 0x34) * 4)) = -1;
                var_v0 = M2C_FIELD(temp_v1, s32 *, 0x34) + temp_v1;
                goto block_29;
            }
            break;
        case 3:
            if ((s8) D_800C8561[var_a0_2] == 3) {
                if (D_800C8566 != 3) {
                    M2C_FIELD((M2C_FIELD(temp_v1, s32 *, 0x34) + temp_v1), s8 *, 0x14) = 1;
                    *(temp_v1 + (M2C_FIELD(temp_v1, s32 *, 0x34) * 4)) = 0x19;
                    M2C_FIELD(temp_v1, s32 *, 0x34) = (s32) (M2C_FIELD(temp_v1, s32 *, 0x34) + 1);
                } else {
                    *(temp_v1 + (M2C_FIELD(temp_v1, s32 *, 0x34) * 4)) = -1;
                    var_v0 = M2C_FIELD(temp_v1, s32 *, 0x34) + temp_v1;
                    goto block_29;
                }
            } else {
                *(temp_v1 + (M2C_FIELD(temp_v1, s32 *, 0x34) * 4)) = -1;
                var_v0 = M2C_FIELD(temp_v1, s32 *, 0x34) + temp_v1;
                goto block_29;
            }
            break;
        case 4:
            if ((s8) D_800C8561[var_a0_2] == 4) {
                if (D_800C8566 != 4) {
                    M2C_FIELD((M2C_FIELD(temp_v1, s32 *, 0x34) + temp_v1), s8 *, 0x14) = 1;
                    *(temp_v1 + (M2C_FIELD(temp_v1, s32 *, 0x34) * 4)) = 0x17;
                    M2C_FIELD(temp_v1, s32 *, 0x34) = (s32) (M2C_FIELD(temp_v1, s32 *, 0x34) + 1);
                } else {
                    *(temp_v1 + (M2C_FIELD(temp_v1, s32 *, 0x34) * 4)) = -1;
                    var_v0 = M2C_FIELD(temp_v1, s32 *, 0x34) + temp_v1;
                    goto block_29;
                }
            } else {
                *(temp_v1 + (M2C_FIELD(temp_v1, s32 *, 0x34) * 4)) = -1;
                var_v0 = M2C_FIELD(temp_v1, s32 *, 0x34) + temp_v1;
                goto block_29;
            }
            break;
        }
        var_a0_2 += 1;
        var_a1_2 += 4;
        goto loop_31;
    }
    if (func_8002ECFC(arg0) != 0) {
        temp_s0 = M2C_FIELD(arg0, void **, 0x1C);
        M2C_FIELD(temp_s0, s16 *, 0x4C) = 0;
        M2C_FIELD(temp_s0, s16 *, 0x4E) = 0;
        M2C_FIELD(temp_s0, u8 *, 0x51) = (u8) *M2C_FIELD(arg0, u16 **, 0x64);
        M2C_FIELD(temp_s0, u8 *, 0x50) = 0U;
        M2C_FIELD(temp_s0, u8 *, 0x53) = (u8) M2C_FIELD(temp_s0, u8 *, 0x51);
        M2C_FIELD(temp_s0, u8 *, 0x52) = (u8) M2C_FIELD(temp_s0, u8 *, 0x50);
        M2C_FIELD(temp_s0, s8 *, 8) = func_80030068(M2C_FIELD(M2C_FIELD(arg0, void **, 0x60), s32 *, 4));
    }
}
