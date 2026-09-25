#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u8 D_8008AF88[];
extern u8 D_8008AFD8[];
extern s32 D_8007CB44;
extern s32 func_8002579C();


s32 func_800256E0(void) {
    s32 var_a1;
    u8 *temp_a0;
    void *var_s0;

    var_s0 = NULL;
    var_a1 = 0;
loop_4:
    if (var_a1 < 0x50) {
        temp_a0 = &D_8008AF88[var_a1];
        if ((s8) *temp_a0 == 0) {
            var_s0 = D_8008AFD8 + (var_a1 * 0x120);
            *temp_a0 = 1;
            memset((s32) var_s0, 0, 0x120);
            M2C_FIELD(var_s0, s32 (**)(), 0) = func_8002579C;
            M2C_FIELD(var_s0, s32 (**)(), 4) = func_8002579C;
            M2C_FIELD(var_s0, s32 (**)(), 0x14) = func_8002579C;
            M2C_FIELD(var_s0, s32 (**)(), 0x18) = func_8002579C;
            D_8007CB44 += 1;
        } else {
            var_a1 += 1;
            goto loop_4;
        }
    }
    return (s32) var_s0;
}
