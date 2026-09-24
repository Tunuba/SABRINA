#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u8 D_8008AB78[];
extern u8 D_8006C1C0[];
extern u8 D_8006C240[];
extern s32 D_8007CA48;
extern u16 D_8007CAE2;

u8 D_8006C240[0x10];                                /* unable to generate initializer: cannot parse D_8006C1C0 as integer */

void DibujarCeldasVisibles(s32 arg0, s32 arg1) {
    s16 *var_s0;
    s16 temp_a0;
    s16 temp_v1;
    s16 var_s1;
    s32 temp_a1;
    s32 temp_s3;
    u32 temp_a0_2;
    u32 temp_v0;
    void *temp_a2;

    var_s0 = *(*(D_8006C240 + (arg1 * 4)) + (((((s32) D_8007CAE2 >> 7) + 0x18) & 0x1F & 0xFFFF) * 4));
    temp_s3 = M2C_FIELD(arg0, s32 *, 4);
    var_s1 = 0;
    if ((u32) (BitDeZona((((s16) ((s32) (~(((s32) p_sabrina->z >> 0x10) + 0x80) & 0xFF) >> 2) << 6) + (s16) ((s32) (((s32) p_sabrina->x >> 0x10) + 0x80) >> 2)) & 0xFFFF) & 0xFFFF) < 0x8000U) {

    }
    do {
        temp_v1 = M2C_FIELD(var_s0, s16 *, 0);
        temp_a0 = M2C_FIELD(var_s0, s16 *, 2);
        var_s0 = var_s0 + 2 + 2;
        temp_a0_2 = (((M2C_ERROR(/* Read from unset register $t0 */) + temp_v1) << 6) + (M2C_ERROR(/* Read from unset register $t1 */) + temp_a0)) & 0xFFFF;
        if (temp_a0_2 < 0x1000U) {
            temp_a2 = D_8007CA48 + (temp_a0_2 * 0xC);
            temp_v0 = M2C_FIELD(temp_a2, u32 *, 8);
            if ((temp_v0 >= (u32) M2C_ERROR(/* Read from unset register $t3 */)) && ((u32) M2C_ERROR(/* Read from unset register $t2 */) >= temp_v0) && (M2C_FIELD(temp_a2, s16 *, 0) != -1)) {
                temp_a1 = *(D_8008AB78 + (var_s1 * 4));
                var_s1 += 1;
                func_800207AC(temp_s3, temp_a1, (s32) temp_a2);
            }
        }
    } while (*var_s0 != 0x7F);
    func_80020764(var_s1 & 0xFFFF);
}
