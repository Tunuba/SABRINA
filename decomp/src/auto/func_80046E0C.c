#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u16 D_8007C8C6;
extern s16 D_8007CA14;
extern s32 D_8007CA58;


void func_80046E0C(void) {
    D_8007CA14 = 1;
    if ((D_8007CA58 & 0x8000) && (D_8007C8C6 != 0)) {
        D_8007C8C6 -= 1;
    }
    if ((D_8007CA58 & 0x2000) && ((u16) D_8007C8C6 < 8U)) {
        D_8007C8C6 += 1;
    }
    func_800193F8(0xB, (s32) D_8007C8C6, 0xB);
    func_8003DD74((D_8007C8C6 * 0xF) & 0xFF);
}
