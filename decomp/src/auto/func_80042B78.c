#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s32 D_800C6F7C;
extern s32 D_800C6F80;
extern u8 D_800C6FC6[];
extern s8 D_800C6FDD;
extern u8 D_800C6FDE[];
extern u8 D_800C6FEA[];
extern u16 D_800C7500;
extern u16 D_800C7502;
extern u16 D_800C7504;
extern u16 D_800C7506;
extern u8 D_800C7510;
extern u16 D_800C7528;
extern u8 D_800C76A8;
extern u16 D_800C76AA;
extern u8 D_800C76AC;
extern u16 D_800C76AE;
extern s8 D_800C76DC;
extern s8 D_800C7700;


void func_80042B78(void) {
    s32 sp10;
    s32 sp14;
    u16 sp18;
    u16 sp1A;
    u16 sp24;
    s32 sp2C;
    u16 sp4A;
    u16 sp4C;
    s16 var_a1;
    s32 *temp_v0_2;
    s32 *var_v1;
    s32 temp_v0;
    s32 var_s0;
    s32 var_s0_2;
    s32 var_s0_3;
    s32 var_s0_4;
    s32 var_s1;
    s32 var_s1_3;
    s32 var_s2_2;
    s32 var_v0;
    s8 *var_s1_2;
    u16 *var_s2_3;
    u16 *var_s3;
    u16 *var_s4;
    u16 *var_s5;
    u16 *var_s6;
    u16 *var_s7;
    u8 *var_s1_4;
    u8 *var_s2;

    temp_v0 = (D_800C6F7C + 1) & 0xF;
    D_800C6F7C = temp_v0;
    (&D_800C6F80)[temp_v0] = 0;
    var_s0 = 0;
    if (D_800C76DC > 0) {
        var_s2 = D_800C6FC6;
        var_s1 = 0;
        do {
            SpuGetVoiceEnvelope(var_s0, (s32) var_s2);
            if (D_800C6FC6[var_s1] == 0) {
                temp_v0_2 = &(&D_800C6F80)[D_800C6F7C];
                *temp_v0_2 |= 1 << var_s0;
            }
            var_s2 += 0x38;
            var_s0 += 1;
            var_s1 += 0x38;
        } while (var_s0 < D_800C76DC);
    }
    var_s0_2 = 0;
    if (D_800C7700 == 0) {
        var_s2_2 = -1;
        var_v1 = &D_800C6F80;
        do {
            var_s0_2 += 1;
            var_s2_2 &= *var_v1;
            var_v1 += 4;
        } while (var_s0_2 < 0xF);
        var_s0_3 = 0;
        if (D_800C76DC > 0) {
            var_s1_2 = &D_800C6FDD;
            do {
                var_a1 = 1 << var_s0_3;
                if (var_s2_2 & var_a1) {
                    if (*var_s1_2 == 2) {
                        var_v0 = 0;
                        if (var_s0_3 >= 0x10) {
                            var_a1 = 0;
                            var_v0 = 1 << (var_s0_3 - 0x10);
                        }
                        func_8003F728(0, ((var_v0 & 0xFF) << 0x10) | var_a1);
                    }
                    *var_s1_2 = 0;
                }
                var_s0_3 += 1;
                var_s1_2 += 0x38;
            } while (var_s0_3 < D_800C76DC);
        }
        var_s0_2 = 0;
    }
    var_s1_3 = 0;
    D_800C7502 &= ~D_800C7500;
    D_800C7506 &= ~D_800C7504;
    do {
        if (D_800C6FDE[var_s1_3] != 0) {
            D_800C7508(var_s0_2);
        }
        if (D_800C6FEA[var_s1_3] != 0) {
            D_800C750C(var_s0_2);
        }
        var_s0_2 += 1;
        var_s1_3 += 0x38;
    } while (var_s0_2 < 0x18);
    var_s0_4 = 0;
    var_s1_4 = &D_800C7510;
    var_s7 = &D_800C7528 + 0xA;
    var_s6 = &D_800C7528 + 8;
    var_s5 = &D_800C7528 + 6;
    var_s4 = &D_800C7528 + 4;
    var_s3 = &D_800C7528 + 2;
    var_s2_3 = &D_800C7528;
    do {
        sp14 = 0;
        sp10 = 1 << var_s0_4;
        if (*var_s1_4 & 1) {
            sp14 = 3;
            sp18 = *var_s2_3;
            sp1A = *var_s3;
        }
        if (*var_s1_4 & 4) {
            sp14 |= 0x10;
            sp24 = *var_s4;
        }
        if (*var_s1_4 & 8) {
            sp14 |= 0x80;
            sp2C = *var_s5 * 8;
        }
        if (*var_s1_4 & 0x10) {
            sp14 |= 0x60000;
            sp4A = *var_s6;
            sp4C = *var_s7;
        }
        if (sp14 != 0) {
            SpuSetVoiceAttr((s32) &sp10);
        }
        *var_s1_4 = 0;
        var_s1_4 += 1;
        var_s7 += 0x10;
        var_s6 += 0x10;
        var_s5 += 0x10;
        var_s4 += 0x10;
        var_s3 += 0x10;
        var_s0_4 += 1;
        var_s2_3 += 0x10;
    } while (var_s0_4 < 0x18);
    SpuSetKey(0, ((u8) D_800C7504 << 0x10) | D_800C7500);
    SpuSetKey(1, ((u8) D_800C7506 << 0x10) | D_800C7502);
    func_8003F7A8(8, (D_800C76A8 << 0x10) | D_800C76AA);
    func_8003F728(8, (D_800C76AC << 0x10) | D_800C76AE);
    D_800C7500 = 0;
    D_800C7504 = 0;
    D_800C7502 = 0;
    D_800C7506 = 0;
    D_800C76AE = 0;
    D_800C76AC = 0;
}
