#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"



s32 func_80026C34(void *arg0) {
    s32 var_a3;
    s32 var_t2;
    s32 var_v1;
    s32 var_v1_2;
    s8 var_t0;
    u8 *var_a1;
    u8 *var_a1_2;
    u8 var_t1;
    void *var_a2;

    var_t0 = 0;
    if (M2C_FIELD(arg0, u8 *, 0xE9) != 0) {
        var_t2 = 0;
        do {
            var_a1 = M2C_FIELD(arg0, u8 **, 0x20);
            var_a3 = 0;
            var_v1 = 5;
loop_3:
            var_a1 += 1;
            if (*var_a1 == var_t0) {
                var_a3 += 1;
            }
            var_v1 -= 1;
            if (var_v1 >= 0) {
                goto loop_3;
            }
            var_t1 = M2C_FIELD((var_t2 + M2C_FIELD(arg0, s32 *, 4)), u8 *, 2);
            var_a1_2 = M2C_FIELD(arg0, u8 **, 0x20);
            var_v1_2 = 0;
            if (var_t1 == 0) {
                var_t1 = 1;
            }
            var_a2 = arg0;
loop_9:
            var_a1_2 += 1;
            if (*var_a1_2 == var_t0) {
                if (var_a3 < (s32) var_t1) {
                    M2C_FIELD(var_a2, s8 *, 0x5D) = -1;
                    var_a3 -= 1;
                } else {
                    M2C_FIELD(var_a2, s8 *, 0x5D) = var_t0;
                }
            }
            var_v1_2 += 1;
            var_a2 += 1;
            if (var_v1_2 < 6) {
                goto loop_9;
            }
            var_t0 += 1;
            var_t2 += 5;
        } while (var_t0 < (s32) M2C_FIELD(arg0, u8 *, 0xE9));
    }
    M2C_FIELD(arg0, s8 *, 0x46) = 0xFE;
    return 0;
}
