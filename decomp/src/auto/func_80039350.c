#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"


extern s32 func_80024DF4();
extern s32 func_80024F6C();

void func_80039350(void *arg0) {
    s16 temp_v0;
    s32 temp_a0;
    s32 temp_v0_2;
    s32 temp_v0_3;
    s32 temp_v1;
    s32 temp_v1_2;
    s32 var_s2;
    s32 var_s2_2;
    s32 var_s4;
    s32 var_s5;
    s32 var_v1;
    s8 temp_v0_4;
    void *temp_s1;
    void *temp_s1_2;
    void *temp_s3;

    temp_v0 = M2C_FIELD(arg0, s16 *, 0x70);
    temp_s3 = arg0 + 0x74;
    if (temp_v0 != 3) {
        if (temp_v0 != 2) {
            if (temp_v0 != 1) {
                if (temp_v0 == 0) {
                    temp_a0 = M2C_FIELD(arg0, s32 *, 0x54);
                    if (temp_a0 < 0x1000) {
                        M2C_FIELD(arg0, s32 *, 0x54) = (s32) (temp_a0 + ((s32) (0x1000 - temp_a0) >> 2));
                        if (M2C_FIELD(arg0, s32 *, 0x54) >= 0x1000) {
                            M2C_FIELD(arg0, s32 *, 0x54) = 0x1000;
                        }
                        M2C_FIELD(arg0, s32 *, 0x58) = (s32) M2C_FIELD(arg0, s32 *, 0x54);
                        M2C_FIELD(arg0, s32 *, 0x5C) = (s32) M2C_FIELD(arg0, s32 *, 0x54);
                    }
                    M2C_FIELD(arg0, s32 *, 0x28) = (s32) (M2C_FIELD(arg0, s32 *, 0x28) + M2C_FIELD(arg0, s32 *, 0x3C));
                    M2C_FIELD(arg0, s32 *, 0x3C) = (s32) (M2C_FIELD(arg0, s32 *, 0x3C) + 0x51E);
                    temp_v0_2 = M2C_FIELD(arg0, s32 *, 0x50);
                    if (temp_v0_2 < M2C_FIELD(arg0, s32 *, 0x28)) {
                        M2C_FIELD(arg0, s32 *, 0x28) = temp_v0_2;
                        M2C_FIELD(arg0, s16 *, 0x70) = 2;
                        M2C_FIELD(arg0, s8 *, 0x118) = 0x14;
                        M2C_FIELD(arg0, s16 *, 0x112) = 2;
                        M2C_FIELD(arg0, s16 *, 0x114) = 2;
                        M2C_FIELD(arg0, s32 (**)(), 4) = func_80024DF4;
                        M2C_FIELD(arg0, s32 (**)(), 8) = func_80024F6C;
                    }
                }
            } else {
                var_s2 = 0;
                M2C_FIELD(arg0, s32 *, 0x28) = (s32) (M2C_FIELD(arg0, s32 *, 0x28) + M2C_FIELD(arg0, s32 *, 0x3C));
                var_s4 = 0;
                var_s5 = 0;
loop_14:
                if (var_s2 < M2C_FIELD(temp_s3, s16 *, 0x32)) {
                    temp_s1 = M2C_FIELD((var_s4 + temp_s3), void **, 0x14);
                    if (temp_s1 != NULL) {
                        temp_v1 = M2C_FIELD(arg0, s32 *, 0x3C);
                        M2C_FIELD(arg0, s32 *, 0x3C) = (s32) (temp_v1 - (temp_v1 >> 4));
                        M2C_FIELD(temp_s1, s32 *, 0x58) = (s32) ((s32) (func_80014AEC(M2C_FIELD(arg0, s32 *, 0x28) - M2C_FIELD(temp_s1, s32 *, 0x28)) * M2C_FIELD((var_s5 + temp_s3), s16 *, 0x28)) / (s32) *(temp_s3 + var_s4));
                    }
                    var_s2 += 1;
                    var_s5 += 2;
                    var_s4 += 4;
                    goto loop_14;
                }
                temp_v0_3 = M2C_FIELD(arg0, s32 *, 0x50);
                if (temp_v0_3 < M2C_FIELD(arg0, s32 *, 0x28)) {
                    M2C_FIELD(arg0, s32 *, 0x28) = temp_v0_3;
                    M2C_FIELD(arg0, s16 *, 0x70) = 2;
                    M2C_FIELD(arg0, s8 *, 0x118) = 0x14;
                    M2C_FIELD(arg0, s16 *, 0x112) = 0;
                    M2C_FIELD(arg0, s16 *, 0x114) = 0;
                    var_s2_2 = 0;
                    var_v1 = 0;
loop_20:
                    if (var_s2_2 < M2C_FIELD(temp_s3, s16 *, 0x32)) {
                        temp_s1_2 = M2C_FIELD((var_v1 + temp_s3), void **, 0x14);
                        if (!(M2C_FIELD(temp_s1_2, s16 *, 0x112) & 1)) {
                            M2C_FIELD(temp_s1_2, u8 *, 0x20) = (u8) (M2C_FIELD(temp_s1_2, u8 *, 0x20) | 0x80);
                        }
                        var_s2_2 += 1;
                        var_v1 += 4;
                        goto loop_20;
                    }
                }
                M2C_FIELD(arg0, s16 *, 0x112) = 0;
                M2C_FIELD(arg0, s16 *, 0x114) = 0;
            }
        } else {
            temp_v0_4 = M2C_FIELD(arg0, s8 *, 0x118);
            if (temp_v0_4 < 0) {
                M2C_FIELD(arg0, s16 *, 0x32) = (s16) (M2C_FIELD(arg0, s16 *, 0x32) + 0x7B);
                temp_v1_2 = M2C_FIELD(arg0, s32 *, 0x54);
                M2C_FIELD(arg0, s32 *, 0x54) = (s32) (temp_v1_2 - (temp_v1_2 >> 1));
                M2C_FIELD(arg0, s32 *, 0x58) = (s32) M2C_FIELD(arg0, s32 *, 0x54);
                M2C_FIELD(arg0, s32 *, 0x5C) = (s32) M2C_FIELD(arg0, s32 *, 0x54);
                if (M2C_FIELD(arg0, s32 *, 0x54) < 0x32) {
                    M2C_FIELD(arg0, s16 *, 0x70) = 3;
                }
            } else {
                M2C_FIELD(arg0, s8 *, 0x118) = (s8) (temp_v0_4 - 1);
            }
        }
    } else {
        M2C_FIELD(arg0, u8 *, 0x20) = (u8) (M2C_FIELD(arg0, u8 *, 0x20) | 0x80);
    }
}
