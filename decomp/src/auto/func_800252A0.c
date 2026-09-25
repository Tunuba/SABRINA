#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u8 modelos_cargados[];
extern u8 D_8006CF48[];
extern u8 D_8006EE70[];
extern u8 D_8007007C[];
extern u8 D_80071288[];
extern u8 D_80072494[];
extern u8 D_800736A0[];
extern u8 tabla_clases_niveles[];
extern s32 D_8007C9F0;
extern s8 nivel_actual;

u8 tabla_clases_niveles[0x40];                      /* unable to generate initializer: cannot parse D_8007007C as integer */

s32 func_800252A0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8_reg, s32 arg9_reg, s32 arg10_reg, s32 arg11, s32 arg12) {
    s16 arg8 = (s16) arg8_reg;
    s16 arg9 = (s16) arg9_reg;
    s16 arg10 = (s16) arg10_reg;
    s32 sp3C;
    s16 temp_s4;
    s16 temp_v0_2;
    s16 temp_v0_3;
    s16 var_s3;
    s16 var_s5;
    s16 var_s6;
    s32 *var_t7;
    s32 *var_t8;
    s32 temp_a0;
    s32 temp_s2;
    s32 temp_s2_2;
    s32 temp_s2_3;
    s32 temp_v0;
    s32 var_s4;
    s32 var_t9;
    s32 var_v0;
    void *temp_s1;

    var_s5 = arg8;
    var_s3 = arg9;
    var_s6 = arg10;
    if (arg0 >= 0x37) {
        goto block_20;
    }
    if (arg0 == 0) {
        goto block_20;
    }
    temp_s1 = *(tabla_clases_niveles + (nivel_actual * 4)) + (arg0 * 0x54);
    temp_v0 = func_800256E0();
    if (temp_v0 != 0) {
        M2C_FIELD(temp_v0, s16 *, 0x22) = (s16) arg0;
        M2C_FIELD(temp_v0, s32 *, 0x6C) = 0;
        temp_a0 = *(modelos_cargados + (M2C_FIELD(temp_s1, s16 *, 0x22) * 4));
        var_s4 = 0;
        if (temp_a0 != 0) {
            var_s4 = func_8001E06C(temp_a0, D_8007C9F0);
            func_800206E0();
        }
        M2C_FIELD(temp_v0, s32 *, 0x64) = (s32) M2C_FIELD(temp_s1, s32 *, 0x24);
        M2C_FIELD(temp_v0, s32 *, 0x60) = var_s4;
        if (arg1 != 0) {
            var_s5 += M2C_FIELD(arg1, s16 *, 0x30);
            var_s3 += M2C_FIELD(arg1, s16 *, 0x32);
            sp3C = (s32) var_s3;
            var_s6 += M2C_FIELD(arg1, s16 *, 0x34);
            temp_s4 = rsin((s32) var_s3);
            temp_v0_2 = rcos(sp3C);
            M2C_FIELD(temp_v0, s32 *, 0x24) = (s32) (M2C_FIELD(arg1, s32 *, 0x24) + ((s32) (temp_v0_2 * arg2) >> 0xC) + ((s32) (temp_s4 * arg4) >> 0xC));
            M2C_FIELD(temp_v0, s32 *, 0x2C) = (s32) ((M2C_FIELD(arg1, s32 *, 0x2C) - ((s32) (temp_s4 * arg2) >> 0xC)) + ((s32) (temp_v0_2 * arg4) >> 0xC));
            M2C_FIELD(temp_v0, s32 *, 0x28) = (s32) (arg3 + M2C_FIELD(arg1, s32 *, 0x28));
            M2C_FIELD(temp_v0, s32 *, 0x38) = (s32) (((s32) (temp_v0_2 * arg5) >> 0xC) + ((s32) (temp_s4 * arg7) >> 0xC));
            var_v0 = ((s32) (temp_v0_2 * arg7) >> 0xC) - ((s32) (temp_s4 * arg5) >> 0xC);
        } else {
            M2C_FIELD(temp_v0, s32 *, 0x24) = arg2;
            M2C_FIELD(temp_v0, s32 *, 0x28) = arg3;
            M2C_FIELD(temp_v0, s32 *, 0x2C) = arg4;
            M2C_FIELD(temp_v0, s32 *, 0x38) = arg5;
            var_v0 = arg7;
        }
        M2C_FIELD(temp_v0, s32 *, 0x40) = var_v0;
        M2C_FIELD(temp_v0, s32 *, 0x3C) = arg6;
        M2C_FIELD(temp_v0, s16 *, 0x30) = var_s5;
        M2C_FIELD(temp_v0, s16 *, 0x32) = var_s3;
        M2C_FIELD(temp_v0, s16 *, 0x34) = var_s6;
        M2C_FIELD(temp_v0, s32 *, 0x54) = (s32) M2C_FIELD(temp_s1, s16 *, 0x28);
        M2C_FIELD(temp_v0, s32 *, 0x58) = (s32) M2C_FIELD(temp_s1, s16 *, 0x2A);
        M2C_FIELD(temp_v0, s32 *, 0x5C) = (s32) M2C_FIELD(temp_s1, s16 *, 0x2C);
        M2C_FIELD(temp_v0, s32 *, 0) = (s32) M2C_FIELD(temp_s1, s32 *, 4);
        M2C_FIELD(temp_v0, s32 *, 4) = (s32) M2C_FIELD(temp_s1, s32 *, 8);
        M2C_FIELD(temp_v0, s32 *, 8) = (s32) M2C_FIELD(temp_s1, s32 *, 0xC);
        M2C_FIELD(temp_v0, s32 *, 0xC) = (s32) M2C_FIELD(temp_s1, s32 *, 0x10);
        M2C_FIELD(temp_v0, s32 *, 0x10) = (s32) M2C_FIELD(temp_s1, s32 *, 0x14);
        M2C_FIELD(temp_v0, s32 *, 0x14) = (s32) M2C_FIELD(temp_s1, s32 *, 0x18);
        M2C_FIELD(temp_v0, s32 *, 0x18) = (s32) M2C_FIELD(temp_s1, s32 *, 0x1C);
        func_8001E588(temp_v0);
        var_t8 = temp_s1 + 0x30;
        var_t7 = temp_v0 + 0xF4;
        var_t9 = 9;
        do {
            var_t9 -= 1;
            *var_t7 = *var_t8;
            var_t8 += 4;
            var_t7 += 4;
        } while (var_t9 > 0);
        M2C_FIELD(temp_v0, s32 *, 0xF4) = (s32) (temp_v0 + 0x24);
        temp_v0_3 = M2C_FIELD(temp_v0, s16 *, 0x110);
        if (temp_v0_3 != 1) {
            if (temp_v0_3 != 2) {
                if (temp_v0_3 == 3) {
                    temp_s2 = temp_v0 + 0xF4;
                    func_80039A34(temp_s2, func_8003A258(temp_s2), (s32) M2C_FIELD(temp_v0, s16 *, 0x114), (s32) M2C_FIELD(temp_v0, s16 *, 0x112));
                }
            } else {
                temp_s2_2 = temp_v0 + 0xF4;
                func_80039A70(temp_s2_2, func_8003A250(temp_s2_2), (s32) M2C_FIELD(temp_v0, s16 *, 0x114), (s32) M2C_FIELD(temp_v0, s16 *, 0x112));
            }
        } else {
            temp_s2_3 = temp_v0 + 0xF4;
            func_80039B1C(temp_s2_3, func_8003A260(temp_s2_3), (s32) M2C_FIELD(temp_v0, s16 *, 0x114), (s32) M2C_FIELD(temp_v0, s16 *, 0x112));
        }
        M2C_FIELD(temp_s1, M2C_UNK (**)(s32, s32, s32), 0)(temp_v0, arg11, arg12);
        return temp_v0;
    }
    ImprimirDepuracion((s32) "Cannot Spawn: Out of World Objects", M2C_ERROR(/* Read from unset register $a1 */), M2C_ERROR(/* Read from unset register $a2 */), M2C_ERROR(/* Read from unset register $a3 */));
block_20:
    return 0;
}
