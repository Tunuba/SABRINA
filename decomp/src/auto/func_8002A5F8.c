#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u8 D_80091448[];
extern u8 D_80091450[];
extern u8 * D_8006D2B0;
extern u8 D_8006D2C9;

static M2C_UNK (*D_8006D304)(u8, u8 *) = NULL;
static M2C_UNK (*D_8006D308)(u8, u8 *) = NULL;

void func_8002A5F8(void) {
    s32 temp_v0;
    s32 var_v0;
    u8 temp_s2;

    temp_s2 = *D_8006D2B0 & 3;
loop_1:
    temp_v0 = func_8002A09C();
    if (temp_v0 != 0) {
        var_v0 = temp_v0 & 2;
        if (temp_v0 & 4) {
            if (D_8006D308 != NULL) {
                D_8006D308(D_8006D2C9, D_80091450);
            }
            var_v0 = temp_v0 & 2;
        }
        if ((var_v0 != 0) && (D_8006D304 != NULL)) {
            D_8006D304(*(&D_8006D2C9 - 1), D_80091448);
        }
        goto loop_1;
    }
    *D_8006D2B0 = temp_s2;
}
