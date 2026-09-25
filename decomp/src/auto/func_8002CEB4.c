#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s32 D_8006D5AC;
extern s32 D_8006D5B0;


void func_8002CEB4(void) {
    u8 sp10;

    D_8006D5B0 = 0;
    func_80029AA4(0);
    func_80029AB8(1, 0, 0);
loop_1:
    if (func_80029D28(9, 0, (s32) &sp10) == 0) {
        if (sp10 & 0x10) {

        } else {
            goto loop_1;
        }
    }
    D_8006D5AC = -1;
}
