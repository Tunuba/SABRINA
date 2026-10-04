#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"


extern s32 func_80024F6C();
extern s32 func_80038154();

void func_80053138(void *arg0, void *arg1) {
    s32 sp44;
    s32 sp48;
    s32 sp4C;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 temp_v0_3;
    void *temp_s0;
    void *temp_v0_4;

    temp_s0 = arg0 + 0x74;
    if ((M2C_FIELD(arg1, u16 *, 0x22) == 5) && (M2C_FIELD(arg0, s16 *, 0x70) == 1) && (M2C_FIELD(temp_s0, s32 *, 0x14) == 0)) {
        temp_v0 = -M2C_FIELD(arg1, s32 *, 0x38);
        sp44 = temp_v0;
        temp_v0_2 = -M2C_FIELD(arg1, s32 *, 0x3C);
        sp48 = temp_v0_2;
        temp_v0_3 = -M2C_FIELD(arg1, s32 *, 0x40);
        sp4C = temp_v0_3;
        temp_v0_4 = func_800252A0(5, (s32) arg1, temp_v0, temp_v0_2, /* extra? */ temp_v0_3, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0);
        M2C_FIELD(temp_v0_4, s32 *, 0x38) = sp44;
        M2C_FIELD(temp_v0_4, s32 *, 0x3C) = sp48;
        M2C_FIELD(temp_v0_4, s32 *, 0x40) = sp4C;
        M2C_FIELD(temp_v0_4, s32 *, 0x7C) = 0xC8;
        M2C_FIELD(temp_v0_4, s32 (**)(s32), 0) = func_80038154;
        M2C_FIELD(temp_v0_4, s32 (**)(), 8) = func_80024F6C;
        M2C_FIELD(temp_v0_4, s16 *, 0x114) = (s16) (M2C_FIELD(temp_v0_4, s16 *, 0x114) | 2);
        M2C_FIELD(temp_v0_4, s16 *, 0x112) = (s16) (M2C_FIELD(temp_v0_4, s16 *, 0x112) | 0x1000);
        M2C_FIELD(temp_s0, s32 *, 0x14) = 1;
    }
}
