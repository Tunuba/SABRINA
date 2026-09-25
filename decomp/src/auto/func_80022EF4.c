#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u8 hechizos[];
extern u8 D_8007CB1C;


s32 func_80022EF4(s32 arg0) {
    u32 var_v1;

    var_v1 = 0;
loop_5:
    if (var_v1 >= 6U) {
        D_8007CB1C = 0;
        return -1;
    }
    if (hechizos[var_v1] != 0) {
        do {
            D_8007CB1C += arg0;
            D_8007CB1C &= 7;
        } while (hechizos[D_8007CB1C] == 0);
        return (s32) (s8) D_8007CB1C;
    }
    var_v1 = (var_v1 + 1) & 0xFF;
    goto loop_5;
}
