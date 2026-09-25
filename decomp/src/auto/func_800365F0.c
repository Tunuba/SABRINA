#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s32 D_800C6594;
extern s32 D_800C6598;
extern s32 D_800C659C;
extern s32 D_800C65A0;
extern s32 D_800C65A4;
extern s32 D_800C65A8;
extern void * D_8007CAFC;


s32 func_800365F0(s32 arg0, s32 arg1) {
    s32 sp34;
    s32 sp38;
    s32 sp3C;
    s32 temp_a0;
    s32 temp_a0_2;
    s32 temp_s0;
    s32 temp_s1;
    s32 temp_s2;
    s32 temp_s3;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 temp_v0_3;
    s32 var_v0;

    sp34 = M2C_FIELD(D_8007CAFC, s32 *, 0x24) - p_sabrina->x;
    sp38 = 0;
    sp3C = M2C_FIELD(D_8007CAFC, s32 *, 0x2C) - p_sabrina->z;
    func_8001C45C((s32) &sp34);
    temp_a0 = sp3C >> 4;
    temp_s3 = ((s32) (temp_a0 * 0x33) >> 8) << 8;
    temp_a0_2 = sp34 >> 4;
    temp_s1 = ((s32) (temp_a0 << 7) >> 8) << 8;
    temp_v0 = (s32) (temp_a0_2 << 7) >> 8;
    temp_s0 = temp_v0 * -0x100;
    temp_v0_2 = temp_v0 << 8;
    sp34 = temp_v0_2;
    temp_s2 = ((s32) (temp_a0_2 * 0x33) >> 8) * -0x100;
    temp_v0_3 = ((s32) ((sp3C >> 4) << 7) >> 8) << 8;
    sp3C = temp_v0_3;
    sp38 = p_sabrina->y;
    D_800C6594 = (p_sabrina->x + temp_s3) - temp_v0_2;
    D_800C659C = (p_sabrina->z + temp_s2) - temp_v0_3;
    D_800C6598 = p_sabrina->y + 0xFFFE999A;
    D_800C65A0 = M2C_FIELD(D_8007CAFC, s32 *, 0x24) + temp_s1;
    D_800C65A8 = M2C_FIELD(D_8007CAFC, s32 *, 0x2C) + temp_s0;
    D_800C65A4 = M2C_FIELD(D_8007CAFC, s32 *, 0x28);
    func_8003B38C((s32) &D_800C6594, (s32) &D_800C6594, (s32) &D_800C65A0);
    if (func_8003AE84() != 0) {
        *arg1 = 1;
        *arg0 = -0x12C;
        return 1;
    }
    *arg1 = 0;
    D_800C6594 = (p_sabrina->x - temp_s3) - sp34;
    D_800C659C = (p_sabrina->z - temp_s2) - sp3C;
    D_800C6598 = p_sabrina->y + 0xFFFE999A;
    D_800C65A0 = M2C_FIELD(D_8007CAFC, s32 *, 0x24) - temp_s1;
    D_800C65A8 = M2C_FIELD(D_8007CAFC, s32 *, 0x2C) - temp_s0;
    D_800C65A4 = M2C_FIELD(D_8007CAFC, s32 *, 0x28);
    func_8003B38C((s32) &D_800C6594, (s32) &D_800C6594, (s32) &D_800C65A0);
    var_v0 = 0;
    if (func_8003AE84() != 0) {
        *arg0 = 0x12C;
        var_v0 = 1;
    }
    return var_v0;
}
