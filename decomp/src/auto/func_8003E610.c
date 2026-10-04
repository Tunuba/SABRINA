#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s32 * D_80074E88;
extern s32 * D_80074E8C;
extern s32 * D_80074E90;
extern s32 D_80074EAC;
extern s32 D_80074EB0;
extern s32 D_80074EB4;
extern void * D_80074EBC;
extern u16 D_80074EC0;
extern s32 D_80074ED0;


void func_8003E610(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 *var_s0;
    s32 temp_a0;
    s32 temp_a0_2;
    s32 var_a0;
    s32 var_a2;
    u32 temp_v0;
    u32 var_v1;
    u32 var_v1_2;
    u32 var_v1_3;

    switch (arg0) {                                 /* irregular */
    case 2:
        temp_v0 = (u32) arg1 >> D_80074ED0;
        D_80074EC0 = (u16) temp_v0;
        M2C_FIELD(D_80074EBC, u16 *, 0x1A6) = (u16) temp_v0;
        return;
    case 1:
        D_80074EAC = 0;
        if (M2C_FIELD(D_80074EBC, u16 *, 0x1A6) != D_80074EC0) {
            var_v1 = 1;
loop_10:
            if (var_v1 < 0xF01U) {
                var_v1 += 1;
                if (M2C_FIELD(D_80074EBC, u16 *, 0x1A6) == D_80074EC0) {
                    goto block_12;
                }
                goto loop_10;
            }
            return;
        }
block_12:
        M2C_FIELD(D_80074EBC, u16 *, 0x1AA) = (u16) ((M2C_FIELD(D_80074EBC, u16 *, 0x1AA) & 0xFFCF) | 0x20);
        return;
    case 0:
        D_80074EAC = 1;
        if (M2C_FIELD(D_80074EBC, u16 *, 0x1A6) != D_80074EC0) {
            var_v1_2 = 1;
loop_15:
            if (var_v1_2 < 0xF01U) {
                var_v1_2 += 1;
                if (M2C_FIELD(D_80074EBC, u16 *, 0x1A6) == D_80074EC0) {
                    goto block_17;
                }
                goto loop_15;
            }
        } else {
block_17:
            M2C_FIELD(D_80074EBC, u16 *, 0x1AA) = (u16) (M2C_FIELD(D_80074EBC, u16 *, 0x1AA) | 0x30);
            return;
        }
        break;
    case 3:
        var_a0 = 0x20;
        if (D_80074EAC == 1) {
            var_a0 = 0x30;
        }
        temp_a0 = var_a0 & 0xFFFF;
        var_v1_3 = 1;
        if ((M2C_FIELD(D_80074EBC, u16 *, 0x1AA) & 0x30) != temp_a0) {
loop_21:
            if (var_v1_3 < 0xF01U) {
                var_v1_3 += 1;
                if ((M2C_FIELD(D_80074EBC, u16 *, 0x1AA) & 0x30) == temp_a0) {
                    goto block_23;
                }
                goto loop_21;
            }
        } else {
block_23:
            if (D_80074EAC == 1) {
                var_s0 = &arg1 + 4;
                func_8003E2AC();
            } else {
                var_s0 = &arg1 + 4;
                func_8003E284();
            }
            D_80074EB0 = M2C_FIELD(var_s0, s32 *, -4);
            temp_a0_2 = M2C_FIELD(var_s0, s32 *, 0);
            D_80074EB4 = ((u32) temp_a0_2 >> 6) + ((temp_a0_2 & 0x3F) != 0);
            *D_80074E88 = D_80074EB0;
            *D_80074E8C = (D_80074EB4 << 0x10) | 0x10;
            var_a2 = 0x01000201;
            if (D_80074EAC == 1) {
                var_a2 = 0x01000200;
            }
            *D_80074E90 = var_a2;
        }
        break;
    }
}
