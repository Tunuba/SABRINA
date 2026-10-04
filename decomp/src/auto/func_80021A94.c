#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"


extern s32 func_8001E040();
extern s32 func_800211D4();

void func_80021A94(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 sp20;
    s16 sp24;
    s16 sp26;
    s16 sp28;
    s16 sp2A;
    s16 sp2C;
    s16 sp2E;
    s16 sp30;
    s32 sp34;
    s32 sp38;
    s16 sp3C;
    s16 temp_s0;

    func_800169A0(0);
    sp20 = arg0;
    sp24 = 0;
    sp26 = 1;
    sp28 = 0x140;
    sp2A = (s16) arg1;
    sp2C = 0;
    sp38 = 0;
    sp3C = 0x7F;
    sp2E = 0x140;
    sp30 = 0xF0;
    sp34 = arg3 - 4;
    temp_s0 = func_8005D50C((s32) &sp20, (s32) func_8001E040);
    func_800169A0((s32) func_800211D4);
    do {

    } while (func_80012D74(1) != 0);
}
