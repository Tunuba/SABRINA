#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u8 D_80074BC4[];
extern s8 nivel_actual;
extern s32 func_80024F6C();
extern s32 func_80038E50();

u8 D_80074BC4[4];                                   /* unable to generate initializer: cannot parse func_80038E50 as integer */

void func_80037738(void *arg0, void *arg1) {
    M2C_UNK (*temp_v0_2)(void *);
    u16 temp_v0;
    void *temp_s1;

    temp_s1 = arg0 + 0x74;
    if (!(M2C_FIELD(arg1, s16 *, 0x112) & 0x100)) {
        temp_v0 = M2C_FIELD(arg1, u16 *, 0x22);
        switch (temp_v0) {
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
            if (M2C_FIELD(temp_s1, s8 *, 0x1F) >= 8) {
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
block_12:
                if (M2C_FIELD(arg1, s16 *, 0x112) & 0x100) {
                    if (arg1 != M2C_FIELD(temp_s1, void **, 0x14)) {
                        M2C_FIELD(temp_s1, s32 *, 0x10) = 0;
                        M2C_FIELD(arg0, s16 *, 0x112) = 0x3800;
                        M2C_FIELD(arg0, s16 *, 0x114) = 0x27;
                        M2C_FIELD(arg0, s16 *, 0x32) = (s16) (M2C_FIELD(arg0, s16 *, 0x32) + (s16) (func_80021CE4(0xC8) + 0x79C));
                        M2C_FIELD(arg0, s16 *, 0x30) = (s16) (M2C_FIELD(arg0, s16 *, 0x30) + (s16) (func_80021CE4(0xC8) - 0x64));
                        M2C_FIELD(temp_s1, s32 *, 0xC) = 0;
                        M2C_FIELD(temp_s1, void **, 0x14) = arg1;
                        return;
                    }
                } else {
                    CrearParticula(0x13, (s32) arg0, 0, 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0, /* extra? */ 0x19, /* extra? */ 0x202, /* extra? */ 0);
                    if (M2C_FIELD(arg1, s16 *, 0x112) & 3) {
                        temp_v0_2 = *(D_80074BC4 + (M2C_FIELD(temp_s1, s8 *, 0x1F) * 0x10));
                        if (temp_v0_2 != NULL) {
                            temp_v0_2(arg1);
                        }
                        M2C_FIELD(arg1, M2C_UNK (**)(void *, void *), 8)(arg1, arg0);
                    }
                    M2C_FIELD(arg0, s32 (**)(), 8) = func_80024F6C;
                    M2C_FIELD(temp_s1, s32 *, 0xC) = (s32) M2C_FIELD(temp_s1, s32 *, 8);
                }
            }
            break;
        case 0x28:
        case 0x29:
            if (M2C_FIELD(temp_s1, s8 *, 0x1F) < 8) {
                return;
            }
            goto block_12;
        }
    }
}
