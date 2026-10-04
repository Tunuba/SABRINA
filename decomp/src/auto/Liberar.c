#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u8 D_800C98C4[];
extern u8 D_800C98D4[];
extern u8 D_800C98D8[];
extern u8 D_800C98DC[];
extern u8 D_800C98E0[];
extern u8 D_80075894[];
extern u8 D_8007C8E0;
extern void * D_8007C9DC;
extern u32 D_8007CC20;
extern u8 D_8007CC24;
extern s32 D_8007CC28;


void Liberar(s32 arg0) {
    s32 sp28;
    s32 sp2C;
    s32 sp30;
    s32 sp34;
    s32 temp_v1;
    s32 var_s0;
    s32 var_t1;
    s32 var_v1;
    u32 var_s1;
    u32 var_s2;
    u32 var_t0;
    u8 *temp_a2;
    u8 *temp_a2_2;
    u8 *temp_a3;

    if (D_8007CC24 == 1) {
        var_v1 = 0;
        var_s2 = 0;
        var_s0 = 0;
        var_s1 = 1;
loop_14:
        if (var_s2 < (u32) D_8007CC20) {
            temp_a2 = &D_800C98D4[var_s0];
            if (M2C_FIELD(temp_a2, s32 *, 0) == arg0) {
                D_8007CC28 -= D_800C98E0[var_s0];
                sp28 = M2C_FIELD(temp_a2, s32 *, 0);
                sp2C = M2C_FIELD(temp_a2, s32 *, 4);
                sp30 = M2C_FIELD(temp_a2, s32 *, 8);
                sp34 = M2C_FIELD(temp_a2, s32 *, 0xC);
                if ((D_800C98D8[var_s0] != 0) && (D_8007C8E0 != 0)) {
                    func_800150F0(M2C_FIELD(temp_a2, s32 *, 4));
                    sp2C = func_800161BC();
                    strcpy(sp2C, M2C_FIELD(&D_800C98D4[var_s0], s32 *, 4));
                    func_800161C8();
                }
                if (D_8007C8E0 == 0) {
                    M2C_FIELD(M2C_FIELD(D_8007C9DC, void **, 8), M2C_UNK (**)(void *, s32), 0x38)(D_8007C9DC, arg0);
                } else {
                    func_800161C8();
                }
                var_t0 = var_s1;
                var_t1 = var_s1 * 0x10;
loop_11:
                if (var_t0 < (u32) D_8007CC20) {
                    temp_a3 = &D_800C98D4[var_t1];
                    temp_a2_2 = &D_800C98C4[var_t1];
                    var_t0 += 1;
                    M2C_FIELD(temp_a2_2, s32 *, 0) = (s32) M2C_FIELD(temp_a3, s32 *, 0);
                    M2C_FIELD(temp_a2_2, s32 *, 4) = (s32) M2C_FIELD(temp_a3, s32 *, 4);
                    M2C_FIELD(temp_a2_2, s32 *, 8) = (s32) M2C_FIELD(temp_a3, s32 *, 8);
                    M2C_FIELD(temp_a2_2, s32 *, 0xC) = (s32) M2C_FIELD(temp_a3, s32 *, 0xC);
                    var_t1 += 0x10;
                    goto loop_11;
                }
                D_8007CC20 -= 1;
                temp_v1 = D_8007CC20 * 0x10;
                *(D_800C98D8 + temp_v1) = 0;
                *(D_800C98DC + temp_v1) = 0;
                *(D_800C98D4 + temp_v1) = 0;
                var_v1 = 1;
            }
            var_s2 += 1;
            var_s1 += 1;
            var_s0 += 0x10;
            goto loop_14;
        }
        if (var_v1 == 0) {
            printf((s32) "Value deleted twice\n");
            return;
        }
        if ((sp2C != 0) && (D_8007C8E0 != 0)) {
            func_800161C8();
        }
    } else {
        if (D_8007C8E0 == 0) {
            M2C_FIELD(M2C_FIELD(D_8007C9DC, void **, 8), M2C_UNK (**)(void *, s32), 0x38)(D_8007C9DC, arg0);
            return;
        }
        func_800161C8();
    }
}
