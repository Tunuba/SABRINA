#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s32 D_8007CC90;
extern s32 D_8007CC94;


void func_8005D3F4(void) {
    s32 var_a0;
    s32 var_a0_2;
    s32 var_a0_3;
    s32 var_v1;

    var_a0 = D_8007CC94;
    var_v1 = D_8007CC90 - D_8007CC94;
    if (var_v1 > 0) {
        if (var_v1 >= 0xB) {
            var_v1 = 0xA;
        }
        D_8007CC94 += var_v1;
        var_a0_2 = D_8007CC94;
        if (var_a0_2 < 0) {
            var_a0_2 = 0;
        }
        SsSetSerialVol(0, (s32) (s16) var_a0_2, (s32) (s16) var_a0_2);
        return;
    }
    if (var_v1 < 0) {
        if (var_v1 < -0xA) {
            var_v1 = -0xA;
        }
        D_8007CC94 += var_v1;
        var_a0_3 = D_8007CC94;
        if (var_a0_3 < 0) {
            var_a0_3 = 0;
        }
        SsSetSerialVol(0, (s32) (s16) var_a0_3, (s32) (s16) var_a0_3);
        return;
    }
    if (var_a0 < 0) {
        var_a0 = 0;
    }
    if (var_a0 >= 0x80) {
        var_a0 = 0x7F;
    }
    SsSetSerialVol(0, (s32) (s16) var_a0, (s32) (s16) var_a0);
}
