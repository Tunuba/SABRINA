#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"



void func_8003B894(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 sp68;
    s32 sp6C;
    s32 sp70;
    s32 sp74;
    s32 sp78;
    s32 sp7C;
    s16 var_s3;
    s32 temp_fp;
    s32 temp_s5;
    s32 temp_s6;
    s32 temp_s7;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 temp_v0_3;
    s32 temp_v0_4;
    s32 temp_v0_5;
    s32 temp_v0_6;
    s32 var_s0;
    s32 var_s1;
    s32 var_s2;

    temp_v0 = M2C_FIELD(arg0, s32 *, 0x24);
    sp68 = temp_v0;
    temp_v0_2 = M2C_FIELD(arg0, s32 *, 0x28);
    sp6C = temp_v0_2;
    temp_v0_3 = M2C_FIELD(arg0, s32 *, 0x2C);
    sp70 = temp_v0_3;
    temp_v0_4 = M2C_FIELD(arg1, s32 *, 0x24) - temp_v0;
    sp74 = temp_v0_4;
    temp_v0_5 = M2C_FIELD(arg1, s32 *, 0x28) - temp_v0_2;
    sp78 = temp_v0_5;
    temp_v0_6 = M2C_FIELD(arg1, s32 *, 0x2C) - temp_v0_3;
    sp7C = temp_v0_6;
    var_s2 = sp68;
    var_s0 = sp6C;
    var_s3 = (s16) (func_8002225C(arg0, sp74, sp78, sp7C) / arg2);
    temp_s5 = arg2 >> 2;
    arg2 = arg2 >> 1;
    var_s1 = sp70;
    sp74 = temp_v0_4 / var_s3;
    sp78 = temp_v0_5 / var_s3;
    sp7C = temp_v0_6 / var_s3;
loop_2:
    var_s3 -= 1;
    if (var_s3 >= 2) {
        sp68 += sp74;
        sp6C += sp78;
        sp70 += sp7C;
        temp_fp = sp68 + (func_80021CE4(arg2) - temp_s5);
        temp_s7 = sp6C + (func_80021CE4(arg2) - temp_s5);
        temp_s6 = sp70 + (func_80021CE4(arg2) - temp_s5);
        CrearParticula((s32) (s8) arg3, 0, 0, var_s2, /* extra? */ var_s0, /* extra? */ var_s1, /* extra? */ (temp_fp - var_s2), /* extra? */ (temp_s7 - var_s0), /* extra? */ (temp_s6 - var_s1), /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0xF, /* extra? */ 0x402, /* extra? */ 0);
        var_s2 = temp_fp;
        var_s0 = temp_s7;
        var_s1 = temp_s6;
        goto loop_2;
    }
    CrearParticula((s32) (s8) arg3, 0, 0, var_s2, /* extra? */ var_s0, /* extra? */ var_s1, /* extra? */ (M2C_FIELD(arg1, s32 *, 0x24) - var_s2), /* extra? */ (M2C_FIELD(arg1, s32 *, 0x28) - var_s0), /* extra? */ (M2C_FIELD(arg1, s32 *, 0x2C) - var_s1), /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0xF, /* extra? */ 0x402, /* extra? */ 0);
}
