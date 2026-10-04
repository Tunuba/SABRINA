#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"



static void *(*D_8006CF98)() = NULL;

s32 func_80027AD0(s32 arg0, s32 arg1, s32 arg2) {
    void *temp_v1;

    temp_v1 = D_8006CF98();
    if (arg1 != 3) {
        if (arg1 < 4) {
            if (arg1 != 1) {
                if (arg1 != 2) {
                    return 0;
                }
                return (s32) M2C_FIELD(temp_v1, u16 *, 0xE6);
            }
            return (s32) M2C_FIELD(temp_v1, u8 *, 0xE8);
        }
        if (arg1 != 4) {
            if (arg1 != 0x64) {
                return 0;
            }
            return M2C_FIELD(temp_v1, s32 *, 0x4C);
        }
        if (arg2 < 0) {
            return (s32) M2C_FIELD(temp_v1, u8 *, 0xE3);
        }
        if (arg2 < (s32) M2C_FIELD(temp_v1, u8 *, 0xE3)) {
            return (s32) *((arg2 * 2) + M2C_FIELD(temp_v1, s32 *, 0));
        }
        return 0;
    }
    return (s32) M2C_FIELD(temp_v1, u8 *, 0xE4);
}
