#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s32 D_80074CD8;
extern s32 D_80074CDC;


void func_8003DE68(s32 arg0) {
    s32 var_v0;

    if (arg0 == 0) {
        var_v0 = 0x5A;
    } else if (arg0 == 1) {
        var_v0 = func_80021CE4(3) + 0x5B;
    } else {
        var_v0 = func_80021CE4(3) + 0x5E;
    }
    D_80074CD8 = var_v0;
    D_80074CDC = 0;
    func_8002CF28(1, (s32) &D_80074CD8, 0);
}
