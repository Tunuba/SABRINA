#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s32 * D_80075CA4;
extern s32 * D_80075CA8;
extern s32 * D_80075CAC;
extern s32 * D_80075CBC;
extern s32 * D_80075CC4;


void func_8005D9C0(s32 arg0, s32 arg1) {
    func_8005DADC();
    *D_80075CC4 |= 0x88;
    *D_80075CA4 = arg0 + 4;
    *D_80075CA8 = (((u32) arg1 >> 5) << 0x10) | 0x20;
    *D_80075CBC = *arg0;
    *D_80075CAC = 0x01000201;
}
