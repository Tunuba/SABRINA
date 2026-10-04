#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s32 * D_80075CB0;
extern s32 * D_80075CB4;
extern s32 * D_80075CB8;
extern s32 * D_80075CC4;


void func_8005DA50(s32 arg0, u32 arg1) {
    func_8005DB70();
    *D_80075CC4 |= 0x88;
    *D_80075CB8 = 0;
    *D_80075CB0 = arg0;
    *D_80075CB4 = ((arg1 >> 5) << 0x10) | 0x20;
    *D_80075CB8 = 0x01000200;
}
