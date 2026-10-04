#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u8 D_80061D10[];
extern u8 D_80061D30[];
extern u8 D_80061D44[];
extern void * D_80074EBC;
extern u16 D_80074EC0;


void func_8003E0C4(s32 arg0, s32 arg1) {
    s32 temp_a1;
    s32 temp_s3;
    s32 var_s0;
    s32 var_s1;
    s32 var_s2;
    s32 var_v0;
    s32 var_v1;
    u16 temp_v0;
    u32 var_v1_2;
    u32 var_v1_3;

    var_s1 = arg1;
    var_s2 = arg0;
    M2C_FIELD(D_80074EBC, u16 *, 0x1A6) = (u16) D_80074EC0;
    temp_s3 = M2C_FIELD(D_80074EBC, u16 *, 0x1AE) & 0x7FF;
    func_8003EA90();
    var_v0 = (u32) var_s1 < 0x41U;
    if (var_s1 != 0) {
        do {
            var_s0 = 0x40;
            if (var_v0 != 0) {
                var_s0 = var_s1;
            }
            var_v1 = 0;
            if (var_s0 > 0) {
                do {
                    temp_v0 = *var_s2;
                    var_s2 += 2;
                    var_v1 += 2;
                    M2C_FIELD(D_80074EBC, u16 *, 0x1A8) = temp_v0;
                } while (var_v1 < var_s0);
            }
            M2C_FIELD(D_80074EBC, u16 *, 0x1AA) = (u16) ((M2C_FIELD(D_80074EBC, u16 *, 0x1AA) & 0xFFCF) | 0x10);
            func_8003EA90();
            if (M2C_FIELD(D_80074EBC, u16 *, 0x1AE) & 0x400) {
                var_v1_2 = 1;
loop_8:
                if (var_v1_2 >= 0xF01U) {
                    printf((s32) "SPU:T/O [%s]\n", "wait (wrdy H -> L)");
                } else {
                    var_v1_2 += 1;
                    if (M2C_FIELD(D_80074EBC, u16 *, 0x1AE) & 0x400) {
                        goto loop_8;
                    }
                }
            }
            var_s1 -= var_s0;
            func_8003EA90();
            func_8003EA90();
            var_v0 = (u32) var_s1 < 0x41U;
        } while (var_s1 != 0);
    }
    temp_a1 = temp_s3 & 0xFFFF;
    M2C_FIELD(D_80074EBC, u16 *, 0x1AA) = (u16) (M2C_FIELD(D_80074EBC, u16 *, 0x1AA) & 0xFFCF);
    if ((M2C_FIELD(D_80074EBC, u16 *, 0x1AE) & 0x7FF) != temp_a1) {
        var_v1_3 = 1;
loop_14:
        if (var_v1_3 >= 0xF01U) {
            printf((s32) "SPU:T/O [%s]\n", "wait (dmaf clear/W)");
            return;
        }
        var_v1_3 += 1;
        if ((M2C_FIELD(D_80074EBC, u16 *, 0x1AE) & 0x7FF) == temp_a1) {

        } else {
            goto loop_14;
        }
    }
}
