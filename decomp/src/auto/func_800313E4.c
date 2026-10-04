#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u8 D_8008AF88[];
extern u8 D_8008AFD8[];

void func_800313E4(void) {
    s32 var_a0;
    u16 temp_v0;
    u8 *var_v1;

    var_v1 = D_8008AFD8;
    var_a0 = 0;
loop_11:
    if (var_a0 < 0x50) {
        if (((s8) D_8008AF88[var_a0] != 0) && ((temp_v0 = M2C_FIELD(var_v1, u16 *, 0x22), (temp_v0 == 0x11)) || (temp_v0 == 0xF) || (temp_v0 == 2) || (temp_v0 == 0x2F) || (temp_v0 == 0x16) || (temp_v0 == 0x10) || (temp_v0 == 0xE))) {
            M2C_FIELD(var_v1, u8 *, 0x20) = (u8) (M2C_FIELD(var_v1, u8 *, 0x20) | 0x80);
        }
        var_a0 += 1;
        var_v1 += 0x120;
        goto loop_11;
    }
}
