#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u8 D_80086338[];
extern s32 D_8007CA28;


void func_80055634(void *arg0) {
    s32 sp34;
    s32 sp38;
    s32 sp3C;
    s16 temp_s1;
    s16 temp_v0;
    s32 temp_a1;
    s32 temp_a2_2;
    s32 temp_s2;
    s32 var_s1;
    s32 var_s2;
    s32 var_s4;
    s32 var_s4_2;
    s32 var_s5;
    s32 var_s6;
    u8 *temp_a0;
    void *temp_a2;
    void *temp_s3;
    void *temp_v0_2;
    void *temp_v1;

    temp_s3 = arg0 + 0x74;
    if (D_8007CA28 == 0xA) {
        if ((M2C_FIELD(temp_s3, s32 *, 0x14) == 0) && (M2C_FIELD(temp_s3, s32 *, 0x18) == 0)) {
            var_s4 = 0;
            var_s1 = 0;
loop_8:
            if (var_s4 < D_8007CA28) {
                temp_v1 = D_80086338[var_s1];
                if (M2C_FIELD(temp_v1, s32 *, 0x74) != 0) {
                    M2C_FIELD(temp_s3, s32 *, 0x14) = func_8001BF8C(M2C_FIELD(arg0, s32 *, 0x24), M2C_FIELD(arg0, s32 *, 0x2C), M2C_FIELD(temp_v1, s32 *, 0x24), M2C_FIELD(temp_v1, s32 *, 0x2C));
                } else {
                    M2C_FIELD(temp_s3, s32 *, 0x18) = func_8001BF8C(M2C_FIELD(arg0, s32 *, 0x24), M2C_FIELD(arg0, s32 *, 0x2C), M2C_FIELD(temp_v1, s32 *, 0x24), M2C_FIELD(temp_v1, s32 *, 0x2C));
                }
                var_s4 += 1;
                var_s1 += 4;
                goto loop_8;
            }
        }
        if ((M2C_FIELD(temp_s3, s32 *, 0x14) != 0) && (M2C_FIELD(temp_s3, s32 *, 0x18) != 0)) {
            var_s4_2 = 0;
            var_s6 = 0;
loop_16:
            if (var_s4_2 < D_8007CA28) {
                var_s2 = M2C_FIELD(temp_s3, s32 *, 0x18);
                if (M2C_FIELD(D_80086338[var_s6], s32 *, 0x74) != 0) {
                    var_s2 = M2C_FIELD(temp_s3, s32 *, 0x14);
                    var_s5 = 0xA;
                } else {
                    var_s5 = -0xA;
                }
                temp_s2 = var_s2 >> 8;
                temp_s1 = rsin(var_s5);
                temp_v0 = rcos(var_s5);
                temp_a2 = D_80086338[var_s6];
                temp_a1 = (s32) (M2C_FIELD(temp_a2, s32 *, 0x24) - M2C_FIELD(arg0, s32 *, 0x24)) >> 4;
                temp_a2_2 = (s32) (M2C_FIELD(temp_a2, s32 *, 0x2C) - M2C_FIELD(arg0, s32 *, 0x2C)) >> 4;
                sp34 = (s32) ((temp_v0 * temp_a1) + (temp_s1 * temp_a2_2)) >> 8;
                sp3C = (s32) ((-temp_s1 * temp_a1) + (temp_v0 * temp_a2_2)) >> 8;
                sp38 = 0;
                func_8001C45C((s32) &sp34);
                var_s4_2 += 1;
                sp34 = ((s32) ((sp34 >> 4) * temp_s2) >> 8) << 8;
                sp3C = ((s32) ((sp3C >> 4) * temp_s2) >> 8) << 8;
                sp34 += M2C_FIELD(arg0, s32 *, 0x24);
                sp3C += M2C_FIELD(arg0, s32 *, 0x2C);
                temp_a0 = &D_80086338[var_s6];
                temp_v0_2 = *temp_a0;
                var_s6 += 4;
                M2C_FIELD(temp_v0_2, s32 *, 0x24) = sp34;
                M2C_FIELD(*temp_a0, s32 *, 0x2C) = sp3C;
                goto loop_16;
            }
        }
    }
}
