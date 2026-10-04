#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern u16 D_800D581A;

void func_8005C964(void) {
    s16 sp18;
    s16 sp1A;
    s16 sp1C;
    s16 sp1E;

    sp18 = 0;
    sp1A = 0;
    sp1C = func_8005D3A0((s32) D_800D581A);
    sp1E = 0x100;
    func_80012DDC((s32) &sp18, 0, 0, 0);
    sp1A = 0x100;
    func_80012DDC((s32) &sp18, 0, 0, 0);
}
