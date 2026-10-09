#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u8 D_80061214[];
extern s32 D_8006D024;
extern s32 func_80029808();
extern s32 func_80029830();
extern s32 func_80029858();

extern s32 (*D_8006D020)();
extern s32 (*D_8006D304)();
extern s32 (*D_8006D308)();

void func_8002988C(void) {
    s32 var_s0;

    var_s0 = 4;
loop_1:
    if (func_800297CC() == 1) {
        D_8006D304 = func_80029808;
        D_8006D308 = func_80029830;
        D_8006D020 = func_80029858;
        D_8006D024 = 0;
        return;
    }
    var_s0 -= 1;
    if (var_s0 == -1) {
        printf((s32) "CdInit: Init failed\n");
        return;
    }
    goto loop_1;
}
