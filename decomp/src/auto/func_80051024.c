#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u8 D_800D52C0[];
extern s32 D_800D52D0;
extern s32 D_800D5318;
extern u8 D_800621BC[];
extern u8 D_80062360[];
extern s32 func_80050034();


s32 func_80051024(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    M2C_UNK sp10;
    M2C_UNK sp30;
    M2C_UNK sp50;
    s32 sp58;
    s32 sp5C;
    M2C_UNK *sp60;
    M2C_UNK *var_a2;
    s32 temp_v0;
    s32 var_s0;
    s32 var_s1;
    s32 var_s2;
    s32 var_s4;
    s32 var_s5;
    s32 var_v0;
    void *var_a3;

    sp5C = arg3;
    if (M2C_FIELD(D_800D52C0, s32 *, 0) != 0) {
        printf((s32) D_80062360);
        return -1;
    }
    func_800508D4(arg0, (s32) &sp10);
    strcat((s32) &sp10, arg1);
    var_s2 = 0;
    var_s1 = 0;
    sp58 = 0;
    M2C_FIELD(D_800D52C0, s32 *, 0xC) = (s32) (M2C_FIELD(D_800D52C0, s32 *, 0xC) | (1 << M2C_FIELD(D_800D52C0, s32 *, 0x10)));
    var_s5 = 0;
    if ((arg4 + arg5) > 0) {
        sp60 = &sp50;
        var_s4 = 0;
loop_4:
        if (var_s1 == 0) {
loop_5:
            func_80051D14();
            var_s0 = func_80014774((s32) &sp10, (s32) &sp30);
            var_v0 = var_s1 < arg4;
            if (var_s0 == 0) {
                temp_v0 = func_800507D4(func_80051EF4());
                sp58 = temp_v0;
                if (temp_v0 != 0) {
                    var_s2 += 1;
                    if (var_s2 >= 4) {
                        D_800D5318 = func_80051284(0);
                        if (M2C_FIELD(D_800D52C0, s32 *, 0) > 0) {
                            printf((s32) D_800621BC);
                        } else {
                            M2C_FIELD(D_800D52C0, s32 *, 0) = 2;
                            M2C_FIELD(D_800D52C0, s32 *, 4) = 0;
                            M2C_FIELD(D_800D52C0, s32 *, 8) = 0;
                            D_800D52D0 = arg0;
                            UserFuncOpen((s32) func_80050034);
                        }
                        func_80051298(0, 0, (s32) &sp58);
                        func_80051284(D_800D5318);
                        return sp58;
                    }
                    goto loop_5;
                }
                goto block_13;
            }
            goto block_14;
        }
        var_s0 = nextfile();
block_13:
        var_v0 = var_s1 < arg4;
        if (var_s0 != 0) {
block_14:
            if (var_v0 == 0) {
                var_a3 = var_s4 + arg2;
                if (arg2 != 0) {
                    var_a2 = &sp30;
                    do {
                        M2C_FIELD(var_a3, s32 *, 0) = (s32) M2C_FIELD(var_a2, s32 *, 0);
                        M2C_FIELD(var_a3, s32 *, 4) = (s32) M2C_FIELD(var_a2, s32 *, 4);
                        M2C_FIELD(var_a3, s32 *, 8) = (s32) M2C_FIELD(var_a2, s32 *, 8);
                        M2C_FIELD(var_a3, s32 *, 0xC) = (s32) M2C_FIELD(var_a2, s32 *, 0xC);
                        var_a2 += 0x10;
                        var_a3 += 0x10;
                    } while (var_a2 != sp60);
                    M2C_FIELD(var_a3, s32 *, 0) = (s32) M2C_FIELD(var_a2, s32 *, 0);
                    M2C_FIELD(var_a3, s32 *, 4) = (s32) M2C_FIELD(var_a2, s32 *, 4);
                    var_s4 += 0x28;
                    var_s5 += 1;
                }
            }
            var_s1 += 1;
            if (var_s1 >= (arg4 + arg5)) {
                goto block_20;
            }
            goto loop_4;
        }
        goto block_20;
    }
block_20:
    if (sp5C != 0) {
        *sp5C = var_s5;
    }
    return 0;
}
