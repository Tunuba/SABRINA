#include "objeto.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s32 D_800C6594;
extern s32 D_800C6598;
extern s32 D_800C659C;
extern s32 D_800C65A0;
extern s32 D_800C65A4;
extern s32 D_800C65A8;


void func_80048DC0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    s32 sp54;
    s32 sp58;
    s32 sp5C;
    s32 temp_a0;
    s32 temp_v1;
    s32 temp_v1_2;
    void *temp_v0;

    temp_v0 = func_800252A0(5, arg0, M2C_FIELD(arg1, s32 *, 0), M2C_FIELD(arg1, s32 *, 4), /* extra? */ M2C_FIELD(arg1, s32 *, 8), /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 1, /* extra? */ 1);
    M2C_FIELD(temp_v0, s32 *, 0x54) = arg4;
    M2C_FIELD(temp_v0, s32 *, 0x58) = arg4;
    M2C_FIELD(temp_v0, s32 *, 0x5C) = arg4;
    func_800249CC((s32) temp_v0, arg3);
    func_8001E588((s32) temp_v0);
    M2C_FIELD(arg2, s32 *, 0) = (s32) p_sabrina->x;
    M2C_FIELD(arg2, s32 *, 4) = (s32) ((p_sabrina->y - 0xCCD) - 0x7FFF);
    M2C_FIELD(arg2, s32 *, 8) = (s32) p_sabrina->z;
    func_80048CF4((s32) temp_v0, arg2, 0x4000, (s32) &sp54);
    M2C_FIELD(temp_v0, s32 *, 0x38) = sp54;
    M2C_FIELD(temp_v0, s32 *, 0x3C) = sp58;
    M2C_FIELD(temp_v0, s32 *, 0x40) = sp5C;
    func_8001C45C((s32) &sp54);
    temp_v1 = sp54 >> 4;
    temp_a0 = (sp5C >> 4) * 0x33;
    sp54 = (s32) (temp_v1 * 0x280) >> 8;
    temp_v1_2 = (sp58 >> 4) * 0xCC;
    sp58 = (s32) ((sp58 >> 4) * 0x280) >> 8;
    sp5C = (s32) ((sp5C >> 4) * 0x280) >> 8;
    D_800C6594 = M2C_FIELD(temp_v0, s32 *, 0x24);
    D_800C6598 = M2C_FIELD(temp_v0, s32 *, 0x28);
    D_800C659C = M2C_FIELD(temp_v0, s32 *, 0x2C);
    D_800C6594 -= ((s32) (temp_v1 * 0xCC) >> 8) << 8;
    D_800C6598 -= (temp_v1_2 >> 8) << 8;
    D_800C659C -= ((s32) (temp_a0 * 4) >> 8) << 8;
    D_800C65A0 = M2C_FIELD(temp_v0, s32 *, 0x24) + M2C_FIELD(temp_v0, s32 *, 0x38);
    D_800C65A4 = M2C_FIELD(temp_v0, s32 *, 0x28) + M2C_FIELD(temp_v0, s32 *, 0x3C);
    D_800C65A8 = M2C_FIELD(temp_v0, s32 *, 0x2C) + M2C_FIELD(temp_v0, s32 *, 0x40);
    func_8003B38C((s32) &D_800C6594, (s32) &D_800C6594, (s32) &D_800C65A0);
    if (func_8003AE84() != 0) {
        M2C_FIELD(temp_v0, u8 *, 0x20) = (u8) (M2C_FIELD(temp_v0, u8 *, 0x20) | 0x80);
    }
}
