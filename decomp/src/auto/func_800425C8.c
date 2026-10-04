#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s32 D_800C6E60;
extern u8 D_800C6FC0[];
extern u8 D_800C6FC2[];
extern u8 D_800C6FCE[];
extern u8 D_800C6FD0[];
extern u8 D_800C6FD2[];
extern u8 D_800C6FD4[];
extern u8 D_800C6FD6[];
extern u8 D_800C6FD8[];
extern u8 D_800C6FDD[];
extern u8 D_800C6FF6[];
extern u8 D_800C76EE[];
extern u8 D_800C76F8[];
extern s32 D_800C7848;
extern s32 D_800C784C;

void func_800425C8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4_reg, s32 arg5_reg, s32 arg6, s32 arg7) {
    u16 arg4 = (u16) arg4_reg;
    u16 arg5 = (u16) arg5_reg;
    u16 sp10;
    s32 temp_v1_2;
    s32 var_v0;
    u16 temp_a0;
    void *temp_v0;
    void *temp_v1;

    sp10 = (u16) arg1;
    if (D_800C6E60 == 1) {
        return;
    }
    D_800C6E60 = 1;
    if (((u32) (arg0 & 0xFFFF) < 0x18U) && (_SsVmVSetUp((s32) (s16) arg1, (s32) (s16) arg2) == 0)) {
        M2C_FIELD(D_800C76F8, s16 *, 0) = 0x21;
        M2C_FIELD(D_800C76F8, s8 *, -0x12) = (s8) arg4;
        M2C_FIELD(D_800C76F8, s8 *, -0x11) = (s8) arg5;
        M2C_FIELD(D_800C76F8, s8 *, -8) = (s8) arg3;
        if ((s16) arg6 == (s16) arg7) {
            M2C_FIELD(D_800C76F8, s8 *, -0xF) = 0x40;
            M2C_FIELD(D_800C76F8, s8 *, -0x10) = (s8) arg6;
        } else {
            if ((s16) arg7 < (s16) arg6) {
                var_v0 = (s32) ((s16) arg7 << 6) / (s16) arg6;
                M2C_FIELD(D_800C76F8, s8 *, -0x10) = (s8) arg6;
            } else {
                M2C_FIELD(D_800C76F8, s8 *, -0x10) = (s8) arg7;
                var_v0 = 0x7F - ((s32) ((s16) arg6 << 6) / (s16) arg7);
            }
            M2C_FIELD(D_800C76F8, s8 *, -0xF) = (s8) var_v0;
        }
        temp_v1 = ((s32) (arg2 << 0x10) >> 0xC) + D_800C7848;
        M2C_FIELD(D_800C76EE, u8 *, 0) = M2C_FIELD(temp_v1, u8 *, 1);
        M2C_FIELD(D_800C76EE, u8 *, 1) = (u8) M2C_FIELD(temp_v1, u8 *, 4);
        M2C_FIELD(D_800C76EE, u8 *, -0xA) = (u8) M2C_FIELD(temp_v1, u8 *, 0);
        temp_v0 = ((s32) (((s8) M2C_FIELD(D_800C76EE, u8 *, 2) + (M2C_FIELD(D_800C76EE, s8 *, -3) * 0x10)) << 0x10) >> 0xB) + D_800C784C;
        M2C_FIELD(D_800C76EE, u8 *, 5) = (u8) M2C_FIELD(temp_v0, u8 *, 0);
        temp_a0 = M2C_FIELD(temp_v0, u16 *, 0x16);
        M2C_FIELD(D_800C76EE, u16 *, 0xC) = temp_a0;
        M2C_FIELD(D_800C76EE, u8 *, 3) = (u8) M2C_FIELD(temp_v0, u8 *, 2);
        M2C_FIELD(D_800C76EE, u8 *, 4) = (u8) M2C_FIELD(temp_v0, u8 *, 3);
        M2C_FIELD(D_800C76EE, u8 *, 6) = (u8) M2C_FIELD(temp_v0, u8 *, 4);
        M2C_FIELD(D_800C76EE, u8 *, 7) = (u8) M2C_FIELD(temp_v0, u8 *, 5);
        M2C_FIELD(D_800C76EE, u8 *, 8) = (u8) M2C_FIELD(temp_v0, u8 *, 1);
        if (temp_a0 == 0) {
            goto block_11;
        }
        temp_v1_2 = (s16) arg0 * 0x38;
        M2C_FIELD(D_800C76EE, s16 *, 0xE) = (s16) arg0;
        *(D_800C6FD0 + temp_v1_2) = 0x21;
        *(D_800C6FD8 + temp_v1_2) = sp10;
        *(D_800C6FD4 + temp_v1_2) = (s16) arg2;
        *(D_800C6FD2 + temp_v1_2) = (s16) (s8) (u8) M2C_FIELD(D_800C76EE, s8 *, -3);
        *(D_800C6FC0 + temp_v1_2) = M2C_FIELD(D_800C76EE, u16 *, 0xC);
        *(D_800C6FCE + temp_v1_2) = arg4;
        *(D_800C6FDD + temp_v1_2) = 1;
        *(D_800C6FC2 + temp_v1_2) = 0;
        *(D_800C6FD6 + temp_v1_2) = (s16) (s8) M2C_FIELD(D_800C76EE, u8 *, 2);
        *(D_800C6FF6 + temp_v1_2) = (s16) (s8) M2C_FIELD(D_800C76EE, u8 *, -6);
        _SsVmDoAllocate();
        if ((s16) M2C_FIELD(D_800C76EE, u16 *, 0xC) == 0xFF) {
            vmNoiseOn(arg0 & 0xFF);
        } else {
            _SsVmKeyOnNow(1, func_80043358((s32) arg4, (s32) arg5) & 0xFFFF);
        }
        D_800C6E60 = 0;
        return;
    }
block_11:
    D_800C6E60 = 0;
}
