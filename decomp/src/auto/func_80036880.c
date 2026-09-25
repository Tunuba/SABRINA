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


s32 func_80036880(s32 arg0, s32 arg1) {
    s32 sp30;
    s32 sp34;
    s32 sp38;
    s32 sp3C;
    s32 sp40;
    s32 sp44;
    s32 sp48;
    s32 sp4C;
    s32 sp50;
    s32 sp54;
    s32 sp58;
    s32 sp5C;
    s32 temp_s4;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 temp_v0_3;
    s32 temp_v0_4;
    s32 temp_v0_5;
    s32 temp_v0_6;

    temp_v0 = p_sabrina->x - M2C_FIELD(D_8007CAFC, s32 *, 0x24);
    sp48 = temp_v0;
    sp50 = p_sabrina->z - M2C_FIELD(D_8007CAFC, s32 *, 0x2C);
    sp4C = p_sabrina->y - M2C_FIELD(D_8007CAFC, s32 *, 0x28);
    sp54 = M2C_FIELD(D_8007CAFC, s32 *, 0x24);
    sp58 = M2C_FIELD(D_8007CAFC, s32 *, 0x28);
    sp5C = M2C_FIELD(D_8007CAFC, s32 *, 0x2C);
    sp4C = 0;
    sp48 = -temp_v0;
    func_8001C45C((s32) &sp48);
    sp30 = sp48;
    temp_v0_2 = sp50;
    sp34 = sp4C;
    sp38 = temp_v0_2;
    sp48 = ((s32) ((sp48 >> 4) * 0x19) >> 8) << 8;
    sp50 = ((s32) ((sp50 >> 4) * 0x19) >> 8) << 8;
    sp44 = sp30;
    sp3C = temp_v0_2;
    sp40 = 0;
    temp_s4 = func_8001C33C(arg0, (s32) &sp3C);
    sp30 = ((s32) ((sp30 >> 4) * 0xC0) >> 8) << 8;
    sp38 = ((s32) ((sp38 >> 4) * 0xC0) >> 8) << 8;
    if (temp_s4 >= 0) {
        if (arg1 < 0) {
            return 1;
        }
        D_800C6594 = sp54;
        D_800C6598 = sp58;
        D_800C659C = sp5C;
        temp_v0_3 = sp54 + sp38;
        D_800C65A0 = temp_v0_3;
        temp_v0_4 = sp5C + sp30;
        D_800C65A8 = temp_v0_4;
        D_800C65A4 = sp58;
        func_8003B38C((s32) &D_800C6594, (s32) &D_800C6594, (s32) &D_800C65A0);
        if (func_8003AE84() != 0) {
            return 1;
        }
        D_800C6594 = sp54;
        D_800C6598 = sp58;
        D_800C659C = sp5C;
        D_800C65A0 = sp48 + temp_v0_3;
        D_800C65A8 = sp50 + temp_v0_4;
        D_800C65A4 = sp58;
        func_8003B38C((s32) &D_800C6594, (s32) &D_800C6594, (s32) &D_800C65A0);
        if (func_8003AE84() != 0) {
            return 1;
        }
        D_800C6594 = sp54;
        D_800C6598 = sp58;
        D_800C659C = sp5C;
        D_800C65A0 = temp_v0_3 - sp48;
        D_800C65A8 = temp_v0_4 - sp50;
        D_800C65A4 = sp58;
        func_8003B38C((s32) &D_800C6594, (s32) &D_800C6594, (s32) &D_800C65A0);
        if (func_8003AE84() != 0) {
            return 1;
        }
        goto block_9;
    }
block_9:
    if (temp_s4 <= 0) {
        if (arg1 > 0) {
            return 1;
        }
        D_800C6594 = sp54;
        D_800C6598 = sp58;
        D_800C659C = sp5C;
        temp_v0_5 = sp54 - sp38;
        D_800C65A0 = temp_v0_5;
        temp_v0_6 = sp5C - sp30;
        D_800C65A8 = temp_v0_6;
        D_800C65A4 = sp58;
        func_8003B38C((s32) &D_800C6594, (s32) &D_800C6594, (s32) &D_800C65A0);
        if (func_8003AE84() != 0) {
            return 1;
        }
        D_800C6594 = sp54;
        D_800C6598 = sp58;
        D_800C659C = sp5C;
        D_800C65A0 = sp48 + temp_v0_5;
        D_800C65A8 = sp50 + temp_v0_6;
        D_800C65A4 = sp58;
        func_8003B38C((s32) &D_800C6594, (s32) &D_800C6594, (s32) &D_800C65A0);
        if (func_8003AE84() != 0) {
            return 1;
        }
        D_800C6594 = sp54;
        D_800C6598 = sp58;
        D_800C659C = sp5C;
        D_800C65A0 = temp_v0_5 - sp48;
        D_800C65A8 = temp_v0_6 - sp50;
        D_800C65A4 = sp58;
        func_8003B38C((s32) &D_800C6594, (s32) &D_800C6594, (s32) &D_800C65A0);
        if (func_8003AE84() != 0) {
            return 1;
        }
        goto block_18;
    }
block_18:
    return 0;
}
