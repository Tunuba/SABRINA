#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s32 D_80062AF8;
extern s32 D_80062AFC;
extern struct _struct_D_80063508_0x10 D_80063508[];
extern u8 D_8006352C[];

struct _struct_D_80063508_0x10 D_80063508[];        /* unable to generate initializer: unsized array */

void func_80010BD8(s32 arg0) {
    void *sp10;
    s32 sp14;
    s32 sp18;
    s32 sp1C;
    s32 sp20;
    s32 sp24;
    s16 var_s1;
    s16 var_s5;
    s32 temp_a0;
    s32 temp_s6;
    s32 temp_s7;
    s32 var_a0;
    s32 var_fp;
    s32 var_s4;
    s32 var_v0;
    s32 var_v0_2;
    s32 var_v1;
    s8 *var_s0;
    s8 temp_v0;
    s8 temp_v1_2;
    u8 temp_v1;
    u8 temp_v1_3;
    void *temp_a1;
    void *temp_s0;
    void *temp_s3;
    void *var_s2;

    var_a0 = arg0;
    sp1C = 0x80;
    sp20 = 0x80;
    sp14 = 0;
    sp24 = 0x80;
    if ((var_a0 < 0) || (var_v0 = var_a0 * 2, ((var_a0 < D_80062AF8) == 0))) {
        var_a0 = D_80062AFC;
        var_v0 = var_a0 * 2;
        if (*(D_8006352C + (var_a0 * 0x30)) == 0) {
            return;
        }
    }
    temp_s3 = ((var_v0 + var_a0) * 0x10) + D_80063508;
    sp10 = temp_s3 + 0x10;
    var_s0 = M2C_FIELD(temp_s3, s8 **, 0x24);
    var_fp = M2C_FIELD(temp_s3, s32 *, 0x1C);
    var_s1 = M2C_FIELD(temp_s3, s16 *, 8);
    var_s5 = M2C_FIELD(temp_s3, s16 *, 0xA);
    sp18 = var_s5 + M2C_FIELD(temp_s3, s16 *, 0xE);
    var_s2 = M2C_FIELD(temp_s3, void **, 0x20);
    temp_s6 = M2C_FIELD(temp_s3, s32 *, 0x2C);
    temp_s7 = var_s1 + M2C_FIELD(temp_s3, s16 *, 0xC);
    func_800140BC((s32) sp10);
loop_30:
    temp_v1 = (u8) *var_s0;
    if (*var_s0 != 0) {
        if (var_fp != 0) {
            var_s4 = 0;
            if ((s8) temp_v1 != 0x20) {
                if ((s8) temp_v1 < 0x21) {
                    if ((s8) temp_v1 != 9) {
                        if ((s8) temp_v1 != 0xA) {
                            goto block_15;
                        }
                        goto block_24;
                    }
                    var_s1 += 0x20;
                    goto block_22;
                }
                if ((s8) temp_v1 == 0x7E) {
                    var_s0 += 1;
                    if (M2C_FIELD(var_s0, s8 *, 0) == 0x63) {
                        temp_s0 = var_s0 + 1;
                        temp_v0 = M2C_FIELD(var_s0, s8 *, 1);
                        temp_v1_2 = M2C_FIELD(temp_s0, s8 *, 1);
                        var_s0 = temp_s0 + 1 + 1;
                        sp1C = (temp_v0 - 0x30) * 0x10;
                        sp20 = (temp_v1_2 - 0x30) * 0x10;
                        sp24 = (*var_s0 - 0x30) * 0x10;
                    }
                } else {
block_15:
                    temp_v1_3 = (u8) *var_s0;
                    if ((u32) (temp_v1_3 - 0x61) < 0x1AU) {
                        var_v1 = (s8) temp_v1_3 - 0x40;
                    } else {
                        var_v1 = (s8) temp_v1_3 - 0x20;
                    }
                    var_v0_2 = var_v1;
                    if (var_v1 < 0) {
                        var_v0_2 = var_v1 + 0xF;
                    }
                    temp_a0 = var_v0_2 >> 4;
                    M2C_FIELD(var_s2, s8 *, 0xC) = (s8) ((var_v1 - (temp_a0 * 0x10)) * 8);
                    M2C_FIELD(var_s2, s8 *, 0xD) = (s8) (temp_a0 * 8);
                    M2C_FIELD(var_s2, s16 *, 8) = var_s1;
                    M2C_FIELD(var_s2, s16 *, 0xA) = var_s5;
                    temp_a1 = var_s2;
                    M2C_FIELD(var_s2, u8 *, 4) = (u8) sp1C;
                    M2C_FIELD(var_s2, u8 *, 5) = (u8) sp20;
                    M2C_FIELD(var_s2, u8 *, 6) = (u8) sp24;
                    var_s2 += 0x10;
                    AddPrim((s32) sp10, (s32) temp_a1);
                    goto block_21;
                }
            } else {
block_21:
                var_s1 += 8;
block_22:
                if ((var_s1 >= temp_s7) && (temp_s6 == 0)) {
block_24:
                    var_s4 = 1;
                }
            }
            if (var_s4 != 0) {
                if (sp14 < var_s1) {
                    sp14 = (s32) var_s1;
                }
                var_s5 += 8;
                var_s1 = M2C_FIELD(temp_s3, s16 *, 8);
                if (var_s5 < sp18) {
                    goto block_29;
                }
            } else {
block_29:
                var_s0 += 1;
                var_fp -= 1;
                goto loop_30;
            }
        }
    }
    if (M2C_FIELD(temp_s3, u8 *, 7) != 0) {
        AddPrim((s32) sp10, (s32) temp_s3);
        if (temp_s6 != 0) {
            M2C_FIELD(temp_s3, s16 *, 0xC) = (s16) (sp14 - (u16) M2C_FIELD(temp_s3, s16 *, 8));
            M2C_FIELD(temp_s3, s16 *, 0xE) = (s16) (var_s5 - ((u16) M2C_FIELD(temp_s3, s16 *, 0xA) - 8));
        }
    }
    func_800130EC((s32) sp10);
    M2C_FIELD(temp_s3, s32 *, 0x28) = 0;
    *M2C_FIELD(temp_s3, s8 **, 0x24) = 0;
}
/* Warning: struct _struct_D_80063508_0x10 is not defined (only forward-declared) */
