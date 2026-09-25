#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u8 D_800C65E0[];
extern u8 D_800C6608[];
extern u8 D_800C6630[];
extern u16 D_8007C8C0;
extern u16 D_8007C8C2;
extern s16 D_8007CBE4;


s32 TocarSonido(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s16 temp_v1;
    s16 var_s0;
    s16 var_s1;
    s16 var_s3;
    s32 temp_v1_2;
    s32 var_s2;
    u16 temp_v0;

    var_s0 = 0x13;
    var_s3 = 0xA;
    var_s1 = 0xA;
    var_s2 = 0x26;
loop_7:
    if (var_s0 != 0) {
        temp_v0 = D_800C65E0[var_s2];
        temp_v1 = SpuGetKeyStatus(1 << var_s0);
        if ((s32) temp_v0 < var_s1) {
            var_s1 = (s16) temp_v0;
            var_s3 = var_s0;
        }
        if (((temp_v1 != 0) && (temp_v1 != 3)) || (D_800C6630[var_s0] != 0)) {
            var_s0 -= 1;
            var_s2 -= 2;
            goto loop_7;
        }
    }
    if (var_s0 == 0) {
        if (var_s1 < arg3) {
            var_s0 = var_s3;
            goto block_12;
        }
        return -1;
    }
block_12:
    D_800C6630[var_s0] = 1;
    temp_v1_2 = var_s0 * 2;
    *(D_800C65E0 + temp_v1_2) = (s16) arg3;
    *(D_800C6608 + temp_v1_2) = (s16) arg2;
    func_800425C8((s32) var_s0, (s32) D_8007CBE4, arg0, arg1, /* extra? */ arg2, /* extra? */ 0, /* extra? */ (s32) (s16) D_8007C8C0, /* extra? */ (s32) (s16) D_8007C8C2);
    return (s32) var_s0;
}
