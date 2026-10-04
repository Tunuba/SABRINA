#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u8 D_800D588C[];

void func_8003BC04(void *arg0) {
    s32 sp24;

    M2C_FIELD(arg0, s16 *, 0x70) = 0;
    M2C_FIELD(arg0, s32 *, 0x74) = (s32) (D_800D588C + ((s16) M2C_FIELD(arg0, s32 *, 0x74) * 0x18));
    func_8002205C((s32) &sp24, (s32) M2C_FIELD(arg0, s16 *, 0x30), (s32) M2C_FIELD(arg0, s16 *, 0x32));
    M2C_FIELD(arg0, s32 *, 0x38) = sp24;
    M2C_FIELD(arg0, s32 *, 0x3C) = sp28;
    M2C_FIELD(arg0, s32 *, 0x40) = sp2C;
    if (M2C_FIELD(M2C_FIELD(arg0, s32 *, 0x74), s16 *, 0x10) == 0) {
        M2C_FIELD((arg0 + 0x74), s8 *, 4) = 1;
    }
}
