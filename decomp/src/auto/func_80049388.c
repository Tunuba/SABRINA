#include "objeto.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s32 D_8007CBA8;


void func_80049388(void *arg0, void *arg1, void *arg2, s32 arg3_reg) {
    s16 arg3 = (s16) arg3_reg;
    s32 sp2C;
    s32 sp30;
    s32 sp34;
    u16 temp_v0;
    u16 temp_v0_2;
    void *temp_s0;

    temp_s0 = M2C_FIELD(arg0, void **, 0x1C);
    func_800487B0((s32) arg0, (s32) p_sabrina, 0x96);
    sp2C = M2C_FIELD(arg0, s32 *, 0x24) - p_sabrina->x;
    sp30 = 0;
    sp34 = M2C_FIELD(arg0, s32 *, 0x2C) - p_sabrina->z;
    if (func_8001C180((s32) &sp2C) < 0x400) {
        temp_v0 = M2C_FIELD(arg2, u16 *, 0xE);
        if (M2C_FIELD(temp_s0, u8 *, 0x51) != temp_v0) {
            M2C_FIELD(temp_s0, u8 *, 0x51) = (u8) temp_v0;
            M2C_FIELD(temp_s0, u8 *, 0x50) = 0U;
            M2C_FIELD(temp_s0, s16 *, 0x4E) = 0x800;
            return;
        }
        if (D_8007CBA8 == 0) {
            M2C_FIELD(temp_s0, s16 *, 0x4E) = 0x800;
            if (((s32) M2C_FIELD(temp_s0, u8 *, 0x50) >= M2C_FIELD(arg1, s8 *, 0x23)) && (M2C_FIELD(arg1, s16 *, 0x42) == 0)) {
                M2C_FIELD(arg1, s16 *, 0x42) = 1;
                TocarSonido((s32) arg3, 0, 0x2A, 0x7F);
                if (func_80048374((s32) arg0, (s32) p_sabrina, M2C_FIELD(arg1, s32 *, 0xC)) == 1) {
                    func_800483E8((s32) arg0);
                }
            }
            if (func_8002EFD0((s32) arg0) != 0) {
                M2C_FIELD(temp_s0, u8 *, 0x51) = (u8) M2C_FIELD(arg2, u16 *, 0);
                M2C_FIELD(temp_s0, u8 *, 0x50) = 0U;
                goto block_12;
            }
        }
    } else {
        temp_v0_2 = M2C_FIELD(arg2, u16 *, 0);
        if (M2C_FIELD(temp_s0, u8 *, 0x51) != temp_v0_2) {
            M2C_FIELD(temp_s0, u8 *, 0x51) = (u8) temp_v0_2;
            M2C_FIELD(temp_s0, u8 *, 0x50) = 0U;
block_12:
            M2C_FIELD(arg1, s16 *, 0x42) = 0;
        }
    }
}
