#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u8 D_800D50B0[];
extern u8 D_800D50B8[];
extern u8 D_800D50BA[];
extern u8 D_800D50BE[];
extern u8 D_800D50C0[];
extern u8 D_800D50C1[];
extern void * D_8007CACC;
extern s32 D_8007CAD0;
extern void * D_8007CAD4;
extern u16 D_8007CC50;
extern u16 D_8007CC58;
extern u16 D_8007CC5A;


void func_80023FD4(s32 arg0) {
    s32 temp_a1_2;
    s32 temp_s4;
    s32 var_s0;
    s32 var_s1;
    s32 var_s2;
    s32 var_s3;
    void *temp_a1;
    void *temp_a1_3;

    if ((D_8007CC58 + D_8007CC5A) != 0) {
        var_s1 = 0;
        var_s3 = 0;
        var_s2 = 0;
        var_s0 = 0;
        temp_s4 = arg0 + 4;
loop_3:
        if (var_s1 != (D_8007CC58 + D_8007CC5A)) {
            M2C_FIELD(D_8007CACC, s16 *, 8) = (s16) (var_s2 + var_s3 + 0x32);
            M2C_FIELD(D_8007CACC, s16 *, 0xA) = 0x64;
            M2C_FIELD(D_8007CACC, s16 *, 0x10) = (s16) D_800D50B8[var_s0];
            M2C_FIELD(D_8007CACC, s16 *, 0x12) = (s16) D_800D50BA[var_s0];
            M2C_FIELD(D_8007CACC, s8 *, 6) = 0xFF;
            M2C_FIELD(D_8007CACC, s8 *, 5) = 0xFF;
            M2C_FIELD(D_8007CACC, s8 *, 4) = 0xFF;
            M2C_FIELD(D_8007CACC, u8 *, 0xD) = (u8) D_800D50C1[var_s0];
            M2C_FIELD(D_8007CACC, u8 *, 0xC) = (u8) D_800D50C0[var_s0];
            M2C_FIELD(D_8007CACC, u16 *, 0xE) = (u16) D_800D50BE[var_s0];
            temp_a1 = D_8007CACC;
            D_8007CACC = temp_a1 + 0x14;
            AddPrim(temp_s4, (s32) temp_a1);
            SetDrawTPage(D_8007CAD0, 1, 0, (s32) M2C_FIELD(&D_800D50B0[var_s0], u16 *, 0xC));
            temp_a1_2 = D_8007CAD0;
            D_8007CAD0 = temp_a1_2 + 8;
            AddPrim(temp_s4, temp_a1_2);
            var_s1 = (var_s1 + 1) & 0xFFFF;
            var_s0 += 0x20;
            var_s2 += 0x10;
            var_s3 += 0xA;
            goto loop_3;
        }
        M2C_FIELD(D_8007CAD4, s8 *, 4) = 0xC8;
        M2C_FIELD(D_8007CAD4, s8 *, 5) = 0;
        M2C_FIELD(D_8007CAD4, s8 *, 6) = 0x64;
        M2C_FIELD(D_8007CAD4, s16 *, 8) = (s16) ((D_8007CC50 * 0x1A) + 0x2D);
        M2C_FIELD(D_8007CAD4, s16 *, 0xA) = 0x5F;
        M2C_FIELD(D_8007CAD4, s16 *, 0xC) = 0x1A;
        M2C_FIELD(D_8007CAD4, s16 *, 0xE) = 0x1A;
        temp_a1_3 = D_8007CAD4;
        D_8007CAD4 = temp_a1_3 + 0x10;
        AddPrim(arg0 + 8, (s32) temp_a1_3);
    }
}
