#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u8 D_8008AF88[];
extern u8 D_8008AFD8[];

void func_800257F4(void) {
    s16 var_v1;
    s32 var_s1;
    u8 *var_s0;
    u8 temp_v0_2;
    void *temp_v0;

    var_s0 = D_8008AFD8;
    var_s1 = 0;
loop_19:
    if (var_s1 < 0x50) {
        if ((s8) D_8008AF88[var_s1] != 0) {
            M2C_FIELD(var_s0, M2C_UNK (**)(u8 *), 0)(var_s0);
            M2C_FIELD(var_s0, M2C_UNK (**)(u8 *), 4)(var_s0);
            M2C_FIELD(var_s0, M2C_UNK (**)(u8 *), 0x14)(var_s0);
            temp_v0 = M2C_FIELD(var_s0, void **, 0x6C);
            if (temp_v0 != NULL) {
                var_v1 = M2C_FIELD(temp_v0, s16 *, 0x1A);
            } else {
                var_v1 = 0;
            }
            temp_v0_2 = M2C_FIELD(var_s0, u8 *, 0x20);
            if ((temp_v0_2 & 0xC0) || (var_v1 == 1)) {
                if (temp_v0_2 & 0x80) {
                    if (temp_v0 != NULL) {
                        M2C_FIELD(temp_v0, s16 *, 0x1A) = 4;
                    }
                } else if (temp_v0 != NULL) {
                    M2C_FIELD(temp_v0, s16 *, 0x1A) = 0;
                }
                M2C_FIELD(var_s0, M2C_UNK (**)(u8 *, u8), 0x18)(var_s0, temp_v0_2);
                func_80025258((s32) var_s0);
                if (M2C_FIELD(var_s0, s32 *, 0x1C) != 0) {
                    func_8002ED30((s32) var_s0);
                }
                D_8008AF88[var_s1] = 0;
            } else if (temp_v0 != NULL) {
                M2C_FIELD(temp_v0, s16 *, 0x1A) = 1;
            }
        }
        var_s1 += 1;
        var_s0 += 0x120;
        goto loop_19;
    }
    func_800257A4();
}
