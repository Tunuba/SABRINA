#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u16 D_8007C8C4;
extern u16 D_8007C8C6;
extern u16 D_8007CA1C;
extern u16 D_8007CA1E;
extern u16 D_8007CBFA;
extern s8 D_8007CBFD;


void func_80046BC4(void) {
    D_8007CBFA = D_8007CA1E;
    D_8007CBFD = (s8) D_8007CA1C;
    D_8007CA1C = 2;
    D_8007CA1E = 0;
    func_800193F8(0xB, (s32) D_8007C8C6, 0xB);
    func_800193F8(0xC, (s32) D_8007C8C4, 0xD);
}
