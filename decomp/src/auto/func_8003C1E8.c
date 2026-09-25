#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s32 D_800C6594;
extern s32 D_800C6598;
extern s32 D_800C659C;
extern s32 D_800C65A0;
extern s32 D_800C65A4;
extern s32 D_800C65A8;
extern s32 func_80024DF4();
extern s32 func_80024F74();
extern s32 func_80024F84();
extern s32 func_8003BFC4();
extern s32 func_8003BFEC();
extern s32 thunk_FUN_8001e588();
extern s32 thunk_FUN_8004866c();


void func_8003C1E8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4_reg, s32 arg5_reg, s32 arg6_reg, s32 arg7_reg) {
    s16 arg4 = (s16) arg4_reg;
    s16 arg5 = (s16) arg5_reg;
    s16 arg6 = (s16) arg6_reg;
    s16 arg7 = (s16) arg7_reg;
    s32 sp58;
    s32 sp5C;
    s32 sp60;
    s32 sp64;
    s32 sp68;
    s32 sp6C;
    s32 temp_a0;
    s32 temp_v0;
    s32 temp_v1;
    s32 temp_v1_2;
    void *temp_v0_2;

    temp_v0 = func_800252A0(0xC, arg0, M2C_FIELD(arg1, s32 *, 0), M2C_FIELD(arg1, s32 *, 4), /* extra? */ M2C_FIELD(arg1, s32 *, 8), /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 1, /* extra? */ 1);
    if (temp_v0 != 0) {
        temp_v0_2 = temp_v0 + 0x74;
        M2C_FIELD(temp_v0_2, s16 *, 0x24) = arg5;
        M2C_FIELD(temp_v0_2, s16 *, 0x20) = arg6;
        M2C_FIELD(temp_v0_2, s8 *, 0x12) = (s8) arg3;
        M2C_FIELD(temp_v0_2, s16 *, 0x22) = arg4;
        M2C_FIELD(temp_v0_2, s16 *, 0x26) = arg7;
        func_800249CC(temp_v0, -1);
        M2C_FIELD(temp_v0, s32 (**)(s32), 0) = func_8003BFEC;
        M2C_FIELD(temp_v0, s32 (**)(), 4) = func_80024DF4;
        M2C_FIELD(temp_v0, s32 (**)(s32, s32), 8) = func_8003BFC4;
        M2C_FIELD(temp_v0, s32 (**)(), 0xC) = func_80024F74;
        M2C_FIELD(temp_v0, s32 (**)(), 0x10) = func_80024F84;
        M2C_FIELD(temp_v0, void (**)(s32), 0x14) = thunk_FUN_8001e588;
        M2C_FIELD(temp_v0, s32 (**)(s32), 0x18) = thunk_FUN_8004866c;
        M2C_FIELD(temp_v0, s16 *, 0x112) = 0x801;
        M2C_FIELD(temp_v0, s16 *, 0x114) = 1;
        M2C_FIELD(temp_v0, s8 *, 0x119) = 1;
        sp64 = p_sabrina->x;
        sp68 = (p_sabrina->y - 0xCCD) - 0x7FFF;
        sp6C = p_sabrina->z;
        func_80048CF4(temp_v0, (s32) &sp64, 0x4000, (s32) &sp58);
        M2C_FIELD(temp_v0, s32 *, 0x38) = sp58;
        M2C_FIELD(temp_v0, s32 *, 0x3C) = sp5C;
        M2C_FIELD(temp_v0, s32 *, 0x40) = sp60;
        func_8001C45C((s32) &sp58);
        temp_a0 = sp58 >> 4;
        sp64 = ((s32) (temp_a0 * 0xCC) >> 8) << 8;
        temp_v1 = ((s32) ((sp5C >> 4) * 0xCC) >> 8) << 8;
        sp68 = temp_v1;
        temp_v1_2 = ((s32) ((sp60 >> 4) * 0xCC) >> 8) << 8;
        sp6C = temp_v1_2;
        sp58 = (s32) (temp_a0 * 0x280) >> 8;
        sp5C = (s32) ((sp5C >> 4) * 0x280) >> 8;
        sp60 = (s32) ((sp60 >> 4) * 0x280) >> 8;
        D_800C6594 = M2C_FIELD(temp_v0, s32 *, 0x24);
        D_800C6598 = M2C_FIELD(temp_v0, s32 *, 0x28);
        D_800C659C = M2C_FIELD(temp_v0, s32 *, 0x2C);
        D_800C6594 -= sp64;
        D_800C6598 -= temp_v1;
        D_800C659C -= temp_v1_2;
        D_800C65A0 = M2C_FIELD(temp_v0, s32 *, 0x24) + M2C_FIELD(temp_v0, s32 *, 0x38);
        D_800C65A4 = M2C_FIELD(temp_v0, s32 *, 0x28) + M2C_FIELD(temp_v0, s32 *, 0x3C);
        D_800C65A8 = M2C_FIELD(temp_v0, s32 *, 0x2C) + M2C_FIELD(temp_v0, s32 *, 0x40);
        func_8003B38C((s32) &D_800C6594, (s32) &D_800C6594, (s32) &D_800C65A0);
        if (func_8003AE84() != 0) {
            M2C_FIELD(temp_v0, u8 *, 0x20) = (u8) (M2C_FIELD(temp_v0, u8 *, 0x20) | 0x80);
        }
    }
}
