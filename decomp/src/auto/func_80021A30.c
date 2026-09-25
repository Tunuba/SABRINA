#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s32 D_8007C804;
extern s32 D_8007C808;
extern s32 D_8007C9E8;
extern s32 D_8007C9F0;
extern s32 D_8007C9F4;


void func_80021A30(void) {
    func_80021120(D_8007C804, D_8007C808);
    func_8001FD50(D_8007C9F0, D_8007C9E8, 0);
    func_8001FD50(D_8007C9F4, D_8007C9E8, 0);
    DibujarTexto(D_8007C9E8, 0x5D);
    func_800218D4();
    func_800218D4();
}
