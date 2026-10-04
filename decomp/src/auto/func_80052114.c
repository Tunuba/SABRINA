#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"



void func_80052114(void) {
    s32 var_t0;

    M2C_FIELD(M2C_ERROR(/* Read from unset register $v1 */), s16 *, 0xA) = (s16) (M2C_FIELD(M2C_ERROR(/* Read from unset register $v1 */), u16 *, 0xA) | M2C_ERROR(/* Read from unset register $v0 */) | 0x12);
    var_t0 = 0x28;
    do {
        var_t0 -= 1;
    } while (var_t0 != 0);
}
