#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s32 * D_80063750;
extern s32 * D_80063754;


s32 func_800120DC(s32 arg0) {
    *D_80063754 = arg0 | 0x10000000;
    return *D_80063750 & 0xFFFFFF;
}
