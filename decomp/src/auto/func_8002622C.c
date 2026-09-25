#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s32 D_800913F8;
extern s32 D_800913FC;
extern s32 * D_8006CF6C;
extern void * D_8006CF70;


s32 func_8002622C(s32 arg0, s32 arg1) {
    s16 var_s1;
    s32 temp_s2;
    s8 temp_s2_2;
    s8 var_v0;

    if (arg1 < 0) {
        M2C_FIELD(arg0, u8 *, 0x44) = 0xFFU;
        M2C_FIELD(arg0, u8 *, 0x45) = 1U;
        *M2C_FIELD(arg0, s8 **, 0x40) = ~arg1;
        temp_s2 = M2C_FIELD(D_8006CF70, u8 *, 0) & 0xFF;
        if (!(M2C_FIELD(D_8006CF70, u16 *, 4) & 1)) {
            do {

            } while (!(M2C_FIELD(D_8006CF70, u16 *, 4) & 1));
        }
        do {

        } while (func_800290AC() == 0);
        M2C_FIELD(D_8006CF70, u8 *, 0) = (u8) ~arg1;
        return temp_s2;
    }
    var_s1 = 0x88;
    if (((s32) *M2C_FIELD(arg0, u8 **, 0x3C) >> 4) == 8) {
        if ((u8) M2C_FIELD(arg0, u8 *, 0x44) >= 9U) {
            var_s1 = 0x22;
        }
    }
    D_800913F8 = 0x1AE;
    D_800913FC = (s32) *(u16 *)0x1F801120;
    if (!(M2C_FIELD(D_8006CF70, u16 *, 4) & 2)) {
        do {

        } while (!(M2C_FIELD(D_8006CF70, u16 *, 4) & 2));
    }
    M2C_FIELD(D_8006CF70, s16 *, 0xE) = var_s1;
    temp_s2_2 = M2C_FIELD(D_8006CF70, u8 *, 0) & 0xFF;
    if (!(*D_8006CF6C & 0x80)) {
loop_12:
        var_v0 = -0x14;
        if (func_800290AC() == 0) {
            if (*D_8006CF6C & 0x80) {
                goto block_14;
            }
            goto loop_12;
        }
    } else {
block_14:
        M2C_FIELD(D_8006CF70, u8 *, 0) = (u8) arg1;
        if (var_s1 == 0x22) {
            *D_8006CF6C = -0x81;
            M2C_FIELD(D_8006CF70, u16 *, 0xA) = (u16) (M2C_FIELD(D_8006CF70, u16 *, 0xA) | 0x10);
        }
        M2C_FIELD(arg0, u8 *, 0x45) = (u8) (M2C_FIELD(arg0, u8 *, 0x45) + 1);
        *(M2C_FIELD(arg0, u8 **, 0x3C) + M2C_FIELD(arg0, u8 *, 0x44)) = temp_s2_2;
        M2C_FIELD(arg0, u8 *, 0x44) = (u8) (M2C_FIELD(arg0, u8 *, 0x44) + 1);
        var_v0 = temp_s2_2;
    }
    return (s32) var_v0;
}
