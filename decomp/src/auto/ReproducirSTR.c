#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s32 D_8007C9E0;
extern s32 D_8007C9E4;

s32 D_8007C9E0;                                     /* unable to generate initializer: not enough data */
s32 D_8007C9E4;                                     /* unable to generate initializer: not enough data */

void ReproducirSTR(s32 arg0, s32 arg1) {
    func_80012CDC(0);
    func_80021120(D_8007C9E0, D_8007C9E4);
    func_80017158(0x140, 0xF0, 4, 1, /* extra? */ 0);
    GsDefDispBuff(0, 0, 0, 0x100);
    func_80012CDC(1);
    func_80021A94(arg0, 0, 0x28, arg1);
    func_80021120(D_8007C9E0, D_8007C9E4);
    func_80012CDC(1);
    func_80017B5C(0x100, 0x6E);
    func_80017B7C();
}
