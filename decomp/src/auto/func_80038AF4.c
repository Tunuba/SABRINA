#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s32 D_80086408;
extern s32 D_8007C9F0;
extern s32 func_80024F74();
extern s32 func_80038FAC();
extern s32 func_80039670();
extern s32 thunk_FUN_8001e588();
extern s32 thunk_FUN_8004866c();


void func_80038AF4(void *arg0) {
    s32 temp_v0;
    void *temp_s1;
    void *temp_v1;

    if (!(M2C_FIELD(arg0, s16 *, 0x112) & 0x8000)) {
        TocarSonido(0x25, 0, 0x2A, 0x7F);
        temp_v0 = func_800252A0(9, (s32) arg0, 0, 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 3, /* extra? */ 0xC8);
        if (temp_v0 != 0) {
            temp_s1 = temp_v0 + 0x74;
            func_800399A0((s32) arg0, temp_v0);
            M2C_FIELD(arg0, s32 (**)(), 0) = func_80024F74;
            M2C_FIELD(arg0, s32 (**)(s32, s32), 8) = func_80039670;
            M2C_FIELD(arg0, void (**)(s32), 0x14) = thunk_FUN_8001e588;
            M2C_FIELD(arg0, s32 (**)(s32), 0x18) = thunk_FUN_8004866c;
            M2C_FIELD(temp_s1, s32 (**)(s32, s32), 0x10) = func_80038FAC;
            M2C_FIELD(temp_s1, void **, 0xC) = arg0;
            M2C_FIELD(arg0, s16 *, 0x112) = (s16) (M2C_FIELD(arg0, s16 *, 0x112) | ~0x7FFF);
            M2C_FIELD(arg0, s32 *, 0x11C) = temp_v0;
            M2C_FIELD(temp_s1, void **, 0x40) = (void *) M2C_FIELD(arg0, void **, 0x60);
            temp_v1 = M2C_FIELD(temp_s1, void **, 0x40);
            M2C_FIELD(temp_v1, s32 *, 0x28) = 0;
            M2C_FIELD(temp_v1, s32 *, 0x2C) = 0x7E00;
            M2C_FIELD(temp_v1, s32 *, 0x30) = 0;
            M2C_FIELD(arg0, void **, 0x60) = func_8001E06C(D_80086408, D_8007C9F0);
            func_800206E0();
        }
    }
}
