#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u8 D_8007C874[];
extern u16 D_8007C876[];
extern u16 D_8007C87A;
extern u8 D_8007C87C[];
extern u16 D_8007C87E[];
extern u16 D_8007C882;
extern u8 D_8007C884[];
extern void * D_8007CACC;
extern s32 D_8007CAD0;
extern void * D_8007CAD4;
extern s32 D_8007CADC;
extern s16 D_8007CB1E;
extern s16 D_8007CB22;
extern s32 D_8007CB24;
extern s32 D_8007CB30;


void func_80023B3C(s32 arg0) {
    s32 temp_a0;
    s32 temp_a1_2;
    s32 temp_a1_3;
    s32 temp_a1_5;
    s32 temp_s3;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 var_s0;
    s32 var_s2;
    void *temp_a1;
    void *temp_a1_4;
    void *temp_a1_6;
    void *temp_s1;

    D_8007CB30 = 0;
    var_s0 = 0;
    var_s2 = 0;
    temp_s3 = arg0 + 0xC;
loop_2:
    if (var_s0 != 4) {
        temp_s1 = D_8007CB24 + (D_8007C884[var_s2] << 5);
        M2C_FIELD(D_8007CACC, u16 *, 8) = (u16) D_8007C874[var_s2];
        M2C_FIELD(D_8007CACC, u16 *, 0xA) = (u16) D_8007C87C[var_s2];
        M2C_FIELD(D_8007CACC, s16 *, 0x10) = (s16) M2C_FIELD(temp_s1, s16 *, 8);
        M2C_FIELD(D_8007CACC, s16 *, 0x12) = (s16) M2C_FIELD(temp_s1, s16 *, 0xA);
        M2C_FIELD(D_8007CACC, s8 *, 4) = 0xFF;
        M2C_FIELD(D_8007CACC, s8 *, 5) = 0xFF;
        M2C_FIELD(D_8007CACC, s8 *, 6) = 0xFF;
        M2C_FIELD(D_8007CACC, u8 *, 0xD) = (u8) M2C_FIELD(temp_s1, u8 *, 0x11);
        M2C_FIELD(D_8007CACC, u8 *, 0xC) = (u8) M2C_FIELD(temp_s1, u8 *, 0x10);
        M2C_FIELD(D_8007CACC, u16 *, 0xE) = (u16) M2C_FIELD(temp_s1, u16 *, 0xE);
        temp_a1 = D_8007CACC;
        D_8007CACC = temp_a1 + 0x14;
        AddPrim(temp_s3, (s32) temp_a1);
        SetDrawTPage(D_8007CAD0, 1, 0, (s32) M2C_FIELD(temp_s1, u16 *, 0xC));
        temp_a1_2 = D_8007CAD0;
        D_8007CAD0 = temp_a1_2 + 8;
        AddPrim(temp_s3, temp_a1_2);
        var_s0 = (var_s0 + 1) & 0xFFFF;
        var_s2 += 2;
        goto loop_2;
    }
    temp_a1_3 = D_8007CB1E & 0xFFFF;
    temp_v0 = temp_a1_3 << 7;
    M2C_FIELD(D_8007CAD4, s8 *, 4) = (s8) ((s32) ((((0x100 - temp_a1_3) & 0xFFFF) << 7) + temp_v0) >> 8);
    temp_a0 = arg0 + 8;
    M2C_FIELD(D_8007CAD4, s8 *, 5) = (s8) (temp_v0 >> 8);
    M2C_FIELD(D_8007CAD4, s8 *, 6) = 0;
    M2C_FIELD(D_8007CAD4, u16 *, 8) = (u16) *D_8007C876;
    M2C_FIELD(D_8007CAD4, s16 *, 0xA) = (s16) (*D_8007C87E + 2);
    M2C_FIELD(D_8007CAD4, s16 *, 0xC) = (s16) D_8007CB1E;
    M2C_FIELD(D_8007CAD4, s16 *, 0xE) = 0xC;
    M2C_FIELD(D_8007CAD4, u8 *, 7) = (u8) (M2C_FIELD(D_8007CAD4, u8 *, 7) | 2);
    temp_a1_4 = D_8007CAD4;
    D_8007CAD4 = temp_a1_4 + 0x10;
    AddPrim(temp_a0, (s32) temp_a1_4);
    temp_a1_5 = D_8007CB22 & 0xFFFF;
    temp_v0_2 = temp_a1_5 << 7;
    M2C_FIELD(D_8007CAD4, s8 *, 4) = (s8) ((s32) ((((0x100 - temp_a1_5) & 0xFFFF) << 7) + temp_v0_2) >> 8);
    M2C_FIELD(D_8007CAD4, s8 *, 5) = (s8) (temp_v0_2 >> 8);
    M2C_FIELD(D_8007CAD4, s8 *, 6) = 0;
    M2C_FIELD(D_8007CAD4, u16 *, 8) = (u16) (D_8007C87A + (0x80 - D_8007CB22));
    M2C_FIELD(D_8007CAD4, s16 *, 0xA) = (s16) (D_8007C882 + 2);
    M2C_FIELD(D_8007CAD4, s16 *, 0xC) = (s16) D_8007CB22;
    M2C_FIELD(D_8007CAD4, s16 *, 0xE) = 0xC;
    M2C_FIELD(D_8007CAD4, u8 *, 7) = (u8) (M2C_FIELD(D_8007CAD4, u8 *, 7) | 2);
    temp_a1_6 = D_8007CAD4;
    D_8007CAD4 = temp_a1_6 + 0x10;
    AddPrim(temp_a0, (s32) temp_a1_6);
    AddPrim(temp_a0, D_8007CADC);
}
