#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u8 D_800C4E2E[];

void func_8002EF8C(s32 arg0) {
    void *temp_a1;

    temp_a1 = M2C_FIELD(arg0, void **, 0x1C);
    if ((s32) M2C_FIELD(temp_a1, u8 *, 0x50) >= (*(D_800C4E2E + (M2C_FIELD(temp_a1, u8 *, 0x51) * 4)) - 1)) {
        M2C_FIELD(temp_a1, u8 *, 0x50) = 0U;
    }
}
