#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s8 D_800C855F;
extern s32 D_800C98B0;

void func_80056B18(s32 arg0) {
    void *temp_s0;
    void *temp_s2;

    temp_s2 = arg0 + 0x74;
    M2C_FIELD(temp_s2, s32 *, 0x28) = 0;
    M2C_FIELD(temp_s2, s32 *, 0x30) = 0;
    M2C_FIELD(temp_s2, s32 *, 0x2C) = func_80056A08();
    if (func_8002ECFC(arg0) != 0) {
        temp_s0 = M2C_FIELD(arg0, void **, 0x1C);
        M2C_FIELD(temp_s0, s16 *, 0x4C) = 0;
        M2C_FIELD(temp_s0, u8 *, 0x51) = (u8) *M2C_FIELD(arg0, u16 **, 0x64);
        M2C_FIELD(temp_s0, u8 *, 0x50) = 0U;
        M2C_FIELD(temp_s0, u8 *, 0x53) = (u8) M2C_FIELD(temp_s0, u8 *, 0x51);
        M2C_FIELD(temp_s0, u8 *, 0x52) = (u8) M2C_FIELD(temp_s0, u8 *, 0x50);
        M2C_FIELD(temp_s0, s8 *, 8) = func_80030068(M2C_FIELD(M2C_FIELD(arg0, void **, 0x60), s32 *, 4));
        M2C_FIELD(temp_s0, s16 *, 0x4E) = 0x800;
    }
    M2C_FIELD(temp_s2, s32 *, 0x34) = 0;
    func_800483F8(arg0);
    if (D_800C98B0 == 1) {
        M2C_FIELD(arg0, s16 *, 0x70) = 6;
    }
    M2C_FIELD(temp_s2, s32 *, 0x38) = 0;
    if (D_800C855F >= 4) {
        M2C_FIELD(temp_s2, s32 *, 0x38) = 1;
    }
}
