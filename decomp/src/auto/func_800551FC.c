#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"



void func_800551FC(void *arg0) {
    s32 sp1C;
    s32 sp20;
    s32 sp24;
    void *temp_v1;

    temp_v1 = arg0 + 0x74;
    M2C_FIELD(temp_v1, s32 *, 0xC) = 0;
    M2C_FIELD(temp_v1, s32 *, 8) = 0;
    M2C_FIELD(arg0, s32 *, 0x74) = 0x64;
    func_800483F8((s32) arg0);
    sp1C = M2C_FIELD(arg0, s32 *, 0x24);
    sp20 = (M2C_FIELD(arg0, s32 *, 0x28) - 0x6667) - 0x7FFF;
    sp24 = M2C_FIELD(arg0, s32 *, 0x2C);
    sp20 = func_800223E8((s32) &sp1C);
    if (sp20 != ((M2C_FIELD(arg0, s32 *, 0x28) - 0x6667) - 0x7FFF)) {
        M2C_FIELD(arg0, s32 *, 0x28) = sp20;
    }
    M2C_FIELD(arg0, s16 *, 0x70) = 0;
}
