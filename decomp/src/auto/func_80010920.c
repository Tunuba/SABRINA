#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u8 D_8007ED9C[];
extern u8 D_8007F19C[];
extern u16 D_8008319C;
extern u16 D_800831A0;
extern s32 D_80062AF8;
extern s32 D_80063500;
extern u8 D_80063518[];
extern u8 D_80063524[];
extern u8 D_80063528[];
extern u8 D_8006352C[];
extern u8 D_80063530[];
extern struct _struct_D_80063534_0x30 D_80063534[];

struct _struct_D_80063534_0x30 D_80063534[];        /* unable to generate initializer: unsized array */

void func_80010920(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    s16 sp18;
    s16 sp1A;
    s16 sp1C;
    s16 sp1E;
    s32 temp_a0;
    s32 temp_v1;
    s32 var_s0;
    s32 var_s1;
    s32 var_s2;
    u8 *temp_s0;
    void *temp_v0;

    var_s2 = arg5;
    if (D_80062AF8 >= 8) {
        return;
    }
    if (D_80062AF8 == 0) {
        D_80063500 = 0;
    }
    temp_a0 = D_80062AF8 * 0x30;
    *(D_80063534 + temp_a0) = arg2 == 0;
    if ((D_80063500 + var_s2) >= 0x401) {
        var_s2 = 0x400 - D_80063500;
    }
    sp1C = 0x100;
    sp1E = 0x100;
    sp18 = 0;
    sp1A = 0;
    SetDrawMode((s32) (temp_a0 + D_80063518), 0, 0, (s32) D_8008319C, /* extra? */ &sp18);
    temp_s0 = D_80063518 - 0x10;
    if (arg4 != 0) {
        func_800141AC((s32) ((D_80062AF8 * 0x30) + temp_s0));
        M2C_FIELD(((D_80062AF8 * 0x30) + temp_s0), s8 *, 4) = 0;
        M2C_FIELD(((D_80062AF8 * 0x30) + temp_s0), s8 *, 5) = 0;
        M2C_FIELD(((D_80062AF8 * 0x30) + temp_s0), s8 *, 6) = 0;
        func_800140DC((s32) ((D_80062AF8 * 0x30) + temp_s0), arg4 == 2);
    }
    temp_v1 = D_80062AF8 * 0x30;
    temp_v0 = temp_v1 + (D_80063518 - 0x10);
    M2C_FIELD(temp_v0, s16 *, 8) = (s16) arg0;
    M2C_FIELD(temp_v0, s16 *, 0xA) = (s16) arg1;
    M2C_FIELD(temp_v0, s16 *, 0xC) = (s16) arg2;
    M2C_FIELD(temp_v0, s16 *, 0xE) = (s16) arg3;
    *(D_80063524 + temp_v1) = var_s2;
    *(D_80063530 + temp_v1) = 0;
    *(D_8006352C + temp_v1) = &D_8007ED9C[D_80063500];
    *(D_80063528 + temp_v1) = (D_80063500 * 0x10) + D_8007F19C;
    **(D_8006352C + temp_v1) = 0;
    var_s0 = *(D_80063528 + (D_80062AF8 * 0x30));
    var_s1 = 0;
    if (var_s2 > 0) {
        do {
            func_8001416C(var_s0);
            var_s1 += 1;
            M2C_FIELD(var_s0, u16 *, 0xE) = (u16) D_800831A0;
            var_s0 += 0x10;
        } while (var_s1 < var_s2);
    }
    D_80063500 += var_s2;
    D_80062AF8 += 1;
}
/* Warning: struct _struct_D_80063534_0x30 is not defined (only forward-declared) */
