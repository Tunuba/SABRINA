#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u8 D_800656A0[];
extern struct _struct_D_800676C4_0x40 D_800676C4[];

struct _struct_D_800676C4_0x40 D_800676C4[];        /* unable to generate initializer: unsized array */

void func_8001A4C0(s32 arg0) {
    s32 temp_t4;
    s32 var_t1;
    s32 var_t2;
    s32 var_t3;
    s32 var_t3_2;
    s32 var_t7;
    s32 var_t8;
    s32 var_t9;
    s32 var_v1;
    s32 var_v1_2;
    u16 temp_v0;

    temp_v0 = M2C_FIELD(arg0, u16 *, 0x1A);
    var_t1 = 0;
loop_18:
    var_t2 = 0;
    if (var_t1 == 0x3F) {
        printf((s32) D_800656A0);
loop_20:
        goto loop_20;
    }
    var_v1 = 0;
loop_16:
    if (var_t2 == 0x1D) {
        var_t1 = (var_t1 + 1) & 0xFF;
        goto loop_18;
    }
    if ((u16) *(var_v1 + (D_800676C4 + (var_t1 << 6))) >= temp_v0) {
        var_t9 = (s32) temp_v0 >> 4;
        if ((s32) temp_v0 < 0) {
            var_t9 = (s32) (temp_v0 + 0xF) >> 4;
        }
        temp_t4 = (var_t9 + var_t2) & 0xFF;
        var_t7 = 0;
        var_t3 = var_t2 & 0xFF;
        var_t8 = var_t2 * 2;
loop_9:
        if (var_t3 != temp_t4) {
            if (*(var_t8 + (D_800676C4 + (var_t1 << 6))) == 0) {
                var_t7 = 1;
            }
            var_t3 = (var_t3 + 1) & 0xFF;
            var_t8 += 2;
            goto loop_9;
        }
        if (var_t7 == 0) {
            M2C_FIELD(arg0, s16 *, 0x16) = (s16) ((var_t2 * 0x10) + 0x200);
            M2C_FIELD(arg0, s16 *, 0x18) = (s16) (var_t1 + 0x1C0);
            var_t3_2 = var_t2 & 0xFF;
            var_v1_2 = var_t2 * 2;
loop_13:
            if (var_t3_2 != temp_t4) {
                *(var_v1_2 + (D_800676C4 + (var_t1 << 6))) = 0;
                var_t3_2 = (var_t3_2 + 1) & 0xFF;
                var_v1_2 += 2;
                goto loop_13;
            }
            return;
        }
        goto block_15;
    }
block_15:
    var_t2 = (var_t2 + 1) & 0xFF;
    var_v1 += 2;
    goto loop_16;
}
/* Warning: struct _struct_D_800676C4_0x40 is not defined (only forward-declared) */
