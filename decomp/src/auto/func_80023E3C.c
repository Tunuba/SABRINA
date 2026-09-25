#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u16 D_8007CA20;
extern void * D_8007CACC;
extern s32 D_8007CAD0;
extern void * D_8007CB24;


void func_80023E3C(s32 arg0) {
    s32 temp_a1_2;
    s32 temp_s3;
    s32 var_s1;
    s32 var_s2;
    void *temp_a1;
    void *var_s0;

    if ((D_8007CA20 == 0x13) || (D_8007CA20 == 0x5F)) {
        var_s0 = D_8007CB24;
    } else {
        var_s0 = D_8007CB24 + 0x400;
    }
    var_s2 = 0;
loop_9:
    var_s1 = 0;
    if (var_s2 != 4) {
        temp_s3 = arg0 + 0x190;
loop_7:
        if (var_s1 != 8) {
            M2C_FIELD(D_8007CACC, s16 *, 8) = (s16) (M2C_FIELD(var_s0, s16 *, 8) * var_s1);
            M2C_FIELD(D_8007CACC, s16 *, 0xA) = (s16) (var_s2 << 6);
            M2C_FIELD(D_8007CACC, s16 *, 0x10) = (s16) M2C_FIELD(var_s0, s16 *, 8);
            M2C_FIELD(D_8007CACC, s16 *, 0x12) = (s16) M2C_FIELD(var_s0, s16 *, 0xA);
            M2C_FIELD(D_8007CACC, s8 *, 4) = 0xFF;
            M2C_FIELD(D_8007CACC, s8 *, 5) = 0xFF;
            M2C_FIELD(D_8007CACC, s8 *, 6) = 0xFF;
            M2C_FIELD(D_8007CACC, u8 *, 0xD) = (u8) M2C_FIELD(var_s0, u8 *, 0x11);
            M2C_FIELD(D_8007CACC, u8 *, 0xC) = (u8) M2C_FIELD(var_s0, u8 *, 0x10);
            M2C_FIELD(D_8007CACC, u16 *, 0xE) = (u16) M2C_FIELD(var_s0, u16 *, 0xE);
            temp_a1 = D_8007CACC;
            D_8007CACC = temp_a1 + 0x14;
            AddPrim(temp_s3, (s32) temp_a1);
            SetDrawTPage(D_8007CAD0, 1, 0, (s32) M2C_FIELD(var_s0, u16 *, 0xC));
            temp_a1_2 = D_8007CAD0;
            D_8007CAD0 = temp_a1_2 + 8;
            AddPrim(temp_s3, temp_a1_2);
            var_s0 += 0x20;
            var_s1 = (var_s1 + 1) & 0xFFFF;
            goto loop_7;
        }
        var_s2 = (var_s2 + 1) & 0xFFFF;
        goto loop_9;
    }
}
