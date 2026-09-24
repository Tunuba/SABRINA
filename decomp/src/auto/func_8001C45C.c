#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"



void func_8001C45C(s32 arg0) {
    u32 sp3C;
    s32 temp_a0_2;
    s32 temp_ret;
    s32 temp_ret_2;
    s32 temp_ret_3;
    s32 temp_s0;
    s32 temp_s2;
    s32 temp_s3;
    s32 temp_s4;
    s32 temp_s5;
    s32 temp_s6;
    s32 temp_s7;
    s32 temp_t1;
    s32 temp_v0_3;
    s32 temp_v0_4;
    s32 temp_v0_5;
    s32 temp_v0_6;
    s32 temp_v1;
    u32 temp_a0;
    u32 temp_fp;
    u32 temp_v0;
    u32 temp_v0_2;

    temp_s3 = M2C_FIELD(arg0, s32 *, 0);
    temp_s2 = M2C_FIELD(arg0, s32 *, 4);
    temp_s6 = temp_s3 >> 0x1F;
    temp_s0 = M2C_FIELD(arg0, s32 *, 8);
    temp_s5 = temp_s2 >> 0x1F;
    temp_s4 = temp_s0 >> 0x1F;
    temp_ret = func_80029214(temp_s3, temp_s6, temp_s3);
    temp_v0 = temp_ret;
    sp3C = (u32) (u64) temp_ret;
    temp_ret_2 = func_80029214(temp_s2, temp_s5, temp_s2);
    temp_fp = temp_v0 + temp_ret_2;
    temp_s7 = (temp_fp < temp_v0) + sp3C + (u32) (u64) temp_ret_2;
    temp_ret_3 = func_80029214(temp_s0, temp_s4, temp_s0);
    temp_v0_2 = temp_ret_3;
    temp_a0 = temp_v0_2 + temp_fp;
    temp_v0_3 = (temp_a0 < temp_v0_2) + (u32) (u64) temp_ret_3 + temp_s7;
    if ((temp_v0_3 >= 0) && ((temp_v0_3 >= 1) || (temp_a0 >= 0x80000000U))) {
        func_80014B00((temp_a0 >> 0x10) | (temp_v0_3 << 0x10));
        temp_v0_4 = SquareRoot0() >> 4;
        M2C_FIELD(arg0, s32 *, 0) = (s32) ((s32) M2C_FIELD(arg0, s32 *, 0) / temp_v0_4);
        M2C_FIELD(arg0, s32 *, 4) = (s32) ((s32) M2C_FIELD(arg0, s32 *, 4) / temp_v0_4);
        M2C_FIELD(arg0, s32 *, 8) = (s32) ((s32) M2C_FIELD(arg0, s32 *, 8) / temp_v0_4);
    } else if ((temp_v0_3 >= 0) && ((temp_v0_3 >= 1) || (temp_a0 >= 0x80000U))) {
        temp_v0_5 = func_8001C3C4(func_80014B00((s32) temp_a0));
        temp_t1 = temp_s3 << 0xC;
        temp_v1 = temp_s2 << 0xC;
        temp_a0_2 = temp_s0 << 0xC;
        if ((temp_t1 >= 0) != ((((u32) temp_s3 >= 0U) & (temp_s6 == 0)) | (temp_s6 > 0))) {
            M2C_FIELD(arg0, s32 *, 0) = (s32) -(temp_t1 / temp_v0_5);
        } else {
            M2C_FIELD(arg0, s32 *, 0) = (s32) (temp_t1 / temp_v0_5);
        }
        if ((temp_v1 >= 0) != ((((u32) temp_s2 >= 0U) & (temp_s5 == 0)) | (temp_s5 > 0))) {
            M2C_FIELD(arg0, s32 *, 4) = (s32) -(temp_v1 / temp_v0_5);
        } else {
            M2C_FIELD(arg0, s32 *, 4) = (s32) (temp_v1 / temp_v0_5);
        }
        if ((temp_a0_2 >= 0) != ((((u32) temp_s0 >= 0U) & (temp_s4 == 0)) | (temp_s4 > 0))) {
            M2C_FIELD(arg0, s32 *, 8) = (s32) -(temp_a0_2 / temp_v0_5);
        } else {
            M2C_FIELD(arg0, s32 *, 8) = (s32) (temp_a0_2 / temp_v0_5);
        }
    } else {
        temp_v0_6 = func_8001C3C4(func_80014B00(temp_a0 << 0xC));
        M2C_FIELD(arg0, s32 *, 0) = (s32) ((s32) (M2C_FIELD(arg0, s32 *, 0) << 0x12) / temp_v0_6);
        M2C_FIELD(arg0, s32 *, 4) = (s32) ((s32) (M2C_FIELD(arg0, s32 *, 4) << 0x12) / temp_v0_6);
        M2C_FIELD(arg0, s32 *, 8) = (s32) ((s32) (M2C_FIELD(arg0, s32 *, 8) << 0x12) / temp_v0_6);
        if ((temp_v0_6 * 0x64) < 0) {

        }
    }
}
