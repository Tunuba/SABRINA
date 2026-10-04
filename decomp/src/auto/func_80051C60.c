#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"



void func_80051C60(void) {
    s32 temp_s0;

    temp_s0 = func_800143E4();
    CloseEvent();
    CloseEvent();
    CloseEvent();
    CloseEvent();
    CloseEvent();
    CloseEvent();
    CloseEvent();
    CloseEvent();
    if (temp_s0 == 1) {
        func_800143F4();
    }
}
