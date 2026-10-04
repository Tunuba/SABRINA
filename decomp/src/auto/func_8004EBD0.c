#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u8 D_800D50B0[];
extern u8 D_800D50B8[];
extern u8 D_800D50BA[];
extern u8 D_800D50BC[];
extern u8 D_800D50BE[];
extern u8 D_800D50C0[];
extern u8 D_800D50C1[];
extern u8 D_800D50C2[];
extern u8 D_800D50C4[];
extern u8 D_800D50C6[];
extern u8 D_800D50C8[];

void func_8004EBD0(void) {
    M2C_UNK sp28;
    s16 var_s2;
    s32 var_s0;
    s32 var_s1;
    u16 var_s3;
    u8 *temp_a0;
    u8 *temp_a0_2;
    u8 *temp_a1;
    u8 *temp_v0;

    func_8004FD04(0);
    func_80050938();
    _bu_init();
    func_8004EB04();
    var_s1 = 0;
    var_s0 = 0;
    var_s3 = 0;
    var_s2 = 0;
loop_2:
    if (var_s1 != 0xF) {
        D_800D50B8[var_s0] = 0x10;
        D_800D50BA[var_s0] = 0x10;
        temp_a1 = &D_800D50C2[var_s0];
        temp_a0 = &D_800D50C4[var_s0];
        *temp_a1 = var_s3;
        *temp_a0 = 0x1E0U;
        D_800D50C6[var_s0] = var_s2;
        D_800D50C8[var_s0] = 0x1F0;
        D_800D50C0[var_s0] = (*temp_a1 & 0x3F) * 4;
        D_800D50C1[var_s0] = (u8) *temp_a0;
        temp_a0_2 = &D_800D50B0[var_s0];
        D_800D50BC[var_s0] = GetTPage(0, 0, M2C_FIELD(temp_a0_2, u16 *, 0x12) & ~0x3F, (s32) M2C_FIELD(temp_a0_2, u16 *, 0x14));
        temp_v0 = &D_800D50B0[var_s0];
        D_800D50BE[var_s0] = LoadClut2((s32) &sp28, (s32) M2C_FIELD(temp_v0, u16 *, 0x16), (s32) M2C_FIELD(temp_v0, u16 *, 0x18));
        var_s1 = (var_s1 + 1) & 0xFFFF;
        var_s2 += 0x20;
        var_s3 += 0x10;
        var_s0 += 0x20;
        goto loop_2;
    }
}
