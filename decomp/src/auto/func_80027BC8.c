#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern void *(*D_8006CF98)();


u8 func_80027BC8(s32 arg0, s32 arg1, s32 arg2) {
    void *temp_v1;
    void *temp_v1_2;

    temp_v1_2 = D_8006CF98();
    if (arg1 < 0) {
        return M2C_FIELD(temp_v1_2, u8 *, 0xE9);
    }
    if (arg1 < (s32) M2C_FIELD(temp_v1_2, u8 *, 0xE9)) {
        temp_v1 = M2C_FIELD(temp_v1_2, s32 *, 4) + (arg1 * 5);
        switch (arg2) {
        case 1:
            return M2C_FIELD(temp_v1, u8 *, 0);
        case 2:
            return M2C_FIELD(temp_v1, u8 *, 1);
        case 3:
            return M2C_FIELD(temp_v1, u8 *, 2);
        case 4:
            return M2C_FIELD(temp_v1, u8 *, 3);
        case 5:
            return M2C_FIELD(temp_v1, u8 *, 4);
        }
    } else {
    default:
        return 0U;
    }
}
