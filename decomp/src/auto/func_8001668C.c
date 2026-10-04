#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s32 D_8006391C[];
extern u16 * D_800649A8;


s32 func_8001668C(s32 arg0, s32 arg1) {
    s32 *temp_a0;
    s32 *temp_a2;
    s32 temp_s3;
    s32 temp_s4;
    s32 temp_v0;
    s32 temp_v1_2;
    u16 temp_v1;
    u16 var_s3;

    temp_a0 = &D_8006391C[arg0];
    temp_s4 = *temp_a0;
    if (arg1 != temp_s4) {
        temp_a2 = D_8006391C - 4;
        if (M2C_FIELD(D_8006391C, u16 *, -4) != 0) {
            temp_v1 = *D_800649A8;
            *D_800649A8 = 0;
            temp_s3 = temp_v1 & 0xFFFF;
            if (arg1 != 0) {
                temp_v1_2 = 1 << arg0;
                *temp_a0 = arg1;
                var_s3 = temp_s3 | temp_v1_2;
                M2C_FIELD(temp_a2, u16 *, 0x30) = (u16) (M2C_FIELD(temp_a2, u16 *, 0x30) | temp_v1_2);
            } else {
                temp_v0 = ~(1 << arg0);
                *temp_a0 = 0;
                var_s3 = temp_s3 & temp_v0;
                M2C_FIELD(D_8006391C, u16 *, 0x2C) = (u16) (M2C_FIELD(D_8006391C, u16 *, 0x2C) & temp_v0);
            }
            if (arg0 == 0) {
                ChangeClearPAD();
                ChangeClearRCnt();
            }
            if (arg0 == 4) {
                ChangeClearRCnt();
            }
            if (arg0 == 5) {
                ChangeClearRCnt();
            }
            if (arg0 == 6) {
                ChangeClearRCnt();
            }
            *D_800649A8 = var_s3;
        }
    }
    return temp_s4;
}
