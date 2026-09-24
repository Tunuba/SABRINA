#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s16 D_8006379C;
extern s16 D_8006379E;


void func_800113DC(s32 arg0, s32 arg1) {
    u16 sp10;
    u16 sp12;
    u16 sp14;
    u16 sp16;
    s32 var_t0;
    u16 temp_a0;
    u16 var_v0;
    u16 var_v0_2;

    M2C_FIELD(arg0, s32 *, 4) = func_8001166C((s32) M2C_FIELD(arg1, s16 *, 0), (s32) M2C_FIELD(arg1, s16 *, 2));
    M2C_FIELD(arg0, s32 *, 8) = func_80011704((s32) (s16) ((M2C_FIELD(arg1, u16 *, 4) + (u16) M2C_FIELD(arg1, s16 *, 0)) - 1), (s32) (s16) (((u16) M2C_FIELD(arg1, s16 *, 2) + M2C_FIELD(arg1, u16 *, 6)) - 1));
    M2C_FIELD(arg0, s32 *, 0xC) = func_8001179C((s32) M2C_FIELD(arg1, s16 *, 8), (s32) M2C_FIELD(arg1, s16 *, 0xA));
    M2C_FIELD(arg0, s32 *, 0x10) = func_8001164C((s32) M2C_FIELD(arg1, u8 *, 0x17), (s32) M2C_FIELD(arg1, u8 *, 0x16), (s32) M2C_FIELD(arg1, u16 *, 0x14));
    M2C_FIELD(arg0, s32 *, 0x14) = func_800117B8(arg1 + 0xC);
    M2C_FIELD(arg0, s32 *, 0x18) = 0xE6000000;
    var_t0 = 7;
    if (M2C_FIELD(arg1, u8 *, 0x18) != 0) {
        sp10 = (u16) M2C_FIELD(arg1, s16 *, 0);
        sp12 = (u16) M2C_FIELD(arg1, s16 *, 2);
        temp_a0 = M2C_FIELD(arg1, u16 *, 4);
        sp14 = temp_a0;
        sp16 = M2C_FIELD(arg1, u16 *, 6);
        var_v0 = 0;
        if ((s16) temp_a0 >= 0) {
            var_v0 = (u16) D_8006379C - 1;
            if ((D_8006379C - 1) >= (s16) temp_a0) {
                var_v0 = temp_a0;
            }
        }
        sp14 = var_v0;
        if ((s16) sp16 >= 0) {
            var_v0_2 = (u16) D_8006379E - 1;
            if ((D_8006379E - 1) >= (s16) sp16) {
                var_v0_2 = sp16;
            }
        } else {
            var_v0_2 = 0;
        }
        sp16 = var_v0_2;
        if ((sp10 & 0x3F) || (sp14 & 0x3F)) {
            var_t0 = 0xA;
            sp10 -= (u16) M2C_FIELD(arg1, s16 *, 8);
            sp12 -= (u16) M2C_FIELD(arg1, s16 *, 0xA);
            *((7 * 4) + arg0) = (M2C_FIELD(arg1, u8 *, 0x1B) << 0x10) | ((M2C_FIELD(arg1, u8 *, 0x1A) << 8) | 0x60000000) | M2C_FIELD(arg1, u8 *, 0x19);
            *((8 * 4) + arg0) = (s32) sp10;
            *((9 * 4) + arg0) = (s32) sp14;
        } else {
            var_t0 = 0xA;
            *((7 * 4) + arg0) = (M2C_FIELD(arg1, u8 *, 0x1B) << 0x10) | ((M2C_FIELD(arg1, u8 *, 0x1A) << 8) | 0x02000000) | M2C_FIELD(arg1, u8 *, 0x19);
            *((8 * 4) + arg0) = (s32) sp10;
            *((9 * 4) + arg0) = (s32) sp14;
        }
    }
    M2C_FIELD(arg0, s8 *, 3) = (s8) (var_t0 - 1);
}
