#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u16 D_8007C8C4;
extern s16 D_8007CA14;
extern s32 D_8007CA58;


void func_80046D6C(void) {
    D_8007CA14 = 1;
    if ((D_8007CA58 & 0x8000) && (D_8007C8C4 != 0)) {
        D_8007C8C4 -= 1;
    }
    if ((D_8007CA58 & 0x2000) && ((u16) D_8007C8C4 < 8U)) {
        D_8007C8C4 += 1;
    }
    func_800193F8(0xC, (s32) D_8007C8C4, 0xD);
    func_8003DD44((D_8007C8C4 * 0xF) & 0xFF);
    func_8003DD84();
}
