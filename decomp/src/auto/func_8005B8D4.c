#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"


extern s32 func_80024DE4();
extern s32 func_80024DF4();
extern s32 func_80024F6C();
extern s32 func_80024F74();
extern s32 thunk_FUN_8001e588();
extern s32 thunk_FUN_8004866c();

s32 func_8005B8D4(s32 arg0) {
    void *temp_v0;

    temp_v0 = func_800252A0(5, arg0, 0, -0x4000, /* extra? */ 0x6666, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0);
    M2C_FIELD(temp_v0, s32 (**)(), 0) = func_80024DE4;
    M2C_FIELD(temp_v0, s32 (**)(), 4) = func_80024DF4;
    M2C_FIELD(temp_v0, s32 (**)(), 8) = func_80024F6C;
    M2C_FIELD(temp_v0, s32 (**)(), 0xC) = func_80024F74;
    M2C_FIELD(temp_v0, s32 (**)(), 0x10) = func_80024F6C;
    M2C_FIELD(temp_v0, void (**)(s32), 0x14) = thunk_FUN_8001e588;
    M2C_FIELD(temp_v0, s32 (**)(s32), 0x18) = thunk_FUN_8004866c;
    M2C_FIELD(temp_v0, s32 *, 0x54) = 5;
    M2C_FIELD(temp_v0, s32 *, 0x58) = 5;
    M2C_FIELD(temp_v0, s32 *, 0x5C) = 5;
    M2C_FIELD(temp_v0, s16 *, 0x112) = 0;
    M2C_FIELD(temp_v0, s16 *, 0x114) = 0;
    return (s32) temp_v0;
}
