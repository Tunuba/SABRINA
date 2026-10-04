#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u8 D_80086338[];
extern s32 D_8007CA28;


void func_800537C4(void *arg0) {
    void *temp_a1;

    temp_a1 = arg0 + 0x74;
    *(D_80086338 + (D_8007CA28 * 4)) = arg0;
    D_8007CA28 += 1;
    M2C_FIELD(temp_a1, s16 *, 8) = (s16) M2C_FIELD(arg0, s16 *, 0x114);
    M2C_FIELD(temp_a1, s16 *, 0xA) = (s16) M2C_FIELD(arg0, s16 *, 0x112);
}
