#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s32 D_80074CD8;
extern s32 D_80074CDC;


void func_8003DDA0(s32 arg0, s32 arg1) {
    D_80074CD8 = arg0;
    D_80074CDC = 0;
    if (arg1 == 0) {
        func_8002CF28(1, (s32) &D_80074CD8, 0);
        return;
    }
    func_8002CF28(2, (s32) &D_80074CD8, 0);
}
