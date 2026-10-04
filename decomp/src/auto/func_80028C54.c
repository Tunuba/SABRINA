#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"



s32 func_80028C54(void *arg0) {
    s32 var_a1;
    s32 var_v0;
    u8 temp_v0;
    u8 temp_v1;
    void *var_v1;

    var_v0 = 1;
    if (M2C_FIELD(arg0, u16 *, 0xE6) != 0) {
        if (M2C_FIELD(arg0, s32 *, 0xC) != 0) {
            var_v0 = 1;
            if (M2C_FIELD(arg0, u8 *, 0x46) == 0xFF) {
                var_a1 = 0;
                var_v1 = M2C_FIELD(M2C_FIELD(arg0, void **, 0x10), void **, 0xC);
loop_4:
                temp_v0 = M2C_FIELD(var_v1, u8 *, 0x46);
                if ((temp_v0 == 0xFF) || (var_v0 = 1, (temp_v0 == 0))) {
                    var_a1 += 1;
                    var_v1 += 0xF0;
                    if (var_a1 >= 4) {
                        return 0;
                    }
                    goto loop_4;
                }
                /* Duplicate return node #11. Try simplifying control flow for better match */
                return var_v0;
            }
            /* Duplicate return node #11. Try simplifying control flow for better match */
            return var_v0;
        }
        temp_v1 = M2C_FIELD(M2C_FIELD(arg0, void **, 0x10), u8 *, 0x46);
        if ((temp_v1 != 0xFF) || (var_v0 = 0, (M2C_FIELD(arg0, u8 *, 0x46) != temp_v1))) {
            var_v0 = 1;
        }
        /* Duplicate return node #11. Try simplifying control flow for better match */
        return var_v0;
    }
    return var_v0;
}
