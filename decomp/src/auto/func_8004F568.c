#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u8 D_800D15E4[];
extern s8 D_800D1610;
extern s8 D_800D1611;
extern s8 D_800D1612;
extern s8 D_800D1613;
extern u8 D_800D1614[];
extern u8 D_800D1810[];
extern u8 D_800D3090[];
extern u8 D_800D5090[];
extern u8 D_80075938[];
extern s8 D_80075946[];
extern u8 D_8007594C[];
extern s8 D_8007595D[];
extern s8 D_8007595F[];
extern u8 D_8007C8EC[];
extern s16 D_8007CA20;
extern s32 D_8007CC40;
extern s32 D_8007CC44;
extern s16 D_8007CC4E;
extern u16 D_8007CC50;
extern u16 D_8007CC56;
extern s16 D_8007CC58;
extern s16 D_8007CC5A;
extern s32 (*D_8007CC34)();


void func_8004F568(s32 arg0, s32 arg1) {
    s32 sp34;
    s32 temp_ret;
    s32 temp_v0_2;
    s8 temp_v0;
    void *temp_a2;

    sp34 = 0x45;
    D_8007CC5A = 0;
    D_8007CC58 = 0;
    D_8007CC4E = 0;
    D_8007CA20 = 0xFC;
    memset((s32) D_800D3090, 0, 0x2000);
    if (D_8007CC56 == 2) {
        temp_a2 = D_800D1810 + (arg1 * 0x258);
        D_8007CC40 = func_80051024(arg0, (s32) D_8007C8EC, (s32) temp_a2, (s32) (D_800D15E4 + (arg1 * 4)), /* extra? */ 0, /* extra? */ 0xF);
        if (D_8007CC40 == 0) {
            if (*(D_800D5090 + (D_8007CC50 * 2)) != 0) {
                sp34 = func_800515B0(arg0, (s32) (temp_a2 + (D_8007CC50 * 0x28)));
                func_80051298(0, 0, (s32) &sp34);
            }
            do {
                func_80050AB8(arg0, (s32) D_80075938, 2);
                sp34 = func_800513B4(arg0, (s32) D_80075938, 1);
                func_80051298(0, 0, (s32) &sp34);
                if (sp34 == 6) {
                    *D_80075946 += 1;
                    func_80050C40();
                }
            } while (sp34 == 6);
            temp_ret = func_8004AF50();
            temp_v0 = temp_ret;
            temp_v0_2 = (temp_ret / 10) + ((u32) temp_v0 >> 0x1F);
            *D_8007595D = temp_v0_2 + 0x4F;
            *D_8007595F = (temp_v0 - (temp_v0_2 * 0xA)) + 0x4F;
            D_800D1610 = 0x53;
            D_800D1611 = 0x43;
            D_800D1612 = 0x11;
            D_800D1613 = 1;
            strcpy((s32) D_800D1614, (s32) D_8007594C);
            memcpy((s32) D_800D3090, (s32) &D_800D1610, 0x200);
            if (D_8007CC34 != NULL) {
                D_8007CC34(D_800D3090 + 0x200);
            }
            D_8007CC40 = func_80050F0C(arg0, (s32) D_80075938, (s32) D_800D3090, 0, /* extra? */ 0x2000);
            func_80051298(0, 0, (s32) &sp34);
            func_80050C40();
            D_8007CC44 = 2;
            D_8007CA20 = 0;
        }
    }
}
