#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u8 D_800654B4[];
extern u8 D_8007C78C[];


void ArchivoAbrir(s32 arg0, s32 arg1, s32 arg2) {
    M2C_FIELD(arg0, s8 *, 0x14) = (s8) arg2;
    printf((s32) "Loading %s...\n");
loop_1:
    if (!(func_800188C4(arg0, arg1) & 0xFF)) {
        return;
    }
    if ((func_800189A4(arg0) & 0xFFFF) != 1) {
        sprintf(arg0 + 0x15, (s32) "%s", arg1);
        return;
    }
    goto loop_1;
}
