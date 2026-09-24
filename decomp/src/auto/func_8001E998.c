#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s32 D_8007CA80;


void func_8001E998(s32 arg0) {
    void *temp_a0;
    void *temp_v1;

    temp_a0 = M2C_FIELD(arg0, void **, 0x1C);
    D_8007CA80 = temp_a0 + 0xA;
    temp_v1 = M2C_FIELD(M2C_FIELD(arg0, void **, 0x60), void **, 4);
    M2C_FIELD(temp_v1, s32 *, 0x28) = (s32) M2C_FIELD(temp_a0, s16 *, 0);
    M2C_FIELD(temp_v1, s32 *, 0x2C) = (s32) M2C_FIELD(temp_a0, s16 *, 2);
    M2C_FIELD(temp_v1, s32 *, 0x30) = (s32) M2C_FIELD(temp_a0, s16 *, 4);
    func_8001E8F4((s32) temp_v1);
}
