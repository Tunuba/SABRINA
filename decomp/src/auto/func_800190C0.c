#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u8 ascii_a_letra[];
extern u8 D_800798BC[];
extern u8 D_80079D48[];
extern u8 D_8007C9D2[];

u8 D_800798BC[0x48C];                               /* unable to generate initializer: cannot parse D_80076B0C as integer */
u8 D_80079D48[0xEC];                                /* unable to generate initializer: cannot parse D_8007C938 as integer */

void func_800190C0(void) {
    s32 var_a0;
    s32 var_t0;
    s32 var_t1;
    s8 *temp_a2;
    void *temp_v0;

    var_a0 = 0;
loop_8:
    if (M2C_ERROR(/* Read from unset register $v0 */) != D_8007C9D2) {
        temp_v0 = D_800798BC[var_a0];
        if ((temp_v0 != D_8007C9D2) && (temp_v0 != NULL)) {
            var_t0 = 0;
            var_t1 = 0x45;
loop_5:
            if (var_t1 != 0) {
                temp_a2 = D_80079D48[var_a0] + var_t0;
                var_t1 = *temp_a2 & 0xFF;
                *temp_a2 = (s8) ascii_a_letra[var_t1];
                var_t0 = (var_t0 + 1) & 0xFF;
                goto loop_5;
            }
            M2C_FIELD(temp_v0, s16 *, 0x16) = (s16) (var_t0 - 1);
            M2C_FIELD(temp_v0, u16 *, 0x10) = (u16) ((s32) (M2C_FIELD(temp_v0, u16 *, 0x10) - M2C_FIELD(temp_v0, u16 *, 0xA)) / var_t0);
            M2C_FIELD(temp_v0, u16 *, 0x12) = (u16) ((s32) (M2C_FIELD(temp_v0, u16 *, 0x12) - M2C_FIELD(temp_v0, u16 *, 0xC)) / var_t0);
            M2C_FIELD(temp_v0, u16 *, 0x14) = (u16) ((s32) (M2C_FIELD(temp_v0, u16 *, 0x14) - M2C_FIELD(temp_v0, u16 *, 0xE)) / var_t0);
            M2C_FIELD(temp_v0, u16 *, 6) = (u16) M2C_FIELD(temp_v0, u16 *, 0);
            M2C_FIELD(temp_v0, u16 *, 8) = (u16) M2C_FIELD(temp_v0, u16 *, 2);
        }
        var_a0 += 4;
        goto loop_8;
    }
}
