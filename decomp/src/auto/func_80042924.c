#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s32 D_800C6E60;
extern s16 D_800C76FC;

void func_80042924(s32 arg0) {
    if (D_800C6E60 == 1) {
        return;
    }
    D_800C6E60 = 1;
    if ((u32) (arg0 & 0xFFFF) >= 0x18U) {
        D_800C6E60 = 0;
        return;
    }
    D_800C76FC = (s16) arg0;
    _SsVmKeyOffNow();
    D_800C6E60 = 0;
}
