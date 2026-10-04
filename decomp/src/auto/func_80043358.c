#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u8 D_800C76EB[];
extern s32 D_800C784C;

s32 func_80043358(s32 arg0, s32 arg1) {
    void *temp_v0;

    temp_v0 = ((s32) (((s8) M2C_FIELD(D_800C76EB, u8 *, 5) + ((s8) M2C_FIELD(D_800C76EB, u8 *, 0) * 0x10)) << 0x10) >> 0xB) + D_800C784C;
    return func_800433C0((s32) (s16) arg0, (s32) (s16) arg1, (s32) M2C_FIELD(temp_v0, u8 *, 4), (s32) M2C_FIELD(temp_v0, u8 *, 5)) & 0xFFFF;
}
