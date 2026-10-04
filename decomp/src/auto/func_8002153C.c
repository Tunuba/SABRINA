#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u8 D_8006C438[];
extern s32 D_8007CAA0;
extern s32 D_8007CAA4;
extern s32 D_8007CAA8;
extern s32 D_8007CAAC;
extern s32 D_8007CAB0;
extern s32 D_8007CAB4;
extern s32 D_8007CAB8;
extern s32 D_8007CABC;
extern s32 D_8007CAC0;
extern s32 D_8007CAC4;
extern s32 D_8007CAC8;
extern s32 D_8007CACC;
extern s32 D_8007CAD0;
extern s32 D_8007CAD4;
extern s32 D_8007CAD8;
extern s32 D_8007CADC;


void func_8002153C(void) {
    s32 temp_a0;
    s32 temp_a0_2;
    s32 temp_a0_3;
    s32 temp_a0_4;
    s32 temp_a0_5;
    s32 temp_a0_6;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 temp_v0_3;
    s32 temp_v0_4;
    s32 temp_v0_5;
    s32 temp_v0_6;
    s32 temp_v0_7;
    s32 temp_v0_8;
    u32 var_s0;
    u32 var_s0_2;
    u32 var_s0_3;
    u32 var_s0_4;
    u32 var_s0_5;
    u32 var_s0_6;
    u32 var_s0_7;

    temp_v0 = Reservar(0x27100, (s32) "Screen.c");
    D_8007CAA0 = temp_v0;
    D_8007CAC0 = temp_v0;
    temp_v0_2 = Reservar(0x190, (s32) "Screen.c");
    D_8007CAA4 = temp_v0_2;
    D_8007CAC4 = temp_v0_2;
    temp_v0_3 = Reservar(0x3E80, (s32) "Screen.c");
    D_8007CAA8 = temp_v0_3;
    D_8007CAC8 = temp_v0_3;
    temp_v0_4 = Reservar(0x2710, (s32) "Screen.c");
    D_8007CAAC = temp_v0_4;
    D_8007CACC = temp_v0_4;
    temp_v0_5 = Reservar(0xFA0, (s32) "Screen.c");
    D_8007CAB0 = temp_v0_5;
    D_8007CAD0 = temp_v0_5;
    temp_v0_6 = Reservar(0x1900, (s32) "Screen.c");
    D_8007CAB4 = temp_v0_6;
    D_8007CAD4 = temp_v0_6;
    temp_v0_7 = Reservar(0x7D0, (s32) "Screen.c");
    D_8007CAB8 = temp_v0_7;
    D_8007CAD8 = temp_v0_7;
    temp_v0_8 = Reservar(0x18, (s32) "Screen.c");
    D_8007CABC = temp_v0_8;
    D_8007CADC = temp_v0_8;
    var_s0 = 0;
loop_2:
    if (var_s0 < 0xFA0U) {
        temp_a0 = D_8007CAC0;
        D_8007CAC0 = temp_a0 + 0x28;
        func_8001412C(temp_a0);
        var_s0 = (var_s0 + 1) & 0xFFFF;
        goto loop_2;
    }
    var_s0_2 = 0;
loop_5:
    if (var_s0_2 < 0x14U) {
        temp_a0_2 = D_8007CAC4;
        D_8007CAC4 = temp_a0_2 + 0x14;
        func_8001410C(temp_a0_2);
        var_s0_2 = (var_s0_2 + 1) & 0xFFFF;
        goto loop_5;
    }
    var_s0_3 = 0;
loop_8:
    if (var_s0_3 < 0x190U) {
        temp_a0_3 = D_8007CAC8;
        D_8007CAC8 = temp_a0_3 + 0x28;
        func_8001414C(temp_a0_3);
        var_s0_3 = (var_s0_3 + 1) & 0xFFFF;
        goto loop_8;
    }
    var_s0_4 = 0;
loop_11:
    if (var_s0_4 < 0x1F4U) {
        temp_a0_4 = D_8007CACC;
        D_8007CACC = temp_a0_4 + 0x14;
        func_8001418C(temp_a0_4);
        var_s0_4 = (var_s0_4 + 1) & 0xFFFF;
        goto loop_11;
    }
    var_s0_5 = 0;
loop_14:
    if (var_s0_5 < 0x190U) {
        temp_a0_5 = D_8007CAD4;
        D_8007CAD4 = temp_a0_5 + 0x10;
        func_800141AC(temp_a0_5);
        var_s0_5 = (var_s0_5 + 1) & 0xFFFF;
        goto loop_14;
    }
    var_s0_6 = 0;
loop_17:
    if (var_s0_6 < 0x64U) {
        temp_a0_6 = D_8007CAD8;
        D_8007CAD8 = temp_a0_6 + 0x14;
        func_800141CC(temp_a0_6);
        var_s0_6 = (var_s0_6 + 1) & 0xFFFF;
        goto loop_17;
    }
    var_s0_7 = 0;
loop_20:
    if (var_s0_7 < 2U) {
        SetDrawMode(D_8007CADC, 1, 0, GetTPage(0, 1, 0, 0), /* extra? */ 0);
        D_8007CADC += 0xC;
        var_s0_7 = (var_s0_7 + 1) & 0xFFFF;
        goto loop_20;
    }
    func_800217D0();
}
