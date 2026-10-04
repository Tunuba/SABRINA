#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"


extern s32 func_80024F74();
extern s32 func_80024F84();
extern s32 func_80038F08();
extern s32 func_80039670();
extern s32 func_8003BBA8();

void func_80038C38(void *arg0) {
    s32 temp_v0;
    void *temp_v1;

    if (!(M2C_FIELD(arg0, s16 *, 0x112) & 0x8000)) {
        TocarSonido(0x23, 0, 0x2A, 0x7F);
        temp_v0 = func_800252A0(9, (s32) arg0, 0, 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 2, /* extra? */ 0xC8);
        if (temp_v0 != 0) {
            temp_v1 = temp_v0 + 0x74;
            M2C_FIELD(temp_v1, s32 (**)(s32, s32), 0x10) = func_80038F08;
            M2C_FIELD(temp_v1, void **, 0xC) = arg0;
            func_800399A0((s32) arg0, temp_v0);
            M2C_FIELD(arg0, s32 (**)(s32), 0) = func_8003BBA8;
            M2C_FIELD(arg0, s32 (**)(s32, s32), 8) = func_80039670;
            M2C_FIELD(arg0, s32 (**)(), 0xC) = func_80024F74;
            M2C_FIELD(arg0, s32 (**)(), 0x10) = func_80024F84;
            M2C_FIELD(arg0, s16 *, 0x112) = (s16) (M2C_FIELD(arg0, s16 *, 0x112) | ~0x7FFF);
            M2C_FIELD(arg0, s32 *, 0x11C) = temp_v0;
        }
    }
}
