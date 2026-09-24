#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u8 D_8006108C[];
extern u8 D_800610A8[];
extern u8 D_80063918[];
extern s16 D_8006391A;
extern u16 D_80063948;
extern u16 * D_800649A4;
extern u16 * D_800649A8;
extern s32 D_800649B0;


void func_800164BC(void) {
    M2C_UNK (*temp_v0_3)();
    s32 var_s1;
    u32 temp_v0;
    u32 temp_v0_2;
    u32 var_s0;
    u8 *var_s2;

    if (M2C_FIELD(D_80063918, u16 *, 0) == 0) {
        printf((s32) "unexpected interrupt(%04x)\n", *D_800649A4);
        ReturnFromException();
    }
    M2C_FIELD(D_80063918, s16 *, 2) = 1;
    temp_v0 = *D_800649A8 & (M2C_FIELD(D_80063918, u16 *, 0x30) & *D_800649A4);
    var_s0 = temp_v0;
    if (temp_v0 != 0) {
        do {
            var_s1 = 0;
            if (var_s0 != 0) {
                var_s2 = D_80063918 + 4;
loop_6:
                if (var_s1 < 0xB) {
                    if (var_s0 & 1) {
                        *D_800649A4 = ~(1 << var_s1);
                        temp_v0_3 = *var_s2;
                        if (temp_v0_3 != NULL) {
                            temp_v0_3();
                        }
                    }
                    var_s2 += 4;
                    var_s0 = var_s0 >> 1;
                    var_s1 += 1;
                    if (var_s0 & 0xFFFF) {
                        goto loop_6;
                    }
                }
            }
            temp_v0_2 = *D_800649A8 & (D_80063948 & *D_800649A4);
            var_s0 = temp_v0_2;
        } while (temp_v0_2 != 0);
    }
    if (*D_800649A4 & *D_800649A8) {
        D_800649B0 += 1;
        if (D_800649B0 >= 0x801) {
            printf((s32) "intr timeout(%04x:%04x)\n", *D_800649A4, *D_800649A8);
            D_800649B0 = 0;
            *D_800649A4 = 0;
        }
    } else {
        D_800649B0 = 0;
    }
    D_8006391A = 0;
    ReturnFromException();
}
