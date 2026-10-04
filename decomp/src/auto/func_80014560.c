#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s32 D_80063824[];


u16 func_80014560(s32 arg0) {
    s32 temp_v1;

    temp_v1 = arg0 & 0xFFFF;
    if (temp_v1 < 3) {
        return *((temp_v1 * 0x10) + *D_80063824);
    }
    return 0U;
}
