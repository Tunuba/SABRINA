#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u8 D_800C4E2E[];

s32 func_8002EFD0(s32 arg0) {
    s32 var_v0;
    void *temp_v0;

    temp_v0 = M2C_FIELD(arg0, void **, 0x1C);
    if (temp_v0 != NULL) {
        var_v0 = 0;
        if ((s32) M2C_FIELD(temp_v0, u8 *, 0x50) >= (*(D_800C4E2E + (M2C_FIELD(temp_v0, u8 *, 0x51) * 4)) - 2)) {
            return 1;
        }
        /* Duplicate return node #4. Try simplifying control flow for better match */
        return var_v0;
    }
    var_v0 = 1;
    return var_v0;
}
