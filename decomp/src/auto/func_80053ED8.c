#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s32 D_8007CBAC;
extern s32 D_8007CBB0;


void func_80053ED8(void *arg0) {
    s16 temp_v0;
    void *temp_a1;
    void *temp_v0_2;
    void *temp_v0_3;
    void *temp_v1;

    temp_v0 = M2C_FIELD(arg0, s16 *, 0x70);
    temp_a1 = arg0 + 0x74;
    switch (temp_v0) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 6:
    case 7:
        break;
    case 5:
        if (M2C_FIELD(temp_a1, s32 *, 0x20) != 0) {
            D_8007CBB0 = 0;
        } else {
            D_8007CBAC = 0;
        }
        break;
    case 4:
        temp_v0_2 = M2C_FIELD(temp_a1, void **, 0x30);
        if (temp_v0_2 != NULL) {
            M2C_FIELD(temp_v0_2, s32 *, 0x8C) = 0;
        }
        break;
    case 8:
        temp_v0_3 = M2C_FIELD(arg0, void **, 0x6C);
        temp_v1 = temp_v0_3 + 0x1C;
        M2C_FIELD(temp_v0_3, s32 *, 0x1C) = 0;
        M2C_FIELD(temp_v1, s32 *, 8) = 0;
        M2C_FIELD(temp_v1, s32 *, 4) = 0x640000;
        M2C_FIELD(temp_v1, s32 *, 0xC) = 0;
        M2C_FIELD(temp_v1, s32 *, 0x14) = 0;
        M2C_FIELD(temp_v1, s32 *, 0x10) = 0x640000;
        break;
    }
    thunk_FUN_8004866c((s32) arg0);
}
