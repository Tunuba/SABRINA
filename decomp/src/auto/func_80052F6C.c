#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u8 D_80086324[];
extern s32 D_8007CA24;


void func_80052F6C(void *arg0) {
    void *temp_v1;

    temp_v1 = arg0 + 0x74;
    M2C_FIELD(temp_v1, s32 *, 0xC) = 0;
    M2C_FIELD(temp_v1, s32 *, 4) = 0x800;
    M2C_FIELD(temp_v1, s32 *, 8) = 0;
    M2C_FIELD(arg0, s32 *, 0x74) = 0x15E;
    M2C_FIELD(temp_v1, s32 *, 0x14) = 0;
    M2C_FIELD(temp_v1, s32 *, 0x18) = 0;
    *(D_80086324 + (D_8007CA24 * 4)) = arg0;
    D_8007CA24 += 1;
}
