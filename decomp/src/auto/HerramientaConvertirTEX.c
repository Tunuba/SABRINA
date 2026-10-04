#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u8 D_8007A1D0[];
extern u8 D_8007C7B8[];
extern u8 D_8007C7C0[];


void HerramientaConvertirTEX(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6_reg, s32 arg7, M2C_UNK arg8, s32 arg9, s32 arg10, s32 arg11, s32 arg12, s32 arg13, s32 arg14, s32 arg15, s32 arg16, s32 arg17, s32 arg18, s32 arg19, s32 arg20, s32 arg21, s32 arg22, s32 arg23, s32 arg24, s32 arg25, s32 arg26, s32 arg27, s32 arg28, s32 arg29, s32 arg30, s32 arg31, s32 arg32, s32 arg33, s32 arg34, s32 arg35, s32 arg36, s32 arg37, s32 arg38, s32 arg39, M2C_UNK arg40) {
    s16 arg6 = (s16) arg6_reg;
    s32 temp_s0;
    void *temp_v0;

    arg6 = M2C_FIELD(D_8007C7B8, s16 *, 0);
    arg6 = M2C_FIELD(D_8007C7B8, s16 *, 2);
    arg7 = M2C_FIELD(D_8007C7B8, s16 *, 4);
    arg7 = M2C_FIELD(D_8007C7B8, s16 *, 6);
    sprintf((s32) &arg8, (s32) D_8007C7C0, D_8007A1D0, arg0);
    temp_v0 = func_80014FF0((s32) &arg8, 0x2E);
    M2C_FIELD(temp_v0, s8 *, 1) = 0x54;
    M2C_FIELD(temp_v0, s8 *, 2) = 0x45;
    M2C_FIELD(temp_v0, s8 *, 3) = 0x58;
    temp_s0 = func_800294F0((s32) &arg8);
    func_80012ECC((s32) &arg6, (s32) &arg40);
    func_80012D74(0);
    func_80029530(temp_s0, (s32) &arg40);
    func_80029518(temp_s0);
}
