#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s32 D_80084B3C;
extern u8 D_80084B40[];
extern s32 D_80084B48;
extern s32 func_800149C0();
extern s32 func_80014A28();

s32 func_80014910(void) {
    func_800143E4();
    M2C_FIELD(D_80084B40, s32 (**)(), 0) = func_800149C0;
    M2C_FIELD(D_80084B40, s32 (**)(), 4) = func_80014A28;
    D_80084B3C = 0;
    D_80084B48 = 0;
    SysDeqIntRP();
    SysEnqIntRP();
    func_800143F4();
    return 1;
}
