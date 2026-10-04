#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern void *(*D_8006CF98)();


u8 func_80027C9C(s32 arg0, s32 arg1, s32 arg2) {
    void *temp_v1;
    void *temp_v1_2;

    temp_v1_2 = D_8006CF98();
    if (arg1 < 0) {
        return M2C_FIELD(temp_v1_2, u8 *, 0xEA);
    }
    if (arg1 < (s32) M2C_FIELD(temp_v1_2, u8 *, 0xEA)) {
        temp_v1 = M2C_FIELD(temp_v1_2, s32 *, 8) + (arg1 * 8);
        if (arg2 < 0) {
            return M2C_FIELD(temp_v1, u8 *, 0);
        }
        if (arg2 < (s32) M2C_FIELD(temp_v1, u8 *, 0)) {
            return *(M2C_FIELD(temp_v1, s32 *, 4) + arg2);
        }
        /* Duplicate return node #8. Try simplifying control flow for better match */
        return 0U;
    }
    return 0U;
}
