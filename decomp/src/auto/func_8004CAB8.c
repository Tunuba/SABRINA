#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s8 nivel_actual;
extern u32 D_8007CB3C;
extern s32 D_8007CB40;


void func_8004CAB8(void) {
    s32 var_s1;
    u32 var_s0;
    void *temp_a0;

    if (nivel_actual == 0xD) {
        var_s0 = 0;
        var_s1 = 0;
loop_6:
        if (var_s0 < (u32) D_8007CB3C) {
            temp_a0 = var_s1 + D_8007CB40;
            if ((M2C_FIELD(temp_a0, s16 *, 0xC) == 0x19) && (M2C_FIELD(temp_a0, s16 *, 0x1A) == 0)) {
                CrearObjetoMundo((s32) temp_a0);
            }
            var_s0 += 1;
            var_s1 += 0x9C;
            goto loop_6;
        }
    }
}
