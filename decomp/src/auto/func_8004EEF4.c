#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u8 D_800D15E4[];
extern u8 D_800D1810[];
extern u8 D_800D2AD0[];
extern u8 D_800D2E90[];
extern u8 D_800D2E94[];
extern u8 D_800D2EF0[];
extern u8 D_800D2F10[];
extern u8 D_800D5090[];
extern u8 D_800D50B0[];
extern u8 D_800D50B8[];
extern u8 D_800D50BA[];
extern u8 D_800D50C2[];
extern u8 D_800D50C4[];
extern u8 D_80075A04[];
extern u8 D_80075A84[];
extern u8 D_8007C8E4[];
extern u8 D_8007C8EC[];
extern s16 D_8007CA20;
extern s32 D_8007CC40;
extern u16 D_8007CC56;
extern u16 D_8007CC58;
extern u16 D_8007CC5A;


void func_8004EEF4(s32 arg0, s32 arg1) {
    void *sp44;
    void *sp48;
    s16 sp4C;                                       /* compiler-managed */
    s16 sp4E;                                       /* compiler-managed */
    s16 sp50;
    s16 sp52;
    s32 sp54;
    s16 temp_v0_4;
    s16 temp_v0_6;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 temp_v0_3;
    s32 var_s1;
    s32 var_s2;
    s32 var_s3;
    s32 var_s4;
    s32 var_t9;
    s32 var_t9_2;
    s32 var_t9_3;
    s32 var_t9_4;
    u8 *temp_v0_5;
    u8 *temp_v0_7;
    void *var_s0;

    sp4C = M2C_FIELD(D_8007C8E4, s16 *, 0);
    sp4E = M2C_FIELD(D_8007C8E4, s16 *, 2);
    sp50 = M2C_FIELD(D_8007C8E4, s16 *, 4);
    sp52 = M2C_FIELD(D_8007C8E4, s16 *, 6);
    D_8007CA20 = 0xEC;
    if (D_8007CC56 == 2) {
        sp44 = D_800D15E4 + (arg1 * 4);
        sp48 = D_800D1810 + (arg1 * 0x258);
        do {
            D_8007CC40 = func_80051024(arg0, (s32) "*", (s32) sp48, (s32) sp44, /* extra? */ 0, /* extra? */ 0xF);
            if (D_8007CC40 == 0) {
                var_s0 = sp48;
                var_s4 = 0;
                D_8007CC58 = 0;
                var_s1 = 0;
                var_s3 = 0;
                var_s2 = 0;
loop_18:
                if (var_s4 != 0xF) {
                    temp_v0 = M2C_FIELD(var_s0, s32 *, 0x18);
                    var_t9 = temp_v0 >> 0xD;
                    if (temp_v0 < 0) {
                        var_t9 = (s32) (temp_v0 + 0x1FFF) >> 0xD;
                    }
                    D_8007CC58 += var_t9 & 0xFFFF;
                    temp_v0_2 = M2C_FIELD(var_s0, s32 *, 0x18);
                    var_t9_2 = temp_v0_2 >> 0xD;
                    if (temp_v0_2 < 0) {
                        var_t9_2 = (s32) (temp_v0_2 + 0x1FFF) >> 0xD;
                    }
                    if (var_t9_2 != 0) {
                        temp_v0_3 = func_80050AB8(arg0, (s32) var_s0, 1);
                        sp54 = temp_v0_3;
                        if (temp_v0_3 == 0) {
                            func_80051298(0, 0, (s32) &sp54);
                            func_80050C84((s32) D_800D2E90, 0, 0x200);
                            func_80051298(0, 0, (s32) &sp54);
                            func_80050C40();
                            sp4C = D_800D50C2[var_s1];
                            sp4E = D_800D50C4[var_s1];
                            temp_v0_4 = D_800D50B8[var_s1];
                            var_t9_3 = temp_v0_4 >> 2;
                            if (temp_v0_4 < 0) {
                                var_t9_3 = (s32) (temp_v0_4 + 3) >> 2;
                            }
                            sp50 = (s16) var_t9_3;
                            sp52 = D_800D50BA[var_s1];
                            SubirAVRAM((s32) &sp4C, (s32) D_800D2F10);
                            func_80012D74(0);
                            temp_v0_5 = &D_800D50B0[var_s1];
                            LoadClut2((s32) D_800D2EF0, (s32) M2C_FIELD(temp_v0_5, u16 *, 0x16), (s32) M2C_FIELD(temp_v0_5, u16 *, 0x18));
                            memcpy((s32) &D_800D2AD0[var_s3], (s32) D_800D2E94, 0x40);
                            D_800D5090[var_s2] = 1;
                        } else {
                            D_8007CC58 -= 1;
                        }
                    } else {
                        D_8007CC5A += 1;
                        sp4C = D_800D50C2[var_s1];
                        sp4E = D_800D50C4[var_s1];
                        temp_v0_6 = D_800D50B8[var_s1];
                        var_t9_4 = temp_v0_6 >> 2;
                        if (temp_v0_6 < 0) {
                            var_t9_4 = (s32) (temp_v0_6 + 3) >> 2;
                        }
                        sp50 = (s16) var_t9_4;
                        sp52 = D_800D50BA[var_s1];
                        SubirAVRAM((s32) &sp4C, (s32) D_80075A04);
                        func_80012D74(0);
                        temp_v0_7 = &D_800D50B0[var_s1];
                        LoadClut2((s32) D_80075A84, (s32) M2C_FIELD(temp_v0_7, u16 *, 0x16), (s32) M2C_FIELD(temp_v0_7, u16 *, 0x18));
                        D_800D5090[var_s2] = 0;
                    }
                    var_s0 += 0x28;
                    var_s4 = (var_s4 + 1) & 0xFFFF;
                    var_s2 += 2;
                    var_s3 += 0x40;
                    var_s1 += 0x20;
                    goto loop_18;
                }
                D_8007CA20 = 0;
            }
        } while (D_8007CC40 != 0);
    }
}
