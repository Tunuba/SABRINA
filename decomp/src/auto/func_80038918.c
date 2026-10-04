#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"


extern s32 func_80024DEC();
extern s32 func_80024DF4();
extern s32 func_80024F74();
extern s32 func_80024F84();
extern s32 func_80039670();

void func_80038918(void *arg0) {
    s32 temp_v0;

    if (!(M2C_FIELD(arg0, s16 *, 0x112) & 0x8000)) {
        temp_v0 = func_800252A0(0x24, (s32) arg0, 0, -0x50000, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ arg0, /* extra? */ arg0);
        if (temp_v0 != 0) {
            M2C_FIELD(arg0, s32 *, 0x11C) = temp_v0;
            M2C_FIELD(arg0, s16 *, 0x112) = 0;
            M2C_FIELD(arg0, s16 *, 0x114) = 0;
            M2C_FIELD(arg0, s16 *, 0x112) = -0x8000;
            M2C_FIELD(arg0, s32 (**)(), 0) = func_80024DEC;
            M2C_FIELD(arg0, s32 (**)(), 4) = func_80024DF4;
            M2C_FIELD(arg0, s32 (**)(s32, s32), 8) = func_80039670;
            M2C_FIELD(arg0, s32 (**)(), 0xC) = func_80024F74;
            M2C_FIELD(arg0, s32 (**)(), 0x10) = func_80024F84;
        }
    }
}
