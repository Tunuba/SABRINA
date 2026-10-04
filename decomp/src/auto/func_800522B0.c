#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"


extern s32 func_80052114();
extern s32 func_80052184();

void func_800522B0(void) {
    s32 (*var_t2)();
    s32 *var_v0;

    var_v0 = (s32 *)0xDF80;
    var_t2 = func_80052114;
    do {
        *var_v0 = *var_t2;
        var_t2 += 4;
        var_v0 += 4;
    } while (var_t2 != func_80052184);
}
