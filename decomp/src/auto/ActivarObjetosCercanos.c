#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s16 D_8006C250[];
extern s32 D_8006C444;
extern s32 D_8006C44C;
extern s32 D_8007CA48;
extern s32 D_8007CB40;


void ActivarObjetosCercanos(void) {
    s16 *var_s3;
    s16 temp_v0_2;
    s32 temp_a0;
    s32 temp_a1;
    s32 temp_s5;
    s32 temp_s6;
    s32 var_s1;
    s32 var_s4;
    u32 temp_a0_2;
    u32 temp_s7;
    u32 temp_v0;
    void *temp_s2;
    void *var_s0;

    var_s3 = D_8006C250;
    var_s4 = BitDeZona((((((s32) (~(((s32) p_sabrina->z >> 0x10) + 0x80) & 0xFF) >> 2) & 0xFFFF) << 6) + (((s32) (((s32) p_sabrina->x >> 0x10) + 0x80) >> 2) & 0xFFFF)) & 0xFFFF) & 0xFFFF;
    temp_s7 = (var_s4 >> 1) & 0xFFFF;
    if ((u32) var_s4 < 0x8000U) {
        var_s4 = (var_s4 * 2) & 0xFFFF;
    }
    temp_s6 = ((s32) (((s32) D_8006C444 >> 8) + 0x80) >> 2) & 0xFFFF;
    temp_s5 = ((s32) (~(((s32) D_8006C44C >> 8) + 0x80) & 0xFF) >> 2) & 0xFFFF;
    do {
        temp_a0 = M2C_FIELD(var_s3, s16 *, 0) & 0xFFFF;
        temp_a1 = var_s3[1] & 0xFFFF;
        var_s3 = &var_s3[1] + 2;
        temp_a0_2 = (((temp_s5 + temp_a0) << 6) + (temp_s6 + temp_a1)) & 0xFFFF;
        if (temp_a0_2 < 0x1000U) {
            temp_s2 = D_8007CA48 + (temp_a0_2 * 0xC);
            temp_v0 = M2C_FIELD(temp_s2, u32 *, 8);
            if (((u32) var_s4 >= temp_v0) && (temp_v0 >= temp_s7) && (M2C_FIELD(temp_s2, s16 *, 4) >= 0)) {
                var_s1 = 0;
                var_s0 = D_8007CB40 + (M2C_FIELD(temp_s2, s16 *, 6) * 0x9C);
loop_14:
                if (var_s1 != M2C_FIELD(temp_s2, s16 *, 4)) {
                    temp_v0_2 = M2C_FIELD(var_s0, s16 *, 0x1A);
                    if ((temp_v0_2 != 4) && (temp_v0_2 == 0)) {
                        CrearObjetoMundo((s32) var_s0);
                    }
                    if (M2C_FIELD(var_s0, s16 *, 0x1A) != 4) {
                        M2C_FIELD(var_s0, s16 *, 0x1A) = 2;
                    }
                    var_s0 += 0x9C;
                    var_s1 = (var_s1 + 1) & 0xFFFF;
                    goto loop_14;
                }
            }
        }
    } while (*var_s3 != 0x7F);
}
