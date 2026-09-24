#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s32 * D_80063764;
extern s32 * D_80063768;
extern s32 * D_8006376C;
extern s32 * D_80063770;


s32 func_80011850(s32 arg0, s32 arg1) {
    s32 var_v0;

    *D_80063770 |= 0x08000000;
    *D_8006376C = 0;
    *D_80063764 = arg0 + ((arg1 * 4) - 4);
    *D_80063768 = arg1;
    *D_8006376C = 0x11000002;
    func_800128CC();
    var_v0 = arg1;
    if (*D_8006376C & 0x01000000) {
loop_2:
        var_v0 = -1;
        if (func_80012900() == 0) {
            var_v0 = arg1;
            if (*D_8006376C & 0x01000000) {
                goto loop_2;
            }
        }
    }
    return var_v0;
}
