#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s8 * D_8006D2B0;
extern u8 * D_8006D2B4;
extern u8 * D_8006D2B8;
extern u8 * D_8006D2BC;


void func_8002B024(s32 arg0) {
    *D_8006D2B0 = 2;
    *D_8006D2B8 = M2C_FIELD(arg0, u8 *, 0);
    *D_8006D2BC = M2C_FIELD(arg0, u8 *, 1);
    *D_8006D2B0 = 3;
    *D_8006D2B4 = M2C_FIELD(arg0, u8 *, 2);
    *D_8006D2B8 = M2C_FIELD(arg0, u8 *, 3);
    *D_8006D2BC = 0x20;
}
