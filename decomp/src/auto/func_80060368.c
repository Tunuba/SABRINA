#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"


extern s32 func_80024DEC();
extern s32 func_80024DF4();
extern s32 func_80024F6C();
extern s32 func_80060274();
extern s32 thunk_FUN_8001e588();
extern s32 thunk_FUN_8004866c();

void func_80060368(s32 arg0) {
    s32 temp_v0_2;
    void *temp_s1;
    void *temp_v0;

    temp_s1 = arg0 + 0x74;
    M2C_FIELD(temp_s1, s32 *, 0x14) = (s32) (M2C_FIELD(temp_s1, s32 *, 0x14) - 1);
    if (M2C_FIELD(temp_s1, s32 *, 0x14) < 0) {
        M2C_FIELD(temp_s1, s32 *, 0x14) = (s32) M2C_FIELD(temp_s1, s32 *, 0x10);
        temp_v0 = func_800252A0(0xC, arg0, 0, 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0);
        M2C_FIELD(temp_v0, s32 (**)(s32), 0) = func_80060274;
        M2C_FIELD(temp_v0, s32 (**)(), 4) = func_80024DF4;
        M2C_FIELD(temp_v0, s32 (**)(), 8) = func_80024F6C;
        M2C_FIELD(temp_v0, s32 (**)(), 0xC) = func_80024DEC;
        M2C_FIELD(temp_v0, s32 (**)(), 0x10) = func_80024F6C;
        M2C_FIELD(temp_v0, void (**)(s32), 0x14) = thunk_FUN_8001e588;
        M2C_FIELD(temp_v0, s32 (**)(s32), 0x18) = thunk_FUN_8004866c;
        func_8002205C((s32) (temp_v0 + 0x38), (s32) M2C_FIELD(arg0, s16 *, 0x30), (s32) M2C_FIELD(arg0, s16 *, 0x32));
        M2C_FIELD(temp_v0, s32 *, 0x38) = (s32) (((s32) (((s32) M2C_FIELD(temp_v0, s32 *, 0x38) >> 4) * ((s32) M2C_FIELD(temp_s1, s32 *, 0xC) >> 8)) >> 8) << 8);
        M2C_FIELD(temp_v0, s32 *, 0x3C) = (s32) (((s32) (((s32) M2C_FIELD(temp_v0, s32 *, 0x3C) >> 4) * ((s32) M2C_FIELD(temp_s1, s32 *, 0xC) >> 8)) >> 8) << 8);
        M2C_FIELD(temp_v0, s32 *, 0x40) = (s32) (((s32) (((s32) M2C_FIELD(temp_v0, s32 *, 0x40) >> 4) * ((s32) M2C_FIELD(temp_s1, s32 *, 0xC) >> 8)) >> 8) << 8);
        M2C_FIELD(temp_v0, s32 *, 0x74) = (s32) M2C_FIELD(arg0, s32 *, 0x74);
        M2C_FIELD(temp_v0, s32 *, 0x78) = (s32) M2C_FIELD(temp_s1, s32 *, 8);
        M2C_FIELD(temp_v0, s32 *, 0x7C) = (s32) M2C_FIELD(temp_s1, s32 *, 4);
        temp_v0_2 = M2C_FIELD(temp_s1, s32 *, 4);
        switch (temp_v0_2) {                        /* irregular */
        case -1:
            func_800249CC((s32) temp_v0, -1);
            M2C_FIELD(arg0, s32 *, 0x54) = 3;
            M2C_FIELD(arg0, s32 *, 0x58) = 3;
            M2C_FIELD(arg0, s32 *, 0x5C) = 3;
            return;
        case 0:
            M2C_FIELD(arg0, s32 *, 0x54) = 3;
            M2C_FIELD(arg0, s32 *, 0x58) = 3;
            M2C_FIELD(arg0, s32 *, 0x5C) = 3;
            return;
        case 1:
            func_800249CC((s32) temp_v0, 0x32);
            break;
        }
    }
}
