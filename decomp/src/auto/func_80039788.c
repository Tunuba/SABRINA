#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"



void func_80039788(void *arg0) {
    s32 temp_s2;
    void *temp_s1;

    temp_s1 = arg0 + 0x74;
    temp_s2 = M2C_FIELD(temp_s1, s32 *, 0xC);
    if (M2C_FIELD(temp_s1, M2C_UNK (**)(void *, s32), 0x10) != NULL) {
        M2C_FIELD(arg0, u8 *, 0x20) = 0U;
        if (temp_s2 != 0) {
loop_4:
            if (!(M2C_FIELD(arg0, u8 *, 0x20) & 0x80)) {
                M2C_FIELD(temp_s1, M2C_UNK (**)(void *, s32), 0x10)(arg0, temp_s2);
                goto loop_4;
            }
        }
    }
    thunk_FUN_8004866c((s32) arg0);
}
