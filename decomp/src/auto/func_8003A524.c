#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u16 D_8007CBD4;


s32 func_8003A524(s32 arg0, s32 arg1) {
    s32 sp2C;
    s32 sp30;
    s32 sp34;
    s32 sp38;
    s32 sp3C;
    s32 sp40;
    s32 sp44;
    s32 sp48;
    s32 sp4C;
    s32 temp_lo;
    s32 temp_s3;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 temp_v0_3;

    if (M2C_FIELD(arg1, u16 *, 0x16) & D_8007CBD4) {
        return 0;
    }
    sp44 = (s32) M2C_FIELD(M2C_FIELD(arg1, void **, 0), s16 *, 0);
    sp48 = (s32) M2C_FIELD(M2C_FIELD(arg1, void **, 0), s16 *, 2);
    sp4C = (s32) M2C_FIELD(M2C_FIELD(arg1, void **, 0), s16 *, 4);
    sp2C = M2C_FIELD(arg1, s8 *, 0x18) * 2;
    sp30 = M2C_FIELD(arg1, s8 *, 0x19) * 2;
    sp34 = M2C_FIELD(arg1, s8 *, 0x1A) * 2;
    temp_v0_2 = func_8001C33C((s32) &sp2C, arg0 + 0x24);
    if (temp_v0_2 >= 0) {
        return 0;
    }
    if ((sp2C + sp34) == 0) {
        return func_8003A46C(arg0, arg1, (s32) &sp2C);
    }
    temp_s3 = -func_8001C33C((s32) &sp44, (s32) &sp2C);
    temp_v0_3 = temp_s3 + func_8001C33C((s32) &sp2C, arg0);
    if (((s32) (temp_v0_2 * 2) >> 8) < -temp_v0_3) {
        return 0;
    }
    temp_lo = (s32) (temp_v0_3 * -0x100) / temp_v0_2;
    sp38 = M2C_FIELD(arg0, s32 *, 0) + ((s32) (M2C_FIELD(arg0, s32 *, 0x24) * temp_lo) >> 8);
    sp3C = M2C_FIELD(arg0, s32 *, 4) + ((s32) (M2C_FIELD(arg0, s32 *, 0x28) * temp_lo) >> 8);
    sp40 = M2C_FIELD(arg0, s32 *, 8) + ((s32) (M2C_FIELD(arg0, s32 *, 0x2C) * temp_lo) >> 8);
    temp_v0 = (PuntoEnTriangulo((s32) &sp2C, (s32) &sp38, arg1) != 0) & 0xFF;
    if (temp_v0 != 0) {
        M2C_FIELD(arg0, s32 *, 0x30) = sp38;
        M2C_FIELD(arg0, s32 *, 0x34) = sp3C;
        M2C_FIELD(arg0, s32 *, 0x38) = sp40;
        M2C_FIELD(arg0, s32 *, 0x3C) = (s32) (sp2C << 8);
        M2C_FIELD(arg0, s32 *, 0x40) = (s32) (sp30 << 8);
        M2C_FIELD(arg0, s32 *, 0x44) = (s32) (sp34 << 8);
    }
    return temp_v0;
}
