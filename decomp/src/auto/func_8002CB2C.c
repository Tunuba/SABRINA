#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s32 D_80091478;
extern s32 data_ready_callback();
extern s32 func_8002CB00();

s32 func_8002CB2C(s32 arg0) {
    s8 sp10;

    sp10 = (s8) arg0;
    func_80029AB8(0xE, (s32) &sp10, 0);
    if (arg0 & 0x100) {
        if (arg0 & 0x20) {
            D_80091478 = 0;
        } else {
            D_80091478 = 1;
        }
        func_80029ED4((s32) data_ready_callback);
        func_80029AA4((s32) func_8002CB00);
    }
    return func_80029AB8(0x1B, 0, 0);
}
