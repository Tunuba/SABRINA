#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u16 D_800D5820;
extern u16 D_800D5822;
extern u32 D_800D5824;
extern u32 D_800D582C;
extern s16 D_800D5848;

s32 func_8005CEBC(void) {
    s32 sp18;
    void *sp1C;
    s32 temp_v0;
    s32 var_s0;
    u16 temp_v1_2;
    u32 temp_v1;

    var_s0 = 0x800000;
loop_3:
    if (StGetNext((s32) &sp18, (s32) &sp1C) == 0) {
        Afirmar((sp18 & 0x80000000) == 0x80000000);
        D_800D582C += 1;
        if ((D_800D5824 - M2C_FIELD(sp1C, u32 *, 8)) == 0xE) {
            func_8005D504();
        }
        temp_v1 = M2C_FIELD(sp1C, u32 *, 8);
        if ((u32) D_800D5824 < temp_v1) {
            D_800D5848 = 1;
            return sp18;
        }
        if (temp_v1 < (u32) D_800D582C) {
            D_800D5848 = 1;
            return sp18;
        }
        temp_v1_2 = M2C_FIELD(sp1C, u16 *, 0x10);
        if ((temp_v1_2 != D_800D5820) || (M2C_FIELD(sp1C, u16 *, 0x12) != D_800D5822)) {
            D_800D5820 = temp_v1_2;
            D_800D5822 = M2C_FIELD(sp1C, u16 *, 0x12);
        }
        return sp18;
    }
    temp_v0 = var_s0 - 1;
    var_s0 = temp_v0;
    if (temp_v0 == 0) {
        return 0;
    }
    goto loop_3;
}
