#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u32 D_800913F8;
extern u32 D_800913FC;

s32 func_800290AC(void) {
    u32 var_a0;
    u32 var_v0;

    var_a0 = *(u16 *)0x1F801120 & 0xFFFF;
    if (var_a0 < (u32) D_800913FC) {
        if (*(u16 *)0x1F801128 != 0) {
            var_a0 += *(u16 *)0x1F801128;
        } else {
            var_a0 += 0x10000;
        }
    }
    if (!(*(u16 *)0x1F801124 & 0x200)) {
        var_v0 = (u32) (var_a0 - D_800913FC) >> 3;
    } else {
        var_v0 = var_a0 - D_800913FC;
    }
    return var_v0 >= D_800913F8;
}
