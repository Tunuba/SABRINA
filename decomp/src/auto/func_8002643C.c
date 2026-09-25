#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u32 D_800913F8;
extern u32 D_800913FC;
extern s32 * D_8006CF6C;
extern void * D_8006CF70;
extern s32 D_8006CFC8;


s32 func_8002643C(s32 arg0, s32 arg1) {
    s16 var_s1;
    s8 temp_s2;
    s8 var_v0;
    u32 temp_v0;
    u32 var_v1;

    var_s1 = 0x88;
    if ((((s32) *M2C_FIELD(arg0, u8 **, 0x3C) >> 4) == 8) && ((u8) M2C_FIELD(arg0, u8 *, 0x44) >= 9U)) {
        var_s1 = 0x22;
    }
    do {

    } while (!(M2C_FIELD(D_8006CF70, u16 *, 4) & 2));
    func_8002908C(0x190);
    temp_s2 = M2C_FIELD(D_8006CF70, u8 *, 0) & 0xFF;
    if ((M2C_FIELD(arg0, u8 *, 0x44) != 0) || ((temp_s2 >> 4) != 8)) {
        M2C_FIELD(D_8006CF70, s16 *, 0xE) = var_s1;
    } else {
        M2C_FIELD(D_8006CF70, s16 *, 0xE) = 0x22;
    }
    if (!(*D_8006CF6C & 0x80)) {
loop_11:
        var_v1 = *(u16 *)0x1F801120 & 0xFFFF;
        if (var_v1 < (u32) D_800913FC) {
            if (*(u16 *)0x1F801128 != 0) {
                var_v1 += *(u16 *)0x1F801128;
            } else {
                var_v1 += 0x10000;
            }
        }
        temp_v0 = var_v1 - D_800913FC;
        if (*(u16 *)0x1F801124 & 0x200) {
            if (temp_v0 >= (u32) D_800913F8) {
                return -2;
            }
            goto block_19;
        }
        var_v0 = -2;
        if ((u32) (temp_v0 >> 3) < (u32) D_800913F8) {
block_19:
            if (*D_8006CF6C & 0x80) {
                goto block_20;
            }
            goto loop_11;
        }
        /* Duplicate return node #30. Try simplifying control flow for better match */
        return (s32) var_v0;
    }
block_20:
    if ((M2C_FIELD(arg0, u8 *, 0xE8) != 8) && (D_8006CFC8 == 2)) {
        func_8002908C(0x3C);
        do {

        } while (func_800290AC() == 0);
    }
    M2C_FIELD(D_8006CF70, u8 *, 0) = (u8) arg1;
    if ((D_8006CFC8 == 3) && (temp_s2 == 0x80)) {
        *D_8006CF6C = -0x81;
        M2C_FIELD(D_8006CF70, u16 *, 0xA) = (u16) (M2C_FIELD(D_8006CF70, u16 *, 0xA) | 0x10);
    }
    M2C_FIELD(arg0, u8 *, 0x45) = (u8) (M2C_FIELD(arg0, u8 *, 0x45) + 1);
    if (M2C_FIELD(arg0, u8 *, 0x44) != 0xFF) {
        *(M2C_FIELD(arg0, u8 **, 0x3C) + M2C_FIELD(arg0, u8 *, 0x44)) = temp_s2;
    }
    var_v0 = temp_s2;
    M2C_FIELD(arg0, u8 *, 0x44) = (u8) (M2C_FIELD(arg0, u8 *, 0x44) + 1);
    return (s32) var_v0;
}
