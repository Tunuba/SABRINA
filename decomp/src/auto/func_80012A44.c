#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s32 * D_80063750;
extern s32 * D_80063754;


s32 func_80012A44(s32 arg0) {
    *D_80063754 = 0x10000007;
    if ((*D_80063750 & 0xFFFFFF) != 2) {
        *D_80063750 = (*D_80063754 & 0x3FFF) | 0xE1001000;
        return 0;
    }
    if (arg0 & 8) {
        *D_80063754 = 0x09000001;
        return 2;
    }
    return 1;
}
