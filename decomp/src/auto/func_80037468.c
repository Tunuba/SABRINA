#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u8 D_8007C8AC;
extern s8 nivel_actual;
extern s32 func_80037738();


void func_80037468(void *arg0, void *arg1) {
    s32 sp30;
    s32 sp34;
    s32 sp38;
    s32 sp3C;
    s32 sp40;
    s32 sp44;
    s32 temp_v0_3;
    s32 temp_v0_4;
    s32 temp_v0_5;
    s32 var_s3;
    s8 temp_v0;
    u16 temp_v0_2;
    void *temp_s2;

    temp_s2 = arg0 + 0x74;
    temp_v0 = M2C_FIELD(temp_s2, s8 *, 0x1F);
    if (((temp_v0 >= 8) || !(M2C_FIELD(arg1, s16 *, 0x112) & 0x8000)) && !(M2C_FIELD(arg1, s16 *, 0x112) & 0x100)) {
        temp_v0_2 = M2C_FIELD(arg1, u16 *, 0x22);
        switch (temp_v0_2) {
        case 0x0:
        case 0x1:
        case 0x3:
        case 0x4:
        case 0x5:
        case 0x6:
        case 0x7:
        case 0x8:
        case 0x9:
        case 0xA:
        case 0xB:
        case 0xC:
        case 0xD:
        case 0x12:
        case 0x13:
        case 0x14:
        case 0x15:
        case 0x17:
        case 0x18:
        case 0x19:
        case 0x1A:
        case 0x1B:
        case 0x1D:
        case 0x1F:
        case 0x21:
        case 0x22:
        case 0x23:
        case 0x24:
        case 0x25:
        case 0x26:
        case 0x27:
        case 0x2A:
        case 0x2B:
        case 0x2C:
        case 0x2D:
        case 0x2E:
        case 0x34:
            return;
        case 0x1C:
            if (temp_v0 >= 8) {
                if ((nivel_actual != 6) && (nivel_actual != 0xC) && (nivel_actual != 3) && (nivel_actual != 9)) {
                    return;
                }
            default:
            case 0x2:
            case 0xE:
            case 0xF:
            case 0x10:
            case 0x11:
            case 0x16:
            case 0x1E:
            case 0x20:
            case 0x2F:
            case 0x30:
            case 0x31:
            case 0x32:
            case 0x33:
block_14:
                sp30 = M2C_FIELD(arg1, s32 *, 0x24) - M2C_FIELD(arg0, s32 *, 0x24);
                temp_v0_3 = (M2C_FIELD(arg1, s32 *, 0x28) - M2C_FIELD(arg0, s32 *, 0x28)) - 0x8000;
                sp34 = temp_v0_3;
                temp_v0_4 = M2C_FIELD(arg1, s32 *, 0x2C) - M2C_FIELD(arg0, s32 *, 0x2C);
                sp38 = temp_v0_4;
                var_s3 = 0;
                if (func_800221FC(0, 0, 0, sp30, /* extra? */ temp_v0_3, /* extra? */ temp_v0_4) < 0x24000) {
                    var_s3 = 1;
                }
                if (D_8007C8AC == 1) {
                    sp30 = M2C_FIELD(arg1, s32 *, 0x24) - M2C_FIELD(arg0, s32 *, 0x24);
                    sp34 = (M2C_FIELD(arg1, s32 *, 0x28) - M2C_FIELD(arg0, s32 *, 0x28)) - 0x8000;
                    sp38 = M2C_FIELD(arg1, s32 *, 0x2C) - M2C_FIELD(arg0, s32 *, 0x2C);
                    func_8002205C((s32) &sp3C, (s32) M2C_FIELD(arg0, s16 *, 0x30), (s32) M2C_FIELD(arg0, s16 *, 0x32));
                    func_8001C45C((s32) &sp3C);
                    func_8001C45C((s32) &sp30);
                    sp30 = sp30 >> 4;
                    sp34 = sp34 >> 4;
                    sp38 = sp38 >> 4;
                    sp3C = sp3C >> 4;
                    sp40 = sp40 >> 4;
                    sp44 = sp44 >> 4;
                    temp_v0_5 = func_8001C33C((s32) &sp30, (s32) &sp3C);
                    if (((temp_v0_5 > 0) && (temp_v0_5 >= 0xBE)) || (var_s3 != 0)) {
                        M2C_FIELD(temp_s2, void **, 0x10) = arg1;
                        M2C_FIELD(temp_s2, s32 *, 4) = temp_v0_5;
                        func_80039BA0((s32) (arg0 + 0xF4), 0xC000);
                        M2C_FIELD(arg0, s16 *, 0x114) = 0x26;
                        M2C_FIELD(arg0, s16 *, 0x112) = 0x3000;
                        goto block_22;
                    }
                } else {
                    M2C_FIELD(temp_s2, s32 *, 4) = 0x80;
                    M2C_FIELD(temp_s2, s32 *, 8) = 0x140000;
block_22:
                    M2C_FIELD(arg0, s32 (**)(s32, s32), 8) = func_80037738;
                }
            }
            break;
        case 0x28:
        case 0x29:
            if (temp_v0 < 8) {
                return;
            }
            goto block_14;
        }
    }
}
