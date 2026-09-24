#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"



s32 func_800189A4(s32 arg0) {
    M2C_UNK sp2C;
    s32 var_s0;
    s32 var_s0_2;
    u32 var_s1;
    u32 var_s1_2;

    var_s1 = 0;
    var_s0 = 0;
    if ((u32) M2C_FIELD(arg0, u32 *, 0x9C) < (u32) M2C_FIELD(arg0, u32 *, 0x98)) {
        Afirmar(0);
    }
    func_80029F18((s32) M2C_FIELD(arg0, u32 *, 0x98), (s32) &sp2C);
loop_3:
    if (func_80029D28(0x15, (s32) &sp2C, 0) != 0) {
        var_s0 = 1;
    }
    var_s1 = (var_s1 + 1) & 0xFF;
    if ((var_s0 == 0) && (var_s1 < 0xAU)) {
        goto loop_3;
    }
    if (var_s0 == 0) {
        return 1;
    }
    Afirmar(1);
    Afirmar(1);
    var_s1_2 = 0;
    var_s0_2 = 0;
loop_10:
    if (CdRead(0x19, M2C_FIELD(arg0, s32 *, 0), 0x80) != 0) {
        var_s0_2 = 1;
    }
    var_s1_2 = (var_s1_2 + 1) & 0xFF;
    if ((var_s0_2 == 0) && (var_s1_2 < 0xAU)) {
        goto loop_10;
    }
    if (var_s0_2 == 0) {
        return 1;
    }
    M2C_FIELD(arg0, u32 *, 0x98) = (u32) (M2C_FIELD(arg0, u32 *, 0x98) + 0x19);
    M2C_FIELD(arg0, s32 *, 4) = (s32) M2C_FIELD(arg0, s32 *, 0);
    do {

    } while (CdReadSync(1, 0) > 0);
    return 0;
}
