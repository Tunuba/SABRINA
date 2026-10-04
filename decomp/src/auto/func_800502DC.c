#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u8 D_800D52C0[];
extern u8 D_800D52D4[];
extern s32 D_80075B2C;


s32 func_800502DC(s32 *arg0) {
    s32 temp_v0;
    s32 temp_v1;
    s32 var_a0;

    temp_v1 = *arg0;
    if (temp_v1 != 0xA) {
        if (temp_v1 < 0xB) {
            if (temp_v1 != 0) {
                return 0;
            }
            D_80075B2C = 0;
            *arg0 = 0xA;
            goto block_7;
        }
        if (temp_v1 != 0x1E) {
            return 0;
        }
        if (func_80051FCC() != 0) {
            var_a0 = func_80051E1C();
            if (var_a0 != 0) {
                temp_v0 = D_80075B2C + 1;
                D_80075B2C = temp_v0;
                if (temp_v0 < 4) {
                    *arg0 = 0xA;
                    goto block_18;
                }
                goto block_17;
            }
            var_a0 = 0;
block_17:
            M2C_FIELD(D_800D52C0, s32 *, 4) = func_800507D4(var_a0);
            return 1;
        }
        /* Duplicate return node #19. Try simplifying control flow for better match */
        return 0;
    }
block_7:
    do {

    } while (lseek() != M2C_FIELD(D_800D52D4, s32 *, 4));
    func_80051D14();
    do {

    } while (read() != 0);
    *arg0 = 0x1E;
block_18:
    return 0;
}
