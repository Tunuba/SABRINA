#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u8 D_8006562C[];
extern u8 D_80065654[];
extern u8 D_8006567C[];
extern struct _struct_D_800656C4_0x100 D_800656C4[];

struct _struct_D_800656C4_0x100 D_800656C4[];       /* unable to generate initializer: unsized array */

void func_8001A228(s32 arg0, s32 arg1) {
    s32 sp3C;
    s32 sp40;
    s32 sp44;
    s32 sp48;
    s32 sp4C;
    s32 sp50;
    s32 sp54;
    s32 sp58;
    u32 sp5C;
    s32 temp_s1;
    s32 temp_s4;
    s32 temp_s7;
    s32 temp_v0;
    s32 var_a0;
    s32 var_a0_2;
    s32 var_a1;
    s32 var_a2;
    s32 var_s0;
    s32 var_s2;
    s32 var_t9;
    s32 var_t9_2;
    s32 var_v1;
    s32 var_v1_2;
    u16 temp_v0_2;
    u32 temp_fp;

    var_a1 = arg1;
    temp_s7 = var_a1;
    temp_v0 = M2C_FIELD(arg0, s16 *, 8) & 0xFFFF;
    sp3C = temp_v0;
    var_s2 = 0;
    temp_fp = M2C_FIELD(arg0, s16 *, 0xA) & 0xFFFF;
    sp5C = temp_fp;
    sp58 = temp_v0;
loop_31:
    if (var_s2 == 0x18) {
        printf((s32) D_8006567C, var_a1);
loop_33:
        goto loop_33;
    }
    sp44 = var_s2 << 8;
    var_s0 = 0;
    sp48 = sp58 & 0xF;
    sp40 = 0;
    sp4C = sp3C;
    sp50 = var_s2;
    sp54 = sp5C & 0xF;
loop_29:
    if (var_s0 == 0x7F) {
        var_s2 = (var_s2 + 1) & 0xFF;
        goto loop_31;
    }
    temp_v0_2 = *(sp40 + (D_800656C4 + sp44));
    if (((s32) temp_v0_2 >= temp_s7) && (temp_v0_2 >= temp_fp)) {
        var_t9 = temp_s7 >> 4;
        if (temp_s7 < 0) {
            var_t9 = (s32) (temp_s7 + 0xF) >> 4;
        }
        temp_s1 = (var_t9 + var_s0) & 0xFF;
        if (sp48 != 0) {
            printf((s32) D_8006562C, sp4C, M2C_FIELD(arg0, s32 *, 4));
        }
        var_t9_2 = (s32) temp_fp >> 4;
        if ((s32) temp_fp < 0) {
            var_t9_2 = (s32) (temp_fp + 0xF) >> 4;
        }
        temp_s4 = (var_t9_2 + sp50) & 0xFF;
        if (sp54 != 0) {
            printf((s32) D_80065654, temp_fp, M2C_FIELD(arg0, s32 *, 4));
        }
        var_a1 = 0;
        var_a0 = var_s2 & 0xFF;
loop_19:
        var_v1 = var_s0 & 0xFF;
        if (var_a0 != temp_s4) {
            var_a2 = var_s0 * 2;
loop_17:
            if (var_v1 != temp_s1) {
                if (*(var_a2 + (D_800656C4 + (var_a0 << 8))) == 0) {
                    var_a1 = 1;
                }
                var_v1 = (var_v1 + 1) & 0xFF;
                var_a2 += 2;
                goto loop_17;
            }
            var_a0 = (var_a0 + 1) & 0xFF;
            goto loop_19;
        }
        if (var_a1 == 0) {
            M2C_FIELD(arg0, s16 *, 0x12) = (s16) ((var_s0 * 4) + 0x200);
            M2C_FIELD(arg0, s16 *, 0x14) = (s16) (var_s2 * 0x10);
loop_26:
            var_v1_2 = var_s0 & 0xFF;
            if (var_s2 != temp_s4) {
                var_a0_2 = var_s0 * 2;
loop_24:
                if (var_v1_2 != temp_s1) {
                    *(var_a0_2 + (D_800656C4 + (var_s2 << 8))) = 0;
                    var_v1_2 = (var_v1_2 + 1) & 0xFF;
                    var_a0_2 += 2;
                    goto loop_24;
                }
                var_s2 = (var_s2 + 1) & 0xFF;
                goto loop_26;
            }
            return;
        }
        goto block_28;
    }
block_28:
    var_s0 = (var_s0 + 1) & 0xFF;
    sp40 += 2;
    goto loop_29;
}
/* Warning: struct _struct_D_800656C4_0x100 is not defined (only forward-declared) */
