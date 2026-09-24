#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u8 D_800653F8[];
extern u8 D_8007C774[];


s32 func_80017D80(s32 arg0) {
    M2C_UNK sp2C;
    M2C_UNK spAC;
    M2C_UNK spC4;
    s32 temp_s2;
    s32 temp_s3;
    s32 var_s1;
    s32 var_s1_2;
    s8 var_s0;
    s8 var_s0_2;
    s8 var_s0_3;
    u32 temp_s4;

    var_s0 = 0;
    var_s1 = 0;
    memset((s32) &spAC, 0, 0x18);
    func_80017D3C(arg0);
    sprintf((s32) &sp2C, (s32) "\\%s;1", arg0);
loop_1:
    func_8002BE88((s32) &spAC, (s32) &sp2C);
    var_s0 += 1;
    if (spB0 == 0) {
        if (var_s0 < 0xA) {
            goto loop_1;
        }
    }
    temp_s3 = CdPosToInt((s32) &spAC);
    temp_s4 = (temp_s3 + ((u32) (spB0 + 0x7FF) >> 0xB)) - 1;
    temp_s2 = Reservar(spB0, (s32) "BasicTools.c");
    var_s0_2 = 0;
    if (temp_s4 < (u32) temp_s3) {
        Liberar(temp_s2);
        return 0;
    }
    func_80029F18(temp_s3, (s32) &spC4);
loop_6:
    if (func_80029D28(0x15, (s32) &spC4, 0) != 0) {
        var_s1 = 1;
    }
    var_s0_2 += 1;
    if ((var_s1 == 0) && (var_s0_2 < 0xA)) {
        goto loop_6;
    }
    if (var_s1 == 0) {
        Liberar(temp_s2);
        return 0;
    }
    var_s1_2 = 0;
    var_s0_3 = 0 & 0xFF;
loop_13:
    if (CdRead(temp_s4 - temp_s3, temp_s2, 0x80) != 0) {
        var_s1_2 = 1;
    }
    var_s0_3 += 1;
    if ((var_s1_2 == 0) && (var_s0_3 < 0xA)) {
        goto loop_13;
    }
    if (var_s1_2 == 0) {
        Liberar(temp_s2);
        return 0;
    }
    do {

    } while (CdReadSync(1, 0) > 0);
    return temp_s2;
}
