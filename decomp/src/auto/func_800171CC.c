#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u8 D_80084B8C[];
extern u8 D_80084B90[];
extern u8 D_80084B91[];
extern u8 D_80084B92[];
extern u8 D_80084B94[];
extern u8 D_80084B96[];
extern u8 D_80084B98[];
extern u8 D_80084B9A[];
extern s16 D_80084BAC;
extern u8 D_80084C1D;
extern u8 D_80084C24[];
extern u8 D_80084C28[];
extern s32 D_80084C48;
extern u16 D_80084C4C;

void func_800171CC(s32 arg0_reg, s32 arg1_reg, s32 arg2_reg, void *arg3) {
    s8 arg0 = (s8) arg0_reg;
    s8 arg1 = (s8) arg1_reg;
    s8 arg2 = (s8) arg2_reg;
    s32 temp_a0;
    s32 temp_a1;

    *(D_80084B90 + (D_80084BAC * 0x10)) = arg0;
    *(D_80084B91 + (D_80084BAC * 0x10)) = arg1;
    *(D_80084B92 + (D_80084BAC * 0x10)) = arg2;
    temp_a0 = D_80084BAC * 2;
    temp_a1 = D_80084BAC * 0x10;
    *(D_80084B94 + temp_a1) = *(D_80084C24 + temp_a0);
    *(D_80084B9A + temp_a1) = D_80084C4C;
    *(D_80084B96 + temp_a1) = *(D_80084C28 + temp_a0);
    if (D_80084C1D != 0) {
        *(D_80084B98 + temp_a1) = (s16) ((s32) (D_80084C48 * 3) / 2);
    } else {
        *(D_80084B98 + temp_a1) = (u16) D_80084C48;
    }
    AddPrim(M2C_FIELD(arg3, s32 *, 0x10), (s32) ((D_80084BAC * 0x10) + D_80084B8C));
}
