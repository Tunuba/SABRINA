#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u8 * D_8006D2B0;
extern s8 * D_8006D2BC;
extern s32 * D_8006D2C0;
extern s32 * D_8006D2E4;
extern s32 * D_8006D2E8;
extern s32 * D_8006D2EC;
extern s32 * D_8006D2F0;
extern s32 * D_8006D2F4;


s32 func_8002B704(s32 arg0, s32 arg1) {
    s32 sp0;

    *D_8006D2B0 = 0;
    *D_8006D2BC = 0x80;
    *D_8006D2E4 = 0x21020843;
    *D_8006D2C0 = 0x1325;
    *D_8006D2E8 |= 0x8000;
    *D_8006D2EC = arg0;
    *D_8006D2F0 = arg1 | 0x10000;
    if (!(*D_8006D2B0 & 0x40)) {
        do {

        } while (!(*D_8006D2B0 & 0x40));
    }
    *D_8006D2F4 = 0x11400100;
    sp0 = *D_8006D2F4;
    return 0;
}
