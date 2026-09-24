#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s32 * D_80063900;
extern s32 * D_80063904;
extern s32 D_80063908;
extern s32 D_80063914;
extern s32 D_800649EC;


s32 func_8001626C(s32 arg0) {
    s32 sp10;
    s32 temp_s0;
    s32 temp_s1;
    s32 var_a1;
    s32 var_v0;

    do {
        sp10 = *D_80063904;
    } while (sp10 != *D_80063904);
    temp_s1 = (sp10 - D_80063914) & 0xFFFF;
    if (arg0 < 0) {
        return D_800649EC;
    }
    if (arg0 != 1) {
        if (arg0 > 0) {
            var_v0 = D_80063908 - 1 + arg0;
        } else {
            var_v0 = D_80063908;
        }
        var_a1 = 0;
        if (arg0 > 0) {
            var_a1 = arg0 - 1;
        }
        func_800161D4(var_v0, var_a1);
        temp_s0 = *D_80063900;
        func_800161D4(D_800649EC + 1, 1);
        if ((temp_s0 & 0x400000) && ((temp_s0 ^ *D_80063900) >= 0)) {
            do {

            } while (!((temp_s0 ^ *D_80063900) & 0x80000000));
        }
        D_80063908 = D_800649EC;
        do {
            D_80063914 = *D_80063904;
        } while (D_80063914 != *D_80063904);
    }
    return temp_s1;
}
