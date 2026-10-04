#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u8 D_800D568C[];
extern u8 D_800D5690[];
extern u8 D_800D5694[];
extern s32 D_8007CC6C;


void func_80053C74(void *arg0) {
    s32 sp34;
    s32 sp38;
    s32 sp3C;
    s16 temp_v0;
    s32 temp_v0_2;
    s32 var_s2;
    s32 var_s3;
    void *temp_a1;
    void *temp_s1;

    temp_s1 = arg0 + 0x74;
    M2C_FIELD(arg0, s16 *, 0x70) = (s16) M2C_FIELD(temp_s1, s32 *, 0x18);
    temp_v0 = M2C_FIELD(arg0, s16 *, 0x70);
    switch (temp_v0) {
    case 4:
        M2C_FIELD(temp_s1, s32 *, 0x28) = (s32) M2C_FIELD(temp_s1, s32 *, 0x1C);
    default:
block_16:
        M2C_FIELD(temp_s1, s32 *, 0x30) = 0;
        M2C_FIELD(temp_s1, s32 *, 0x2C) = 1;
        func_80053B30((s32) temp_s1);
        return;
    case 6:
        M2C_FIELD(temp_s1, s32 *, 0x20) = 0;
        M2C_FIELD(temp_s1, s32 *, 0x24) = 0;
        M2C_FIELD(temp_s1, void **, 0x34) = (void *) (temp_s1 + 0x38);
        if (func_80053A98((s32) (arg0 + 0x24)) == 1) {
            M2C_FIELD(arg0, u8 *, 0x20) = (u8) (M2C_FIELD(arg0, u8 *, 0x20) | 0x80);
        }
        goto block_16;
    case 8:
        var_s2 = 0;
        var_s3 = 0;
loop_9:
        if (var_s2 >= D_8007CC6C) {
            M2C_FIELD(temp_s1, s32 *, 0x20) = 0;
            M2C_FIELD(temp_s1, s32 *, 0x24) = 0;
            M2C_FIELD(temp_s1, void **, 0x34) = (void *) (temp_s1 + 0x38);
            if (func_80053A98((s32) (arg0 + 0x24)) == 1) {
                M2C_FIELD(arg0, u8 *, 0x20) = (u8) (M2C_FIELD(arg0, u8 *, 0x20) | 0x80);
            }
            if (D_8007CC6C < 0x1F) {
                temp_a1 = D_800D568C + (D_8007CC6C * 0xC);
                M2C_FIELD(temp_a1, s32 *, 0) = (s32) M2C_FIELD(arg0, s32 *, 0x24);
                M2C_FIELD(temp_a1, s32 *, 4) = (s32) M2C_FIELD(arg0, s32 *, 0x28);
                M2C_FIELD(temp_a1, s32 *, 8) = (s32) M2C_FIELD(arg0, s32 *, 0x2C);
                D_8007CC6C += 1;
            } else {
                Afirmar(0);
            }
            goto block_16;
        }
        sp34 = (s32) (M2C_FIELD(arg0, s32 *, 0x24) - D_800D568C[var_s3]) >> 8;
        sp38 = (s32) (M2C_FIELD(arg0, s32 *, 0x28) - D_800D5690[var_s3]) >> 8;
        temp_v0_2 = (s32) (M2C_FIELD(arg0, s32 *, 0x2C) - D_800D5694[var_s3]) >> 8;
        sp3C = temp_v0_2;
        if (func_8001C390(sp34, sp38, sp3C, subroutine_arg3, /* extra? */ sp38, /* extra? */ temp_v0_2) < 0x100) {
            M2C_FIELD(arg0, u8 *, 0x20) = (u8) (M2C_FIELD(arg0, u8 *, 0x20) | 0x80);
            return;
        }
        var_s2 += 1;
        var_s3 += 0xC;
        goto loop_9;
    case 7:
        M2C_FIELD(temp_s1, s32 *, 0x20) = 0;
        goto block_16;
    }
}
