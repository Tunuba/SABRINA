#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u8 D_800C65E0[];
extern s16 D_8007CBE6;


void func_8003DC48(void) {
    s32 sp18;
    s16 sp1C;
    s16 sp1E;
    s16 sp28;
    s16 sp2A;
    s32 sp30;
    s32 sp40;
    s32 sp44;
    s16 sp48;
    s16 sp4A;
    s16 sp54;
    s32 sp64;
    s32 sp68;
    s32 sp6C;
    s16 sp70;
    s16 sp72;
    s16 sp74;
    s16 sp76;
    s16 sp78;
    s32 var_a0;
    s32 var_v1;

    func_80041C48();
    SsSetTickMode(5);
    SsUtReverbOn();
    var_v1 = 0x14;
    var_a0 = 0x28;
loop_2:
    if (var_v1 != 0) {
        D_800C65E0[var_a0] = 0;
        var_v1 = (var_v1 - 1) & 0xFF;
        var_a0 -= 2;
        goto loop_2;
    }
    sp18 = 0x2C3;
    sp1C = 0x3FFF;
    sp1E = 0x3FFF;
    sp30 = 1;
    sp28 = 0x2FFF;
    sp2A = 0x2FFF;
    SpuSetCommonAttr((s32) &sp18);
    sp44 = 0xFF93;
    sp40 = 0xFFFFFF;
    sp48 = 0x3FFF;
    sp4A = 0x3FFF;
    sp54 = 0x800;
    sp64 = 1;
    sp68 = 1;
    sp6C = 3;
    sp70 = 0;
    sp72 = 0;
    sp74 = 0;
    sp76 = 0;
    sp78 = 0xF;
    SpuSetVoiceAttr((s32) &sp40);
    SsSetMVol(0x7F, 0x7F);
    D_8007CBE6 = 0;
}
